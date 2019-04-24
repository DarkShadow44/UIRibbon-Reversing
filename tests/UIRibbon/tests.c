#include "uiribbon_transformer.h"
#include "parser_test.h"

/* FIXME: No macros, use methods */
/* FIXME: Test all defaults */

static void _ok(int expr, const char *message, const char *file, int line)
{
    if (!expr)
        printf("%s:%d - %s\n", file, line, message);
}

#define ok(expr, message) \
    _ok(expr, message, __FILE__, __LINE__)

#define ASSERT(expr) \
    do { \
        CHECK2(!(expr), "Assert failed") \
    } while (0)

#define ASSERT_INT(actual, expected) \
    do { \
         if (expected != actual) { \
                printf("%s:%d - Expected %d, got %d.\n", __FILE__, __LINE__, expected, actual); return 1; \
         } \
     } while (0)

#define ASSERT_STR(actual, expected) \
    do { \
         if (strcmp(expected, actual) != 0) { \
                printf("%s:%d - Expected %s, got %s.\n", __FILE__, __LINE__, expected, actual); return 1; \
         } \
     } while (0)

#define ASSERT_SUBCONTROL_GROUP(control, count) \
    ASSERT(control.count_subcontrols == 1); \
    ASSERT(control.subcontrols[0].type == UIRIBBON_CONTROL_TYPE_GROUP); \
    ASSERT(control.subcontrols[0].count_subcontrols == count);

