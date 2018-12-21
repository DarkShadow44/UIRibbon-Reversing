#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expr, err) \
   if (expr) { printf("%s:%d - %s\n", __FILE__, __LINE__, err); return 1; }

typedef struct _test_data
{
    const char *name;
    const char *xml_data;
    const char *bml_data;
    int xml_len;
    int bml_len;
} test_data;

const test_data *get_test_data(char *name);

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
int _stream_expect_bytes(stream *s, void *data, int len);
#define stream_expect_bytes(s, data) \
    _stream_expect_bytes(s, data, sizeof(data))
int stream_read_uint32(stream *s, uint32_t *ret);
int stream_read_uint16(stream *s, uint16_t *ret);
int stream_read_uint8(stream *s, uint8_t *ret);
int stream_read_int32(stream *s, int32_t *ret);
int stream_read_int16(stream *s, int16_t *ret);
int stream_read_int8(stream *s, int8_t *ret);


/* Parser */

typedef struct
{
    uint16_t size_str;
    char *str;
} type_string;

typedef struct
{
    uint8_t count_strings;
    type_string *strings;
} type_strings;

typedef struct
{
    uint32_t length_this_file;
    type_strings strings;
} type_main;

int read_type_main(stream *s, type_main *ret);
