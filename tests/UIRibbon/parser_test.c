/* This file is generated - Do not edit manually */

#include "parser_test.h"

int stream_read_type_t1(stream *s_root, stream *s, type_t1 *data, type_test *_root);
int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t1(type_t1 *data);
int stream_read_type_t3(stream *s_root, stream *s, type_t3 *data, type_test *_root);
int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t3(type_t3 *data);
int stream_read_type_t2(stream *s_root, stream *s, type_t2 *data, type_test *_root);
int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t2(type_t2 *data);
int stream_read_type_t5(stream *s_root, stream *s, type_t5 *data, type_test *_root);
int stream_write_type_t5(stream *s_root, stream *s, type_t5 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t5(type_t5 *data);
int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data, type_test *_root);
int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t4(type_t4 *data);
int stream_read_type_t6(stream *s_root, stream *s, type_t6 *data, type_test *_root);
int stream_write_type_t6(stream *s_root, stream *s, type_t6 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_t6(type_t6 *data);
int stream_read_type_test(stream *s_root, stream *s, type_test *data, type_test *_root);
int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL do_sequence, type_test *_root);
void stream_free_type_test(type_test *data);

int stream_read_type_t1(stream *s_root, stream *s, type_t1 *data, type_test *_root)
{
	stream substream_instance_i1;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1, _root));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i1, (data->pos1), s_root->max - (data->pos1)));
	data->i1 = malloc(sizeof(type_t2));
	CHECK(stream_read_type_t2(s_root, &substream_instance_i1, data->i1, _root));
	return 0;
}

int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	stream substream_instance_i1;

	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence, _root));

	/* Start writing instance data */
	if (!do_sequence)
	{
		/* Store position for instance */
		if (stage == STREAM_WRITE_STAGE_DRYRUN)
		{
			data->_dryrun_pos_instance_i1 = stream_write_get_position_absolute(s_root);
			data->pos1 = stream_write_get_position_absolute(s_root);
		}

		/* Make substream for instance */
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i1, data->_dryrun_pos_instance_i1));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i1));
		}

		/* Write instance */
		CHECK(stream_write_type_t2(s_root, &substream_instance_i1, data->i1, stage, TRUE, _root));
		CHECK(stream_write_type_t2(s_root, &substream_instance_i1, data->i1, stage, FALSE, _root));
	}
	return 0;
}

void stream_free_type_t1(type_t1 *data)
{
	stream_free_type_t2(data->i1);
	free(data->i1);
}

int stream_read_type_t3(stream *s_root, stream *s, type_t3 *data, type_test *_root)
{
	stream substream_instance_i2;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1, _root));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i2, (data->pos1), s_root->max - (data->pos1)));
	data->i2 = malloc(sizeof(type_t4));
	CHECK(stream_read_type_t4(s_root, &substream_instance_i2, data->i2, _root));
	return 0;
}

int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	stream substream_instance_i2;

	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence, _root));

	/* Start writing instance data */
	if (!do_sequence)
	{
		/* Store position for instance */
		if (stage == STREAM_WRITE_STAGE_DRYRUN)
		{
			data->_dryrun_pos_instance_i2 = stream_write_get_position_absolute(s_root);
			data->pos1 = stream_write_get_position_absolute(s_root);
		}

		/* Make substream for instance */
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i2, data->_dryrun_pos_instance_i2));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i2));
		}

		/* Write instance */
		CHECK(stream_write_type_t4(s_root, &substream_instance_i2, data->i2, stage, TRUE, _root));
		CHECK(stream_write_type_t4(s_root, &substream_instance_i2, data->i2, stage, FALSE, _root));
	}
	return 0;
}

void stream_free_type_t3(type_t3 *data)
{
	stream_free_type_t4(data->i2);
	free(data->i2);
}

int stream_read_type_t2(stream *s_root, stream *s, type_t2 *data, type_test *_root)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_type_t3(s_root, s, &data->sub2, _root));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2, _root));
	return 0;
}

int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_type_t3(s_root, s, &data->sub2, stage, do_sequence, _root));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence, _root));
	return 0;
}

void stream_free_type_t2(type_t2 *data)
{
	stream_free_type_t3(&data->sub2);
}

