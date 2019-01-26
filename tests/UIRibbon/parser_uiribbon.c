/* This file is generated - Do not edit manually */

#include "parser_uiribbon.h"

int read_type_id(stream *s_root, stream *s, type_id *ret);
int read_type_string(stream *s_root, stream *s, type_string *ret);
int read_type_strings(stream *s_root, stream *s, type_strings *ret);
int read_type_resource_generic(stream *s_root, stream *s, type_resource_generic *ret);
int read_type_resource(stream *s_root, stream *s, type_resource *ret);
int read_type_tabgroup(stream *s_root, stream *s, type_tabgroup *ret);
int read_type_ribbon_tabs_normal(stream *s_root, stream *s, type_ribbon_tabs_normal *ret);
int read_type_ribbon_tabs_context(stream *s_root, stream *s, type_ribbon_tabs_context *ret);
int read_type_ribbon_tabs_applicationmenu(stream *s_root, stream *s, type_ribbon_tabs_applicationmenu *ret);
int read_type_block_tabs(stream *s_root, stream *s, type_block_tabs *ret);
int read_type_ribbon(stream *s_root, stream *s, type_ribbon *ret);
int read_block_unk1(stream *s_root, stream *s, block_unk1 *ret);
int read_type_sizeinfo_maybe(stream *s_root, stream *s, type_sizeinfo_maybe *ret);
int read_type_sizedefinitions_command(stream *s_root, stream *s, type_sizedefinitions_command *ret);
int read_type_sizedefinition(stream *s_root, stream *s, type_sizedefinition *ret);
int read_type_group_elements_info(stream *s_root, stream *s, type_group_elements_info *ret);
int read_type_scalingpolicy(stream *s_root, stream *s, type_scalingpolicy *ret);
int read_type_group_info(stream *s_root, stream *s, type_group_info *ret);
int read_type_tab_extended(stream *s_root, stream *s, type_tab_extended *ret);
int read_type_tab(stream *s_root, stream *s, type_tab *ret);
int read_type_unk1_extended(stream *s_root, stream *s, type_unk1_extended *ret);
int read_type_control_block2_number(stream *s_root, stream *s, type_control_block2_number *ret);
int read_type_control_block2_long(stream *s_root, stream *s, type_control_block2_long *ret);
int read_type_subcontrols(stream *s_root, stream *s, type_subcontrols *ret);
int read_type_control_block2(stream *s_root, stream *s, type_control_block2 *ret);
int read_type_control_blocks2(stream *s_root, stream *s, type_control_blocks2 *ret);
int read_type_control(stream *s_root, stream *s, type_control *ret);
int read_type_menugroup_extended(stream *s_root, stream *s, type_menugroup_extended *ret);
int read_type_recent2(stream *s_root, stream *s, type_recent2 *ret);
int read_type_recent1(stream *s_root, stream *s, type_recent1 *ret);
int read_type_command_ext(stream *s_root, stream *s, type_command_ext *ret);
int read_application_views(stream *s_root, stream *s, application_views *ret);
int read_quick_ribbon_button(stream *s_root, stream *s, quick_ribbon_button *ret);
int read_quick_ribbon(stream *s_root, stream *s, quick_ribbon *ret);
int read_type_block_quickaccess(stream *s_root, stream *s, type_block_quickaccess *ret);
int read_type_block_generic(stream *s_root, stream *s, type_block_generic *ret);
int read_type_command(stream *s_root, stream *s, type_command *ret);
int read_type_command_container(stream *s_root, stream *s, type_command_container *ret);

