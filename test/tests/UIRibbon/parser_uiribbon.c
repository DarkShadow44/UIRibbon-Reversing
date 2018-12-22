/* This file is generated - Do not edit manually */

#include "parser_uiribbon.h"

int read_type_string(stream *s, type_string *ret);
int read_type_strings(stream *s, type_strings *ret);
int read_type_resource_generic(stream *s, type_resource_generic *ret);
int read_type_resource(stream *s, type_resource *ret);
int read_type_tab(stream *s, type_tab *ret);
int read_type_tab_context(stream *s, type_tab_context *ret);
int read_type_ribbon_tabs_normal(stream *s, type_ribbon_tabs_normal *ret);
int read_type_ribbon_tabs_context(stream *s, type_ribbon_tabs_context *ret);
int read_type_ribbon_tabs_applicationmenu(stream *s, type_ribbon_tabs_applicationmenu *ret);
int read_type_block_tabs(stream *s, type_block_tabs *ret);
int read_block_unk1(stream *s, block_unk1 *ret);
int read_type_sizeinfo_maybe(stream *s, type_sizeinfo_maybe *ret);
int read_type_sizedefinitions_command(stream *s, type_sizedefinitions_command *ret);
int read_type_sizedefinition(stream *s, type_sizedefinition *ret);
int read_type_unk1_extended(stream *s, type_unk1_extended *ret);
int read_type_control_block_subcomponents(stream *s, type_control_block_subcomponents *ret);
int read_type_control_block_id(stream *s, type_control_block_id *ret);
int read_type_control_block_6(stream *s, type_control_block_6 *ret);
int read_type_control_block_maybe_sizedefinition_override_imagesize(stream *s, type_control_block_maybe_sizedefinition_override_imagesize *ret);
int read_type_control_block_36(stream *s, type_control_block_36 *ret);
int read_type_control_block_37(stream *s, type_control_block_37 *ret);
int read_type_control_block_generic(stream *s, type_control_block_generic *ret);
int read_type_control_blocks(stream *s, type_control_blocks *ret);
int read_type_control(stream *s, type_control *ret);
int read_type_group_elements_info(stream *s, type_group_elements_info *ret);
int read_type_group_info(stream *s, type_group_info *ret);
int read_type_tab_extended(stream *s, type_tab_extended *ret);
int read_type_control_otherinfo(stream *s, type_control_otherinfo *ret);
int read_type_menugroup_extended(stream *s, type_menugroup_extended *ret);
int read_type_recent2(stream *s, type_recent2 *ret);
int read_type_recent1(stream *s, type_recent1 *ret);
int read_type_command_ext(stream *s, type_command_ext *ret);
int read_quick_ribbon_button(stream *s, quick_ribbon_button *ret);
int read_quick_ribbon(stream *s, quick_ribbon *ret);
int read_type_block_quickaccess(stream *s, type_block_quickaccess *ret);
int read_type_block_generic(stream *s, type_block_generic *ret);
int read_type_ribbon(stream *s, type_ribbon *ret);
int read_application_views(stream *s, application_views *ret);
int read_type_command(stream *s, type_command *ret);
int read_type_command_container(stream *s, type_command_container *ret);

int read_type_string(stream *s, type_string *ret)
{
	const char unk1[] = {1};

	CHECK(stream_expect_bytes(s, unk1));
	CHECK(stream_read_uint16_t(s, &ret->size_str));
	CHECK(stream_read_bytes(s, &ret->str, ret->size_str));
	return 0;
}

int read_type_strings(stream *s, type_strings *ret)
{
	const char unk1[] = {0, 0, 1};
	int i;

	CHECK(stream_expect_bytes(s, unk1));
	CHECK(stream_read_uint8_t(s, &ret->count_strings));
	ret->strings = malloc(sizeof(type_string) * ret->count_strings);
	for (i = 0; i < ret->count_strings; i++)
	{
		CHECK(read_type_string(s, &ret->strings[i]));
	}
	return 0;
}

