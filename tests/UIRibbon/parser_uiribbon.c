/* This file is generated - Do not edit manually */

#include "parser_uiribbon.h"

int read_type_id(stream *s_root, stream *s, type_id *ret);
int read_type_string(stream *s_root, stream *s, type_string *ret);
int read_type_strings(stream *s_root, stream *s, type_strings *ret);
int read_type_resource_generic(stream *s_root, stream *s, type_resource_generic *ret);
int read_type_resource(stream *s_root, stream *s, type_resource *ret);
int read_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *ret);
int read_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *ret);
int read_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *ret);
int read_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *ret);
int read_type_subcontrols(stream *s_root, stream *s, type_subcontrols *ret);
int read_type_control_block_number(stream *s_root, stream *s, type_control_block_number *ret);
int read_type_control_block_special(stream *s_root, stream *s, type_control_block_special *ret);
int read_type_control_blocks(stream *s_root, stream *s, type_control_blocks *ret);
int read_type_block_inline(stream *s_root, stream *s, type_block_inline *ret);
int read_type_control_block(stream *s_root, stream *s, type_control_block *ret);
int read_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *ret);
int read_type_control(stream *s_root, stream *s, type_control *ret);
int read_type_menugroup_extended(stream *s_root, stream *s, type_menugroup_extended *ret);
int read_type_recent2(stream *s_root, stream *s, type_recent2 *ret);
int read_type_recent1(stream *s_root, stream *s, type_recent1 *ret);
int read_type_command_ext(stream *s_root, stream *s, type_command_ext *ret);
int read_application_views(stream *s_root, stream *s, application_views *ret);
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

int read_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *ret)
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

int read_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *ret)
{
	int i;

	CHECK(stream_read_uint16_t(s, &ret->count_commands));
	ret->commands = malloc(sizeof(type_sizedefinitions_order_command) * ret->count_commands);
	for (i = 0; i < ret->count_commands; i++)
	{
		CHECK(read_type_sizedefinitions_order_command(s_root, s, &ret->commands[i]));
	}
	return 0;
}

int read_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *ret)
{
	CHECK(read_type_id(s_root, s, &ret->id));
	return 0;
}

int read_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *ret)
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

int read_type_control_block_number(stream *s_root, stream *s, type_control_block_number *ret)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s, &ret->block_len));
	CHECK(stream_read_uint8_t(s, &block_type));
	ret->block_type = block_type;
	if (ret->block_len == 1)
	{
		CHECK(read_type_control_block_number_variable(s_root, s, &ret->content_number));
	}
	if (ret->block_len == 4)
	{
		CHECK(read_type_control_block_number_long(s_root, s, &ret->content_long));
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID)
	{
		ret->id = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED)
	{
		ret->sizedefinition_labelvisible_mixed = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE)
	{
		ret->sizedefinition_labelvisible = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE)
	{
		ret->sizedefinition_imagevisible = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE)
	{
		ret->sizedefinition_imagesize = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED)
	{
		ret->sizedefinition_imagesize_mixed = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED)
	{
		ret->autocomplete_enabled = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE)
	{
		ret->gallery_type = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE)
	{
		ret->dropdowncolorpicker_colortemplate = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE)
	{
		ret->dropdowncolorpicker_chipsize = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS)
	{
		ret->dropdowncolorpicker_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON)
	{
		ret->dropdowncolorpicker_has_autocolor_button = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON)
	{
		ret->dropdowncolorpicker_has_nocolor_button = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_recent_color_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_standard_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS)
	{
		ret->dropdowncolorpicker_theme_color_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		ret->gallery_elements_type = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS)
	{
		ret->gallery_has_large_items = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT)
	{
		ret->gallery_item_height = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH)
	{
		ret->gallery_item_width = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION)
	{
		ret->gallery_text_position = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT)
	{
		ret->gallery_menulayout = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER)
	{
		ret->gallery_gripper = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS)
	{
		ret->gallery_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS)
	{
		ret->gallery_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS)
	{
		ret->gallery_max_rows = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS)
	{
		ret->gallery_max_columns = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE)
	{
		ret->gallery_min_columns_large = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM)
	{
		ret->gallery_max_columns_medium = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM)
	{
		ret->gallery_min_columns_medium = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX)
	{
		ret->is_checkbox = ret->content_long.value1;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		ret->scalepolicy = ret->content_number.id.id;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		ret->scalepolicy_medium = ret->scalepolicy / 256;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		ret->scalepolicy_small = (ret->scalepolicy % 256) / 16;
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		ret->scalepolicy_popup = (ret->scalepolicy % 16) / 1;
	}
	return 0;
}

