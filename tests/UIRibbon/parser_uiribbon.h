/* This file is generated - Do not edit manually */

#include "parser_generic.h"

typedef enum
{
	ENUM_RESOURCE_TYPE_LABELTITLE = 1,
	ENUM_RESOURCE_TYPE_LABELDESCRIPTION = 2,
	ENUM_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE = 3,
	ENUM_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE = 4,
	ENUM_RESOURCE_TYPE_SMALLIMAGE = 5,
	ENUM_RESOURCE_TYPE_LARGEIMAGE = 6,
	ENUM_RESOURCE_TYPE_KEYTIP = 7,
	ENUM_RESOURCE_TYPE_TOOLTIPTITLE = 8,
	ENUM_RESOURCE_TYPE_TOOLTIPDESCRIPTION = 9,
} enum_resource_type;

typedef enum
{
	ENUM_TAB_TYPE_APPLICATIONMENU = 0,
	ENUM_TAB_TYPE_NORMAL = 2,
	ENUM_TAB_TYPE_CONTEXT = 3,
	ENUM_TAB_TYPE_HELP = 5,
} enum_tab_type;

typedef enum
{
	ENUM_SIZEDEFINITIONS_COMMAND_COMMAND_INTERNAL = 2,
	ENUM_SIZEDEFINITIONS_COMMAND_COMMAND = 3,
	ENUM_SIZEDEFINITIONS_COMMAND_SPECIAL = 9,
} enum_sizedefinitions_command;

typedef enum
{
	ENUM_TYPE_CONTROL_BUTTON = 15,
	ENUM_TYPE_CONTROL_SPINNER = 13,
	ENUM_TYPE_CONTROL_DROPDOWNBUTTON = 20,
	ENUM_TYPE_CONTROL_CHECKBOX = 6,
	ENUM_TYPE_CONTROL_OTHERINFO = 25,
	ENUM_TYPE_CONTROL_GALLERY = 21,
	ENUM_TYPE_CONTROL_SPLITBUTTON = 18,
	ENUM_TYPE_CONTROL_MENUGROUP = 24,
	ENUM_TYPE_CONTROL_TAB = 26,
	ENUM_TYPE_CONTROL_GROUP = 7,
	ENUM_TYPE_CONTROL_TABGROUP = 27,
	ENUM_TYPE_CONTROL_MINITOOLBAR = 5,
	ENUM_TYPE_CONTROL_CONTEXTPOPUP = 4,
	ENUM_TYPE_CONTROL_APPLICATIONMENU = 19,
	ENUM_TYPE_CONTROL_SUBGROUP = 38,
} enum_type_control;

typedef enum
{
	ENUM_SIZEDEFINITION_IMAGESIZE_SMALL = 0,
	ENUM_SIZEDEFINITION_IMAGESIZE_LARGE = 1,
} enum_sizedefinition_imagesize;

typedef enum
{
	ENUM_SIZEDEFINITION_LABELVISIBLE_HIDDEN = 0,
	ENUM_SIZEDEFINITION_LABELVISIBLE_VISIBLE = 1,
} enum_sizedefinition_labelvisible;

typedef enum
{
	ENUM_SIZEDEFINITION_IMAGEVISIBLE_HIDDEN = 0,
	ENUM_SIZEDEFINITION_IMAGEVISIBLE_VISIBLE = 1,
} enum_sizedefinition_imagevisible;

typedef enum
{
	ENUM_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLISSMALL = 2,
	ENUM_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLANDMEDIUMARESMALL = 3,
} enum_sizedefinition_imagesize_mixed;

typedef enum
{
	ENUM_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALL = 2,
	ENUM_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALLANDMEDIUM = 3,
} enum_sizedefinition_labelvisible_mixed;

typedef enum
{
	ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_THEME_COLORS = 0,
	ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_STANDARD_COLORS = 1,
	ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_HIGHLIGHT_COLORS = 2,
} enum_dropdowncolorpicker_colortemplate;

typedef enum
{
	ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_SMALL = 1,
	ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_MEDIUM = 2,
	ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_LARGE = 3,
} enum_dropdowncolorpicker_chipsize;