static int _parse_from_testdata(char *name, uiribbon_main *ret, const char *file, int line)
{
    stream *s;
    int error;
    type_uiribbon uiribbon;
    const test_data *test = get_test_data(name);

    _ok(test != NULL, "Failed to get test data", file, line);
    if (!test)
        return 1;

    s = create_read_stream(test->bml_data, test->bml_len);

    error = stream_read_uiribbon(s, &uiribbon);
    destroy_read_stream(s);
    _ok(error == 0, "Failed to parse file", file, line);
    if (error)
        return error;

    uiribbon_transform(&uiribbon, ret);
    stream_free_uiribbon(&uiribbon);
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
            ASSERT(group->controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
            ASSERT(group->controls[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        }
    }
    uiribbon_free(&uiribbon);

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
                ASSERT(group->controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
                ASSERT(group->controls[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);
            }
        }
    }

    uiribbon_free(&uiribbon);
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
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 0);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_small_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_large", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 1);
    uiribbon_free(&uiribbon);

    /* LabelVisible */

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelhidden_labelhidden_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 0);
    ASSERT(control->size_definitions->medium.labelvisible == 0);
    ASSERT(control->size_definitions->small.labelvisible == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelhidden_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 0);
    ASSERT(control->size_definitions->small.labelvisible == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelvisible_labelhidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 1);
    ASSERT(control->size_definitions->small.labelvisible == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_label_largetosmall__labelvisible_labelvisible_labelvisible", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.labelvisible == 1);
    ASSERT(control->size_definitions->medium.labelvisible == 1);
    ASSERT(control->size_definitions->small.labelvisible == 1);
    uiribbon_free(&uiribbon);

    /* ImageVisible */
    CHECK(parse_from_testdata("sizeinfo_image_largetosmall__imagehidden_imagehidden_imagehidden", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.imagevisible == 0);
    ASSERT(control->size_definitions->medium.imagevisible == 0);
    ASSERT(control->size_definitions->small.imagevisible == 0);
    uiribbon_free(&uiribbon);

    CHECK(parse_from_testdata("sizeinfo_image_largetosmall__imagevisible_imagevisible_imagevisible", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.imagevisible == 1);
    ASSERT(control->size_definitions->medium.imagevisible == 1);
    ASSERT(control->size_definitions->small.imagevisible == 1);
    uiribbon_free(&uiribbon);

    /* Order */

    CHECK(parse_from_testdata("sizedefinition_order", &uiribbon));
    group = &uiribbon.tabs[0].groups[0];
    ASSERT(group->sizedefinition_orders != NULL);

    ASSERT(group->sizedefinition_orders->large.count_orders == 13);
    orders = group->sizedefinition_orders->large.orders;
    ASSERT(orders[0].is_special && orders[0].special_command == UIRIBBON_SIZEINFO_ORDER_OPEN_GROUP);
    ASSERT(!orders[1].is_special && orders[1].command_id == 10003);
    ASSERT(orders[2].is_special && orders[2].special_command == UIRIBBON_SIZEINFO_ORDER_CLOSE_GROUP);
    ASSERT(orders[3].is_special && orders[3].special_command == UIRIBBON_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(orders[4].is_special && orders[4].special_command == UIRIBBON_SIZEINFO_ORDER_OPEN_GROUP);
    ASSERT(!orders[5].is_special && orders[5].command_id == 10002);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10001);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_SIZEINFO_ORDER_CLOSE_GROUP);
    ASSERT(!orders[8].is_special && orders[8].special_command == 10004);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10005);
    ASSERT(!orders[11].is_special && orders[11].command_id == 10006);
    ASSERT(orders[12].is_special && orders[12].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);

    ASSERT(group->sizedefinition_orders->medium.count_orders == 15);
    orders = group->sizedefinition_orders->medium.orders;
    ASSERT(!orders[0].is_special && orders[0].command_id == 10001);
    ASSERT(!orders[1].is_special && orders[1].command_id == 10002);
    ASSERT(orders[2].is_special && orders[2].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[3].is_special && orders[3].command_id == 10005);
    ASSERT(orders[4].is_special && orders[4].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[5].is_special && orders[5].special_command == UIRIBBON_SIZEINFO_ORDER_INVISIBLE_SEPARATOR);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10004);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[8].is_special && orders[8].special_command == UIRIBBON_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_SIZEINFO_ORDER_VISIBLE_SEPARATOR);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10003);
    ASSERT(orders[11].is_special && orders[11].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(orders[12].is_special && orders[12].special_command == UIRIBBON_SIZEINFO_ORDER_INVISIBLE_SEPARATOR);
    ASSERT(!orders[13].is_special && orders[13].command_id == 10006);
    ASSERT(orders[14].is_special && orders[14].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);

    ASSERT(group->sizedefinition_orders->small.count_orders == 12);
    orders = group->sizedefinition_orders->small.orders;
    ASSERT(!orders[0].is_special && orders[0].command_id == 10001);
    ASSERT(orders[1].is_special && orders[1].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[2].is_special && orders[2].command_id == 10006);
    ASSERT(orders[3].is_special && orders[3].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[4].is_special && orders[4].command_id == 10003);
    ASSERT(orders[5].is_special && orders[5].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[6].is_special && orders[6].command_id == 10004);
    ASSERT(orders[7].is_special && orders[7].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[8].is_special && orders[8].command_id == 10005);
    ASSERT(orders[9].is_special && orders[9].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);
    ASSERT(!orders[10].is_special && orders[10].command_id == 10002);
    ASSERT(orders[11].is_special && orders[11].special_command == UIRIBBON_SIZEINFO_ORDER_BREAK);

    uiribbon_free(&uiribbon);
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

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_scalingpolicy(void)
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
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[0], 10002, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[1], 10004, UIRIBBON_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[0].scalepolicies[2], 10003, UIRIBBON_SCALE_TO_SMALL);

    ASSERT(uiribbon.tabs[1].count_scalepolicies == 9);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[0], 10010, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[1], 10005, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[2], 10006, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[3], 10007, UIRIBBON_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[4], 10008, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[5], 10008, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[6], 10009, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[7], 10009, UIRIBBON_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[1].scalepolicies[8], 10010, UIRIBBON_SCALE_TO_POPUP);

    ASSERT(uiribbon.tabs[2].count_scalepolicies == 9);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[0], 10011, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[1], 10011, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[2], 10012, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[3], 10012, UIRIBBON_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[4], 10013, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[5], 10013, UIRIBBON_SCALE_TO_POPUP);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[6], 10014, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[7], 10014, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[2].scalepolicies[8], 10014, UIRIBBON_SCALE_TO_POPUP);

    ASSERT(uiribbon.tabs[3].count_scalepolicies == 3);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[0], 10015, UIRIBBON_SCALE_TO_MEDIUM);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[1], 10015, UIRIBBON_SCALE_TO_SMALL);
    ASSERT_SCALING(uiribbon.tabs[3].scalepolicies[2], 10015, UIRIBBON_SCALE_TO_POPUP);

    #undef ASSERT_SCALING

    uiribbon_free(&uiribbon);
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
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[1].id == 10004);
    ASSERT(controls[1].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[1].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[1].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[2].id == 10005);
    ASSERT(controls[2].control_info.combobox.is_editable == FALSE);
    ASSERT(controls[2].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[2].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[3].type == UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[3].id == 10006);
    ASSERT(controls[3].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[3].control_info.combobox.has_autocomplete == FALSE);
    ASSERT(controls[3].control_info.combobox.has_vertical_resize == FALSE);
    ASSERT(controls[4].type == UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[4].id == 10007);
    ASSERT(controls[4].control_info.combobox.is_editable == TRUE);
    ASSERT(controls[4].control_info.combobox.has_autocomplete == TRUE);
    ASSERT(controls[4].control_info.combobox.has_vertical_resize == TRUE);
    ASSERT(controls[5].type == UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT(controls[5].id == 10008);
    ASSERT(controls[5].control_info.combobox.is_editable == FALSE);
    ASSERT(controls[5].control_info.combobox.has_autocomplete == FALSE);
    ASSERT(controls[5].control_info.combobox.has_vertical_resize == TRUE);
    ASSERT(controls[6].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_checkbox_and_togglebutton(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    CHECK(parse_from_testdata("checkbox_and_togglebutton", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 4);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_CHECKBOX);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
    ASSERT(controls[2].id == 10003);
    ASSERT(controls[3].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    uiribbon_free(&uiribbon);
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
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[0].count_subcontrols == 0);

    ASSERT(controls[1].count_subcontrols == 1);
    controls = controls[1].subcontrols;
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(controls[0].count_subcontrols == 3);
    controls = controls[0].subcontrols;

    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[0].id == 10003);
    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON);
    ASSERT(controls[1].id == 10004);
    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[2].id == 10006);
    ASSERT(controls[0].count_subcontrols == 1);
    ASSERT(controls[0].subcontrols[0].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(controls[0].subcontrols[0].count_subcontrols == 0);

    ASSERT(controls[1].count_subcontrols == 1);
    controls = controls[1].subcontrols;
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(controls[0].count_subcontrols == 4);
    controls = controls[0].subcontrols;

    for (i = 0; i < 4; i++)
    {
        ASSERT(controls[i].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(controls[i].id == 10005);
    }

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_dropdowncolorpicker(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;

    /* FIXME: Missing id checks */
    #define ASSERT_COLORPICKER(control, _chipsize, _colortemplate, _columns, _has_autocolor_button, _has_nocolor_button, \
                               _recent_color_rows, _standard_color_rows, _theme_color_rows) \
        ASSERT(control.type == UIRIBBON_CONTROL_TYPE_DROPDOWNCOLORPICKER); \
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

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 16);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT_COLORPICKER(controls[1], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[2], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[3], UIRIBBON_CHIPSIZE_MEDIUM, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[4], UIRIBBON_CHIPSIZE_LARGE, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[5], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[6], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_STANDARD, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[7], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_HIGHLIGHT, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[8], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 1, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[9], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 4, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[10], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 200, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[11], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[12], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, FALSE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[13], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[14], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 10, TRUE, FALSE, 1, 1, 6);
    ASSERT(controls[15].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 9);
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_COLORPICKER(controls[0], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[1], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 4, 1, 6);
    ASSERT_COLORPICKER(controls[2], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 200, 1, 6);
    ASSERT_COLORPICKER(controls[3], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 6);
    ASSERT_COLORPICKER(controls[4], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 4, 6);
    ASSERT_COLORPICKER(controls[5], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 200, 6);
    ASSERT_COLORPICKER(controls[6], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 1);
    ASSERT_COLORPICKER(controls[7], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 4);
    ASSERT_COLORPICKER(controls[8], UIRIBBON_CHIPSIZE_SMALL, UIRIBBON_COLORTEMPLATE_THEME, 2, TRUE, TRUE, 1, 1, 200);

    #undef ASSERT_COLORPICKER

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_dropdowngallery(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;
    int i;

    #define ASSERT_GALLERY(control, _id, _elements_type, _text_position, _has_large_items, _item_height, _item_width, _menulayout, _gripper, _rows, _columns) \
        ASSERT(control.type == UIRIBBON_CONTROL_TYPE_DROPDOWNGALLERY); \
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

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 6);
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 10);
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10022, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10023);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10024);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10025);

    ASSERT_GALLERY(controls[1], 10026, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10028);
        ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10029);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10028);
    }

    ASSERT_GALLERY(controls[2], 10032, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10033, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[4], 10035, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 4);
    ASSERT_GALLERY(controls[5], 10036, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 40, 40);
    ASSERT_GALLERY(controls[6], 10037, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, 40, 40);
    ASSERT_GALLERY(controls[7], 10038, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[8], 10039, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 1);
    ASSERT_GALLERY(controls[9], 10040, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 4, 1);

    #undef ASSERT_GALLERY

    uiribbon_free(&uiribbon);
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
        ASSERT(control.type == UIRIBBON_CONTROL_TYPE_INRIBBONGALLERY); \
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

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 12);
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);

    ASSERT_GALLERY(controls[6], 10022, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 44, 33, 20, 10, 30);
    ASSERT_GALLERY(controls[7], 10023, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 45, 34, 21, 11, 31);
    ASSERT_GALLERY(controls[8], 10028, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 9, 1, 9, 9, 9);
    ASSERT_GALLERY(controls[9], 10029, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 8, 1, 8, 8, 8);
    ASSERT_GALLERY(controls[10], 10030, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 7, 1, 7, 7, 7);
    ASSERT_GALLERY(controls[11], 10031, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 6, 1, 6, 6, 6);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 9);
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10034, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10033);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);

    ASSERT_GALLERY(controls[1], 10035, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2, 1, 1, 1, 1, 1);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        ASSERT(controls[1].subcontrols[i].id == 10036 + i);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
        ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10033);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
    }

    ASSERT_GALLERY(controls[2], 10038, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[3], 10039, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[4], 10040, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 40, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[5], 10041, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_SPECIAL, UIRIBBON_GALLERY_GRIPPER_CORNER, 40, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[6], 10042, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[7], 10043, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 1, 1, 1, 1, 1, 1);
    ASSERT_GALLERY(controls[8], 10044, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 4, 1, 1, 1, 1, 1, 1);

    #undef ASSERT_GALLERY

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_splitbuttongallery(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;
    int i;

    #define ASSERT_GALLERY(control, _id, _elements_type, _text_position, _has_large_items, _item_height, _item_width, _menulayout, _gripper, _rows, _columns) \
        ASSERT(control.type == UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY); \
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

    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 11);
    controls = uiribbon.tabs[0].groups[0].controls;
    ASSERT_GALLERY(controls[0], 10005, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10006, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10007, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10008, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10009, UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   FALSE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10010, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[6], 10011, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 32, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[7], 10012, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, 100, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[8], 10013, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[9], 10014, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 32, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[10], 10015, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, 100, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[1].count_controls == 6);
    controls = uiribbon.tabs[0].groups[1].controls;
    ASSERT_GALLERY(controls[0], 10016, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[1], 10017, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_RIGHT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[2], 10018, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10019, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_TOP,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[4], 10020, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_HIDE,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[5], 10021, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);

    ASSERT(uiribbon.tabs[0].groups[2].count_controls == 9);
    controls = uiribbon.tabs[0].groups[2].controls;

    ASSERT_GALLERY(controls[0], 10034, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[1].id == 10033);
    ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
    subcontrols = subcontrols[1].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10032);

    ASSERT_GALLERY(controls[1], 10035, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT(controls[1].count_subcontrols == 2);
    for (i = 0; i < 2; i++)
    {
        ASSERT(controls[1].subcontrols[i].type == UIRIBBON_CONTROL_TYPE_GROUP);
        ASSERT(controls[1].subcontrols[i].count_subcontrols == 2);
        subcontrols = controls[1].subcontrols[i].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
        ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
        ASSERT(subcontrols[1].id == 10033);
        ASSERT_SUBCONTROL_GROUP(subcontrols[1], 1);
        subcontrols = subcontrols[1].subcontrols[0].subcontrols;
        ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT(subcontrols[0].id == 10032);
    }

    ASSERT_GALLERY(controls[2], 10038, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, -1, 2);
    ASSERT_GALLERY(controls[3], 10039, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 4);
    ASSERT_GALLERY(controls[4], 10040, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 40, 40);
    ASSERT_GALLERY(controls[5], 10041, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_FLOW, UIRIBBON_GALLERY_GRIPPER_CORNER, 40, 40);
    ASSERT_GALLERY(controls[6], 10042, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, -1, 1);
    ASSERT_GALLERY(controls[7], 10043, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_NONE, -1, 1);
    ASSERT_GALLERY(controls[8], 10044, UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS, UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
                   TRUE, -1, -1, UIRIBBON_GALLERY_MENULAYOUT_VERTICAL, UIRIBBON_GALLERY_GRIPPER_VERTICAL, 4, 1);

    #undef ASSERT_GALLERY

    uiribbon_free(&uiribbon);
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
    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_SPINNER);
    ASSERT(controls[1].id == 10002);
    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_splitbutton(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *controls;
    uiribbon_control *subcontrols;

    CHECK(parse_from_testdata("splitbutton", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 5);
    controls = uiribbon.tabs[0].groups[0].controls;

    ASSERT(controls[0].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(controls[0].id == 10003);
    ASSERT_SUBCONTROL_GROUP(controls[0], 2);
    subcontrols = controls[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[1].id == 10006);
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(subcontrols[0].id == 10004);
    ASSERT_SUBCONTROL_GROUP(subcontrols[0], 1);
    subcontrols = subcontrols[0].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10005);
    ASSERT(controls[0].control_info.splitbutton.buttonitem->id == 10006);
    ASSERT(controls[0].control_info.splitbutton.buttonitem->type == UIRIBBON_CONTROL_TYPE_BUTTON);

    ASSERT(controls[1].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(controls[1].id == 10007);
    ASSERT(controls[1].count_subcontrols == 2);
    subcontrols = controls[1].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(subcontrols[0].count_subcontrols == 0);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(subcontrols[1].count_subcontrols == 2);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_GROUP);
    ASSERT(subcontrols[1].count_subcontrols == 2);
    ASSERT(subcontrols[1].subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[1].subcontrols[0].id == 10009);
    ASSERT(subcontrols[1].subcontrols[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[1].subcontrols[1].id == 10010);
    ASSERT(controls[1].control_info.splitbutton.buttonitem->id == 10009);
    ASSERT(controls[1].control_info.splitbutton.buttonitem->type == UIRIBBON_CONTROL_TYPE_BUTTON);

    ASSERT(controls[2].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(controls[2].id == 10012);
    ASSERT_SUBCONTROL_GROUP(controls[2], 1);
    subcontrols = controls[2].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10006);
    ASSERT(controls[2].control_info.splitbutton.buttonitem->id == 10013);
    ASSERT(controls[2].control_info.splitbutton.buttonitem->type == UIRIBBON_CONTROL_TYPE_BUTTON);

    ASSERT(controls[3].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(controls[3].id == 10014);
    ASSERT_SUBCONTROL_GROUP(controls[3], 1);
    subcontrols = controls[3].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[0].id == 10006);
    ASSERT(controls[3].control_info.splitbutton.buttonitem->id == 10015);
    ASSERT(controls[3].control_info.splitbutton.buttonitem->type == UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);

    ASSERT(controls[4].type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON);
    ASSERT(controls[4].id == 10016);
    ASSERT_SUBCONTROL_GROUP(controls[4], 2);
    subcontrols = controls[4].subcontrols[0].subcontrols;
    ASSERT(subcontrols[0].type == UIRIBBON_CONTROL_TYPE_CHECKBOX);
    ASSERT(subcontrols[0].id == 10017);
    ASSERT(subcontrols[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);
    ASSERT(subcontrols[1].id == 10006);
    ASSERT(controls[4].control_info.splitbutton.buttonitem->id == 10017);
    ASSERT(controls[4].control_info.splitbutton.buttonitem->type == UIRIBBON_CONTROL_TYPE_CHECKBOX);

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_contextpopups(void)
{
    int i;
    uiribbon_main uiribbon;

    #define ASSERT_MENUGROUP(menugroup, _id, _item_class) \
        ASSERT(menugroup.id == _id); \
        ASSERT(menugroup.item_class == _item_class); \
        ASSERT(menugroup.count_controls == 2); \
        ASSERT(menugroup.controls[0].id == 10004); \
        ASSERT(menugroup.controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON); \
        ASSERT(menugroup.controls[1].id == 10005); \
        ASSERT(menugroup.controls[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    CHECK(parse_from_testdata("contextpopups", &uiribbon));

    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].id == 10001);
    ASSERT(uiribbon.tabs[0].count_groups == 2);
    for (i = 0; i < 2; i++)
    {
        uiribbon_group *group = &uiribbon.tabs[0].groups[i];
        ASSERT(group->id == 10002 + i);
        ASSERT(group->count_controls == 2);

        ASSERT(group->controls[0].id == 10004);
        ASSERT(group->controls[1].id == 10005);
    }

    ASSERT(uiribbon.count_contextmaps == 4);
    ASSERT(uiribbon.contextmaps[0].id == 10006);
    ASSERT(uiribbon.contextmaps[0].minitoolbar.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[0].minitoolbar.menugroups[0], 10010, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[0].minitoolbar.menugroups[1], 10011, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT(uiribbon.contextmaps[0].contextpopup.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[0].contextpopup.menugroups[0], 10012, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[0].contextpopup.menugroups[1], 10013, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);

    ASSERT(uiribbon.contextmaps[1].id == 10007);
    ASSERT(uiribbon.contextmaps[1].minitoolbar.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[1].minitoolbar.menugroups[0], 10008, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[1].minitoolbar.menugroups[1], 10009, UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS);
    ASSERT(uiribbon.contextmaps[1].contextpopup.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[1].contextpopup.menugroups[0], 10014, UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[1].contextpopup.menugroups[1], 10015, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);


    ASSERT(uiribbon.contextmaps[2].id == 10016);
    ASSERT(uiribbon.contextmaps[2].minitoolbar.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[2].minitoolbar.menugroups[0], 10010, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[2].minitoolbar.menugroups[1], 10011, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);
    ASSERT(uiribbon.contextmaps[2].contextpopup.count_menugroups == 0);

    ASSERT(uiribbon.contextmaps[3].id == 10017);
    ASSERT(uiribbon.contextmaps[3].minitoolbar.count_menugroups == 0);
    ASSERT(uiribbon.contextmaps[3].contextpopup.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.contextmaps[3].contextpopup.menugroups[0], 10014, UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS);
    ASSERT_MENUGROUP(uiribbon.contextmaps[3].contextpopup.menugroups[1], 10015, UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS);

    #undef ASSERT_MENUGROUP

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_applicationmenu_single(char *name, int recent_count, bool enable_pinning)
{
    int i;
    uiribbon_main uiribbon;

    CHECK(parse_from_testdata(name, &uiribbon));

    #define ASSERT_MENUGROUP(menugroup, _id, _item_class) \
        ASSERT(menugroup.id == _id); \
        ASSERT(menugroup.item_class == _item_class); \
        ASSERT(menugroup.count_controls == 2); \
        ASSERT(menugroup.controls[0].id == 10004); \
        ASSERT(menugroup.controls[0].type == UIRIBBON_CONTROL_TYPE_BUTTON); \
        ASSERT(menugroup.controls[1].id == 10005); \
        ASSERT(menugroup.controls[1].type == UIRIBBON_CONTROL_TYPE_BUTTON);

    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].id == 10001);
    ASSERT(uiribbon.tabs[0].count_groups == 2);
    for (i = 0; i < 2; i++)
    {
        uiribbon_group *group = &uiribbon.tabs[0].groups[i];
        ASSERT(group->id == 10002 + i);
        ASSERT(group->count_controls == 2);

        ASSERT(group->controls[0].id == 10004);
        ASSERT(group->controls[1].id == 10005);
    }

    ASSERT(uiribbon.applicationmenu.id == 10006);
    ASSERT(uiribbon.applicationmenu.recent.id == 10008);
    ASSERT(uiribbon.applicationmenu.recent.count == recent_count);
    ASSERT(uiribbon.applicationmenu.recent.enable_pinning == enable_pinning);
    ASSERT(uiribbon.applicationmenu.menugroups.count_menugroups == 2);
    ASSERT_MENUGROUP(uiribbon.applicationmenu.menugroups.menugroups[0], 10009, UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS);
    ASSERT_MENUGROUP(uiribbon.applicationmenu.menugroups.menugroups[1], 10010, UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS);

    #undef ASSERT_MENUGROUP

    uiribbon_free(&uiribbon);
    return 0;
}

static int test_applicationmenu(void)
{
    uiribbon_main uiribbon;

    CHECK(test_applicationmenu_single("applicationmenu1", 14, TRUE ));
    CHECK(test_applicationmenu_single("applicationmenu2", 15, FALSE ));
    CHECK(test_applicationmenu_single("applicationmenu3", 10, TRUE ));

    CHECK(parse_from_testdata("simple_tabs", &uiribbon));
    ASSERT(uiribbon.applicationmenu.id == 61000);
    ASSERT(uiribbon.applicationmenu.recent.count == 10);
    ASSERT(uiribbon.applicationmenu.recent.enable_pinning == TRUE);
    ASSERT(uiribbon.applicationmenu.menugroups.count_menugroups == 0);

    uiribbon_free(&uiribbon);
    return 0;
}

static int assert_fontcontrol(uiribbon_group *group, int id, int id_type, int id_size,
                              int id_bold, int id_italic, int id_underline, int id_strikethrough,
                              int id_color, int id_bigger, int id_smaller,
                              int id_subscript, int id_superscript, int id_highlight,
                              int fontsize_min, int fontsize_max, bool show_vertical_fonts, bool truetype_only, char *string_for_width)
{
    int pos = 0;
    int i;
    uiribbon_control *controls = group->controls;

    for (i = 0; i < group->count_controls; i++)
    {
        uiribbon_control *control = &controls[i];
        ASSERT_INT(control->parent_id, id);
    }

    ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_TYPE);
    ASSERT_INT(controls[pos].id, id_type);
    ASSERT_INT(controls[pos].control_info.combobox.fontcontrol_fontsize_min, fontsize_min);
    ASSERT_INT(controls[pos].control_info.combobox.fontcontrol_fontsize_max, fontsize_max);
    ASSERT_INT(controls[pos].control_info.combobox.fontcontrol_show_vertical, show_vertical_fonts);
    ASSERT_INT(controls[pos].control_info.combobox.fontcontrol_show_truetype_only, truetype_only);
    ASSERT_STR(controls[pos].control_info.combobox.fontcontrol_string_for_width, string_for_width);
    pos++;
    ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_SIZE);
    ASSERT_INT(controls[pos].id, id_size);
    pos++;
    if (id_bigger != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_BIGGER);
        ASSERT_INT(controls[pos].id, id_bigger);
        pos++;
    }
    if (id_smaller != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_BUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_SMALLER);
        ASSERT_INT(controls[pos].id, id_smaller);
        pos++;
    }
    ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
    ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_BOLD);
    ASSERT_INT(controls[pos].id, id_bold);
    pos++;
    ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
    ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_ITALIC);
    ASSERT_INT(controls[pos].id, id_italic);
    pos++;
    if (id_underline != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_UNDERLINE);
        ASSERT_INT(controls[pos].id, id_underline);
        pos++;
    }
    if (id_strikethrough != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_STRIKETHROUGH);
        ASSERT_INT(controls[pos].id, id_strikethrough);
        pos++;
    }
    if (id_subscript != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_SUBSCRIPT);
        ASSERT_INT(controls[pos].id, id_subscript);
        pos++;
    }
    if (id_superscript != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_SUPERSCRIPT);
        ASSERT_INT(controls[pos].id, id_superscript);
        pos++;
    }
    if (id_color != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_COLOR);
        ASSERT_INT(controls[pos].id, id_color);
        pos++;
    }
    if (id_highlight != -1)
    {
        ASSERT_INT(controls[pos].type, UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY);
        ASSERT_INT(controls[pos].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_HIGHLIGHT);
        ASSERT_INT(controls[pos].id, id_highlight);
        pos++;
    }

    ASSERT_INT(pos, group->count_controls);

    return 0;
}