int read_type_resource_generic(stream *s, type_resource_generic *ret)
{
	uint8_t resource_type;

	CHECK(stream_read_uint8_t(s, &resource_type));
	ret->resource_type = resource_type;
	CHECK(stream_read_uint32_t(s, &ret->resource_id));
	if (ret->resource_type ==UIRIBBON_RESOURCE_TYPE_LARGEIMAGE ||ret->resource_type ==UIRIBBON_RESOURCE_TYPE_SMALLIMAGE ||ret->resource_type ==UIRIBBON_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE ||ret->resource_type ==UIRIBBON_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE)
	{
		CHECK(stream_read_uint16_t(s, &ret->mindpi));
	}
	return 0;
}

int read_type_resource(stream *s, type_resource *ret)
{
	int i;

	CHECK(stream_read_uint32_t(s, &ret->command_id));
	CHECK(stream_read_uint8_t(s, &ret->count_resources));
	ret->resources = malloc(sizeof(type_resource_generic) * ret->count_resources);
	for (i = 0; i < ret->count_resources; i++)
	{
		CHECK(read_type_resource_generic(s, &ret->resources[i]));
	}
	return 0;
}

int read_type_tab(stream *s, type_tab *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3a));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk7a));
	CHECK(stream_read_uint16_t(s, &ret->unk7b));
	CHECK(stream_read_uint8_t(s, &ret->unk8));
	CHECK(stream_read_uint8_t(s, &ret->unk9));
	return 0;
}

int read_type_tab_context(stream *s, type_tab_context *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3a));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	CHECK(stream_read_uint16_t(s, &ret->len_tabs));
	ret->tabs = malloc(sizeof(type_tab) * ret->len_tabs);
	for (i = 0; i < ret->len_tabs; i++)
	{
		CHECK(read_type_tab(s, &ret->tabs[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_normal(stream *s, type_ribbon_tabs_normal *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_tabs));
	ret->tabs = malloc(sizeof(type_tab) * ret->count_tabs);
	for (i = 0; i < ret->count_tabs; i++)
	{
		CHECK(read_type_tab(s, &ret->tabs[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_context(stream *s, type_ribbon_tabs_context *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_tabs));
	ret->tabs = malloc(sizeof(type_tab_context) * ret->count_tabs);
	for (i = 0; i < ret->count_tabs; i++)
	{
		CHECK(read_type_tab_context(s, &ret->tabs[i]));
	}
	return 0;
}

int read_type_ribbon_tabs_applicationmenu(stream *s, type_ribbon_tabs_applicationmenu *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->unk6));
	CHECK(stream_read_uint8_t(s, &ret->unk7));
	CHECK(stream_read_uint16_t(s, &ret->unk8));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint16_t(s, &ret->unk11));
	CHECK(stream_read_uint16_t(s, &ret->unk12));
	CHECK(stream_read_uint16_t(s, &ret->unk13));
	CHECK(stream_read_uint16_t(s, &ret->unk14));
	CHECK(stream_read_uint8_t(s, &ret->unk15));
	CHECK(stream_read_bytes(s, &ret->unk16, 5));
	CHECK(stream_read_uint32_t(s, &ret->unk17));
	CHECK(stream_read_bytes(s, &ret->unk18, 1));
	CHECK(stream_read_uint32_t(s, &ret->unk19));
	CHECK(stream_read_bytes(s, &ret->unk20, 1));
	CHECK(stream_read_uint32_t(s, &ret->unk21));
	return 0;
}

int read_type_block_tabs(stream *s, type_block_tabs *ret)
{
	uint8_t tab_type;

	CHECK(stream_read_uint8_t(s, &ret->unk1a));
	CHECK(stream_read_uint8_t(s, &tab_type));
	ret->tab_type = tab_type;
	switch(ret->tab_type)
	{
	case UIRIBBON_TAB_TYPE_HELP:
		CHECK(read_type_ribbon_tabs_normal(s, &ret->block_normal));
		break;
	case UIRIBBON_TAB_TYPE_NORMAL:
		CHECK(read_type_ribbon_tabs_normal(s, &ret->block_normal));
		break;
	case UIRIBBON_TAB_TYPE_CONTEXT:
		CHECK(read_type_ribbon_tabs_context(s, &ret->block_context));
		break;
	case UIRIBBON_TAB_TYPE_APPLICATIONMENU:
		CHECK(read_type_ribbon_tabs_applicationmenu(s, &ret->block_applicationmenu));
		break;
	}
	return 0;
}

int read_block_unk1(stream *s, block_unk1 *ret)
{
	CHECK(stream_read_bytes(s, &ret->rest, 10));
	return 0;
}

int read_type_sizeinfo_maybe(stream *s, type_sizeinfo_maybe *ret)
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
	if (ret->unk1 ==4)
	{
		CHECK(stream_read_bytes(s, &ret->unk1e1, 3));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	CHECK(stream_read_uint8_t(s, &ret->unk5));
	CHECK(stream_read_uint8_t(s, &ret->unk6));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk11));
	return 0;
}