int read_type_id(stream *s_root, stream *s, type_id *ret)
{
	int32_t id_block_2;
	int16_t id_block_3;
	int8_t id_block_4;
	int8_t id_block_9;
	int8_t id_block_43;

	CHECK(stream_read_uint8_t(s, &ret->flag));
	switch(ret->flag)
	{
	case 2:
		CHECK(stream_read_int32_t(s, &id_block_2));
		ret->id = id_block_2;
		break;
	case 3:
		CHECK(stream_read_int16_t(s, &id_block_3));
		ret->id = id_block_3;
		break;
	case 4:
		CHECK(stream_read_int8_t(s, &id_block_4));
		ret->id = id_block_4;
		break;
	case 9:
		CHECK(stream_read_int8_t(s, &id_block_9));
		ret->id = id_block_9;
		break;
	case 43:
		CHECK(stream_read_int8_t(s, &id_block_43));
		ret->id = id_block_43;
		break;
	}
	return 0;
}

int read_type_string(stream *s_root, stream *s, type_string *ret)
{
	const char unk1[] = {1};

	CHECK(stream_expect_bytes(s, unk1));
	CHECK(stream_read_uint16_t(s, &ret->size_str));
	ret->str = malloc(ret->size_str);
	CHECK(stream_read_bytes(s, ret->str, ret->size_str));
	return 0;
}

int read_type_strings(stream *s_root, stream *s, type_strings *ret)
{
	const char unk1[] = {0, 0, 1};
	int i;

	CHECK(stream_expect_bytes(s, unk1));
	CHECK(stream_read_uint8_t(s, &ret->count_strings));
	ret->strings = malloc(sizeof(type_string) * ret->count_strings);
	for (i = 0; i < ret->count_strings; i++)
	{
		CHECK(read_type_string(s_root, s, &ret->strings[i]));
	}
	return 0;
}

int read_type_resource_generic(stream *s_root, stream *s, type_resource_generic *ret)
{
	uint8_t resource_type;

	CHECK(stream_read_uint8_t(s, &resource_type));
	ret->resource_type = resource_type;
	CHECK(stream_read_uint32_t(s, &ret->resource_id));
	if (ret->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEIMAGE || ret->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLIMAGE || ret->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE || ret->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE)
	{
		CHECK(stream_read_uint16_t(s, &ret->mindpi));
	}
	return 0;
}

int read_type_resource(stream *s_root, stream *s, type_resource *ret)
{
	int i;

	CHECK(stream_read_uint32_t(s, &ret->command_id));
	CHECK(stream_read_uint8_t(s, &ret->count_resources));
	ret->resources = malloc(sizeof(type_resource_generic) * ret->count_resources);
	for (i = 0; i < ret->count_resources; i++)
	{
		CHECK(read_type_resource_generic(s_root, s, &ret->resources[i]));
	}
	return 0;
}

