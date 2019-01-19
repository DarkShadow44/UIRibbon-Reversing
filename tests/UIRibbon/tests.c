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

static int test_commands(void)
{
    uiribbon_main uiribbon;
    uiribbon_command *command;

    CHECK(parse_from_testdata("command_resources", &uiribbon));
    ASSERT(uiribbon.count_commands == 12);
    command = &uiribbon.commands[8];
    ASSERT(command->id == 10004);
    ASSERT(command->id_label_title == -1);
    ASSERT(command->id_label_description == -1);
    ASSERT(command->id_keytip == -1);
    ASSERT(command->id_toopltip_title == -1);
    ASSERT(command->id_tooltip_description == -1);
    ASSERT(command->count_images_small == 0);
    ASSERT(command->count_images_large == 0);
    ASSERT(command->count_images_large_high_contrast == 0);
    ASSERT(command->count_images_small_high_contrast == 0);
    command = &uiribbon.commands[9];
    ASSERT(command->id == 10003);
    ASSERT(command->id_label_title == 10005);
    ASSERT(command->id_label_description == 10004);
    ASSERT(command->id_keytip == 10003);
    ASSERT(command->id_toopltip_title == 10007);
    ASSERT(command->id_tooltip_description == 10006);
    ASSERT(command->count_images_small == 1);
    ASSERT(command->images_small[0].id_image == 20002);
    ASSERT(command->images_small[0].min_dpi == 100);
    ASSERT(command->count_images_large == 1);
    ASSERT(command->images_large[0].id_image == 20001);
    ASSERT(command->images_large[0].min_dpi == 96);
    ASSERT(command->count_images_large_high_contrast == 3);
    ASSERT(command->images_large_high_contrast[0].id_image == 20003);
    ASSERT(command->images_large_high_contrast[0].min_dpi == 96);
    ASSERT(command->images_large_high_contrast[1].id_image == 20004);
    ASSERT(command->images_large_high_contrast[1].min_dpi == 100);
    ASSERT(command->images_large_high_contrast[2].id_image == 20005);
    ASSERT(command->images_large_high_contrast[2].min_dpi == 110);
    ASSERT(command->count_images_small_high_contrast == 1);
    ASSERT(command->images_small_high_contrast[0].id_image == 20006);
    ASSERT(command->images_small_high_contrast[0].min_dpi == 96);

    return 0;
}

int test_scalingpolicy(void)
{
    uiribbon_main uiribbon;

    #define ASSERT_SCALING(scalingpolicy, id, type) \
        ASSERT(scalingpolicy.group_id == id); \
        ASSERT(scalingpolicy.scale_type == type); \

    CHECK(parse_from_testdata("scalingpolicy", &uiribbon));
    ASSERT(uiribbon.count_tabs == 4);
    ASSERT(uiribbon.tabs[0].count_groups == 4);
    ASSERT(uiribbon.tabs[1].count_groups == 6);
    ASSERT(uiribbon.tabs[2].count_groups == 4);
    ASSERT(uiribbon.tabs[3].count_groups == 1);

    ASSERT(uiribbon.tabs[0].count_scalepolicies == 3);
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[0], 10002, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[1], 10004, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[2], 10003, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);

    ASSERT(uiribbon.tabs[1].count_scalepolicies == 9);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[0], 10010, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[1], 10005, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[2], 10006, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[3], 10007, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[4], 10008, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[5], 10008, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[6], 10009, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[7], 10009, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[8], 10010, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);

    ASSERT(uiribbon.tabs[2].count_scalepolicies == 9);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[0], 10011, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[1], 10011, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[2], 10012, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[3], 10012, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[4], 10013, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[5], 10013, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[6], 10014, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[7], 10014, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[8], 10014, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);

    ASSERT(uiribbon.tabs[3].count_scalepolicies == 3);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[0], 10015, UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[1], 10015, UIRIBBON_TRANSFORMED_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[2], 10015, UIRIBBON_TRANSFORMED_SCALE_TO_POPUP);

    #undef ASSERT_SCALING

    return 0;
}

static int test_combobox(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    CHECK(parse_from_testdata("combobox", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 7);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[1].id == 10004);
    ASSERT(controls[1].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[1].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[1].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[2].id == 10005);
    ASSERT(controls[2].control_info.combobox.is_editable == FALSE);
    ASSERT(controls[2].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[2].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[3].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[3].id == 10006);
    ASSERT(controls[3].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[3].control_info.combobox.has_autocomplete == FALSE);
    ASSERT(controls[3].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[4].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[4].id == 10007);
    ASSERT(controls[4].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[4].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[4].control_info.combobox.has_vertical_resize == TRUE);
    ASSERT(controls[5].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[5].id == 10008);
    ASSERT(controls[5].control_info.combobox.is_editable == FALSE);
    ASSERT(controls[5].control_info.combobox.has_autocomplete == FALSE);
    ASSERT(controls[5].control_info.combobox.has_vertical_resize == TRUE);
    ASSERT(controls[6].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    return 0;
}

static int test_checkbox(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    CHECK(parse_from_testdata("checkbox", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 3);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_CHECKBOX);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    return 0;
}

static int test_dropdownbutton(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    int i;

    CHECK(parse_from_testdata("dropdownbutton", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 3);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[0].count_subcontrols == 0);
    ASSERT(controls[1].count_subcontrols == 3);
    controls = controls[1].subcontrols;

    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[0].id == 10003);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[1].id == 10004);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[2].id == 10006);
    ASSERT(controls[0].count_subcontrols == 0);
    ASSERT(controls[1].count_subcontrols == 4);
    controls = controls[1].subcontrols;

    for (i = 0; i < 4; i++)
    {
        ASSERT(controls[i].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(controls[i].id == 10005);
    }

    return 0;
}

int main()
{
    /*write_test_data("scalingpolicy");
    run_visual_test("scalingpolicy");
    return 0;*/
    CHECK(test_simple());
    CHECK(test_sizeinfo());
    CHECK(test_commands());
    CHECK(test_scalingpolicy());
    CHECK(test_combobox());
    CHECK(test_checkbox());
    CHECK(test_dropdownbutton());

    return 0;
}
