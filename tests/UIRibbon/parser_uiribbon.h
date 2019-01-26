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
	UIRIBBON_TYPE_CONTROL_GROUP = 24,
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
	UIRIBBON_CONTROL_BLOCK_TYPE_ID = 0,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE_MIXED = 6,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE_MIXED = 8,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE = 9,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGEVISIBLE = 36,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE = 37,
	UIRIBBON_CONTROL_BLOCK_TYPE_AUTOCOMPLETE_ENABLED = 93,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_TYPE = 70,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLORTEMPLATE = 110,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_CHIPSIZE = 111,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLUMNS = 112,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON = 116,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON = 117,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS = 115,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS = 114,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS = 113,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ELEMENTS_TYPE = 68,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_HAS_LARGE_ITEMS = 38,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ITEM_HEIGHT = 87,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ITEM_WIDTH = 88,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_TEXT_POSITION = 78,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MENULAYOUT = 71,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_GRIPPER = 73,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ROWS = 76,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_COLUMNS = 77,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_ROWS = 74,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_COLUMNS = 75,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MIN_COLUMNS_LARGE = 119,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_COLUMNS_MEDIUM = 120,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MIN_COLUMNS_MEDIUM = 121,
	UIRIBBON_CONTROL_BLOCK_TYPE_IS_CHECKBOX = 63,
	UIRIBBON_CONTROL_BLOCK_TYPE_SUBCONTROLS = 62,
	UIRIBBON_CONTROL_BLOCK_TYPE_BUTTONITEM = 72,
	UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_SUBCONTROLS = 86,
} enum_control_block_type;

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

typedef struct type_tabgroup_
{
	uint16_t unk1;
	uint16_t unk2;
	uint8_t unk3a;
	uint8_t unk3b;
	uint16_t unk4;
	uint16_t unk5;
	uint8_t unk100;
	type_id id;
	uint8_t unk7;
	uint16_t unk8;
	uint16_t count_tabs;
	struct type_tab_ *tabs;
} type_tabgroup;

typedef struct type_ribbon_tabs_normal_
{
	uint16_t count_tabs;
	struct type_tab_ *tabs;
} type_ribbon_tabs_normal;

typedef struct type_ribbon_tabs_context_
{
	uint16_t count_tabgroups;
	struct type_tabgroup_ *tabgroups;
} type_ribbon_tabs_context;

typedef struct type_ribbon_tabs_applicationmenu_
{
	uint8_t unk2;
	uint16_t unk3;
	uint16_t unk4;
	uint16_t unk5;
	uint16_t unk6;
	uint8_t unk7;
	uint16_t unk8;
	uint8_t unk100;
	type_id id;
	uint16_t unk11;
	uint16_t unk12;
	uint16_t unk13;
	uint16_t unk14;
	uint8_t unk15;
	char *unk16;
	uint32_t unk17;
	char *unk18;
	uint32_t unk19;
	char *unk20;
	uint32_t unk21;
} type_ribbon_tabs_applicationmenu;

typedef struct type_block_tabs_
{
	uint8_t unk1a;
	enum_tab_type tab_type;
	union
	{
		type_ribbon_tabs_normal block_help;
		type_ribbon_tabs_normal block_normal;
		type_ribbon_tabs_context block_context;
		type_ribbon_tabs_applicationmenu block_applicationmenu;
	};
} type_block_tabs;

typedef struct type_ribbon_
{
	uint8_t count_blocks;
	struct type_block_generic_ *block1;
} type_ribbon;

typedef struct block_unk1_
{
	char *rest;
} block_unk1;

typedef struct type_sizeinfo_maybe_
{
	uint8_t unk0;
	uint16_t unk0c;
	uint16_t unk0b;
	uint8_t unk2a;
	uint8_t unk2b;
	uint8_t unk2c;
	uint8_t unk1;
	char *unk1e1;
	uint8_t unk2;
	uint8_t unk3;
	uint8_t unk4;
	uint8_t unk5;
	uint8_t unk6;
	uint8_t unk100;
	type_id id;
	uint8_t unk11;
} type_sizeinfo_maybe;

typedef struct type_sizedefinitions_command_
{
	uint8_t unk1;
	enum_sizedefinitions_command flags_command;
	uint8_t string_id;
	uint16_t command_id;
} type_sizedefinitions_command;

typedef struct type_sizedefinition_
{
	uint16_t unk1;
	uint8_t unk2;
	uint16_t count_commands;
	struct type_sizedefinitions_command_ *commands;
} type_sizedefinition;

