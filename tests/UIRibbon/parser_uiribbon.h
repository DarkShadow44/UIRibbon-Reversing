/* This file is generated - Do not edit manually */

#include "parser_generic.h"

typedef enum
{
	UIRIBBON_BLOCK_TYPE_RIBBON_TABS = 24,
	UIRIBBON_BLOCK_TYPE_RIBBON_QUICKACCESSTOOLBAR = 22,
} enum_block_type;

typedef enum
{
	UIRIBBON_RESOURCE_TYPE_LABELTITLE = 1,
	UIRIBBON_RESOURCE_TYPE_LABELDESCRIPTION = 2,
	UIRIBBON_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE = 3,
	UIRIBBON_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE = 4,
	UIRIBBON_RESOURCE_TYPE_SMALLIMAGE = 5,
	UIRIBBON_RESOURCE_TYPE_LARGEIMAGE = 6,
	UIRIBBON_RESOURCE_TYPE_KEYTIP = 7,
	UIRIBBON_RESOURCE_TYPE_TOOLTIPTITLE = 8,
	UIRIBBON_RESOURCE_TYPE_TOOLTIPDESCRIPTION = 9,
} enum_resource_type;

typedef enum
{
	UIRIBBON_TAB_TYPE_APPLICATIONMENU = 0,
	UIRIBBON_TAB_TYPE_NORMAL = 2,
	UIRIBBON_TAB_TYPE_CONTEXT = 3,
	UIRIBBON_TAB_TYPE_HELP = 5,
} enum_tab_type;

typedef enum
{
	UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND_INTERNAL = 2,
	UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND = 3,
	UIRIBBON_SIZEDEFINITIONS_COMMAND_SPECIAL = 9,
} enum_sizedefinitions_command;

typedef enum
{
	UIRIBBON_TYPE_CONTROL_BUTTON = 15,
	UIRIBBON_TYPE_CONTROL_SPINNER = 13,
	UIRIBBON_TYPE_CONTROL_DROPDOWNBUTTON = 20,
	UIRIBBON_TYPE_CONTROL_CHECKBOX = 6,
	UIRIBBON_TYPE_CONTROL_OTHERINFO = 25,
	UIRIBBON_TYPE_CONTROL_GALLERY = 21,
	UIRIBBON_TYPE_CONTROL_SPLITBUTTON = 18,
	UIRIBBON_TYPE_CONTROL_MENUGROUP = 24,
	UIRIBBON_TYPE_CONTROL_TAB = 26,
	UIRIBBON_TYPE_CONTROL_GROUP = 7,
	UIRIBBON_TYPE_CONTROL_TABGROUP = 27,
	UIRIBBON_TYPE_CONTROL_MINITOOLBAR = 5,
	UIRIBBON_TYPE_CONTROL_CONTEXTPOPUP = 4,
	UIRIBBON_TYPE_CONTROL_APPLICATIONMENU = 19,
} enum_type_control;

typedef enum
{
	UIRIBBON_SIZEDEFINITION_IMAGESIZE_SMALL = 0,
	UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE = 1,
} enum_sizedefinition_imagesize;

typedef enum
{
	UIRIBBON_SIZEDEFINITION_LABELVISIBLE_HIDDEN = 0,
	UIRIBBON_SIZEDEFINITION_LABELVISIBLE_VISIBLE = 1,
} enum_sizedefinition_labelvisible;

typedef enum
{
	UIRIBBON_SIZEDEFINITION_IMAGEVISIBLE_HIDDEN = 0,
	UIRIBBON_SIZEDEFINITION_IMAGEVISIBLE_VISIBLE = 1,
} enum_sizedefinition_imagevisible;

typedef enum
{
	UIRIBBON_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLISSMALL = 2,
	UIRIBBON_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLANDMEDIUMARESMALL = 3,
} enum_sizedefinition_imagesize_mixed;

typedef enum
{
	UIRIBBON_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALL = 2,
	UIRIBBON_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALLANDMEDIUM = 3,
} enum_sizedefinition_labelvisible_mixed;

typedef enum
{
	UIRIBBON_DROPDOWNCOLORPICKER_COLORTEMPLATE_THEME_COLORS = 0,
	UIRIBBON_DROPDOWNCOLORPICKER_COLORTEMPLATE_STANDARD_COLORS = 1,
	UIRIBBON_DROPDOWNCOLORPICKER_COLORTEMPLATE_HIGHLIGHT_COLORS = 2,
} enum_dropdowncolorpicker_colortemplate;

typedef enum
{
	UIRIBBON_DROPDOWNCOLORPICKER_CHIPSIZE_SMALL = 1,
	UIRIBBON_DROPDOWNCOLORPICKER_CHIPSIZE_MEDIUM = 2,
	UIRIBBON_DROPDOWNCOLORPICKER_CHIPSIZE_LARGE = 3,
} enum_dropdowncolorpicker_chipsize;