int read_type_tabgroup(stream *s_root, stream *s, type_tabgroup *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3a));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint8_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	CHECK(stream_read_uint16_t(s, &ret->count_tabs));
	ret->tabs = malloc(sizeof(type_tab) * ret->count_tabs);
	for (i = 0; i < ret->count_tabs; i++)
	{
		CHECK(read_type_tab(s_root, s, &ret->tabs[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_normal(stream *s_root, stream *s, type_ribbon_tabs_normal *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_tabs));
	ret->tabs = malloc(sizeof(type_tab) * ret->count_tabs);
	for (i = 0; i < ret->count_tabs; i++)
	{
		CHECK(read_type_tab(s_root, s, &ret->tabs[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_context(stream *s_root, stream *s, type_ribbon_tabs_context *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_tabgroups));
	ret->tabgroups = malloc(sizeof(type_tabgroup) * ret->count_tabgroups);
	for (i = 0; i < ret->count_tabgroups; i++)
	{
		CHECK(read_type_tabgroup(s_root, s, &ret->tabgroups[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_applicationmenu(stream *s_root, stream *s, type_ribbon_tabs_applicationmenu *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->unk6));
	CHECK(stream_read_uint8_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint16_t(s, &ret->unk11));
	CHECK(stream_read_uint16_t(s, &ret->unk12));
	CHECK(stream_read_uint16_t(s, &ret->unk13));
	CHECK(stream_read_uint16_t(s, &ret->unk14));
	CHECK(stream_read_uint8_t(s, &ret->unk15));
	ret->unk16 = malloc(5);
	CHECK(stream_read_bytes(s, ret->unk16, 5));
	CHECK(stream_read_uint32_t(s, &ret->unk17));
	ret->unk18 = malloc(1);
	CHECK(stream_read_bytes(s, ret->unk18, 1));
	CHECK(stream_read_uint32_t(s, &ret->unk19));
	ret->unk20 = malloc(1);
	CHECK(stream_read_bytes(s, ret->unk20, 1));
	CHECK(stream_read_uint32_t(s, &ret->unk21));
	return 0;
}

int read_type_block_tabs(stream *s_root, stream *s, type_block_tabs *ret)
{
	uint8_t tab_type;

	CHECK(stream_read_uint8_t(s, &ret->unk1a));
	CHECK(stream_read_uint8_t(s, &tab_type));
	ret->tab_type = tab_type;
	switch(ret->tab_type)
	{
	case UIRIBBON_TAB_TYPE_HELP:
		CHECK(read_type_ribbon_tabs_normal(s_root, s, &ret->block_help));
		break;
	case UIRIBBON_TAB_TYPE_NORMAL:
		CHECK(read_type_ribbon_tabs_normal(s_root, s, &ret->block_normal));
		break;
	case UIRIBBON_TAB_TYPE_CONTEXT:
		CHECK(read_type_ribbon_tabs_context(s_root, s, &ret->block_context));
		break;
	case UIRIBBON_TAB_TYPE_APPLICATIONMENU:
		CHECK(read_type_ribbon_tabs_applicationmenu(s_root, s, &ret->block_applicationmenu));
		break;
	}
	return 0;
}

int read_type_ribbon(stream *s_root, stream *s, type_ribbon *ret)
{
	const char unk1[] = {1, 1, 11, 9, 0};
	int i;

	CHECK(stream_read_uint8_t(s, &ret->count_blocks));
	CHECK(stream_expect_bytes(s, unk1));
	ret->block1 = malloc(sizeof(type_block_generic) * ret->count_blocks);
	for (i = 0; i < ret->count_blocks; i++)
	{
		CHECK(read_type_block_generic(s_root, s, &ret->block1[i]));
	}
	return 0;
}

int read_block_unk1(stream *s_root, stream *s, block_unk1 *ret)
{
	ret->rest = malloc(10);
	CHECK(stream_read_bytes(s, ret->rest, 10));
	return 0;
}

int read_type_sizeinfo_maybe(stream *s_root, stream *s, type_sizeinfo_maybe *ret)
{
	const char check1[] = {1, 4, 37, 0, 128, 65, 5};

	CHECK(stream_read_uint8_t(s, &ret->unk0));
	CHECK(stream_expect_bytes(s, check1));
	CHECK(stream_read_uint16_t(s, &ret->unk0c));
	CHECK(stream_read_uint16_t(s, &ret->unk0b));
	CHECK(stream_read_uint8_t(s, &ret->unk2a));
	CHECK(stream_read_uint8_t(s, &ret->unk2b));
	CHECK(stream_read_uint8_t(s, &ret->unk2c));
	CHECK(stream_read_uint8_t(s, &ret->unk1));
	if (ret->unk1 == 4)
	{
		ret->unk1e1 = malloc(3);
		CHECK(stream_read_bytes(s, ret->unk1e1, 3));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	CHECK(stream_read_uint8_t(s, &ret->unk5));
	CHECK(stream_read_uint8_t(s, &ret->unk6));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint8_t(s, &ret->unk11));
	return 0;
}

int read_type_sizedefinitions_command(stream *s_root, stream *s, type_sizedefinitions_command *ret)
{
	uint8_t flags_command;

	CHECK(stream_read_uint8_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &flags_command));
	ret->flags_command = flags_command;
	if (ret->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_SPECIAL)
	{
		CHECK(stream_read_uint8_t(s, &ret->string_id));
	}
	if (ret->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND)
	{
		CHECK(stream_read_uint16_t(s, &ret->command_id));
	}
	return 0;
}

int read_type_sizedefinition(stream *s_root, stream *s, type_sizedefinition *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->count_commands));
	ret->commands = malloc(sizeof(type_sizedefinitions_command) * ret->count_commands);
	for (i = 0; i < ret->count_commands; i++)
	{
		CHECK(read_type_sizedefinitions_command(s_root, s, &ret->commands[i]));
	}
	return 0;
}

int read_type_group_elements_info(stream *s_root, stream *s, type_group_elements_info *ret)
{
	const char check2b[] = {1, 1};
	const char check2c[] = {1, 4, 66, 0, 64, 68, 5, 0};
	int i;

	CHECK(stream_read_uint8_t(s, &ret->unk10));
	CHECK(stream_expect_bytes(s, check2b));
	CHECK(stream_read_uint16_t(s, &ret->unk1b));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	if (ret->unk10 == 3 && ret->unk2 == 9)
	{
		CHECK(stream_expect_bytes(s, check2c));
	}
	CHECK(stream_read_uint16_t(s, &ret->unk1c));
	CHECK(stream_read_uint8_t(s, &ret->unk1d));
	CHECK(stream_read_uint16_t(s, &ret->sub_count));
	ret->subcontents = malloc(sizeof(type_control) * ret->sub_count);
	for (i = 0; i < ret->sub_count; i++)
	{
		CHECK(read_type_control(s_root, s, &ret->subcontents[i]));
	}
	if (ret->unk10 == 5)
	{
		CHECK(read_type_sizedefinition(s_root, s, &ret->sizedefinition_large));
	}
	if (ret->unk10 == 5)
	{
		CHECK(read_type_sizedefinition(s_root, s, &ret->sizedefinition_medium));
	}
	if (ret->unk10 == 5)
	{
		CHECK(read_type_sizedefinition(s_root, s, &ret->sizedefinition_small));
	}
	ret->unk6 = malloc(3);
	CHECK(stream_read_bytes(s, ret->unk6, 3));
	return 0;
}

int read_type_scalingpolicy(stream *s_root, stream *s, type_scalingpolicy *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->unk1a));
	CHECK(stream_read_uint8_t(s, &ret->unk1b));
	CHECK(read_type_id(s_root, s, &ret->scale_value));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	ret->priority_medium = ret->scale_value.id / 256;
	ret->priority_small = (ret->scale_value.id % 256) / 16;
	ret->priority_popup = (ret->scale_value.id % 16) / 1;
	return 0;
}

int read_type_group_info(stream *s_root, stream *s, type_group_info *ret)
{
	stream substream_group_elements_info;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->len_unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint8_t(s, &ret->unk20a));
	if (ret->unk20a == 1)
	{
		CHECK(read_type_scalingpolicy(s_root, s, &ret->scalingpolicy));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk20b));
	CHECK(stream_read_uint16_t(s, &ret->unk12));
	CHECK(stream_read_uint16_t(s, &ret->unk21));
	CHECK(stream_read_uint16_t(s, &ret->unk10));
	CHECK(stream_read_uint16_t(s, &ret->unk11));
	CHECK(stream_read_uint16_t(s, &ret->size_group_elements_info));
	CHECK(stream_make_substream(s, &substream_group_elements_info, ret->size_group_elements_info - 4));
	CHECK(read_type_group_elements_info(s_root, &substream_group_elements_info, &ret->group_elements_info));
	return 0;
}

int read_type_tab_extended(stream *s_root, stream *s, type_tab_extended *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->count_groupinfo));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	ret->groupinfo = malloc(sizeof(type_group_info) * ret->count_groupinfo);
	for (i = 0; i < ret->count_groupinfo; i++)
	{
		CHECK(read_type_group_info(s_root, s, &ret->groupinfo[i]));
	}
	return 0;
}

