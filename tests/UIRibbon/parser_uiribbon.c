/* This file is generated - Do not edit manually */

#include "parser_uiribbon.h"

int stream_read_type_id(stream *s_root, stream *s, type_id *data);
int stream_write_type_id(stream *s_root, stream *s, type_id *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_string(stream *s_root, stream *s, type_string *data);
int stream_write_type_string(stream *s_root, stream *s, type_string *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_strings(stream *s_root, stream *s, type_strings *data);
int stream_write_type_strings(stream *s_root, stream *s, type_strings *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_resource_generic(stream *s_root, stream *s, type_resource_generic *data);
int stream_write_type_resource_generic(stream *s_root, stream *s, type_resource_generic *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_resource(stream *s_root, stream *s, type_resource *data);
int stream_write_type_resource(stream *s_root, stream *s, type_resource *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *data);
int stream_write_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *data);
int stream_write_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *data);
int stream_write_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *data);
int stream_write_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_subcontrols(stream *s_root, stream *s, type_subcontrols *data);
int stream_write_type_subcontrols(stream *s_root, stream *s, type_subcontrols *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block_number(stream *s_root, stream *s, type_control_block_number *data);
int stream_write_type_control_block_number(stream *s_root, stream *s, type_control_block_number *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block_special(stream *s_root, stream *s, type_control_block_special *data);
int stream_write_type_control_block_special(stream *s_root, stream *s, type_control_block_special *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_blocks(stream *s_root, stream *s, type_control_blocks *data);
int stream_write_type_control_blocks(stream *s_root, stream *s, type_control_blocks *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_block_inline(stream *s_root, stream *s, type_block_inline *data);
int stream_write_type_block_inline(stream *s_root, stream *s, type_block_inline *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block(stream *s_root, stream *s, type_control_block *data);
int stream_write_type_control_block(stream *s_root, stream *s, type_control_block *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *data);
int stream_write_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_control(stream *s_root, stream *s, type_control *data);
int stream_write_type_control(stream *s_root, stream *s, type_control *data, stream_write_stage stage, BOOL from_instance);
int stream_read_application_views(stream *s_root, stream *s, application_views *data);
int stream_write_application_views(stream *s_root, stream *s, application_views *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command(stream *s_root, stream *s, type_command *data);
int stream_write_type_command(stream *s_root, stream *s, type_command *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command_container(stream *s_root, stream *s, type_command_container *data);
int stream_write_type_command_container(stream *s_root, stream *s, type_command_container *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command_ext5(stream *s_root, stream *s, type_command_ext5 *data);
int stream_write_type_command_ext5(stream *s_root, stream *s, type_command_ext5 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command_ext4(stream *s_root, stream *s, type_command_ext4 *data);
int stream_write_type_command_ext4(stream *s_root, stream *s, type_command_ext4 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command_ext3(stream *s_root, stream *s, type_command_ext3 *data);
int stream_write_type_command_ext3(stream *s_root, stream *s, type_command_ext3 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_command_ext2(stream *s_root, stream *s, type_command_ext2 *data);
int stream_write_type_command_ext2(stream *s_root, stream *s, type_command_ext2 *data, stream_write_stage stage, BOOL from_instance);

int stream_read_type_id(stream *s_root, stream *s, type_id *data)
{
	int32_t id_block_2;
	int16_t id_block_3;
	int8_t id_block_4;
	int8_t id_block_9;
	int8_t id_block_43;

	CHECK(stream_read_uint8_t(s_root, s, &data->flag));
	switch(data->flag)
	{
		case 2:
		{
			CHECK(stream_read_int32_t(s_root, s, &id_block_2));
			data->id = id_block_2;
			break;
		}
		case 3:
		{
			CHECK(stream_read_int16_t(s_root, s, &id_block_3));
			data->id = id_block_3;
			break;
		}
		case 4:
		{
			CHECK(stream_read_int8_t(s_root, s, &id_block_4));
			data->id = id_block_4;
			break;
		}
		case 9:
		{
			CHECK(stream_read_int8_t(s_root, s, &id_block_9));
			data->id = id_block_9;
			break;
		}
		case 43:
		{
			CHECK(stream_read_int8_t(s_root, s, &id_block_43));
			data->id = id_block_43;
			break;
		}
	}
	return 0;
}

int stream_write_type_id(stream *s_root, stream *s, type_id *data, stream_write_stage stage, BOOL from_instance)
{
	int32_t id_block_2;
	int16_t id_block_3;
	int8_t id_block_4;
	int8_t id_block_9;
	int8_t id_block_43;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint8_t(s_root, s, &data->flag, stage, from_instance));
	switch(data->flag)
	{
		case 2:
		{
			id_block_2 = data->id;
			CHECK(stream_write_int32_t(s_root, s, &id_block_2, stage, from_instance));
			break;
		}
		case 3:
		{
			id_block_3 = data->id;
			CHECK(stream_write_int16_t(s_root, s, &id_block_3, stage, from_instance));
			break;
		}
		case 4:
		{
			id_block_4 = data->id;
			CHECK(stream_write_int8_t(s_root, s, &id_block_4, stage, from_instance));
			break;
		}
		case 9:
		{
			id_block_9 = data->id;
			CHECK(stream_write_int8_t(s_root, s, &id_block_9, stage, from_instance));
			break;
		}
		case 43:
		{
			id_block_43 = data->id;
			CHECK(stream_write_int8_t(s_root, s, &id_block_43, stage, from_instance));
			break;
		}
	}
	return 0;
}

int stream_read_type_string(stream *s_root, stream *s, type_string *data)
{
	const char unk1[] = {1};

	CHECK(stream_read_expect_bytes(s, unk1));
	CHECK(stream_read_uint16_t(s_root, s, &data->size_str));
	data->str = malloc(data->size_str);
	CHECK(stream_read_bytes(s, data->str, data->size_str));
	return 0;
}

int stream_write_type_string(stream *s_root, stream *s, type_string *data, stream_write_stage stage, BOOL from_instance)
{
	const char unk1[] = {1};

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_bytes(s, unk1, sizeof(unk1), stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->size_str, stage, from_instance));
	CHECK(stream_write_bytes(s, data->str, data->size_str, stage, from_instance));
	return 0;
}

int stream_read_type_strings(stream *s_root, stream *s, type_strings *data)
{
	const char unk1[] = {0, 0, 1};
	int i;

	CHECK(stream_read_expect_bytes(s, unk1));
	CHECK(stream_read_uint8_t(s_root, s, &data->count_strings));
	data->strings = malloc(sizeof(type_string) * data->count_strings);
	for (i = 0; i < data->count_strings; i++)
	{
		CHECK(stream_read_type_string(s_root, s, &data->strings[i]));
	}
	return 0;
}

int stream_write_type_strings(stream *s_root, stream *s, type_strings *data, stream_write_stage stage, BOOL from_instance)
{
	const char unk1[] = {0, 0, 1};
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_bytes(s, unk1, sizeof(unk1), stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->count_strings, stage, from_instance));
	for (i = 0; i < data->count_strings; i++)
	{
		CHECK(stream_write_type_string(s_root, s, &data->strings[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_resource_generic(stream *s_root, stream *s, type_resource_generic *data)
{
	uint8_t resource_type;

	CHECK(stream_read_uint8_t(s_root, s, &resource_type));
	data->resource_type = resource_type;
	CHECK(stream_read_uint32_t(s_root, s, &data->resource_id));
	if (data->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE)
	{
		CHECK(stream_read_uint16_t(s_root, s, &data->mindpi));
	}
	return 0;
}

int stream_write_type_resource_generic(stream *s_root, stream *s, type_resource_generic *data, stream_write_stage stage, BOOL from_instance)
{
	uint8_t resource_type;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	resource_type = data->resource_type;
	CHECK(stream_write_uint8_t(s_root, s, &resource_type, stage, from_instance));
	CHECK(stream_write_uint32_t(s_root, s, &data->resource_id, stage, from_instance));
	if (data->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE || data->resource_type == UIRIBBON_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE)
	{
		CHECK(stream_write_uint16_t(s_root, s, &data->mindpi, stage, from_instance));
	}
	return 0;
}

int stream_read_type_resource(stream *s_root, stream *s, type_resource *data)
{
	int i;

	CHECK(stream_read_uint32_t(s_root, s, &data->command_id));
	CHECK(stream_read_uint8_t(s_root, s, &data->count_resources));
	data->resources = malloc(sizeof(type_resource_generic) * data->count_resources);
	for (i = 0; i < data->count_resources; i++)
	{
		CHECK(stream_read_type_resource_generic(s_root, s, &data->resources[i]));
	}
	return 0;
}

int stream_write_type_resource(stream *s_root, stream *s, type_resource *data, stream_write_stage stage, BOOL from_instance)
{
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint32_t(s_root, s, &data->command_id, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->count_resources, stage, from_instance));
	for (i = 0; i < data->count_resources; i++)
	{
		CHECK(stream_write_type_resource_generic(s_root, s, &data->resources[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *data)
{
	uint8_t flags_command;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint8_t(s_root, s, &flags_command));
	data->flags_command = flags_command;
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_SPECIAL)
	{
		CHECK(stream_read_uint8_t(s_root, s, &data->string_id));
	}
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND)
	{
		CHECK(stream_read_uint16_t(s_root, s, &data->command_id));
	}
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND_INTERNAL)
	{
		CHECK(stream_read_uint32_t(s_root, s, &data->unk2));
	}
	return 0;
}

int stream_write_type_sizedefinitions_order_command(stream *s_root, stream *s, type_sizedefinitions_order_command *data, stream_write_stage stage, BOOL from_instance)
{
	uint8_t flags_command;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	flags_command = data->flags_command;
	CHECK(stream_write_uint8_t(s_root, s, &flags_command, stage, from_instance));
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_SPECIAL)
	{
		CHECK(stream_write_uint8_t(s_root, s, &data->string_id, stage, from_instance));
	}
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND)
	{
		CHECK(stream_write_uint16_t(s_root, s, &data->command_id, stage, from_instance));
	}
	if (data->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND_INTERNAL)
	{
		CHECK(stream_write_uint32_t(s_root, s, &data->unk2, stage, from_instance));
	}
	return 0;
}

int stream_read_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *data)
{
	int i;

	CHECK(stream_read_uint16_t(s_root, s, &data->count_commands));
	data->commands = malloc(sizeof(type_sizedefinitions_order_command) * data->count_commands);
	for (i = 0; i < data->count_commands; i++)
	{
		CHECK(stream_read_type_sizedefinitions_order_command(s_root, s, &data->commands[i]));
	}
	return 0;
}

int stream_write_type_sizedefinition_order(stream *s_root, stream *s, type_sizedefinition_order *data, stream_write_stage stage, BOOL from_instance)
{
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->count_commands, stage, from_instance));
	for (i = 0; i < data->count_commands; i++)
	{
		CHECK(stream_write_type_sizedefinitions_order_command(s_root, s, &data->commands[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *data)
{
	CHECK(stream_read_type_id(s_root, s, &data->id));
	return 0;
}

int stream_write_type_control_block_number_variable(stream *s_root, stream *s, type_control_block_number_variable *data, stream_write_stage stage, BOOL from_instance)
{
	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_type_id(s_root, s, &data->id, stage, from_instance));
	return 0;
}

int stream_read_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *data)
{
	CHECK(stream_read_uint32_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint8_t(s_root, s, &data->value1));
	return 0;
}

int stream_write_type_control_block_number_long(stream *s_root, stream *s, type_control_block_number_long *data, stream_write_stage stage, BOOL from_instance)
{
	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint32_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->value1, stage, from_instance));
	return 0;
}

int stream_read_type_subcontrols(stream *s_root, stream *s, type_subcontrols *data)
{
	int i;

	CHECK(stream_read_uint16_t(s_root, s, &data->count_subcontrols));
	data->subcontrols = malloc(sizeof(type_control) * data->count_subcontrols);
	for (i = 0; i < data->count_subcontrols; i++)
	{
		CHECK(stream_read_type_control(s_root, s, &data->subcontrols[i]));
	}
	return 0;
}

int stream_write_type_subcontrols(stream *s_root, stream *s, type_subcontrols *data, stream_write_stage stage, BOOL from_instance)
{
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->count_subcontrols, stage, from_instance));
	for (i = 0; i < data->count_subcontrols; i++)
	{
		CHECK(stream_write_type_control(s_root, s, &data->subcontrols[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_control_block_number(stream *s_root, stream *s, type_control_block_number *data)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s_root, s, &data->block_len));
	CHECK(stream_read_uint8_t(s_root, s, &block_type));
	data->block_type = block_type;
	if (data->block_len == 1)
	{
		CHECK(stream_read_type_control_block_number_variable(s_root, s, &data->content_number));
	}
	if (data->block_len == 4)
	{
		CHECK(stream_read_type_control_block_number_long(s_root, s, &data->content_long));
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID)
	{
		data->id = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED)
	{
		data->sizedefinition_labelvisible_mixed = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE)
	{
		data->sizedefinition_labelvisible = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE)
	{
		data->sizedefinition_imagevisible = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE)
	{
		data->sizedefinition_imagesize = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED)
	{
		data->sizedefinition_imagesize_mixed = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED)
	{
		data->autocomplete_enabled = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE)
	{
		data->gallery_type = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE)
	{
		data->dropdowncolorpicker_colortemplate = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE)
	{
		data->dropdowncolorpicker_chipsize = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS)
	{
		data->dropdowncolorpicker_columns = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON)
	{
		data->dropdowncolorpicker_has_autocolor_button = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON)
	{
		data->dropdowncolorpicker_has_nocolor_button = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS)
	{
		data->dropdowncolorpicker_recent_color_rows = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS)
	{
		data->dropdowncolorpicker_standard_rows = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS)
	{
		data->dropdowncolorpicker_theme_color_rows = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->gallery_elements_type = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS)
	{
		data->gallery_has_large_items = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT)
	{
		data->gallery_item_height = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH)
	{
		data->gallery_item_width = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION)
	{
		data->gallery_text_position = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT)
	{
		data->gallery_menulayout = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER)
	{
		data->gallery_gripper = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS)
	{
		data->gallery_rows = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS)
	{
		data->gallery_columns = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS)
	{
		data->gallery_max_rows = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS)
	{
		data->gallery_max_columns = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE)
	{
		data->gallery_min_columns_large = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM)
	{
		data->gallery_max_columns_medium = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM)
	{
		data->gallery_min_columns_medium = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX)
	{
		data->is_checkbox = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->scalepolicy = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->scalepolicy_medium = data->scalepolicy / 256;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->scalepolicy_small = (data->scalepolicy % 256) / 16;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->scalepolicy_popup = (data->scalepolicy % 16) / 1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE)
	{
		data->id_reference = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ENABLE_PINNING)
	{
		data->enable_pinning = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_STR)
	{
		data->fontcontrol_str = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MIN)
	{
		data->fontcontrol_fontsize_min = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MAX)
	{
		data->fontcontrol_fontsize_max = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_PARENT_COMMANDID)
	{
		data->fontcontrol_parent_commandid = data->content_number.id.id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_TRUETYPEONLY)
	{
		data->fontcontrol_truetypeonly = data->content_long.value1;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_VERTICALFONTS)
	{
		data->fontcontrol_verticalfonts = data->content_long.value1;
	}
	return 0;
}

int stream_write_type_control_block_number(stream *s_root, stream *s, type_control_block_number *data, stream_write_stage stage, BOOL from_instance)
{
	uint8_t block_type;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint8_t(s_root, s, &data->block_len, stage, from_instance));
	block_type = data->block_type;
	CHECK(stream_write_uint8_t(s_root, s, &block_type, stage, from_instance));
	if (data->block_len == 1)
	{
		CHECK(stream_write_type_control_block_number_variable(s_root, s, &data->content_number, stage, from_instance));
	}
	if (data->block_len == 4)
	{
		CHECK(stream_write_type_control_block_number_long(s_root, s, &data->content_long, stage, from_instance));
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID)
	{
		data->content_number.id.id = data->id;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED)
	{
		data->content_number.id.id = data->sizedefinition_labelvisible_mixed;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE)
	{
		data->content_long.value1 = data->sizedefinition_labelvisible;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE)
	{
		data->content_long.value1 = data->sizedefinition_imagevisible;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE)
	{
		data->content_long.value1 = data->sizedefinition_imagesize;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED)
	{
		data->content_number.id.id = data->sizedefinition_imagesize_mixed;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED)
	{
		data->content_long.value1 = data->autocomplete_enabled;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE)
	{
		data->content_number.id.id = data->gallery_type;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE)
	{
		data->content_number.id.id = data->dropdowncolorpicker_colortemplate;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE)
	{
		data->content_number.id.id = data->dropdowncolorpicker_chipsize;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS)
	{
		data->content_number.id.id = data->dropdowncolorpicker_columns;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON)
	{
		data->content_long.value1 = data->dropdowncolorpicker_has_autocolor_button;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON)
	{
		data->content_long.value1 = data->dropdowncolorpicker_has_nocolor_button;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS)
	{
		data->content_number.id.id = data->dropdowncolorpicker_recent_color_rows;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS)
	{
		data->content_number.id.id = data->dropdowncolorpicker_standard_rows;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS)
	{
		data->content_number.id.id = data->dropdowncolorpicker_theme_color_rows;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->content_number.id.id = data->gallery_elements_type;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS)
	{
		data->content_long.value1 = data->gallery_has_large_items;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT)
	{
		data->content_number.id.id = data->gallery_item_height;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH)
	{
		data->content_number.id.id = data->gallery_item_width;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION)
	{
		data->content_number.id.id = data->gallery_text_position;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT)
	{
		data->content_number.id.id = data->gallery_menulayout;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER)
	{
		data->content_number.id.id = data->gallery_gripper;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS)
	{
		data->content_number.id.id = data->gallery_rows;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS)
	{
		data->content_number.id.id = data->gallery_columns;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS)
	{
		data->content_number.id.id = data->gallery_max_rows;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS)
	{
		data->content_number.id.id = data->gallery_max_columns;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE)
	{
		data->content_number.id.id = data->gallery_min_columns_large;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM)
	{
		data->content_number.id.id = data->gallery_max_columns_medium;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM)
	{
		data->content_number.id.id = data->gallery_min_columns_medium;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX)
	{
		data->content_long.value1 = data->is_checkbox;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
		data->content_number.id.id = data->scalepolicy;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
	{
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE)
	{
		data->content_number.id.id = data->id_reference;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_ENABLE_PINNING)
	{
		data->content_long.value1 = data->enable_pinning;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_STR)
	{
		data->content_number.id.id = data->fontcontrol_str;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MIN)
	{
		data->content_number.id.id = data->fontcontrol_fontsize_min;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MAX)
	{
		data->content_number.id.id = data->fontcontrol_fontsize_max;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_PARENT_COMMANDID)
	{
		data->content_number.id.id = data->fontcontrol_parent_commandid;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_TRUETYPEONLY)
	{
		data->content_long.value1 = data->fontcontrol_truetypeonly;
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_VERTICALFONTS)
	{
		data->content_long.value1 = data->fontcontrol_verticalfonts;
	}
	return 0;
}

int stream_read_type_control_block_special(stream *s_root, stream *s, type_control_block_special *data)
{
	uint8_t block_type;

	CHECK(stream_read_uint8_t(s_root, s, &data->block_len));
	CHECK(stream_read_uint8_t(s_root, s, &block_type));
	data->block_type = block_type;
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_QUICKACCESS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_HELP || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_CONTEXTPOPUPS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_UNK73)
	{
		CHECK(stream_read_type_subcontrols(s_root, s, &data->content_subcontrols));
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL)
	{
		CHECK(stream_read_type_sizedefinition_order(s_root, s, &data->sizedefinition_order));
	}
	return 0;
}

int stream_write_type_control_block_special(stream *s_root, stream *s, type_control_block_special *data, stream_write_stage stage, BOOL from_instance)
{
	uint8_t block_type;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint8_t(s_root, s, &data->block_len, stage, from_instance));
	block_type = data->block_type;
	CHECK(stream_write_uint8_t(s_root, s, &block_type, stage, from_instance));
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_QUICKACCESS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_TABS_HELP || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_CONTEXTPOPUPS || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_UNK73)
	{
		CHECK(stream_write_type_subcontrols(s_root, s, &data->content_subcontrols, stage, from_instance));
	}
	if (data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM || data->block_type == UIRIBBON_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL)
	{
		CHECK(stream_write_type_sizedefinition_order(s_root, s, &data->sizedefinition_order, stage, from_instance));
	}
	return 0;
}

int stream_read_type_control_blocks(stream *s_root, stream *s, type_control_blocks *data)
{
	int i;

	CHECK(stream_read_uint8_t(s_root, s, &data->count_blocks));
	data->blocks = malloc(sizeof(type_control_block) * data->count_blocks);
	for (i = 0; i < data->count_blocks; i++)
	{
		CHECK(stream_read_type_control_block(s_root, s, &data->blocks[i]));
	}
	return 0;
}

int stream_write_type_control_blocks(stream *s_root, stream *s, type_control_blocks *data, stream_write_stage stage, BOOL from_instance)
{
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint8_t(s_root, s, &data->count_blocks, stage, from_instance));
	for (i = 0; i < data->count_blocks; i++)
	{
		CHECK(stream_write_type_control_block(s_root, s, &data->blocks[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_block_inline(stream *s_root, stream *s, type_block_inline *data)
{
	stream substream_quick_ribbon_info;

	CHECK(stream_read_uint32_t(s_root, s, &data->unk2));
	CHECK(stream_read_uint16_t(s_root, s, &data->len4));
	CHECK(stream_read_make_substream(s, &substream_quick_ribbon_info, data->len4 - 7));
	CHECK(stream_read_type_control_blocks(s_root, &substream_quick_ribbon_info, &data->quick_ribbon_info));
	return 0;
}

int stream_write_type_block_inline(stream *s_root, stream *s, type_block_inline *data, stream_write_stage stage, BOOL from_instance)
{
	stream substream_quick_ribbon_info;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint32_t(s_root, s, &data->unk2, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->len4, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_quick_ribbon_info));
	CHECK(stream_write_type_control_blocks(s_root, &substream_quick_ribbon_info, &data->quick_ribbon_info, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_quick_ribbon_info));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->len4 = stream_write_get_length(&substream_quick_ribbon_info) - (- 7);
	}
	return 0;
}

int stream_read_type_control_block(stream *s_root, stream *s, type_control_block *data)
{
	uint8_t meta_type;
	stream substream_instance_ext;

	CHECK(stream_read_uint8_t(s_root, s, &meta_type));
	data->meta_type = meta_type;
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_NUMBER)
	{
		CHECK(stream_read_type_control_block_number(s_root, s, &data->content_number));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_SPECIAL)
	{
		CHECK(stream_read_type_control_block_special(s_root, s, &data->content_special));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_INLINE)
	{
		CHECK(stream_read_type_block_inline(s_root, s, &data->block_inline));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		CHECK(stream_read_uint32_t(s_root, s, &data->ext_pos));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		CHECK(stream_read_make_substream_instance(s_root, &substream_instance_ext, (data->ext_pos), s_root->max - (data->ext_pos)));
		data->ext = malloc(sizeof(type_control_block_ext));
		CHECK(stream_read_type_control_block_ext(s_root, &substream_instance_ext, data->ext));
	}
	return 0;
}

int stream_write_type_control_block(stream *s_root, stream *s, type_control_block *data, stream_write_stage stage, BOOL from_instance)
{
	uint8_t meta_type;
	stream substream_instance_ext;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	meta_type = data->meta_type;
	CHECK(stream_write_uint8_t(s_root, s, &meta_type, stage, from_instance));
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_NUMBER)
	{
		CHECK(stream_write_type_control_block_number(s_root, s, &data->content_number, stage, from_instance));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_SPECIAL)
	{
		CHECK(stream_write_type_control_block_special(s_root, s, &data->content_special, stage, from_instance));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_INLINE)
	{
		CHECK(stream_write_type_block_inline(s_root, s, &data->block_inline, stage, from_instance));
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		CHECK(stream_write_uint32_t(s_root, s, &data->ext_pos, stage, from_instance));
	}
	if (stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE)
	{
		data->_dryrun_pos_instance_ext = stream_write_get_position_absolute(s);
		data->ext_pos = stream_write_get_position_absolute(s);
	}
	if (data->meta_type == UIRIBBON_CONTROL_BLOCK_META_EXT)
	{
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_ext, data->_dryrun_pos_instance_ext));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_ext));
		}
		data->ext = malloc(sizeof(type_control_block_ext));
		CHECK(stream_write_type_control_block_ext(s_root, &substream_instance_ext, data->ext, stage, 1));
	}
	return 0;
}