int read_type_sizedefinitions_command(stream *s, type_sizedefinitions_command *ret)
{
	uint8_t flags_command;
	uint8_t unk2;

	CHECK(stream_read_uint8_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &flags_command));
	ret->flags_command = flags_command;
	if (ret->flags_command ==UIRIBBON_SIZEDEFINITIONS_COMMAND_NEWLINE)
	{
		CHECK(stream_read_uint8_t(s, &unk2));
		ret->unk2 = unk2;
	}
	if (ret->flags_command ==UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND)
	{
		CHECK(stream_read_uint16_t(s, &ret->command_id));
	}
	return 0;
}

int read_type_sizedefinition(stream *s, type_sizedefinition *ret)
{
	type_sizedefinitions_command *_until_temp_3;
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	ret->commands = NULL;
	i = 0;
	do
	{
		ret->commands = realloc(ret->commands, sizeof(type_sizedefinitions_command) * i);
		CHECK(read_type_sizedefinitions_command(s, &ret->commands[i]));
		_until_temp_3 = &ret->commands[i];
		i++;
	} while(!(_until_temp_3->unk1 ==24 ||_until_temp_3->unk1 ==22));
	return 0;
}

int read_type_unk1_extended(stream *s, type_unk1_extended *ret)
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

int read_type_control_block_subcomponents(stream *s, type_control_block_subcomponents *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->count_elements));
	return 0;
}

int read_type_control_block_id(stream *s, type_control_block_id *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->flag));
	switch(ret->flag)
	{
	case 3:
		CHECK(stream_read_uint16_t(s, &ret->uint16_t));
		break;
	case 4:
		CHECK(stream_read_uint8_t(s, &ret->uint8_t));
		break;
	}
	return 0;
}

int read_type_control_block_6(stream *s, type_control_block_6 *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	return 0;
}

int read_type_control_block_maybe_sizedefinition_override_imagesize(stream *s, type_control_block_maybe_sizedefinition_override_imagesize *ret)
{
	uint8_t sizedefinition_imagesize_override;

	CHECK(stream_read_uint8_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &sizedefinition_imagesize_override));
	ret->sizedefinition_imagesize_override = sizedefinition_imagesize_override;
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	return 0;
}

int read_type_control_block_36(stream *s, type_control_block_36 *ret)
{
	CHECK(stream_read_bytes(s, &ret->unk1, 4));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	return 0;
}

int read_type_control_block_37(stream *s, type_control_block_37 *ret)
{
	uint8_t sizedefinition_imagesize;

	CHECK(stream_read_bytes(s, &ret->unk1, 4));
	CHECK(stream_read_uint8_t(s, &sizedefinition_imagesize));
	ret->sizedefinition_imagesize = sizedefinition_imagesize;
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	return 0;
}

