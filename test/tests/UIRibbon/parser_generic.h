#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK2(expr, err) \
   if (expr) { printf("%s:%d - %s\n", __FILE__, __LINE__, err); return 1; }

#define CHECK(expr) \
   CHECK2(expr, "")

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

/* Stream generic */

typedef struct _stream
{
    int start;
    int pos;
    int max;
    const char *data;
} stream;

int stream_make_substream(stream *s, stream *ret, int len);
int stream_read_bytes(stream *s, void* ret, int len);
int stream_skip_bytes(stream *s, int len);
int _stream_expect_bytes(stream *s, const void *data, int len);
#define stream_expect_bytes(s, data) \
    _stream_expect_bytes(s, data, sizeof(data))
int stream_read_uint32_t(stream *s, uint32_t *ret);
int stream_read_uint16_t(stream *s, uint16_t *ret);
int stream_read_uint8_t(stream *s, uint8_t *ret);
int stream_read_int32_t(stream *s, int32_t *ret);
int stream_read_int16_t(stream *s, int16_t *ret);
int stream_read_int8_t(stream *s, int8_t *ret);