int stream_read_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *data)
{
	CHECK(stream_read_uint16_t(s_root, s, &data->len_ext));
	CHECK(stream_read_type_control_block(s_root, s, &data->block));
	return 0;
}

int stream_write_type_control_block_ext(stream *s_root, stream *s, type_control_block_ext *data, stream_write_stage stage, BOOL from_instance)
{
	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->len_ext, stage, from_instance));
	CHECK(stream_write_type_control_block(s_root, s, &data->block, stage, from_instance));
	return 0;
}

int stream_read_type_control(stream *s_root, stream *s, type_control *data)
{
	uint16_t block_type;
	stream substream_blocks;

	CHECK(stream_read_uint16_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint16_t(s_root, s, &block_type));
	data->block_type = block_type;
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	CHECK(stream_read_uint16_t(s_root, s, &data->size_block));
	CHECK(stream_read_make_substream(s, &substream_blocks, data->size_block - 7));
	CHECK(stream_read_type_control_blocks(s_root, &substream_blocks, &data->blocks));
	return 0;
}

int stream_write_type_control(stream *s_root, stream *s, type_control *data, stream_write_stage stage, BOOL from_instance)
{
	uint16_t block_type;
	stream substream_blocks;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->unk1, stage, from_instance));
	block_type = data->block_type;
	CHECK(stream_write_uint16_t(s_root, s, &block_type, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->size_block, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_blocks));
	CHECK(stream_write_type_control_blocks(s_root, &substream_blocks, &data->blocks, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_blocks));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->size_block = stream_write_get_length(&substream_blocks) - (- 7);
	}
	return 0;
}