int read_type_control_block_generic(stream *s, type_control_block_generic *ret)
{
	CHECK(stream_read_uint8_t(s, &ret->block_type));
	switch(ret->block_type)
	{
	case 0:
		CHECK(read_type_control_block_id(s, &ret->block_id));
		break;
	case 6:
		CHECK(read_type_control_block_6(s, &ret->block_6));
		break;
	case 8:
		CHECK(read_type_control_block_maybe_sizedefinition_override_imagesize(s, &ret->block_imagesize));
		break;
	case 9:
		CHECK(read_type_control_block_36(s, &ret->block_36));
		break;
	case 24:
		CHECK(read_type_control_block_subcomponents(s, &ret->block_subcomponents));
		break;
	case 36:
		CHECK(read_type_control_block_36(s, &ret->block_36));
		break;
	case 37:
		CHECK(read_type_control_block_37(s, &ret->block_37));
		break;
	}
	return 0;
}

int read_type_control_blocks(stream *s, type_control_blocks *ret)
{
	int i;

	CHECK(stream_read_uint8_t(s, &ret->count_blocks));
	CHECK(stream_read_uint16_t(s, &ret->unk1));
	ret->blocks = malloc(sizeof(type_control_block_generic) * ret->count_blocks);
	for (i = 0; i < ret->count_blocks; i++)
	{
		CHECK(read_type_control_block_generic(s, &ret->blocks[i]));
	}
	return 0;
}

int read_type_control(stream *s, type_control *ret)
{
	uint16_t block_type;
	stream substream5;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &block_type));
	ret->block_type = block_type;
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->size_block));
	CHECK(stream_make_substream(s, &substream5, ret->size_block -7));
	CHECK(read_type_control_blocks(&substream5, &ret->block));
	return 0;
}

int read_type_group_elements_info(stream *s, type_group_elements_info *ret)
{
	const char check2b[] = {1, 1};
	const char check2c[] = {1, 4, 66, 0, 64, 68, 5, 0};
	int i;

	CHECK(stream_read_uint8_t(s, &ret->unk10));
	CHECK(stream_expect_bytes(s, check2b));
	CHECK(stream_read_uint16_t(s, &ret->unk1b));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	if (ret->unk10 ==3)
	{
		CHECK(stream_expect_bytes(s, check2c));
	}
	CHECK(stream_read_uint16_t(s, &ret->unk1c));
	CHECK(stream_read_uint8_t(s, &ret->unk1d));
	CHECK(stream_read_uint16_t(s, &ret->sub_count));
	ret->subcontents = malloc(sizeof(type_control) * ret->sub_count);
	for (i = 0; i < ret->sub_count; i++)
	{
		CHECK(read_type_control(s, &ret->subcontents[i]));
	}
	if (ret->unk10 ==5)
	{
		CHECK(read_type_sizedefinition(s, &ret->sizedefinition_large));
	}
	if (ret->unk10 ==5)
	{
		CHECK(read_type_sizedefinition(s, &ret->sizedefinition_medium));
	}
	if (ret->unk10 ==5)
	{
		CHECK(read_type_sizedefinition(s, &ret->sizedefinition_small));
	}
	CHECK(stream_read_uint8_t(s, &ret->unk5));
	return 0;
}

int read_type_group_info(stream *s, type_group_info *ret)
{
	stream substream14;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->len_unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint16_t(s, &ret->unk20));
	CHECK(stream_read_uint16_t(s, &ret->unk12));
	CHECK(stream_read_uint16_t(s, &ret->unk21));
	CHECK(stream_read_uint16_t(s, &ret->unk10));
	CHECK(stream_read_uint16_t(s, &ret->unk11));
	CHECK(stream_read_uint16_t(s, &ret->size_group_elements_info));
	CHECK(stream_make_substream(s, &substream14, ret->size_group_elements_info -4));
	CHECK(read_type_group_elements_info(&substream14, &ret->group_elements_info));
	return 0;
}

int read_type_tab_extended(stream *s, type_tab_extended *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->count_groupinfo));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint8_t(s, &ret->unk3));
	ret->groupinfo = malloc(sizeof(type_group_info) * ret->count_groupinfo);
	for (i = 0; i < ret->count_groupinfo; i++)
	{
		CHECK(read_type_group_info(s, &ret->groupinfo[i]));
	}
	return 0;
}

