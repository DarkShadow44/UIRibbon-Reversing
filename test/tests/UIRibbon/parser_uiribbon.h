#include "parser_generic.h"

typedef enum
{
	BLOCK_TYPE_RIBBON_TABS = 24,
	BLOCK_TYPE_RIBBON_QUICKACCESSTOOLBAR = 22,
} enum_block_type;

typedef enum
{
	RESOURCE_TYPE_LABELTITLE = 1,
	RESOURCE_TYPE_LABELDESCRIPTION = 2,
	RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE = 3,
	RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE = 4,
	RESOURCE_TYPE_SMALLIMAGE = 5,
	RESOURCE_TYPE_LARGEIMAGE = 6,
	RESOURCE_TYPE_KEYTIP = 7,
	RESOURCE_TYPE_TOOLTIPTITLE = 8,
	RESOURCE_TYPE_TOOLTIPDESCRIPTION = 9,
} enum_resource_type;

typedef enum
{
	TAB_TYPE_APPLICATIONMENU = 0,
	TAB_TYPE_NORMAL = 2,
	TAB_TYPE_CONTEXT = 3,
	TAB_TYPE_HELP = 5,
} enum_tab_type;

typedef enum
{
	SIZEDEFINITIONS_COMMAND_COMMAND = 3,
	SIZEDEFINITIONS_COMMAND_NEWLINE = 9,
} enum_sizedefinitions_command;

typedef enum
{
	SIZEDEFINITIONS_COMMAND_NEWLINE_ROWBREAK = 1,
	SIZEDEFINITIONS_COMMAND_NEWLINE_COLUMBREAK_WITH_SEPARATOR = 2,
	SIZEDEFINITIONS_COMMAND_NEWLINE_COLUMBREAK_WITHOUT_SEPARATOR = 3,
} enum_sizedefinitions_command_newline;

typedef enum
{
	TYPE_CONTROL_BUTTON = 15,
	TYPE_CONTROL_DROPDOWNBUTTON = 20,
	TYPE_CONTROL_CHECKBOX = 6,
	TYPE_CONTROL_OTHERINFO = 25,
	TYPE_CONTROL_COMBOBOX = 21,
	TYPE_CONTROL_SPLITBUTTON = 18,
} enum_type_control;

typedef enum
{
	SIZEDEFINITION_IMAGESIZE_SMALL = 0,
	SIZEDEFINITION_IMAGESIZE_LARGE = 1,
} enum_sizedefinition_imagesize;

typedef enum
{
	SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLISSMALL = 2,
	SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLANDMEDIUMARESMALL = 3,
} enum_sizedefinition_imagesize_override;

typedef struct
{
	uint16_t size_str;
	char *str;
} type_string;

typedef struct
{
	uint8_t count_strings;
	type_string *strings;
} type_strings;

typedef struct
{
	enum_resource_type resource_type;
	uint32_t resource_id;
	uint16_t mindpi;
} type_resource_generic;

typedef struct
{
	uint32_t command_id;
	uint8_t count_resources;
	type_resource_generic *resources;
} type_resource;

typedef struct
{
	uint16_t unk1;
	uint16_t unk2;
	uint8_t unk3a;
	uint8_t unk3b;
	uint16_t unk4;
	uint16_t unk5;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
	uint8_t unk7a;
	uint16_t unk7b;
	uint8_t unk8;
	uint8_t unk9;
} type_tab;

typedef struct
{
	uint16_t unk1;
	uint16_t unk2;
	uint8_t unk3a;
	uint8_t unk3b;
	uint16_t unk4;
	uint16_t unk5;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
	uint8_t unk7;
	uint16_t unk8;
	uint16_t len_tabs;
	type_tab *tabs;
} type_tab_context;

typedef struct
{
	uint16_t count_tabs;
	type_tab *tabs;
} type_ribbon_tabs_normal;

typedef struct
{
	uint16_t count_tabs;
	type_tab_context *tabs;
} type_ribbon_tabs_context;

typedef struct
{
	uint8_t unk2;
	uint16_t unk3;
	uint16_t unk4;
	uint16_t unk5;
	uint16_t unk6;
	uint8_t unk7;
	uint16_t unk8;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
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

typedef struct
{
	uint8_t unk1a;
	enum_tab_type tab_type;
	union
	{
		type_ribbon_tabs_normal block_normal;
		type_ribbon_tabs_context block_context;
		type_ribbon_tabs_applicationmenu block_applicationmenu;
	};
} type_block_tabs;

typedef struct
{
	char *rest;
} block_unk1;

typedef struct
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
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
	uint8_t unk11;
} type_sizeinfo_maybe;

typedef struct
{
	uint8_t unk1;
	enum_sizedefinitions_command flags_command;
	enum_sizedefinitions_command_newline unk2;
	uint16_t command_id;
} type_sizedefinitions_command;

typedef struct
{
	uint16_t unk1;
	uint8_t unk2;
	type_sizedefinitions_command *commands;
} type_sizedefinition;