int stream_read_application_views(stream *s_root, stream *s, application_views *data)
{
	const char unk20[] = {0, 0, 22, 0, 36, 0, 16};
	stream substream_ribbon;

	CHECK(stream_read_expect_bytes(s, unk20));
	CHECK(stream_read_uint16_t(s_root, s, &data->ribbon_len));
	CHECK(stream_read_make_substream(s, &substream_ribbon, data->ribbon_len));
	CHECK(stream_read_type_control_blocks(s_root, &substream_ribbon, &data->ribbon));
	return 0;
}

int stream_write_application_views(stream *s_root, stream *s, application_views *data, stream_write_stage stage, BOOL from_instance)
{
	const char unk20[] = {0, 0, 22, 0, 36, 0, 16};
	stream substream_ribbon;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_bytes(s, unk20, sizeof(unk20), stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->ribbon_len, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_ribbon));
	CHECK(stream_write_type_control_blocks(s_root, &substream_ribbon, &data->ribbon, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_ribbon));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->ribbon_len = stream_write_get_length(&substream_ribbon);
	}
	return 0;
}

int stream_read_type_command(stream *s_root, stream *s, type_command *data)
{
	CHECK(stream_read_uint16_t(s_root, s, &data->command_id));
	data->unk1 = malloc(3);
	CHECK(stream_read_bytes(s, data->unk1, 3));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk3b));
	data->unk4 = malloc(2);
	CHECK(stream_read_bytes(s, data->unk4, 2));
	CHECK(stream_read_uint16_t(s_root, s, &data->size_str));
	data->str = malloc(data->size_str);
	CHECK(stream_read_bytes(s, data->str, data->size_str));
	return 0;
}