int read_type_tab(stream *s_root, stream *s, type_tab *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3a));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint8_t(s, &ret->unk7a));
	CHECK(stream_read_uint16_t(s, &ret->offset_ext));
	CHECK(stream_read_uint8_t(s, &ret->unk8));
	CHECK(stream_read_uint8_t(s, &ret->unk9));
	CHECK(read_type_tab_extended(s_root, s_root, &ret->ext));
	return 0;
}

int read_type_unk1_extended(stream *s_root, stream *s, type_unk1_extended *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->unk6));
	CHECK(stream_read_uint16_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	return 0;
}

int read_type_control_block2_number(stream *s_root, stream *s, type_control_block2_number *ret)
{
	CHECK(read_type_id(s_root, s, &ret->id));
	return 0;
}

int read_type_control_block2_long(stream *s_root, stream *s, type_control_block2_long *ret)
{
	CHECK(stream_read_uint32_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->value1));
	return 0;
}

int read_type_subcontrols(stream *s_root, stream *s, type_subcontrols *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_subcontrols));
	ret->subcontrols = malloc(sizeof(type_control) * ret->count_subcontrols);
	for (i = 0; i < ret->count_subcontrols; i++)
	{
		CHECK(read_type_control(s_root, s, &ret->subcontrols[i]));
	}
	return 0;
}

