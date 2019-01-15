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
	UIRIBBON_TYPE_CONTROL_DROPDOWNBUTTON = 20,
	UIRIBBON_TYPE_CONTROL_CHECKBOX = 6,
	UIRIBBON_TYPE_CONTROL_OTHERINFO = 25,
	UIRIBBON_TYPE_CONTROL_COMBOBOX = 21,
	UIRIBBON_TYPE_CONTROL_SPLITBUTTON = 18,
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
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK4 = 4,
	UIRIBBON_CONTROL_BLOCK_TYPE_SUBCOMPONENTS = 24,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGEVISIBLE = 36,
	UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE = 37,
	UIRIBBON_CONTROL_BLOCK_TYPE_AUTOCOMPLETE_ENABLED = 93,
	UIRIBBON_CONTROL_BLOCK_TYPE_VERTICAL_RESIZE = 73,
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK1 = 70,
	UIRIBBON_CONTROL_BLOCK_TYPE_EDITABLE = 71,
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK3 = 87,
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK5 = 88,
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK6 = 63,
	UIRIBBON_CONTROL_BLOCK_TYPE_UNK7 = 68,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLORTEMPLATE = 110,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_CHIPSIZE = 111,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLUMNS = 112,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON = 116,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON = 117,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS = 115,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS = 114,
	UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS = 113,
} enum_control_block_type;

typedef struct type_id_
{
	uint8_t flag;
	uint32_t id;
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
	uint8_t priority_medium;
	uint8_t priority_small;
	uint8_t priority_popup;
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

typedef struct type_subcomponents_
{
	uint16_t count_elements;
	struct type_control_ *elements;
} type_subcomponents;

typedef struct type_control_block_subcomponents_real_
{
	uint16_t len_subcomponents;
	type_subcomponents subcomponents;
} type_control_block_subcomponents_real;

typedef struct type_control_block_subcomponents_
{
	uint8_t unk1;
	uint8_t unk2;
	type_control_block_subcomponents_real components;
	uint16_t unk3;
	uint8_t has_controls;
} type_control_block_subcomponents;

typedef struct type_control_block_sizedefinition_labelvisible_mixed_
{
	uint8_t unk1;
	enum_sizedefinition_labelvisible_mixed sizedefinition_labelvisible_mixed;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_sizedefinition_labelvisible_mixed;

typedef struct type_control_block_sizedefinition_imagesize_mixed_
{
	uint8_t unk1;
	enum_sizedefinition_imagesize_mixed sizedefinition_imagesize_mixed;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_sizedefinition_imagesize_mixed;

typedef struct type_control_block_sizedefinition_imagevisible_
{
	char *unk1;
	enum_sizedefinition_imagevisible sizedefinition_imagevisible;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_sizedefinition_imagevisible;

typedef struct type_control_block_sizedefinition_labelvisible_
{
	char *unk1;
	enum_sizedefinition_labelvisible sizedefinition_labelvisible;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_sizedefinition_labelvisible;

typedef struct type_control_block_sizedefinition_imagesize_
{
	char *unk1;
	enum_sizedefinition_imagesize sizedefinition_imagesize;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_sizedefinition_imagesize;

typedef struct type_control_block_unk4_
{
	uint32_t unk1;
} type_control_block_unk4;

typedef struct type_control_block_info4_
{
	uint8_t unk1;
	uint8_t value_bool;
	uint8_t unk2;
	uint8_t unk3;
} type_control_block_info4;

typedef struct type_control_block_info7_
{
	uint32_t unk1;
	uint8_t value_bool;
	uint8_t unk2;
	uint8_t unk3;
} type_control_block_info7;

typedef struct type_control_block_dropdowncolorpicker_colortemplate_
{
	uint8_t unk1;
	enum_dropdowncolorpicker_colortemplate value;
	uint8_t unk2;
	uint8_t unk3;
} type_control_block_dropdowncolorpicker_colortemplate;

typedef struct type_control_block_dropdowncolorpicker_chipsize_
{
	uint8_t unk1;
	enum_dropdowncolorpicker_chipsize value;
	uint8_t unk2;
	uint8_t unk3;
} type_control_block_dropdowncolorpicker_chipsize;

typedef struct type_control_block_number_
{
	type_id number;
	uint8_t unk1;
	uint8_t unk2;
} type_control_block_number;

typedef struct type_control_block_generic_
{
	enum_control_block_type block_type;
	union
	{
		type_id block_id;
		type_control_block_sizedefinition_labelvisible_mixed block_sizedefinition_labelvisible_mixed;
		type_control_block_sizedefinition_imagesize_mixed block_sizedefinition_imagesize_mixed;
		type_control_block_sizedefinition_labelvisible block_sizedefinition_labelvisible;
		type_control_block_subcomponents block_subcomponents;
		type_control_block_sizedefinition_imagevisible block_sizedefinition_imagevisible;
		type_control_block_sizedefinition_imagesize block_sizedefinition_imagesize;
		type_control_block_unk4 block_unk1;
		type_control_block_unk4 block_editable;
		type_control_block_unk4 block_unk3;
		type_control_block_unk4 block_unk5;
		type_control_block_info7 block_autocomplete_enabled;
		type_control_block_info4 block_vertical_resize;
		type_control_block_info7 block_unk6;
		type_control_block_dropdowncolorpicker_colortemplate block_dropdowncolorpicker_colortemplate;
		type_control_block_dropdowncolorpicker_chipsize block_dropdowncolorpicker_chipsize;
		type_control_block_number block_dropdowncolorpicker_columns;
		type_control_block_info7 block_dropdowncolorpicker_has_autocolor_button;
		type_control_block_info7 block_dropdowncolorpicker_has_nocolor_button;
		type_control_block_number block_dropdowncolorpicker_recent_color_rows;
		type_control_block_number block_dropdowncolorpicker_standard_color_rows;
		type_control_block_number block_dropdowncolorpicker_theme_color_rows;
	};
} type_control_block_generic;

typedef struct type_control_blocks_
{
	uint8_t count_blocks;
	uint16_t unk1;
	struct type_control_block_generic_ *blocks;
} type_control_blocks;

typedef struct type_control_
{
	uint16_t unk1;
	enum_type_control block_type;
	uint8_t unk2;
	uint16_t size_block;
	type_control_blocks block;
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
	uint8_t unk3b;
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
