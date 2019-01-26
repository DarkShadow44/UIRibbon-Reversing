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

#define ASSERT_SUBCONTROL_GROUP(control, count) \
    ASSERT(control.count_subcontrols == 1); \
    ASSERT(control.subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP); \
    ASSERT(control.subcontrols[0].count_subcontrols == count);

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

    ASSERT(controls[1].count_subcontrols == 1);
    controls = controls[1].subcontrols;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP)
    ASSERT(controls[0].count_subcontrols == 3);
    controls = controls[0].subcontrols;

    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[0].id == 10003);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[1].id == 10004);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[2].id == 10006);
    ASSERT(controls[0].count_subcontrols == 1);
    ASSERT(controls[0].subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP)
    ASSERT(controls[0].subcontrols[0].count_subcontrols == 0);

    ASSERT(controls[1].count_subcontrols == 1);
    controls = controls[1].subcontrols;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP)
    ASSERT(controls[0].count_subcontrols == 4);
    controls = controls[0].subcontrols;

    for (i = 0; i < 4; i++)
    {
        ASSERT(controls[i].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(controls[i].id == 10005);
    }

    return 0;
}

int test_dropdowncolorpicker(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    /* FIXME: Missing id checks */
    #define ASSERT_COLORPICKER(control, _chipsize, _colortemplate, _columns, _has_autocolor_button, _has_nocolor_button, \
                               _recent_color_rows, _standard_color_rows, _theme_color_rows) \
        ASSERT(control.type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNCOLORPICKER); \
        ASSERT(control.control_info.dropdowncolorpicker.chipsize == _chipsize); \
        ASSERT(control.control_info.dropdowncolorpicker.colortemplate == _colortemplate); \
        ASSERT(control.control_info.dropdowncolorpicker.columns == _columns); \
        ASSERT(control.control_info.dropdowncolorpicker.has_autocolor_button == _has_autocolor_button); \
        ASSERT(control.control_info.dropdowncolorpicker.has_nocolor_button == _has_nocolor_button); \
        ASSERT(control.control_info.dropdowncolorpicker.recent_color_rows == _recent_color_rows); \
        ASSERT(control.control_info.dropdowncolorpicker.standard_color_rows == _standard_color_rows); \
        ASSERT(control.control_info.dropdowncolorpicker.theme_color_rows == _theme_color_rows); \

    CHECK(parse_from_testdata("dropdowncolorpicker", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 2);

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 16)
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT_COLORPICKER(controls[1], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[2], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[3], UIRIBBON_TRANSFORMED_CHIPSIZE_MEDIUM, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[4], UIRIBBON_TRANSFORMED_CHIPSIZE_LARGE, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[5], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[6], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_STANDARD, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[7], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_HIGHLIGHT, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[8], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 1, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[9], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 4, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[10], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 200, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[11], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[12], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, FALSE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[13], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[14], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 10, TRUE, FALSE, 1, 1, 6);
    ASSERT(controls[15].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 9);
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_COLORPICKER(controls[0], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[1], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 4, 1, 6);
    ASSERT_COLORPICKER(controls[2], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 200, 1, 6);
    ASSERT_COLORPICKER(controls[3], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[4], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 4, 6);
    ASSERT_COLORPICKER(controls[5], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 200, 6);
    ASSERT_COLORPICKER(controls[6], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 1);
    ASSERT_COLORPICKER(controls[7], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 4);
    ASSERT_COLORPICKER(controls[8], UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL, UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 200);

    #undef ASSERT_COLORPICKER

    return 0;
}

static int test_dropdowngallery(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;
    int i;

    #define ASSERT_GALLERY(control, _id, _elements_type, _text_position, _has_large_items, _item_height, _item_width, _menulayout, _gripper, _rows, _columns) \
        ASSERT(control.type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNGALLERY); \
        ASSERT(control.id == _id); \
        ASSERT(control.control_info.dropdowngallery.elements_type == _elements_type); \
        ASSERT(control.control_info.dropdowngallery.text_position == _text_position); \
        ASSERT(control.control_info.dropdowngallery.has_large_items == _has_large_items); \
        ASSERT(control.control_info.dropdowngallery.item_height == _item_height); \
        ASSERT(control.control_info.dropdowngallery.item_width == _item_width); \
        ASSERT(control.control_info.dropdowngallery.menulayout == _menulayout); \
        ASSERT(control.control_info.dropdowngallery.gripper == _gripper); \
        ASSERT(control.control_info.dropdowngallery.rows == _rows); \
        ASSERT(control.control_info.dropdowngallery.columns == _columns);

    CHECK(parse_from_testdata("dropdowngallery", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 3);

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11)
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 6)
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 10)
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10022, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10023);
    ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10024);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10025);

    ASSERT_GALLERY(controls[1], 10026, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10028);
        ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10029);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10028);
    }

    ASSERT_GALLERY(controls[2], 10032, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10033, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[4], 10035, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 4);
    ASSERT_GALLERY(controls[5], 10036, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 40, 40);
    ASSERT_GALLERY(controls[6], 10037, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, 40, 40);
    ASSERT_GALLERY(controls[7], 10038, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[8], 10039, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 1);
    ASSERT_GALLERY(controls[9], 10040, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 4, 1);

    #undef ASSERT_GALLERY

    return 0;
}