int read_type_control_block2(stream *s_root, stream *s, type_control_block2 *ret)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s, &ret->meta_type));
	CHECK(stream_read_uint8_t(s, &ret->block_len));
	CHECK(stream_read_uint8_t(s, &block_type));
	ret->block_type = block_type;
	if (ret->meta_type == 1 && ret->block_len == 1)
	{
		CHECK(read_type_control_block2_number(s_root, s, &ret->content_number));
	}
	if (ret->meta_type == 1 && ret->block_len == 4)
	{
		CHECK(read_type_control_block2_long(s_root, s, &ret->content_long));
	}
	if (ret->meta_type == 24)
	{
		CHECK(read_type_subcontrols(s_root, s, &ret->content_subcontrols));
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_ID)
	{
		ret->id = ret->content_number.id.id;
	}
	ret->is_subcomponents = ret->meta_type == 24;
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE_MIXED)
	{
		ret->sizedefinition_labelvisible_mixed = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE)
	{
		ret->sizedefinition_labelvisible = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGEVISIBLE)
	{
		ret->sizedefinition_imagevisible = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE)
	{
		ret->sizedefinition_imagesize = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE_MIXED)
	{
		ret->sizedefinition_imagesize_mixed = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_AUTOCOMPLETE_ENABLED)
	{
		ret->autocomplete_enabled = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_TYPE)
	{
		ret->gallery_type = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLORTEMPLATE)
	{
		ret->dropdowncolorpicker_colortemplate = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_CHIPSIZE)
	{
		ret->dropdowncolorpicker_chipsize = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_COLUMNS)
	{
		ret->dropdowncolorpicker_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON)
	{
		ret->dropdowncolorpicker_has_autocolor_button = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON)
	{
		ret->dropdowncolorpicker_has_nocolor_button = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_recent_color_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_standard_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_theme_color_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ELEMENTS_TYPE)
	{
		ret->gallery_elements_type = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_HAS_LARGE_ITEMS)
	{
		ret->gallery_has_large_items = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ITEM_HEIGHT)
	{
		ret->gallery_item_height = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ITEM_WIDTH)
	{
		ret->gallery_item_width = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_TEXT_POSITION)
	{
		ret->gallery_text_position = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MENULAYOUT)
	{
		ret->gallery_menulayout = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_GRIPPER)
	{
		ret->gallery_gripper = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_ROWS)
	{
		ret->gallery_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_COLUMNS)
	{
		ret->gallery_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_ROWS)
	{
		ret->gallery_max_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_COLUMNS)
	{
		ret->gallery_max_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MIN_COLUMNS_LARGE)
	{
		ret->gallery_min_columns_large = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MAX_COLUMNS_MEDIUM)
	{
		ret->gallery_max_columns_medium = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_GALLERY_MIN_COLUMNS_MEDIUM)
	{
		ret->gallery_min_columns_medium = ret->content_number.id.id;
	}
	return 0;
}