int read_type_control_block_special(stream *s_root, stream *s, type_control_block_special *ret)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s, &ret->block_len));
	CHECK(stream_read_uint8_t(s, &block_type));
	ret->block_type = block_type;
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_QUICKACCESS || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_HELP)
	{
		CHECK(read_type_subcontrols(s_root, s, &ret->content_subcontrols));
	}
	if (ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM || ret->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL)
	{
		CHECK(read_type_sizedefinition_order(s_root, s, &ret->sizedefinition_order));
	}
	return 0;
}

int read_type_control_blocks(stream *s_root, stream *s, type_control_blocks *ret)
{
	int i;

	CHECK(stream_read_uint8_t(s, &ret->count_blocks));
	ret->blocks = malloc(sizeof(type_control_block) * ret->count_blocks);
	for (i = 0; i < ret->count_blocks; i++)
	{
		CHECK(read_type_control_block(s_root, s, &ret->blocks[i]));
	}
	return 0;
}

int read_type_block_inline(stream *s_root, stream *s, type_block_inline *ret)
{
	stream substream_quick_ribbon_info;

	CHECK(stream_read_uint32_t(s, &ret->unk2));
	CHECK(stream_read_uint16_t(s, &ret->len4));
	CHECK(stream_make_substream(s, &substream_quick_ribbon_info, ret->len4 - 7));
	CHECK(read_type_control_blocks(s_root, &substream_quick_ribbon_info, &ret->quick_ribbon_info));
	return 0;
}

int read_type_control_block(stream *s_root, stream *s, type_control_block *ret)
{
	uint8_t meta_type;
	stream substream_instance_ext;

	CHECK(stream_read_uint8_t(s, &meta_type));
	ret->meta_type = meta_type;
	if (ret->meta_type == UIRIBBON_CONTROL_BLOCK_META_NUMBER)
	{
		CHECK(read_type_control_block_number(s_root, s, &ret->content_number));
	}
	if (ret->meta_type == UIRIBBON_CONTROL_BLOCK_META_SPECIAL)
	{
		CHECK(read_type_control_block_special(s_root, s, &ret->content_special));
	}
	if (ret->meta_type == UIRIBBON_CONTROL_BLOCK_META_INLINE)
	{
		CHECK(read_type_block_inline(s_root, s, &ret->block_inline));
	}
	if (ret->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		CHECK(stream_read_uint32_t(s, &ret->ext_pos));
	}
	if (ret->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		CHECK(stream_make_substream_instance(s_root, &substream_instance_ext, (ret->ext_pos), s_root->max - (ret->ext_pos)));
		ret->ext = malloc(sizeof(type_control_block_ext));
		CHECK(read_type_control_block_ext(s_root, &substream_instance_ext, ret->ext));
	}
	return 0;
}

int read_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *ret)
{
	CHECK(stream_read_uint16_t(s, &ret->len_ext));
	CHECK(read_type_control_block(s_root, s, &ret->block));
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
	CHECK(read_type_control_blocks(s_root, &substream_block, &ret->block));
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
	CHECK(read_type_control_blocks(s_root, &substream_ribbon, &ret->ribbon));
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

