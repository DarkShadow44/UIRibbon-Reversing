#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK2(expr, err) \
   if (expr) { printf("%s:%d - %s\n", __FILE__, __LINE__, err); return 1; }

#define CHECK(expr) \
   CHECK2(expr, "")

typedef int BOOL;

typedef enum
{
    STREAM_WRITE_STAGE_DRYRUN_SEQUENCE,
    STREAM_WRITE_STAGE_DRYRUN_INSTANCE,
    STREAM_WRITE_STAGE_WRITE,
} stream_write_stage;

typedef struct _test_data
{
    const char *name;
    const char *xml_data;
    const char *bml_data;
    int xml_len;
    int bml_len;
} test_data;

const test_data *get_test_data(const char *name);
void write_test_data(const char *name);
int run_visual_test(const char *name);

/* Stream generic */

typedef struct _stream
{
    int start;
    int pos;
    int max;
    int allocated;
    char *data;
    struct _stream *parent;
    BOOL is_instance;
} stream;

int stream_read_make_substream(stream *s, stream *ret, int len);
int stream_read_make_substream_instance(stream *s_root, stream *ret, int pos, int len);
int stream_read_bytes(stream *s, void* data, int len);
int stream_read_skip_bytes(stream *s, int len);
int _stream_read_expect_bytes(stream *s, const void *data, int len);
#define stream_read_expect_bytes(s, data) \
    _stream_read_expect_bytes(s, data, sizeof(data))
int stream_read_uint32_t(stream *s_root, stream *s, uint32_t *ret);
int stream_read_uint16_t(stream *s_root, stream *s, uint16_t *data);
int stream_read_uint8_t(stream *s_root, stream *s, uint8_t *data);
int stream_read_int32_t(stream *s_root, stream *s, int32_t *data);
int stream_read_int16_t(stream *s_root, stream *s, int16_t *data);
int stream_read_int8_t(stream *s_root, stream *s, int8_t *data);
int stream_write_get_position_absolute(stream *s);
int stream_write_get_length(stream *s);
int stream_write_uint32_t(stream *s_root, stream *s, uint32_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_uint16_t(stream *s_root, stream *s, uint16_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_uint8_t(stream *s_root, stream *s, uint8_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_int32_t(stream *s_root, stream *s, int32_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_int16_t(stream *s_root, stream *s, int16_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_int8_t(stream *s_root, stream *s, int8_t *data, stream_write_stage stage, BOOL from_instance);
int stream_write_bytes(stream *s, const void *data, int length, stream_write_stage stage, BOOL from_instance);
int stream_write_make_substream(stream *s, stream *ret);
int stream_write_make_substream_instance(stream *s_root, stream *ret, int pos);