int read_type_control_otherinfo(stream *s, type_control_otherinfo *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	return 0;
}

int read_type_menugroup_extended(stream *s, type_menugroup_extended *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->menu_items_len));
	ret->items = malloc(sizeof(type_control) * ret->menu_items_len);
	for (i = 0; i < ret->menu_items_len; i++)
	{
		CHECK(read_type_control(s, &ret->items[i]));
	}
	CHECK(stream_read_uint32_t(s, &ret->unk1));
	CHECK(stream_read_uint32_t(s, &ret->unk2));
	CHECK(stream_read_uint32_t(s, &ret->unk3));
	CHECK(stream_read_uint16_t(s, &ret->unk4));
	return 0;
}

int read_type_recent2(stream *s, type_recent2 *ret)
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

int read_type_recent1(stream *s, type_recent1 *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk_id1));
	CHECK(stream_read_uint16_t(s, &ret->recent_len));
	ret->elements = malloc(sizeof(type_recent2) * ret->recent_len);
	for (i = 0; i < ret->recent_len; i++)
	{
		CHECK(read_type_recent2(s, &ret->elements[i]));
	}
	return 0;
}

int read_type_command_ext(stream *s, type_command_ext *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->own_index_maybe));
	CHECK(stream_read_uint16_t(s, &ret->unk0));
	CHECK(stream_read_uint16_t(s, &ret->unk1a));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->command_id));
	return 0;
}

int read_quick_ribbon_button(stream *s, quick_ribbon_button *ret)
{
	const char unk2[] = {15, 0};
	const char unk3[] = {16, 22};
	const char unk4[] = {0, 2};
	const char unk6[] = {1, 4};
	const char unk7[] = {10, 0};
	const char unk8[] = {192, 64};
	const char unk9[] = {5, 1};

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_expect_bytes(s, unk2));
	CHECK(stream_expect_bytes(s, unk3));
	CHECK(stream_expect_bytes(s, unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_expect_bytes(s, unk6));
	CHECK(stream_expect_bytes(s, unk7));
	CHECK(stream_expect_bytes(s, unk8));
	CHECK(stream_expect_bytes(s, unk9));
	return 0;
}

int read_quick_ribbon(stream *s, quick_ribbon *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->flags));
	if ((ret->flags &0x400) !=0)
	{
		CHECK(stream_read_uint8_t(s, &ret->id_u1));
	}
	if ((ret->flags &0x300) !=0)
	{
		CHECK(stream_read_uint16_t(s, &ret->id_u2));
	}
	CHECK(stream_read_uint16_t(s, &ret->unk3));
	CHECK(stream_read_uint8_t(s, &ret->unk4));
	CHECK(stream_read_uint16_t(s, &ret->unk5_len));
	ret->entries = malloc(sizeof(quick_ribbon_button) * ret->unk5_len);
	for (i = 0; i < ret->unk5_len; i++)
	{
		CHECK(read_quick_ribbon_button(s, &ret->entries[i]));
	}
	return 0;
}

int read_type_block_quickaccess(stream *s, type_block_quickaccess *ret)
{
	stream substream4;

	CHECK(stream_read_uint16_t(s, &ret->unk1));
	CHECK(stream_read_uint16_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->len4));
	CHECK(stream_make_substream(s, &substream4, ret->len4 -7));
	CHECK(read_quick_ribbon(&substream4, &ret->quick_ribbon_info));
	return 0;
}

int read_type_block_generic(stream *s, type_block_generic *ret)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s, &block_type));
	ret->block_type = block_type;
	switch(ret->block_type)
	{
	case UIRIBBON_BLOCK_TYPE_RIBBON_TABS:
		CHECK(read_type_block_tabs(s, &ret->block_tabs));
		break;
	case UIRIBBON_BLOCK_TYPE_RIBBON_QUICKACCESSTOOLBAR:
		CHECK(read_type_block_quickaccess(s, &ret->block_quickaccess));
		break;
	}
	return 0;
}