static int test_inribbongallery(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;
    int i;

    #define ASSERT_GALLERY(control, _id, _elements_type, _text_position, _has_large_items, _item_height, _item_width, _menulayout, _gripper, _rows, _columns, \
                           _max_columns, _max_rows, _max_columns_medium, _min_columns_medium, _min_columns_large) \
        ASSERT(control.type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_INRIBBONGALLERY); \
        ASSERT(control.id == _id); \
        ASSERT(control.control_info.inribbongallery.generic.elements_type == _elements_type); \
        ASSERT(control.control_info.inribbongallery.generic.text_position == _text_position); \
        ASSERT(control.control_info.inribbongallery.generic.has_large_items == _has_large_items); \
        ASSERT(control.control_info.inribbongallery.generic.item_height == _item_height); \
        ASSERT(control.control_info.inribbongallery.generic.item_width == _item_width); \
        ASSERT(control.control_info.inribbongallery.generic.menulayout == _menulayout); \
        ASSERT(control.control_info.inribbongallery.generic.gripper == _gripper); \
        ASSERT(control.control_info.inribbongallery.generic.rows == _rows); \
        ASSERT(control.control_info.inribbongallery.generic.columns == _columns); \
        ASSERT(control.control_info.inribbongallery.max_columns == _max_columns); \
        ASSERT(control.control_info.inribbongallery.max_rows == _max_rows); \
        ASSERT(control.control_info.inribbongallery.max_columns_medium == _max_columns_medium); \
        ASSERT(control.control_info.inribbongallery.min_columns_medium == _min_columns_medium); \
        ASSERT(control.control_info.inribbongallery.min_columns_large == _min_columns_large);

    CHECK(parse_from_testdata("inribbongallery", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 3);

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11)
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 12)
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);

    ASSERT_GALLERY(controls[6], 10022, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 44, 33, 20, 10, 30);
    ASSERT_GALLERY(controls[7], 10023, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 45, 34, 21, 11, 31);
    ASSERT_GALLERY(controls[8], 10028, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 9, 1, 9, 9, 9);
    ASSERT_GALLERY(controls[9], 10029, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 8, 1, 8, 8, 8);
    ASSERT_GALLERY(controls[10], 10030, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 7, 1, 7, 7, 7);
    ASSERT_GALLERY(controls[11], 10031, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 6, 1, 6, 6, 6);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 9)
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10034, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);
    ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10033);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);

    ASSERT_GALLERY(controls[1], 10035, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        ASSERT(controls[1].subcontrols[i].id == 10036 + i);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
        ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10033);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
    }

    ASSERT_GALLERY(controls[2], 10038, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10039, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10040, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 40, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10041, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, 40, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[6], 10042, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[7], 10043, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[8], 10044, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 4, 1, 1, 1, 1, 1, 1);

    #undef ASSERT_GALLERY

    return 0;
}

static int test_splitbuttongallery(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;
    int i;

    #define ASSERT_GALLERY(control, _id, _elements_type, _text_position, _has_large_items, _item_height, _item_width, _menulayout, _gripper, _rows, _columns) \
        ASSERT(control.type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTONGALLERY); \
        ASSERT(control.id == _id); \
        ASSERT(control.control_info.splitbuttongallery.elements_type == _elements_type); \
        ASSERT(control.control_info.splitbuttongallery.text_position == _text_position); \
        ASSERT(control.control_info.splitbuttongallery.has_large_items == _has_large_items); \
        ASSERT(control.control_info.splitbuttongallery.item_height == _item_height); \
        ASSERT(control.control_info.splitbuttongallery.item_width == _item_width); \
        ASSERT(control.control_info.splitbuttongallery.menulayout == _menulayout); \
        ASSERT(control.control_info.splitbuttongallery.gripper == _gripper); \
        ASSERT(control.control_info.splitbuttongallery.rows == _rows); \
        ASSERT(control.control_info.splitbuttongallery.columns == _columns);

    CHECK(parse_from_testdata("splitbuttongallery", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 3);

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11)
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 6)
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 9)
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10034, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);
    ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10033);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);

    ASSERT_GALLERY(controls[1], 10035, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
        ASSERT(subcontrols[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10033);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
    }

    ASSERT_GALLERY(controls[2], 10038, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10039, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 4);
    ASSERT_GALLERY(controls[4], 10040, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 40, 40);
    ASSERT_GALLERY(controls[5], 10041, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER, 40, 40);
    ASSERT_GALLERY(controls[6], 10042, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[7], 10043, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE, -1, 1);
    ASSERT_GALLERY(controls[8], 10044, UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL, 4, 1);

    #undef ASSERT_GALLERY

    return 0;
}

static int test_spinner(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    CHECK(parse_from_testdata("spinner", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 3);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPINNER);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON);
    return 0;
}

int main()
{
    /*write_test_data("checkbox");
    run_visual_test("dropdowncolorpicker");
    return 0;*/
    CHECK(test_simple());
    CHECK(test_sizeinfo());
    CHECK(test_commands());
    CHECK(test_scalingpolicy());
    CHECK(test_combobox());
    CHECK(test_checkbox());
    CHECK(test_dropdownbutton());
    CHECK(test_dropdowncolorpicker());
    CHECK(test_dropdowngallery());
    CHECK(test_inribbongallery());
    CHECK(test_splitbuttongallery());
    CHECK(test_spinner());

    return 0;
}