typedef enum
{
	UIRIBBON_CONTROL_BLOCK_META_NUMBER = 1,
	UIRIBBON_CONTROL_BLOCK_META_SPECIAL = 24,
	UIRIBBON_CONTROL_BLOCK_META_INLINE = 22,
	UIRIBBON_CONTROL_BLOCK_META_EXT = 62,
} enum_control_block_meta;

typedef enum
{
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID = 0,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED = 6,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED = 8,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE = 9,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE = 36,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE = 37,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED = 93,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE = 70,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE = 110,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE = 111,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS = 112,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON = 116,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON = 117,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS = 115,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS = 114,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS = 113,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO = 68,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS = 38,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT = 87,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH = 88,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION = 78,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT = 71,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER = 73,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS = 76,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS = 77,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS = 74,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS = 75,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE = 119,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM = 120,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM = 121,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX = 63,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE = 65,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ENABLE_PINNING = 64,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_STR = 79,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MIN = 48,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MAX = 49,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_PARENT_COMMANDID = 44,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_TRUETYPEONLY = 46,
	UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_VERTICALFONTS = 47,
} enum_control_block_type_number;

typedef enum
{
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS = 62,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE = 67,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM = 68,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL = 69,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM = 72,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS = 86,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU = 0,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL = 2,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT = 3,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_QUICKACCESS = 66,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_HELP = 5,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_CONTEXTPOPUPS = 10,
	UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_UNK73 = 73,
} enum_control_block_type_special;

typedef enum
{
	UIRIBBON_BOOLEAN_BOOL_FALSE = 0,
	UIRIBBON_BOOLEAN_BOOL_TRUE = 1,
} enum_boolean;

typedef enum
{
	UIRIBBON_GALLERY_TYPE_INRIBBON = 0,
	UIRIBBON_GALLERY_TYPE_DROPDOWNBUTTON = 1,
	UIRIBBON_GALLERY_TYPE_DROPDOWNLIST = 2,
	UIRIBBON_GALLERY_TYPE_COMBO = 3,
	UIRIBBON_GALLERY_TYPE_DROPDOWNSPLIT = 4,
} enum_gallery_type;

typedef enum
{
	UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS = 0,
	UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS = 1,
} enum_gallery_elements_type;

typedef enum
{
	UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM = 0,
	UIRIBBON_GALLERY_TEXT_POSITION_RIGHT = 1,
	UIRIBBON_GALLERY_TEXT_POSITION_TOP = 2,
	UIRIBBON_GALLERY_TEXT_POSITION_LEFT = 3,
	UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY = 4,
	UIRIBBON_GALLERY_TEXT_POSITION_HIDE = 5,
} enum_gallery_text_position;

typedef enum
{
	UIRIBBON_GALLERY_MENULAYOUT_SPECIAL = 0,
	UIRIBBON_GALLERY_MENULAYOUT_VERTICAL = 1,
	UIRIBBON_GALLERY_MENULAYOUT_FLOW = 2,
} enum_gallery_menulayout;

typedef enum
{
	UIRIBBON_GALLERY_GRIPPER_NONE = 0,
	UIRIBBON_GALLERY_GRIPPER_VERTICAL = 1,
	UIRIBBON_GALLERY_GRIPPER_CORNER = 2,
} enum_gallery_gripper;

typedef struct type_id_
{
	uint8_t flag;
	int32_t id;
} type_id;

typedef struct type_string_
{
	uint16_t size_str;
	char *str;
} type_string;

typedef struct type_strings_
{
	uint8_t count_strings;
	struct type_string_ *strings;
} type_strings;

typedef struct type_resource_generic_
{
	enum_resource_type resource_type;
	uint32_t resource_id;
	uint16_t mindpi;
} type_resource_generic;

typedef struct type_resource_
{
	uint32_t command_id;
	uint8_t count_resources;
	struct type_resource_generic_ *resources;
} type_resource;

typedef struct type_sizedefinitions_order_command_
{
	uint8_t unk1;
	enum_sizedefinitions_command flags_command;
	uint8_t string_id;
	uint16_t command_id;
	uint32_t unk2;
} type_sizedefinitions_order_command;

typedef struct type_sizedefinition_order_
{
	uint16_t count_commands;
	struct type_sizedefinitions_order_command_ *commands;
} type_sizedefinition_order;

typedef struct type_control_block_number_variable_
{
	type_id id;
} type_control_block_number_variable;

typedef struct type_control_block_number_long_
{
	uint32_t unk1;
	uint8_t value1;
} type_control_block_number_long;

typedef struct type_subcontrols_
{
	uint16_t count_subcontrols;
	struct type_control_ *subcontrols;
} type_subcontrols;