int stream_write_type_command(stream *s_root, stream *s, type_command *data, stream_write_stage stage, BOOL from_instance)
{
	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->command_id, stage, from_instance));
	CHECK(stream_write_bytes(s, data->unk1, 3, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk3b, stage, from_instance));
	CHECK(stream_write_bytes(s, data->unk4, 2, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->size_str, stage, from_instance));
	CHECK(stream_write_bytes(s, data->str, data->size_str, stage, from_instance));
	return 0;
}

int stream_read_type_command_container(stream *s_root, stream *s, type_command_container *data)
{
	int i;

	CHECK(stream_read_uint32_t(s_root, s, &data->commands_len));
	data->commands = malloc(sizeof(type_command) * data->commands_len);
	for (i = 0; i < data->commands_len; i++)
	{
		CHECK(stream_read_type_command(s_root, s, &data->commands[i]));
	}
	return 0;
}

int stream_write_type_command_container(stream *s_root, stream *s, type_command_container *data, stream_write_stage stage, BOOL from_instance)
{
	int i;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint32_t(s_root, s, &data->commands_len, stage, from_instance));
	for (i = 0; i < data->commands_len; i++)
	{
		CHECK(stream_write_type_command(s_root, s, &data->commands[i], stage, from_instance));
	}
	return 0;
}