typedef enum
{
	ENUM_TREE_ENTRY_TYPE_PROPERTY = 1,
	ENUM_TREE_ENTRY_TYPE_ARRAY = 24,
	ENUM_TREE_ENTRY_TYPE_NODE = 22,
	ENUM_TREE_ENTRY_TYPE_EXT = 62,
	ENUM_TREE_ENTRY_TYPE_SIZEINFO = 59,
} enum_tree_entry_type;

typedef enum
{
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID = 0,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED = 6,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED = 8,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE = 9,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE = 36,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE = 37,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED = 93,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE = 70,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE = 110,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE = 111,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS = 112,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON = 116,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON = 117,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS = 115,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS = 114,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS = 113,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_META_INFO = 68,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS = 38,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT = 87,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH = 88,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION = 78,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT = 71,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER = 73,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS = 76,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS = 77,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS = 74,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS = 75,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE = 119,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM = 120,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM = 121,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX = 63,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE = 65,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_ENABLE_PINNING = 64,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_STR = 79,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MIN = 48,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MAX = 49,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_PARENT_COMMANDID = 44,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_TRUETYPEONLY = 46,
	ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_VERTICALFONTS = 47,
} enum_control_block_type_number;

typedef enum
{
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS = 62,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE = 67,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM = 68,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL = 69,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM = 72,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS = 86,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU = 0,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL = 2,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT = 3,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_QUICKACCESS = 66,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_TABS_HELP = 5,
	ENUM_CONTROL_BLOCK_TYPE_SPECIAL_CONTEXTPOPUPS = 10,
} enum_control_block_type_special;

typedef enum
{
	ENUM_BOOLEAN_BOOL_FALSE = 0,
	ENUM_BOOLEAN_BOOL_TRUE = 1,
} enum_boolean;

typedef enum
{
	ENUM_GALLERY_TYPE_INRIBBON = 0,
	ENUM_GALLERY_TYPE_DROPDOWNBUTTON = 1,
	ENUM_GALLERY_TYPE_DROPDOWNLIST = 2,
	ENUM_GALLERY_TYPE_COMBO = 3,
	ENUM_GALLERY_TYPE_DROPDOWNSPLIT = 4,
} enum_gallery_type;

typedef enum
{
	ENUM_GALLERY_ELEMENTS_TYPE_ITEMS = 0,
	ENUM_GALLERY_ELEMENTS_TYPE_COMMANDS = 1,
} enum_gallery_elements_type;

typedef enum
{
	ENUM_GALLERY_TEXT_POSITION_BOTTOM = 0,
	ENUM_GALLERY_TEXT_POSITION_RIGHT = 1,
	ENUM_GALLERY_TEXT_POSITION_TOP = 2,
	ENUM_GALLERY_TEXT_POSITION_LEFT = 3,
	ENUM_GALLERY_TEXT_POSITION_OVERLAY = 4,
	ENUM_GALLERY_TEXT_POSITION_HIDE = 5,
} enum_gallery_text_position;

typedef enum
{
	ENUM_GALLERY_MENULAYOUT_SPECIAL = 0,
	ENUM_GALLERY_MENULAYOUT_VERTICAL = 1,
	ENUM_GALLERY_MENULAYOUT_FLOW = 2,
} enum_gallery_menulayout;

typedef enum
{
	ENUM_GALLERY_GRIPPER_NONE = 0,
	ENUM_GALLERY_GRIPPER_VERTICAL = 1,
	ENUM_GALLERY_GRIPPER_CORNER = 2,
} enum_gallery_gripper;

typedef struct type_id_
{
	int _dryrun_pos;
	uint8_t flag;
	int32_t id;
} type_id;

typedef struct type_string_
{
	int _dryrun_pos;
	uint16_t size_str;
	char *str;
} type_string;

typedef struct type_strings_
{
	int _dryrun_pos;
	uint8_t count_strings;
	struct type_string_ * strings;
	uint8_t unk2;
} type_strings;

