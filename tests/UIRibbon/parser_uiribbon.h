/* This file is generated - Do not edit manually */

#include "parser_generic.h"

typedef struct type_t1_
{
	int _dryrun_pos;
	uint8_t unk1;
	uint16_t pos1;
	int _dryrun_pos_instance_i1;
	struct type_t2_ *i1;
} type_t1;

typedef struct type_t3_
{
	int _dryrun_pos;
	uint8_t unk1;
	uint16_t pos1;
	int _dryrun_pos_instance_i2;
	struct type_t4_ *i2;
} type_t3;

typedef struct type_t2_
{
	int _dryrun_pos;
	uint8_t unk1;
	type_t3 sub2;
	uint8_t unk2;
} type_t2;

typedef struct type_t4_
{
	int _dryrun_pos;
	uint8_t unk1;
	uint8_t unk2;
} type_t4;

typedef struct type_test_
{
	int _dryrun_pos;
	uint8_t unk1;
	type_t1 sub1;
	uint8_t unk2;
} type_test;

int stream_read_type_test(stream *s_root, stream *s, type_test *data);
int stream_write_type_test(stream *s_root, stream *s, type_test *data, stream_write_stage stage, BOOL from_instance);