int stream_read_type_command_ext5(stream *s_root, stream *s, type_command_ext5 *data)
{
	const char unk3[] = {0, 0};
	const char unk5[] = {0, 0};

	CHECK(stream_read_uint16_t(s_root, s, &data->command_id));
	CHECK(stream_read_uint16_t(s_root, s, &data->count));
	CHECK(stream_read_expect_bytes(s, unk3));
	CHECK(stream_read_uint16_t(s_root, s, &data->offset));
	CHECK(stream_read_expect_bytes(s, unk5));
	return 0;
}

int stream_write_type_command_ext5(stream *s_root, stream *s, type_command_ext5 *data, stream_write_stage stage, BOOL from_instance)
{
	const char unk3[] = {0, 0};
	const char unk5[] = {0, 0};

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->command_id, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->count, stage, from_instance));
	CHECK(stream_write_bytes(s, unk3, sizeof(unk3), stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->offset, stage, from_instance));
	CHECK(stream_write_bytes(s, unk5, sizeof(unk5), stage, from_instance));
	return 0;
}

int stream_read_type_command_ext4(stream *s_root, stream *s, type_command_ext4 *data)
{
	CHECK(stream_read_type_command_ext5(s_root, s, &data->blocks));
	return 0;
}

int stream_write_type_command_ext4(stream *s_root, stream *s, type_command_ext4 *data, stream_write_stage stage, BOOL from_instance)
{
	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_type_command_ext5(s_root, s, &data->blocks, stage, from_instance));
	return 0;
}