int stream_read_type_t5(stream *s_root, stream *s, type_t5 *data, type_test *_root)
{
	stream substream_instance_i3;
	stream substream_instance_i4;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1, _root));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos2, _root));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i3, (data->pos1), s_root->max - (data->pos1)));
	data->i3 = malloc(sizeof(type_t6));
	CHECK(stream_read_type_t6(s_root, &substream_instance_i3, data->i3, _root));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i4, (data->pos2), s_root->max - (data->pos2)));
	data->i4 = malloc(sizeof(type_t6));
	CHECK(stream_read_type_t6(s_root, &substream_instance_i4, data->i4, _root));
	return 0;
}

int stream_write_type_t5(stream *s_root, stream *s, type_t5 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	stream substream_instance_i3;
	stream substream_instance_i4;

	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence, _root));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos2, stage, do_sequence, _root));

	/* Start writing instance data */
	if (!do_sequence)
	{
		/* Store position for instance */
		if (stage == STREAM_WRITE_STAGE_DRYRUN)
		{
			data->_dryrun_pos_instance_i3 = stream_write_get_position_absolute(s_root);
			data->pos1 = stream_write_get_position_absolute(s_root);
		}

		/* Make substream for instance */
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i3, data->_dryrun_pos_instance_i3));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i3));
		}

		/* Write instance */
		CHECK(stream_write_type_t6(s_root, &substream_instance_i3, data->i3, stage, TRUE, _root));
		CHECK(stream_write_type_t6(s_root, &substream_instance_i3, data->i3, stage, FALSE, _root));

		/* Store position for instance */
		if (stage == STREAM_WRITE_STAGE_DRYRUN)
		{
			data->_dryrun_pos_instance_i4 = stream_write_get_position_absolute(s_root);
			data->pos2 = stream_write_get_position_absolute(s_root);
		}

		/* Make substream for instance */
		if (stage == STREAM_WRITE_STAGE_WRITE)
		{
			CHECK(stream_write_make_substream_instance(s_root, &substream_instance_i4, data->_dryrun_pos_instance_i4));
		}
		else
		{
			CHECK(stream_write_make_substream(s_root, &substream_instance_i4));
		}

		/* Write instance */
		CHECK(stream_write_type_t6(s_root, &substream_instance_i4, data->i4, stage, TRUE, _root));
		CHECK(stream_write_type_t6(s_root, &substream_instance_i4, data->i4, stage, FALSE, _root));
	}
	return 0;
}

void stream_free_type_t5(type_t5 *data)
{
	stream_free_type_t6(data->i3);
	free(data->i3);
	stream_free_type_t6(data->i4);
	free(data->i4);
}

int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data, type_test *_root)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_type_t5(s_root, s, &data->sub3, _root));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2, _root));
	return 0;
}

int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_type_t5(s_root, s, &data->sub3, stage, do_sequence, _root));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence, _root));
	return 0;
}

void stream_free_type_t4(type_t4 *data)
{
	stream_free_type_t5(&data->sub3);
}

int stream_read_type_t6(stream *s_root, stream *s, type_t6 *data, type_test *_root)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2, _root));
	return 0;
}

int stream_write_type_t6(stream *s_root, stream *s, type_t6 *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence, _root));
	return 0;
}

void stream_free_type_t6(type_t6 *data)
{
}

int stream_read_type_test(stream *s_root, stream *s, type_test *data, type_test *_root)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1, _root));
	CHECK(stream_read_type_t1(s_root, s, &data->sub1, _root));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2, _root));
	return 0;
}

int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL do_sequence, type_test *_root)
{
	if (stage == STREAM_WRITE_STAGE_WRITE)
	{
		s_root->pos = 0;
	}
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence, _root));
	CHECK(stream_write_type_t1(s_root, s, &data->sub1, stage, do_sequence, _root));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence, _root));
	return 0;
}

void stream_free_type_test(type_test *data)
{
	stream_free_type_t1(&data->sub1);
}

int stream_read_test(stream *s, type_test *data)
{
	return stream_read_type_test(s, s, data, data);
}

int stream_write_test(stream *s, type_test *data, stream_write_stage stage)
{
	CHECK(stream_write_type_test(s, s, data, stage, TRUE, data));
	CHECK(stream_write_type_test(s, s, data, stage, FALSE, data));
	return 0;
}

void stream_free_test(type_test *data)
{
	stream_free_type_test(data);
}