typedef struct
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

typedef struct
{
	uint16_t count_elements;
} type_control_block_subcomponents;

typedef struct
{
	uint8_t flag;
	union
	{
		uint16_t uint16_t;
		uint8_t uint8_t;
	};
} type_control_block_id;

typedef struct
{
	uint8_t unk1;
	uint8_t unk2;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_6;

typedef struct
{
	uint8_t unk1;
	enum_sizedefinition_imagesize_override sizedefinition_imagesize_override;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_maybe_sizedefinition_override_imagesize;

typedef struct
{
	char *unk1;
	uint8_t unk2;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_36;

typedef struct
{
	char *unk1;
	enum_sizedefinition_imagesize sizedefinition_imagesize;
	uint8_t unk3;
	uint8_t unk4;
} type_control_block_37;

typedef struct
{
	uint8_t block_type;
	union
	{
		type_control_block_id block_id;
		type_control_block_6 block_6;
		type_control_block_maybe_sizedefinition_override_imagesize block_imagesize;
		type_control_block_36 block_36;
		type_control_block_subcomponents block_subcomponents;
		type_control_block_37 block_37;
	};
} type_control_block_generic;

typedef struct
{
	uint8_t count_blocks;
	uint16_t unk1;
	type_control_block_generic *blocks;
} type_control_blocks;

typedef struct
{
	uint16_t unk1;
	enum_type_control block_type;
	uint8_t unk2;
	uint16_t size_block;
	type_control_blocks block;
} type_control;

typedef struct
{
	uint8_t unk10;
	uint16_t unk1b;
	uint8_t unk2;
	uint16_t unk1c;
	uint8_t unk1d;
	uint16_t sub_count;
	type_control *subcontents;
	type_sizedefinition sizedefinition_large;
	type_sizedefinition sizedefinition_medium;
	type_sizedefinition sizedefinition_small;
	uint8_t unk5;
} type_group_elements_info;

typedef struct
{
	uint16_t unk1;
	uint16_t len_unk1;
	uint16_t unk3;
	uint8_t unk4;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
	uint16_t unk20;
	uint16_t unk12;
	uint16_t unk21;
	uint16_t unk10;
	uint16_t unk11;
	uint16_t size_group_elements_info;
	type_group_elements_info group_elements_info;
} type_group_info;

typedef struct
{
	uint16_t unk_id1;
	uint16_t count_groupinfo;
	uint16_t unk2;
	uint8_t unk3;
	type_group_info *groupinfo;
} type_tab_extended;

typedef struct
{
	uint16_t unk1;
	uint16_t unk2;
	uint16_t unk3;
} type_control_otherinfo;

typedef struct
{
	uint16_t unk_id1;
	uint16_t menu_items_len;
	type_control *items;
	uint32_t unk1;
	uint32_t unk2;
	uint32_t unk3;
	uint16_t unk4;
} type_menugroup_extended;

typedef struct
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

typedef struct
{
	uint16_t unk_id1;
	uint16_t recent_len;
	type_recent2 *elements;
} type_recent1;

typedef struct
{
	uint16_t own_index_maybe;
	uint16_t unk0;
	uint16_t unk1a;
	uint16_t unk2;
	uint16_t command_id;
} type_command_ext;

typedef struct
{
	uint16_t unk1;
	uint16_t unk5;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
} quick_ribbon_button;

typedef struct
{
	uint16_t unk1;
	uint8_t unk2;
	uint16_t flags;
	uint8_t id_u1;
	uint16_t id_u2;
	uint16_t unk3;
	uint8_t unk4;
	uint16_t unk5_len;
	quick_ribbon_button *entries;
} quick_ribbon;

typedef struct
{
	uint16_t unk1;
	uint16_t unk2;
	uint16_t len4;
	quick_ribbon quick_ribbon_info;
} type_block_quickaccess;

typedef struct
{
	enum_block_type block_type;
	union
	{
		type_block_tabs block_tabs;
		type_block_quickaccess block_quickaccess;
	};
} type_block_generic;

typedef struct
{
	uint8_t unk0;
	type_block_generic *block1;
} type_ribbon;

typedef struct
{
	uint16_t ribbon_len;
	type_ribbon ribbon;
	type_tab_extended *ribbon_tab_info;
} application_views;

typedef struct
{
	uint16_t command_id;
	uint8_t unk3b;
	uint16_t size_str;
	char *str;
} type_command;

typedef struct
{
	uint32_t commands_len;
	type_command *commands;
} type_command_container;

typedef struct
{
	uint32_t length_this_file;
	uint16_t size_strings;
	type_strings strings;
	uint16_t count_command_resources;
	type_resource *command_resources;
	uint32_t size_command_container;
	type_command_container command_container;
	uint16_t len_unk6;
	uint16_t unk5;
	application_views unk6;
} type_uiribbon;

int read_type_uiribbon(stream *s, type_uiribbon *ret);