int stream_read_type_command_ext3(stream *s_root, stream *s, type_command_ext3 *data)
{
	stream substream_unk3;

	CHECK(stream_read_uint16_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint16_t(s_root, s, &data->unk2));
	CHECK(stream_read_make_substream(s, &substream_unk3, data->unk1 - 4));
	CHECK(stream_read_type_command_ext4(s_root, &substream_unk3, &data->unk3));
	return 0;
}

int stream_write_type_command_ext3(stream *s_root, stream *s, type_command_ext3 *data, stream_write_stage stage, BOOL from_instance)
{
	stream substream_unk3;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->unk2, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_unk3));
	CHECK(stream_write_type_command_ext4(s_root, &substream_unk3, &data->unk3, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_unk3));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->unk1 = stream_write_get_length(&substream_unk3) - (- 4);
	}
	return 0;
}

int stream_read_type_command_ext2(stream *s_root, stream *s, type_command_ext2 *data)
{
	stream substream_instance_ext;

	CHECK(stream_read_uint16_t(s_root, s, &data->pos));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_ext, (data->pos), s_root->max - (data->pos)));
	data->ext = malloc(sizeof(type_command_ext3));
	CHECK(stream_read_type_command_ext3(s_root, &substream_instance_ext, data->ext));
	return 0;
}