int read_type_ribbon(stream *s, type_ribbon *ret)
{
	const char unk1[] = {1, 1, 11, 9, 0};
	int i;

	CHECK(stream_read_uint8_t(s, &ret->unk0));
	CHECK(stream_expect_bytes(s, unk1));
	ret->block1 = malloc(sizeof(type_block_generic) * ret->unk0);
	for (i = 0; i < ret->unk0; i++)
	{
		CHECK(read_type_block_generic(s, &ret->block1[i]));
	}
	return 0;
}

int read_application_views(stream *s, application_views *ret)
{
	const char unk20[] = {0, 0, 22, 0, 36, 0, 16};
	stream substream3;
	int i;

	CHECK(stream_expect_bytes(s, unk20));
	CHECK(stream_read_uint16_t(s, &ret->ribbon_len));
	CHECK(stream_make_substream(s, &substream3, ret->ribbon_len));
	CHECK(read_type_ribbon(&substream3, &ret->ribbon));
	ret->ribbon_tab_info = malloc(sizeof(type_tab_extended) * 1);
	for (i = 0; i < 1; i++)
	{
		CHECK(read_type_tab_extended(s, &ret->ribbon_tab_info[i]));
	}
	return 0;
}

int read_type_command(stream *s, type_command *ret)
{
	const char unk1[] = {0, 0, 0};
	const char unk4[] = {0, 16};

	CHECK(stream_read_uint16_t(s, &ret->command_id));
	CHECK(stream_expect_bytes(s, unk1));
	CHECK(stream_read_uint8_t(s, &ret->unk3b));
	CHECK(stream_expect_bytes(s, unk4));
	CHECK(stream_read_uint16_t(s, &ret->size_str));
	CHECK(stream_read_bytes(s, &ret->str, ret->size_str));
	return 0;
}

int read_type_command_container(stream *s, type_command_container *ret)
{
	int i;

	CHECK(stream_read_uint32_t(s, &ret->commands_len));
	ret->commands = malloc(sizeof(type_command) * ret->commands_len);
	for (i = 0; i < ret->commands_len; i++)
	{
		CHECK(read_type_command(s, &ret->commands[i]));
	}
	return 0;
}

int read_type_uiribbon(stream *s, type_uiribbon *ret)
{
	const char unknown1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
	const char magic[] = {83, 67, 66, 105, 110};
	const char unknown2[] = {2};
	stream substream6;
	const char unknown3[] = {0, 0};
	const char unk44[] = {16};
	stream substream12;
	stream substream15;
	int i;

	CHECK(stream_expect_bytes(s, unknown1));
	CHECK(stream_expect_bytes(s, magic));
	CHECK(stream_read_uint32_t(s, &ret->length_this_file));
	CHECK(stream_expect_bytes(s, unknown2));
	CHECK(stream_read_uint16_t(s, &ret->size_strings));
	CHECK(stream_make_substream(s, &substream6, ret->size_strings -2));
	CHECK(read_type_strings(&substream6, &ret->strings));
	CHECK(stream_read_uint16_t(s, &ret->count_command_resources));
	CHECK(stream_expect_bytes(s, unknown3));
	ret->command_resources = malloc(sizeof(type_resource) * ret->count_command_resources);
	for (i = 0; i < ret->count_command_resources; i++)
	{
		CHECK(read_type_resource(s, &ret->command_resources[i]));
	}
	CHECK(stream_expect_bytes(s, unk44));
	CHECK(stream_read_uint32_t(s, &ret->size_command_container));
	CHECK(stream_make_substream(s, &substream12, ret->size_command_container -4));
	CHECK(read_type_command_container(&substream12, &ret->command_container));
	CHECK(stream_read_uint16_t(s, &ret->len_unk6));
	CHECK(stream_read_uint16_t(s, &ret->unk5));
	CHECK(stream_make_substream(s, &substream15, ret->unk5 -ret->count_command_resources *10 -200));
	CHECK(read_application_views(&substream15, &ret->unk6));
	return 0;
}