typedef struct type_resource_generic_
{
	int _dryrun_pos;
	enum_resource_type resource_type;
	uint32_t resource_id;
	uint16_t mindpi;
} type_resource_generic;

typedef struct type_resource_
{
	int _dryrun_pos;
	uint32_t command_id;
	uint8_t count_resources;
	struct type_resource_generic_ * resources;
} type_resource;

typedef struct type_tree_entry_node_
{
	int _dryrun_pos;
	uint8_t unk56;
	enum_type_control type;
	uint8_t unk3;
	uint16_t size_node;
	uint8_t count_children;
	struct type_tree_entry_ * children;
} type_tree_entry_node;

typedef struct type_sizedefinitions_order_command_
{
	int _dryrun_pos;
	enum_sizedefinitions_command flags_command;
	uint8_t string_id;
	uint16_t command_id;
	uint32_t unk2;
} type_sizedefinitions_order_command;

typedef struct type_tree_entry_number_variable_
{
	int _dryrun_pos;
	type_id id;
} type_tree_entry_number_variable;

typedef struct type_tree_entry_number_long_
{
	int _dryrun_pos;
	uint32_t unk1;
	uint8_t value1;
} type_tree_entry_number_long;

typedef struct type_tree_entry_number_
{
	int _dryrun_pos;
	uint8_t block_len;
	enum_control_block_type_number block_type;
	type_tree_entry_number_variable content_number;
	type_tree_entry_number_long content_long;
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
} type_tree_entry_number;

typedef struct type_tree_entry_array_
{
	int _dryrun_pos;
	uint8_t block_len;
	enum_control_block_type_special block_type;
	uint16_t count_children;
	struct type_tree_entry_ * children;
} type_tree_entry_array;

typedef struct type_tree_entry_
{
	int _dryrun_pos;
	enum_tree_entry_type entry_type;
	type_tree_entry_number property;
	type_tree_entry_array array;
	type_tree_entry_node node;
	uint32_t ext_pos;
	type_sizedefinitions_order_command sizeinfo;
	int _dryrun_pos_instance_ext;
	struct type_tree_entry_ext_ *ext;
} type_tree_entry;

typedef struct type_tree_entry_ext_
{
	int _dryrun_pos;
	uint16_t len_ext;
	type_tree_entry block;
} type_tree_entry_ext;

typedef struct type_command_
{
	int _dryrun_pos;
	uint16_t command_id;
	char *unk1;
	uint8_t unk3b;
	char *unk4;
	uint16_t size_str;
	char *str;
} type_command;

typedef struct type_command_container_
{
	int _dryrun_pos;
	uint32_t commands_len;
	struct type_command_ * commands;
	uint8_t unk1;
} type_command_container;

typedef struct type_command_ext5_
{
	int _dryrun_pos;
	uint16_t command_id;
	uint16_t count;
	uint16_t offset;
} type_command_ext5;

typedef struct type_command_ext4_
{
	int _dryrun_pos;
	int blocks_count;
	struct type_command_ext5_ * blocks;
} type_command_ext4;

typedef struct type_command_ext3_
{
	int _dryrun_pos;
	uint16_t size_commands;
	uint16_t unk2;
	type_command_ext4 unk3;
} type_command_ext3;

typedef struct type_command_ext2_
{
	int _dryrun_pos_instance_ext;
	struct type_command_ext3_ *ext;
} type_command_ext2;

typedef struct type_uiribbon_
{
	int _dryrun_pos;
	uint32_t length_this_file;
	uint32_t size_strings;
	type_strings strings;
	uint32_t count_command_resources;
	struct type_resource_ * command_resources;
	uint32_t size_command_container;
	type_command_container command_container;
	uint16_t len_unk6;
	uint32_t command_ext_pos;
	type_tree_entry root_node;
	type_command_ext2 command_ext;
} type_uiribbon;

int stream_read_uiribbon(stream *s, type_uiribbon *data);
int stream_write_uiribbon(stream *s, type_uiribbon *data, stream_write_stage stage);
void stream_free_uiribbon(type_uiribbon *data);