int stream_write_type_command_ext2(stream *s_root, stream *s, type_command_ext2 *data, stream_write_stage stage, BOOL from_instance)
{
	stream substream_instance_ext;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_uint16_t(s_root, s, &data->pos, stage, from_instance));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE)
	{
		data->_dryrun_pos_instance_ext = stream_write_get_position_absolute(s);
		data->pos = stream_write_get_position_absolute(s);
	}
	if (stage == STREAM_WRITE_STAGE_WRITE)
	{
		CHECK(stream_write_make_substream_instance(s_root, &substream_instance_ext, data->_dryrun_pos_instance_ext));
	}
	else
	{
		CHECK(stream_write_make_substream(s_root, &substream_instance_ext));
	}
	data->ext = malloc(sizeof(type_command_ext3));
	CHECK(stream_write_type_command_ext3(s_root, &substream_instance_ext, data->ext, stage, 1));
	return 0;
}

int stream_read_type_uiribbon(stream *s_root, stream *s, type_uiribbon *data)
{
	const char unknown1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
	const char magic[] = {83, 67, 66, 105, 110};
	const char unknown2[] = {2};
	stream substream_strings;
	const char unknown3[] = {0, 0};
	const char unk44[] = {16};
	stream substream_command_container;
	int i;

	CHECK(stream_read_expect_bytes(s, unknown1));
	CHECK(stream_read_expect_bytes(s, magic));
	CHECK(stream_read_uint32_t(s_root, s, &data->length_this_file));
	CHECK(stream_read_expect_bytes(s, unknown2));
	CHECK(stream_read_uint16_t(s_root, s, &data->size_strings));
	CHECK(stream_read_make_substream(s, &substream_strings, data->size_strings - 2));
	CHECK(stream_read_type_strings(s_root, &substream_strings, &data->strings));
	CHECK(stream_read_uint16_t(s_root, s, &data->count_command_resources));
	CHECK(stream_read_expect_bytes(s, unknown3));
	data->command_resources = malloc(sizeof(type_resource) * data->count_command_resources);
	for (i = 0; i < data->count_command_resources; i++)
	{
		CHECK(stream_read_type_resource(s_root, s, &data->command_resources[i]));
	}
	CHECK(stream_read_expect_bytes(s, unk44));
	CHECK(stream_read_uint32_t(s_root, s, &data->size_command_container));
	CHECK(stream_read_make_substream(s, &substream_command_container, data->size_command_container - 4));
	CHECK(stream_read_type_command_container(s_root, &substream_command_container, &data->command_container));
	CHECK(stream_read_uint16_t(s_root, s, &data->len_unk6));
	CHECK(stream_read_type_command_ext2(s_root, s, &data->command_ext));
	CHECK(stream_read_application_views(s_root, s, &data->unk6));
	return 0;
}

