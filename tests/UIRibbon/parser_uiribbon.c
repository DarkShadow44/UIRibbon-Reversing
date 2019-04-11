/* This file is generated - Do not edit manually */

#include "parser_uiribbon.h"

int stream_read_type_t1(stream *s_root, stream *s, type_t1 *data);
int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_t3(stream *s_root, stream *s, type_t3 *data);
int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_t2(stream *s_root, stream *s, type_t2 *data);
int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL from_instance);
int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data);
int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL from_instance);

int stream_read_type_t1(stream *s_root, stream *s, type_t1 *data)
{
	stream substream_instance_i1;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i1, (data->pos1), s_root->max - (data->pos1)));
	data->i1 = malloc(sizeof(type_t2));
	CHECK(stream_read_type_t2(s_root, &substream_instance_i1, data->i1));
	return 0;
}

int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL from_instance)
{
	stream substream_instance_i1;

	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE || (from_instance && stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, from_instance));
	/* Start writing instance data */
	if (stage != STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		if (stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE)
		{
			data->_dryrun_pos_instance_i1 = stream_write_get_position_absolute(s_root);
			data->pos1 = stream_write_get_position_absolute(s_root);
		}
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i1, data->_dryrun_pos_instance_i1));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i1));
		}
		CHECK(stream_write_type_t2(s_root, &substream_instance_i1, data->i1, stage, 1));
	}
	return 0;
}

int stream_read_type_t3(stream *s_root, stream *s, type_t3 *data)
{
	stream substream_instance_i2;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i2, (data->pos1), s_root->max - (data->pos1)));
	data->i2 = malloc(sizeof(type_t4));
	CHECK(stream_read_type_t4(s_root, &substream_instance_i2, data->i2));
	return 0;
}

int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL from_instance)
{
	stream substream_instance_i2;

	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE || (from_instance && stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, from_instance));
	/* Start writing instance data */
	if (stage != STREAM_WRITE_STAGE_DRYRUN_SEQUENCE)
	{
		if (stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE)
		{
			data->_dryrun_pos_instance_i2 = stream_write_get_position_absolute(s_root);
			data->pos1 = stream_write_get_position_absolute(s_root);
		}
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i2, data->_dryrun_pos_instance_i2));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i2));
		}
		CHECK(stream_write_type_t4(s_root, &substream_instance_i2, data->i2, stage, 1));
	}
	return 0;
}

int stream_read_type_t2(stream *s_root, stream *s, type_t2 *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_type_t3(s_root, s, &data->sub2));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL from_instance)
{
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE || (from_instance && stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_type_t3(s_root, s, &data->sub2, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, from_instance));
	return 0;
}

int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL from_instance)
{
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE || (from_instance && stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, from_instance));
	return 0;
}

int stream_read_type_test(stream *s_root, stream *s, type_test *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_type_t1(s_root, s, &data->sub1));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL from_instance)
{
	if (stage == STREAM_WRITE_STAGE_WRITE)
	{
		s_root->pos = 0;
	}
	if (stage == STREAM_WRITE_STAGE_DRYRUN_SEQUENCE || (from_instance && stage == STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}
	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, from_instance));
	CHECK(stream_write_type_t1(s_root, s, &data->sub1, stage, from_instance));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, from_instance));
	return 0;
}

