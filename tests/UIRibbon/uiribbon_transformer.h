#include "parser_uiribbon.h"

typedef int bool;
#define FALSE 0
#define TRUE 1

/* FIXME: Subcontrol not part of ALL controls, only that that can have them */

typedef enum
{
    UIRIBBON_SIZEINFO_ORDER_OPEN_GROUP,
    UIRIBBON_SIZEINFO_ORDER_CLOSE_GROUP,
    UIRIBBON_SIZEINFO_ORDER_VISIBLE_SEPARATOR,
    UIRIBBON_SIZEINFO_ORDER_INVISIBLE_SEPARATOR,
    UIRIBBON_SIZEINFO_ORDER_BREAK,
} uiribbon_sizedefinition_group_order_command;

typedef enum
{
    UIRIBBON_CONTROL_TYPE_BUTTON,
    UIRIBBON_CONTROL_TYPE_COMBOBOX,
    UIRIBBON_CONTROL_TYPE_CHECKBOX,
    UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON,
    UIRIBBON_CONTROL_TYPE_DROPDOWNCOLORPICKER,
    UIRIBBON_CONTROL_TYPE_GROUP,
    UIRIBBON_CONTROL_TYPE_DROPDOWNGALLERY,
    UIRIBBON_CONTROL_TYPE_SPLITBUTTON,
    UIRIBBON_CONTROL_TYPE_INRIBBONGALLERY,
    UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY,
    UIRIBBON_CONTROL_TYPE_SPINNER,
    UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON,
} uiribbon_control_type;

typedef enum
{
    UIRIBBON_SUBCONTROL_TYPE_NONE,
    UIRIBBON_SUBCONTROL_TYPE_FONT_TYPE,
    UIRIBBON_SUBCONTROL_TYPE_FONT_SIZE,
    UIRIBBON_SUBCONTROL_TYPE_FONT_HIGHLIGHT,
    UIRIBBON_SUBCONTROL_TYPE_FONT_COLOR,
    UIRIBBON_SUBCONTROL_TYPE_FONT_ITALIC,
    UIRIBBON_SUBCONTROL_TYPE_FONT_UNDERLINE,
    UIRIBBON_SUBCONTROL_TYPE_FONT_BOLD,
    UIRIBBON_SUBCONTROL_TYPE_FONT_STRIKETHROUGH,
    UIRIBBON_SUBCONTROL_TYPE_FONT_SUPERSCRIPT,
    UIRIBBON_SUBCONTROL_TYPE_FONT_SUBSCRIPT,
    UIRIBBON_SUBCONTROL_TYPE_FONT_BIGGER,
    UIRIBBON_SUBCONTROL_TYPE_FONT_SMALLER,
} uiribbon_subcontrol_type;

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
    int fontcontrol_fontsize_min;
    int fontcontrol_fontsize_max;
    bool fontcontrol_show_truetype_only;
    bool fontcontrol_show_vertical;
    char fontcontrol_string_for_width[80];
} uiribbon_control_combobox;

typedef enum
{
    UIRIBBON_CHIPSIZE_SMALL,
    UIRIBBON_CHIPSIZE_MEDIUM,
    UIRIBBON_CHIPSIZE_LARGE,
} uiribbon_chipsize;

typedef enum
{
    UIRIBBON_COLORTEMPLATE_THEME,
    UIRIBBON_COLORTEMPLATE_STANDARD,
    UIRIBBON_COLORTEMPLATE_HIGHLIGHT,
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
    UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS,
    UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS,
} uiribbon_gallery_elements_type;

typedef enum
{
    UIRIBBON_GALLERY_TEXT_POSITION_LEFT,
    UIRIBBON_GALLERY_TEXT_POSITION_RIGHT,
    UIRIBBON_GALLERY_TEXT_POSITION_TOP,
    UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM,
    UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY,
    UIRIBBON_GALLERY_TEXT_POSITION_HIDE,
} uiribbon_gallery_text_position;

typedef enum
{
    UIRIBBON_GALLERY_MENULAYOUT_FLOW,
    UIRIBBON_GALLERY_MENULAYOUT_VERTICAL,
    UIRIBBON_GALLERY_MENULAYOUT_SPECIAL,
} uiribbon_gallery_menulayout;

typedef enum
{
    UIRIBBON_GALLERY_GRIPPER_NONE,
    UIRIBBON_GALLERY_GRIPPER_VERTICAL,
    UIRIBBON_GALLERY_GRIPPER_CORNER,
} uiribbon_gallery_gripper;

typedef enum
{
    UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS,
    UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS,
} uiribbon_menu_item_class;

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

typedef struct
{
    struct uiribbon_control_ *buttonitem;
} uiribbon_control_splitbutton;

typedef struct uiribbon_control_
{
    uiribbon_control_type type;
    int id;
    int parent_id;
    uiribbon_subcontrol_type subtype;
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
        uiribbon_control_splitbutton splitbutton;
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
    UIRIBBON_SCALE_TO_MEDIUM,
    UIRIBBON_SCALE_TO_SMALL,
    UIRIBBON_SCALE_TO_POPUP,
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
    int id;
    uiribbon_menu_item_class item_class;
    int count_controls;
    uiribbon_control *controls;
} uiribbon_menugroup;

typedef struct
{
    int count_menugroups;
    uiribbon_menugroup *menugroups;
} uiribbon_menugroup_container;

typedef struct
{
    int id;
    uiribbon_menugroup_container minitoolbar;
    uiribbon_menugroup_container contextpopup;
} uiribbon_contextmap;

typedef struct
{
    int id;
    int count;
    bool enable_pinning;
} ribbon_recent;

typedef struct
{
   int id;
   ribbon_recent recent;
   uiribbon_menugroup_container menugroups;
}  uiribbon_applicationmenu;

typedef struct
{
    int count_commands;
    uiribbon_command *commands;
    int count_tabs;
    uiribbon_tab *tabs;
    int count_contexttabgroups;
    uiribbon_tabgroup *contexttabgroups;
    int count_contextmaps;
    uiribbon_contextmap *contextmaps;
    uiribbon_applicationmenu applicationmenu;
} uiribbon_main;

void uiribbon_transform(type_uiribbon *src, uiribbon_main *ret);
void uiribbon_free(uiribbon_main *src);