int stream_write_type_uiribbon(stream *s_root, stream *s, type_uiribbon *data, stream_write_stage stage, BOOL from_instance)
{
	const char unknown1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
	const char magic[] = {83, 67, 66, 105, 110};
	const char unknown2[] = {2};
	stream substream_strings;
	const char unknown3[] = {0, 0};
	const char unk44[] = {16};
	stream substream_command_container;
	int i;

	s_root->pos = 0;

	data->_dryrun_pos = stream_write_get_position_absolute(s);
	CHECK(stream_write_bytes(s, unknown1, sizeof(unknown1), stage, from_instance));
	CHECK(stream_write_bytes(s, magic, sizeof(magic), stage, from_instance));
	CHECK(stream_write_uint32_t(s_root, s, &data->length_this_file, stage, from_instance));
	CHECK(stream_write_bytes(s, unknown2, sizeof(unknown2), stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->size_strings, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_strings));
	CHECK(stream_write_type_strings(s_root, &substream_strings, &data->strings, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_strings));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->size_strings = stream_write_get_length(&substream_strings) - (- 2);
	}
	CHECK(stream_write_uint16_t(s_root, s, &data->count_command_resources, stage, from_instance));
	CHECK(stream_write_bytes(s, unknown3, sizeof(unknown3), stage, from_instance));
	for (i = 0; i < data->count_command_resources; i++)
	{
		CHECK(stream_write_type_resource(s_root, s, &data->command_resources[i], stage, from_instance));
	}
	CHECK(stream_write_bytes(s, unk44, sizeof(unk44), stage, from_instance));
	CHECK(stream_write_uint32_t(s_root, s, &data->size_command_container, stage, from_instance));
	CHECK(stream_write_make_substream(s, &substream_command_container));
	CHECK(stream_write_type_command_container(s_root, &substream_command_container, &data->command_container, stage, from_instance));
	CHECK(stream_write_merge_substream(s, &substream_command_container));
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		data->size_command_container = stream_write_get_length(&substream_command_container) - (- 4);
	}
	CHECK(stream_write_uint16_t(s_root, s, &data->len_unk6, stage, from_instance));
	CHECK(stream_write_type_command_ext2(s_root, s, &data->command_ext, stage, from_instance));
	CHECK(stream_write_application_views(s_root, s, &data->unk6, stage, from_instance));
	return 0;
}

