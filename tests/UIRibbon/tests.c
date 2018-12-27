#include "uiribbon_transformer.h"

void _ok(int expr, const char *message, const char *file, int line)
{
    if (!expr)
        printf("%s:%d - %s\n", file, line, message);
}

#define ok(expr, message) \
    _ok(expr, message, __FILE__, __LINE__)

#define ASSERT(expr) \
    CHECK2(!(expr), "Assert failed")

int _parse_from_testdata(char *name, uiribbon_main *ret, const char *file, int line)
{
    stream s;
    int error;
    type_uiribbon uiribbon;
    const test_data *test = get_test_data(name);

    _ok(test != NULL, "Failed to get test data", file, line);
    if (!test)
        return 1;

    s.start = s.pos = 0;
    s.max = test->bml_len;
    s.data = test->bml_data;

    error = read_type_uiribbon(&s, &s, &uiribbon);
    _ok(error == 0, "Failed to parse file", file, line);

    transform_uiribbon(&uiribbon, ret);
    return error;
}

#define parse_from_testdata(name, ret) \
    _parse_from_testdata(name, ret, __FILE__, __LINE__)

static int test_simple(void)
{
    uiribbon_main uiribbon;
    int i, j, k;
    int id;

    CHECK(parse_from_testdata("simple_tabs", &uiribbon));
    ASSERT(uiribbon.count_tabs == 2);
    id = 10001;
    for (i = 0; i < 2; i++)
    {
        uiribbon_tab *tab = &uiribbon.tabs[i];
        ASSERT(tab->id == id++);
        ASSERT(tab->count_groups == 2);
        for (j = 0; j < 2; j++)
        {
            uiribbon_group *group = &tab->groups[j];
            ASSERT(group->id == id++);
            ASSERT(group->count_controls == 2);

            ASSERT(group->controls[0].id == id++);
            ASSERT(group->controls[1].id == id++);
            ASSERT(group->controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
            ASSERT(group->controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        }
    }

    CHECK(parse_from_testdata("simple_contexttabs", &uiribbon));
    ASSERT(uiribbon.count_contexttabgroups == 2);
    id = 10001;
    for (k = 0; k < 2; k++)
    {
        uiribbon_tabgroup *tab_group = &uiribbon.contexttabgroups[k];
        ASSERT(tab_group->id == id++);
        ASSERT(tab_group->count_tabs == 2);
        for (i = 0; i < 2; i++)
        {
            uiribbon_tab *tab = &tab_group->tabs[i];
            ASSERT(tab->id == id++);
            ASSERT(tab->count_groups == 2);
            for (j = 0; j < 2; j++)
            {
                uiribbon_group *group = &tab->groups[j];
                ASSERT(group->id == id++);
                ASSERT(group->count_controls == 2);

                ASSERT(group->controls[0].id == id++);
                ASSERT(group->controls[1].id == id++);
                ASSERT(group->controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
                ASSERT(group->controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
            }
        }
    }

    return 0;
}

static int test_sizeinfo(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *control;
    uiribbon_group *group;
    uiribbon_sizedefinition_group_order *orders;

    /* Size */

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__small_small_small", &uiribbon));

    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 0);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_small_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_large", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 1);

    /* LabelVisible */

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelhidden_labelhidden_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 0);
    ASSERT(control->size_definitions->medium.labelvisible == 0);
    ASSERT(control->size_definitions->small.labelvisible == 0);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelhidden_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 0);
    ASSERT(control->size_definitions->small.labelvisible == 0);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelvisible_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 1);
    ASSERT(control->size_definitions->small.labelvisible == 0);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelvisible_labelvisible", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 1);
    ASSERT(control->size_definitions->small.labelvisible == 1);

    /* ImageVisible */
    CHECK(parse_from_testdata("sizeinfo_image_largetosmall__imagehidden_imagehidden_imagehidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.imagevisible == 0);
    ASSERT(control->size_definitions->medium.imagevisible == 0);
    ASSERT(control->size_definitions->small.imagevisible == 0);

    CHECK(parse_from_testdata("sizeinfo_image_largetosmall__imagevisible_imagevisible_imagevisible", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.imagevisible == 1);
    ASSERT(control->size_definitions->medium.imagevisible == 1);
    ASSERT(control->size_definitions->small.imagevisible == 1);

    /* Order */

    CHECK(parse_from_testdata("sizedefinition_order", &uiribbon));
    group = &uiribbon.tabs[0].groups[0];
    ASSERT(group->sizedefinition_orders != NULL);

    ASSERT(group->sizedefinition_orders->large.count_orders == 13);
    orders = group->sizedefinition_orders->large.orders;
    ASSERT(orders[0].is_special && orders[0].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_OPEN_GROUP);
    ASSERT(!orders[1].is_special && orders[1].command_id == 10003);
    ASSERT(orders[2].is_special && orders[2].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_CLOSE_GROUP);
    ASSERT(orders[3].is_special && orders[3].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(orders[4].is_special && orders[4].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_OPEN_GROUP);
    ASSERT(!orders[5].is_special && orders[5].command_id == 10002);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10001);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_CLOSE_GROUP);
    ASSERT(!orders[8].is_special && orders[8].special_command == 10004);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10005);
    ASSERT(!orders[11].is_special && orders[11].command_id == 10006);
    ASSERT(orders[12].is_special && orders[12].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);

    ASSERT(group->sizedefinition_orders->medium.count_orders == 15);
    orders = group->sizedefinition_orders->medium.orders;
    ASSERT(!orders[0].is_special && orders[0].command_id == 10001);
    ASSERT(!orders[1].is_special && orders[1].command_id == 10002);
    ASSERT(orders[2].is_special && orders[2].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[3].is_special && orders[3].command_id == 10005);
    ASSERT(orders[4].is_special && orders[4].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[5].is_special && orders[5].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_INVISIBLE_SEPARATOR);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10004);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[8].is_special && orders[8].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10003);
    ASSERT(orders[11].is_special && orders[11].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[12].is_special && orders[12].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_INVISIBLE_SEPARATOR);
    ASSERT(!orders[13].is_special && orders[13].command_id == 10006);
    ASSERT(orders[14].is_special && orders[14].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);

    ASSERT(group->sizedefinition_orders->small.count_orders == 12);
    orders = group->sizedefinition_orders->small.orders;
    ASSERT(!orders[0].is_special && orders[0].command_id == 10001);
    ASSERT(orders[1].is_special && orders[1].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[2].is_special && orders[2].command_id == 10006);
    ASSERT(orders[3].is_special && orders[3].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[4].is_special && orders[4].command_id == 10003);
    ASSERT(orders[5].is_special && orders[5].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10004);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[8].is_special && orders[8].command_id == 10005);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10002);
    ASSERT(orders[11].is_special && orders[11].special_command == UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK);

    return 0;
}

int main()
{
    /*write_test_data("sizeinfo_size_largetosmall__small_small_small");
    run_visual_test("sizeinfo_size_largetosmall__small_small_small");
    return 0;*/
    CHECK(test_simple());
    CHECK(test_sizeinfo());

    return 0;
}