typedef struct type_group_elements_info_
{
	uint8_t unk10;
	uint16_t unk1b;
	uint8_t unk2;
	uint16_t unk1c;
	uint8_t unk1d;
	uint16_t sub_count;
	struct type_control_ *subcontents;
	type_sizedefinition sizedefinition_large;
	type_sizedefinition sizedefinition_medium;
	type_sizedefinition sizedefinition_small;
	char *unk6;
} type_group_elements_info;

typedef struct type_scalingpolicy_
{
	uint8_t unk1a;
	uint8_t unk1b;
	type_id scale_value;
	uint8_t unk3;
	int32_t priority_medium;
	int32_t priority_small;
	int32_t priority_popup;
} type_scalingpolicy;

typedef struct type_group_info_
{
	uint16_t unk1;
	uint16_t len_unk1;
	uint16_t unk3;
	uint16_t unk4;
	type_id id;
	uint8_t unk20a;
	type_scalingpolicy scalingpolicy;
	uint8_t unk20b;
	uint16_t unk12;
	uint16_t unk21;
	uint16_t unk10;
	uint16_t unk11;
	uint16_t size_group_elements_info;
	type_group_elements_info group_elements_info;
} type_group_info;

typedef struct type_tab_extended_
{
	uint16_t unk_id1;
	uint16_t count_groupinfo;
	uint16_t unk2;
	uint8_t unk3;
	struct type_group_info_ *groupinfo;
} type_tab_extended;

typedef struct type_tab_
{
	uint16_t unk1;
	uint16_t unk2;
	uint8_t unk3a;
	uint8_t unk3b;
	uint16_t unk4;
	uint16_t unk5;
	uint8_t unk100;
	type_id id;
	uint8_t unk7a;
	uint16_t offset_ext;
	uint8_t unk8;
	uint8_t unk9;
	type_tab_extended ext;
} type_tab;

typedef struct type_unk1_extended_
{
	uint16_t unk_id1;
	uint16_t unk1;
	uint16_t unk2;
	uint16_t unk3;
	uint16_t unk4;
	uint16_t unk5;
	uint16_t unk6;
	uint16_t unk7;
	uint16_t unk8;
} type_unk1_extended;

typedef struct type_control_block2_number_
{
	type_id id;
} type_control_block2_number;

typedef struct type_control_block2_long_
{
	uint32_t unk1;
	uint8_t value1;
} type_control_block2_long;

typedef struct type_subcontrols_
{
	uint16_t count_subcontrols;
	struct type_control_ *subcontrols;
} type_subcontrols;

typedef struct type_control_block2_
{
	uint8_t meta_type;
	uint8_t block_len;
	enum_control_block_type block_type;
	type_control_block2_number content_number;
	type_control_block2_long content_long;
	type_subcontrols content_subcontrols;
	int32_t id;
	int32_t is_subcomponents;
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
} type_control_block2;

typedef struct type_control_blocks2_
{
	uint8_t count_blocks;
	struct type_control_block2_ *blocks;
} type_control_blocks2;

typedef struct type_control_
{
	uint16_t unk1;
	enum_type_control block_type;
	uint8_t unk2;
	uint16_t size_block;
	type_control_blocks2 block;
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
	type_ribbon ribbon;
} application_views;

typedef struct quick_ribbon_button_
{
	uint16_t unk1;
	uint16_t unk2;
	uint16_t unk3;
	uint16_t unk4;
	uint16_t unk5;
	uint8_t unk100;
	type_id id;
	uint16_t unk7;
	uint16_t unk8;
	uint16_t unk9;
} quick_ribbon_button;

typedef struct quick_ribbon_
{
	uint16_t unk1;
	uint8_t unk2;
	uint8_t unk100;
	type_id id;
	uint16_t unk3;
	uint8_t unk4;
	uint16_t unk5_len;
	struct quick_ribbon_button_ *entries;
} quick_ribbon;

typedef struct type_block_quickaccess_
{
	uint16_t unk1;
	uint16_t unk2;
	uint16_t len4;
	quick_ribbon quick_ribbon_info;
} type_block_quickaccess;

typedef struct type_block_generic_
{
	enum_block_type block_type;
	union
	{
		type_block_tabs block_ribbon_tabs;
		type_block_quickaccess block_ribbon_quickaccesstoolbar;
	};
} type_block_generic;

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