static int test_fontcontrol(void)
{
    uiribbon_main uiribbon;
    uiribbon_group *groups;
    uiribbon_menugroup *menugroup;
    uiribbon_control *controls;

    CHECK(parse_from_testdata("fontcontrol", &uiribbon));
    ASSERT_INT(uiribbon.count_tabs, 1);
    ASSERT_INT(uiribbon.tabs[0].count_groups, 10);
    groups = uiribbon.tabs[0].groups;
    /*                                      id,  type,  size   bold, italic, underline, strike, color, bigger, smaller, subscript, superscript, highlight size_min, size_max, vertical, truetype str */
    CHECK(assert_fontcontrol(&groups[0], 10003, 62001, 62301, 62401,  62101,     62201,  62601,    -1,     -1,     -1,         -1,          -1,        -1,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[1], 10005, 62002, 62302, 62402,  62102,     62202,  62602, 63202,  62902,  63002,         -1,          -1,        -1,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[2], 10007, 62003, 62303, 62403,  62103,     62203,  62603, 63203,  62903,  63003,      62803,       62703,     63103,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[3], 10009, 62004, 62304, 62404,  62104,     62204,  62604, 63204,  62904,  63004,         -1,          -1,     63104,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[4], 10011, 62005, 62305, 62405,  62105,        -1,     -1, 63205,     -1,     -1,         -1,          -1,        -1,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[5], 10013, 62006, 62306, 62406,  62106,     62206,  62606, 63206,  62906,  63006,         -1,          -1,        -1,       44,      45,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[6], 10015, 62007, 62307, 62407,  62107,     62207,  62607, 63207,  62907,  63007,         -1,          -1,        -1,       1,     9999,        1,        1, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[7], 10017, 62008, 62308, 62408,  62108,     62208,  62608, 63208,  62908,  63008,         -1,          -1,        -1,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[8], 10019, 62009, 62309, 62409,  62109,     62209,  62609, 63209,  62909,  63009,         -1,          -1,        -1,       1,     9999,        1,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
    CHECK(assert_fontcontrol(&groups[9], 10021, 62010, 62310, 62410,  62110,     62210,  62610, 63210,  62910,  63010,         -1,          -1,        -1,       1,     9999,        0,        0, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));

    ASSERT_INT(uiribbon.count_contextmaps, 1);
    ASSERT_INT(uiribbon.contextmaps[0].minitoolbar.count_menugroups, 1);
    menugroup = &uiribbon.contextmaps[0].minitoolbar.menugroups[0];
    ASSERT_INT(menugroup->count_controls, 4);
    controls = menugroup->controls;
    ASSERT_INT(controls[0].type, UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT_INT(controls[0].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_TYPE);
    ASSERT_INT(controls[0].id, 62000);
    ASSERT_INT(controls[1].type, UIRIBBON_CONTROL_TYPE_COMBOBOX);
    ASSERT_INT(controls[1].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_SIZE);
    ASSERT_INT(controls[1].id, 62300);
    ASSERT_INT(controls[2].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
    ASSERT_INT(controls[2].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_BOLD);
    ASSERT_INT(controls[2].id, 62400);
    ASSERT_INT(controls[3].type, UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON);
    ASSERT_INT(controls[3].subtype, UIRIBBON_SUBCONTROL_TYPE_FONT_ITALIC);
    ASSERT_INT(controls[3].id, 62100);

    uiribbon_free(&uiribbon);
    return 0;
}

static stream* copy_from_testdata(char *name)
{
    stream *s_read;
    stream *s_write;
    int error;
    type_uiribbon uiribbon;
    FILE *file;
    const test_data *test = get_test_data(name);

    ok(test != NULL, "Failed to get test data");
    if (!test)
        return NULL;

    s_read = create_read_stream(test->bml_data, test->bml_len);

    error = stream_read_uiribbon(s_read, &uiribbon);
    destroy_read_stream(s_read);
    ok(error == 0, "Failed to parse file");
    if (error)
        return NULL;

    s_write = create_write_stream();

    /* ###### */
    uiribbon.unk6.ribbon.blocks[2].content_special.content_subcontrols.subcontrols[0].blocks.count_blocks = 4;
    /* ###### */

    error = stream_write_uiribbon(s_write, &uiribbon, STREAM_WRITE_STAGE_DRYRUN);
    ok(error == 0, "Failed to write file");

    /* Update internal data structures */
    uiribbon.length_this_file = s_write->max;

    /* Do write */
    error = stream_write_uiribbon(s_write, &uiribbon, STREAM_WRITE_STAGE_WRITE);
    ok(error == 0, "Failed to write file");

    file = fopen("dump_write.bml", "wb");
    ok(file != NULL, "Failed to open file");
    fwrite(s_write->contents->data, s_write->max, 1, file);
    fclose(file);
    /*destroy_write_stream(s_write);*/
    stream_free_uiribbon(&uiribbon);

    return s_write;
}

int instance_test()
{
    static char data_test[] = {0xab, 0x11, 0x06, 0x00, 0xcd, 0x13, 0xbc, 0x22, 0x0b, 0x00, 0xde, 0x33, 0x44, 0x20, 0x00, 0x30, 0x00, 0x55, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0xef};

    stream *s_read;
    stream *s_write;
    int error;
    type_test test;
    FILE *file;

    s_read = create_read_stream(data_test, sizeof(data_test));
    error = stream_read_test(s_read, &test);
    destroy_read_stream(s_read);
    ASSERT(error == 0);

    s_write = create_write_stream();

    error = stream_write_test(s_write, &test, STREAM_WRITE_STAGE_DRYRUN);
    ok(error == 0, "Failed to write file");
    error = stream_write_test(s_write, &test, STREAM_WRITE_STAGE_WRITE);
    ok(error == 0, "Failed to write file");

    file = fopen("dump_test_instance.bml", "wb");
    ok(file != NULL, "Failed to open file");
    fwrite(s_write->contents->data, s_write->max, 1, file);
    fclose(file);
    destroy_write_stream(s_write);

    stream_free_test(&test);

    return 0;
}

int main()
{
    stream *s_write;
    const test_data *testdata;
    /* run_visual_test("dropdowncolorpicker"); */
    /*write_test_data("scalingpolicy");
    return 0;*/
    CHECK(test_simple());
    CHECK(test_sizeinfo());
    CHECK(test_commands());
    CHECK(test_scalingpolicy());
    CHECK(test_combobox());
    CHECK(test_dropdownbutton());
    CHECK(test_dropdowncolorpicker());
    CHECK(test_dropdowngallery());
    CHECK(test_inribbongallery());
    CHECK(test_splitbuttongallery());
    CHECK(test_spinner());
    CHECK(test_checkbox_and_togglebutton());
    CHECK(test_splitbutton());
    CHECK(test_contextpopups());
    CHECK(test_applicationmenu());
    CHECK(test_fontcontrol());

    CHECK(instance_test());

    s_write = copy_from_testdata("simple_tabs");

    /*write_test_data("simple_tabs");
    testdata = get_test_data("simple_tabs");
    run_visual_test(testdata->bml_data, testdata->bml_len);*/
    run_visual_test(s_write->contents->data, s_write->max);

    destroy_write_stream(s_write);

    return 0;
}