int read_type_control_blocks2(stream *s_root, stream *s, type_control_blocks2 *ret)
{
	int i;

	CHECK(stream_read_uint8_t(s, &ret->count_blocks));
	ret->blocks = malloc(sizeof(type_control_block2) * ret->count_blocks);
	for (i = 0; i < ret->count_blocks; i++)
	{
		CHECK(read_type_control_block2(s_root, s, &ret->blocks[i]));
	}
	return 0;
}

int read_type_control(stream *s_root, stream *s, type_control *ret)
{
	uint16_t block_type;
	stream substream_block;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &block_type));
	ret->block_type = block_type;
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->size_block));
	CHECK(stream_make_substream(s, &substream_block, ret->size_block - 7));
	CHECK(read_type_control_blocks2(s_root, &substream_block, &ret->block));
	return 0;
}

int read_type_menugroup_extended(stream *s_root, stream *s, type_menugroup_extended *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->menu_items_len));
	ret->items = malloc(sizeof(type_control) * ret->menu_items_len);
	for (i = 0; i < ret->menu_items_len; i++)
	{
		CHECK(read_type_control(s_root, s, &ret->items[i]));
	}
	CHECK(stream_read_uint32_t(s, &ret->unk1));
	CHECK(stream_read_uint32_t(s, &ret->unk2));
	CHECK(stream_read_uint32_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	return 0;
}

int read_type_recent2(stream *s_root, stream *s, type_recent2 *ret)
{
	CHECK(stream_read_uint32_t(s, &ret->unk1));
	CHECK(stream_read_uint32_t(s, &ret->unk2));
	CHECK(stream_read_uint32_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->own_index));
	CHECK(stream_read_uint8_t(s, &ret->unk4b));
	CHECK(stream_read_uint16_t(s, &ret->unk4c));
	CHECK(stream_read_uint32_t(s, &ret->unk5));
	CHECK(stream_read_uint32_t(s, &ret->unk6));
	CHECK(stream_read_uint32_t(s, &ret->unk7));
	CHECK(stream_read_uint32_t(s, &ret->unk8));
	CHECK(stream_read_uint32_t(s, &ret->unk9));
	CHECK(stream_read_uint8_t(s, &ret->unk10));
	return 0;
}

int read_type_recent1(stream *s_root, stream *s, type_recent1 *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->recent_len));
	ret->elements = malloc(sizeof(type_recent2) * ret->recent_len);
	for (i = 0; i < ret->recent_len; i++)
	{
		CHECK(read_type_recent2(s_root, s, &ret->elements[i]));
	}
	return 0;
}

int read_type_command_ext(stream *s_root, stream *s, type_command_ext *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->own_index_maybe));
	CHECK(stream_read_uint16_t(s, &ret->unk0));
	CHECK(stream_read_uint16_t(s, &ret->unk1a));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->command_id));
	return 0;
}

int read_application_views(stream *s_root, stream *s, application_views *ret)
{
	const char unk20[] = {0, 0, 22, 0, 36, 0, 16};
	stream substream_ribbon;

	CHECK(stream_expect_bytes(s, unk20));
	CHECK(stream_read_uint16_t(s, &ret->ribbon_len));
	CHECK(stream_make_substream(s, &substream_ribbon, ret->ribbon_len));
	CHECK(read_type_ribbon(s_root, &substream_ribbon, &ret->ribbon));
	return 0;
}

int read_quick_ribbon_button(stream *s_root, stream *s, quick_ribbon_button *ret)
{
	const char unk6[] = {1, 4};

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_expect_bytes(s, unk6));
	CHECK(stream_read_uint16_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	CHECK(stream_read_uint16_t(s, &ret->unk9));
	return 0;
}

