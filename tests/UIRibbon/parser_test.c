/* This file is generated - Do not edit manually */

#include "parser_test.h"

int stream_read_type_t1(stream *s_root, stream *s, type_t1 *data);
int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_t3(stream *s_root, stream *s, type_t3 *data);
int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_t2(stream *s_root, stream *s, type_t2 *data);
int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_t5(stream *s_root, stream *s, type_t5 *data);
int stream_write_type_t5(stream *s_root, stream *s, type_t5 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data);
int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_t6(stream *s_root, stream *s, type_t6 *data);
int stream_write_type_t6(stream *s_root, stream *s, type_t6 *data, stream_write_stage stage, BOOL do_sequence);
int stream_read_type_test(stream *s_root, stream *s, type_test *data);
int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL do_sequence);

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

int stream_write_type_t1(stream *s_root, stream *s, type_t1 *data, stream_write_stage stage, BOOL do_sequence)
{
	stream substream_instance_i1;

	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence));

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
		CHECK(stream_write_type_t2(s_root, &substream_instance_i1, data->i1, stage, TRUE));
		CHECK(stream_write_type_t2(s_root, &substream_instance_i1, data->i1, stage, FALSE));
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

int stream_write_type_t3(stream *s_root, stream *s, type_t3 *data, stream_write_stage stage, BOOL do_sequence)
{
	stream substream_instance_i2;

	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence));

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
		CHECK(stream_write_type_t4(s_root, &substream_instance_i2, data->i2, stage, TRUE));
		CHECK(stream_write_type_t4(s_root, &substream_instance_i2, data->i2, stage, FALSE));
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

int stream_write_type_t2(stream *s_root, stream *s, type_t2 *data, stream_write_stage stage, BOOL do_sequence)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_type_t3(s_root, s, &data->sub2, stage, do_sequence));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence));
	return 0;
}

int stream_read_type_t5(stream *s_root, stream *s, type_t5 *data)
{
	stream substream_instance_i3;
	stream substream_instance_i4;

	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos1));
	CHECK(stream_read_uint16_t(s_root, s, &data->pos2));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i3, (data->pos1), s_root->max - (data->pos1)));
	data->i3 = malloc(sizeof(type_t6));
	CHECK(stream_read_type_t6(s_root, &substream_instance_i3, data->i3));
	CHECK(stream_read_make_substream_instance(s_root, &substream_instance_i4, (data->pos2), s_root->max - (data->pos2)));
	data->i4 = malloc(sizeof(type_t6));
	CHECK(stream_read_type_t6(s_root, &substream_instance_i4, data->i4));
	return 0;
}

int stream_write_type_t5(stream *s_root, stream *s, type_t5 *data, stream_write_stage stage, BOOL do_sequence)
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

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos1, stage, do_sequence));
	CHECK(stream_write_uint16_t(s_root, s, &data->pos2, stage, do_sequence));

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
		CHECK(stream_write_type_t6(s_root, &substream_instance_i3, data->i3, stage, TRUE));
		CHECK(stream_write_type_t6(s_root, &substream_instance_i3, data->i3, stage, FALSE));

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
		CHECK(stream_write_type_t6(s_root, &substream_instance_i4, data->i4, stage, TRUE));
		CHECK(stream_write_type_t6(s_root, &substream_instance_i4, data->i4, stage, FALSE));
	}
	return 0;
}

int stream_read_type_t4(stream *s_root, stream *s, type_t4 *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_type_t5(s_root, s, &data->sub3));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_t4(stream *s_root, stream *s, type_t4 *data, stream_write_stage stage, BOOL do_sequence)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_type_t5(s_root, s, &data->sub3, stage, do_sequence));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence));
	return 0;
}

int stream_read_type_t6(stream *s_root, stream *s, type_t6 *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_t6(stream *s_root, stream *s, type_t6 *data, stream_write_stage stage, BOOL do_sequence)
{
	/* No separate sequence run during write */
	if (stage == STREAM_WRITE_STAGE_WRITE && do_sequence) return 0;

	/* Store position for current type */
	if (stage == STREAM_WRITE_STAGE_DRYRUN && do_sequence)
	{
		data->_dryrun_pos = stream_write_get_position_absolute(s);
	}

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence));
	return 0;
}

int stream_read_type_test(stream *s_root, stream *s, type_test *data)
{
	CHECK(stream_read_uint8_t(s_root, s, &data->unk1));
	CHECK(stream_read_type_t1(s_root, s, &data->sub1));
	CHECK(stream_read_uint8_t(s_root, s, &data->unk2));
	return 0;
}

int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL do_sequence)
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

	CHECK(stream_write_uint8_t(s_root, s, &data->unk1, stage, do_sequence));
	CHECK(stream_write_type_t1(s_root, s, &data->sub1, stage, do_sequence));
	CHECK(stream_write_uint8_t(s_root, s, &data->unk2, stage, do_sequence));
	return 0;
}

int stream_read_test(stream *s, type_test *data)
{
	return stream_read_type_test(s, s, data);
}
int stream_write_test(stream *s, type_test *data, stream_write_stage stage)
{
	CHECK(stream_write_type_test(s, s, data, stage, TRUE));
	CHECK(stream_write_type_test(s, s, data, stage, FALSE));
	return 0;
}
