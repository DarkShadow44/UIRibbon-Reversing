#include "parser_uiribbon.h"

typedef int bool;
#define FALSE 0
#define TRUE 1

typedef enum
{
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_OPEN_GROUP,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_CLOSE_GROUP,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_INVISIBLE_SEPARATOR,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK,
} uiribbon_sizedefinition_group_order_command;

typedef enum
{
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_COMBOBOX,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_CHECKBOX,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNBUTTON,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNCOLORPICKER,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_GROUP,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_DROPDOWNGALLERY,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTON,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_INRIBBONGALLERY,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPLITBUTTONGALLERY,
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_SPINNER,
} uiribbon_control_type;

typedef struct
{
    bool sizeLarge;
    bool labelvisible;
    bool imagevisible;
} uiribbon_sizedefinition_control;

typedef struct
{
    uiribbon_sizedefinition_control large;
    uiribbon_sizedefinition_control medium;
    uiribbon_sizedefinition_control small;
} uiribbon_sizedefinitions_control;

typedef struct
{
    bool is_special;
    union
    {
        int command_id;
        uiribbon_sizedefinition_group_order_command special_command;
    };
} uiribbon_sizedefinition_group_order;

typedef struct
{
    int count_orders;
    uiribbon_sizedefinition_group_order *orders;

} uiribbon_sizedefinition_group;

typedef struct
{
    uiribbon_sizedefinition_group large;
    uiribbon_sizedefinition_group medium;
    uiribbon_sizedefinition_group small;
} uiribbon_sizedefinitions_orders;

typedef struct
{
    bool has_vertical_resize;
    bool has_autocomplete;
    bool is_editable;
} uiribbon_control_combobox;

typedef enum
{
    UIRIBBON_TRANSFORMED_CHIPSIZE_SMALL,
    UIRIBBON_TRANSFORMED_CHIPSIZE_MEDIUM,
    UIRIBBON_TRANSFORMED_CHIPSIZE_LARGE,
} uiribbon_chipsize;

typedef enum
{
    UIRIBBON_TRANSFORMED_COLORTEMPLATE_THEME,
    UIRIBBON_TRANSFORMED_COLORTEMPLATE_STANDARD,
    UIRIBBON_TRANSFORMED_COLORTEMPLATE_HIGHLIGHT,
} uiribbon_colortemplate;

typedef struct
{
    uiribbon_chipsize chipsize;
    uiribbon_colortemplate colortemplate;
    int columns;
    bool has_autocolor_button;
    bool has_nocolor_button;
    int recent_color_rows;
    int standard_color_rows;
    int theme_color_rows;
} uiribbon_control_dropdowncolorpicker;

typedef enum
{
    UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_ITEMS,
    UIRIBBON_TRANSFORMED_GALLERY_ELEMENTS_TYPE_COMMANDS,
} uiribbon_gallery_elements_type;

typedef enum
{
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_LEFT,
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_RIGHT,
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_TOP,
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_BOTTOM,
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_OVERLAY,
    UIRIBBON_TRANSFORMED_GALLERY_TEXT_POSITION_HIDE,
} uiribbon_gallery_text_position;

typedef enum
{
    UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_FLOW,
    UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_VERTICAL,
    UIRIBBON_TRANSFORMED_GALLERY_MENULAYOUT_SPECIAL,
} uiribbon_gallery_menulayout;

typedef enum
{
    UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_NONE,
    UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_VERTICAL,
    UIRIBBON_TRANSFORMED_GALLERY_GRIPPER_CORNER,
} uiribbon_gallery_gripper;

typedef struct
{
    uiribbon_gallery_elements_type elements_type;
    uiribbon_gallery_text_position text_position;
    bool has_large_items;
    int item_height;
    int item_width;
    uiribbon_gallery_menulayout menulayout;
    uiribbon_gallery_gripper gripper;
    int rows;
    int columns;
} uiribbon_control_gallery_generic;

typedef struct
{
    uiribbon_control_gallery_generic generic;
    int max_columns;
    int max_columns_medium;
    int max_rows;
    int min_columns_large;
    int min_columns_medium;
} uiribbon_control_inribbongallery;

typedef struct uiribbon_control_
{
    uiribbon_control_type type;
    int id;
    uiribbon_sizedefinitions_control *size_definitions;
    int count_subcontrols;
    struct uiribbon_control_ *subcontrols;
    union
    {
        uiribbon_control_combobox combobox;
        uiribbon_control_dropdowncolorpicker dropdowncolorpicker;
        uiribbon_control_gallery_generic dropdowngallery;
        uiribbon_control_inribbongallery inribbongallery;
        uiribbon_control_gallery_generic splitbuttongallery;
    } control_info;
} uiribbon_control;

typedef struct
{
    int id;
    int count_controls;
    uiribbon_control *controls;
    uiribbon_sizedefinitions_orders *sizedefinition_orders;
} uiribbon_group;

typedef enum
{
    UIRIBBON_TRANSFORMED_SCALE_TO_MEDIUM,
    UIRIBBON_TRANSFORMED_SCALE_TO_SMALL,
    UIRIBBON_TRANSFORMED_SCALE_TO_POPUP,
} uiribbon_scalingpolicy_type;

typedef struct
{
    int group_id;
    uiribbon_scalingpolicy_type scale_type;
} uiribbon_scalingpolicy;

typedef struct
{
    int id;
    int count_groups;
    uiribbon_group *groups;
    int count_scalepolicies;
    uiribbon_scalingpolicy *scalepolicies;
} uiribbon_tab;

typedef struct
{
    int id;
    int count_tabs;
    uiribbon_tab *tabs;
} uiribbon_tabgroup;

typedef struct
{
    int id_image;
    int min_dpi;
} uiribbon_command_image;

typedef struct
{
    int id;
    int id_label_title;
    int id_label_description;
    int id_keytip;
    int id_toopltip_title;
    int id_tooltip_description;

    int count_images_small;
    uiribbon_command_image *images_small;
    int count_images_large;
    uiribbon_command_image *images_large;
    int count_images_small_high_contrast;
    uiribbon_command_image *images_small_high_contrast;
    int count_images_large_high_contrast;
    uiribbon_command_image *images_large_high_contrast;
} uiribbon_command;


typedef struct
{
    int count_commands;
    uiribbon_command *commands;
    int count_tabs;
    uiribbon_tab *tabs;
    int count_contexttabgroups;
    uiribbon_tabgroup *contexttabgroups;
} uiribbon_main;

void transform_uiribbon(type_uiribbon *src, uiribbon_main *ret);