int read_quick_ribbon(stream *s_root, stream *s, quick_ribbon *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk100));
	CHECK(read_type_id(s_root, s, &ret->id));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5_len));
	ret->entries = malloc(sizeof(quick_ribbon_button) * ret->unk5_len);
	for (i = 0; i < ret->unk5_len; i++)
	{
		CHECK(read_quick_ribbon_button(s_root, s, &ret->entries[i]));
	}
	return 0;
}

int read_type_block_quickaccess(stream *s_root, stream *s, type_block_quickaccess *ret)
{
	stream substream_quick_ribbon_info;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->len4));
	CHECK(stream_make_substream(s, &substream_quick_ribbon_info, ret->len4 - 7));
	CHECK(read_quick_ribbon(s_root, &substream_quick_ribbon_info, &ret->quick_ribbon_info));
	return 0;
}

int read_type_block_generic(stream *s_root, stream *s, type_block_generic *ret)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s, &block_type));
	ret->block_type = block_type;
	switch(ret->block_type)
	{
	case UIRIBBON_BLOCK_TYPE_RIBBON_TABS:
		CHECK(read_type_block_tabs(s_root, s, &ret->block_ribbon_tabs));
		break;
	case UIRIBBON_BLOCK_TYPE_RIBBON_QUICKACCESSTOOLBAR:
		CHECK(read_type_block_quickaccess(s_root, s, &ret->block_ribbon_quickaccesstoolbar));
		break;
	}
	return 0;
}

int read_type_command(stream *s_root, stream *s, type_command *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->command_id));
	ret->unk1 = malloc(3);
	CHECK(stream_read_bytes(s, ret->unk1, 3));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	ret->unk4 = malloc(2);
	CHECK(stream_read_bytes(s, ret->unk4, 2));
	CHECK(stream_read_uint16_t(s, &ret->size_str));
	ret->str = malloc(ret->size_str);
	CHECK(stream_read_bytes(s, ret->str, ret->size_str));
	return 0;
}

int read_type_command_container(stream *s_root, stream *s, type_command_container *ret)
{
	int i;

	CHECK(stream_read_uint32_t(s, &ret->commands_len));
	ret->commands = malloc(sizeof(type_command) * ret->commands_len);
	for (i = 0; i < ret->commands_len; i++)
	{
		CHECK(read_type_command(s_root, s, &ret->commands[i]));
	}
	return 0;
}

int read_type_uiribbon(stream *s_root, stream *s, type_uiribbon *ret)
{
	const char unknown1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
	const char magic[] = {83, 67, 66, 105, 110};
	const char unknown2[] = {2};
	stream substream_strings;
	const char unknown3[] = {0, 0};
	const char unk44[] = {16};
	stream substream_command_container;
	int i;

	CHECK(stream_expect_bytes(s, unknown1));
	CHECK(stream_expect_bytes(s, magic));
	CHECK(stream_read_uint32_t(s, &ret->length_this_file));
	CHECK(stream_expect_bytes(s, unknown2));
	CHECK(stream_read_uint16_t(s, &ret->size_strings));
	CHECK(stream_make_substream(s, &substream_strings, ret->size_strings - 2));
	CHECK(read_type_strings(s_root, &substream_strings, &ret->strings));
	CHECK(stream_read_uint16_t(s, &ret->count_command_resources));
	CHECK(stream_expect_bytes(s, unknown3));
	ret->command_resources = malloc(sizeof(type_resource) * ret->count_command_resources);
	for (i = 0; i < ret->count_command_resources; i++)
	{
		CHECK(read_type_resource(s_root, s, &ret->command_resources[i]));
	}
	CHECK(stream_expect_bytes(s, unk44));
	CHECK(stream_read_uint32_t(s, &ret->size_command_container));
	CHECK(stream_make_substream(s, &substream_command_container, ret->size_command_container - 4));
	CHECK(read_type_command_container(s_root, &substream_command_container, &ret->command_container));
	CHECK(stream_read_uint16_t(s, &ret->len_unk6));
	CHECK(stream_read_uint16_t(s, &ret->unklen6));
	CHECK(read_application_views(s_root, s, &ret->unk6));
	return 0;
}