typedef struct type_control_block_number_
{
	uint8_t block_len;
	enum_control_block_type_number block_type;
	type_control_block_number_variable content_number;
	type_control_block_number_long content_long;
	int32_t id;
	enum_sizedefinition_labelvisible_mixed sizedefinition_labelvisible_mixed;
	enum_sizedefinition_labelvisible sizedefinition_labelvisible;
	enum_sizedefinition_imagevisible sizedefinition_imagevisible;
	enum_sizedefinition_imagesize sizedefinition_imagesize;
	enum_sizedefinition_imagesize_mixed sizedefinition_imagesize_mixed;
	enum_boolean autocomplete_enabled;
	enum_gallery_type gallery_type;
	enum_dropdowncolorpicker_colortemplate dropdowncolorpicker_colortemplate;
	enum_dropdowncolorpicker_chipsize dropdowncolorpicker_chipsize;
	int32_t dropdowncolorpicker_columns;
	enum_boolean dropdowncolorpicker_has_autocolor_button;
	enum_boolean dropdowncolorpicker_has_nocolor_button;
	int32_t dropdowncolorpicker_recent_color_rows;
	int32_t dropdowncolorpicker_standard_rows;
	int32_t dropdowncolorpicker_theme_color_rows;
	enum_gallery_elements_type gallery_elements_type;
	enum_boolean gallery_has_large_items;
	int32_t gallery_item_height;
	int32_t gallery_item_width;
	enum_gallery_text_position gallery_text_position;
	enum_gallery_menulayout gallery_menulayout;
	enum_gallery_gripper gallery_gripper;
	int32_t gallery_rows;
	int32_t gallery_columns;
	int32_t gallery_max_rows;
	int32_t gallery_max_columns;
	int32_t gallery_min_columns_large;
	int32_t gallery_max_columns_medium;
	int32_t gallery_min_columns_medium;
	int32_t is_checkbox;
	int32_t scalepolicy;
	int32_t scalepolicy_medium;
	int32_t scalepolicy_small;
	int32_t scalepolicy_popup;
	int32_t id_reference;
	int32_t enable_pinning;
	int32_t fontcontrol_str;
	int32_t fontcontrol_fontsize_min;
	int32_t fontcontrol_fontsize_max;
	int32_t fontcontrol_parent_commandid;
	int32_t fontcontrol_truetypeonly;
	int32_t fontcontrol_verticalfonts;
} type_control_block_number;

typedef struct type_control_block_special_
{
	uint8_t block_len;
	enum_control_block_type_special block_type;
	type_subcontrols content_subcontrols;
	type_sizedefinition_order sizedefinition_order;
} type_control_block_special;

typedef struct type_control_blocks_
{
	uint8_t count_blocks;
	struct type_control_block_ *blocks;
} type_control_blocks;

typedef struct type_block_inline_
{
	uint32_t unk2;
	uint16_t len4;
	type_control_blocks quick_ribbon_info;
} type_block_inline;

typedef struct type_control_block_
{
	enum_control_block_meta meta_type;
	type_control_block_number content_number;
	type_control_block_special content_special;
	type_block_inline block_inline;
	uint32_t ext_pos;
	struct type_control_block_ext_ *ext;
} type_control_block;

typedef struct type_control_block_ext_
{
	uint16_t len_ext;
	type_control_block block;
} type_control_block_ext;

typedef struct type_control_
{
	uint16_t unk1;
	enum_type_control block_type;
	uint8_t unk2;
	uint16_t size_block;
	type_control_blocks blocks;
} type_control;

typedef struct type_menugroup_extended_
{
	uint16_t unk_id1;
	uint16_t menu_items_len;
	struct type_control_ *items;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint16_t unk4;
} type_menugroup_extended;

typedef struct type_recent2_
{
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint8_t own_index;
	uint8_t unk4b;
	uint16_t unk4c;
	uint32_t unk5;
	uint32_t unk6;
	uint32_t unk7;
	uint32_t unk8;
	uint32_t unk9;
	uint8_t unk10;
} type_recent2;

typedef struct type_recent1_
{
	uint16_t unk_id1;
	uint16_t recent_len;
	struct type_recent2_ *elements;
} type_recent1;

typedef struct type_command_ext_
{
	uint16_t own_index_maybe;
	uint16_t unk0;
	uint16_t unk1a;
	uint16_t unk2;
	uint16_t command_id;
} type_command_ext;

typedef struct application_views_
{
	uint16_t ribbon_len;
	type_control_blocks ribbon;
} application_views;

typedef struct type_command_
{
	uint16_t command_id;
	char *unk1;
	uint8_t unk3b;
	char *unk4;
	uint16_t size_str;
	char *str;
} type_command;

typedef struct type_command_container_
{
	uint32_t commands_len;
	struct type_command_ *commands;
} type_command_container;

typedef struct type_uiribbon_
{
	uint32_t length_this_file;
	uint16_t size_strings;
	type_strings strings;
	uint16_t count_command_resources;
	struct type_resource_ *command_resources;
	uint32_t size_command_container;
	type_command_container command_container;
	uint16_t len_unk6;
	uint16_t unklen6;
	application_views unk6;
} type_uiribbon;

int read_type_uiribbon(stream *s_root, stream *s, type_uiribbon *ret);
