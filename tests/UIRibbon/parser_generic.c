#include "parser_generic.h"

int stream_make_substream(stream *s, stream *ret, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");

    ret->start = s->start + s->pos;
    ret->pos = 0;
    ret->max = ret->start + len;
    ret->data = s->data;

    s->pos += len;
    return 0;
}

int stream_read_bytes(stream *s, void* ret, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");
    memcpy(ret, s->data + s->start + s->pos, len);
    s->pos += len;
    return 0;
}

int stream_skip_bytes(stream *s, int len)
{
    CHECK2(s->pos + len >= s->max, "End of stream");
    s->pos += len;
    return 0;
}

int _stream_expect_bytes(stream *s, const void *data, int len)
{
    void *tmp = malloc(len);
    CHECK(stream_read_bytes(s, tmp, len));
    CHECK2(memcmp(data, tmp, len), "Byte arrays don't match");

    free(tmp);
    return 0;
}

int stream_read_uint32_t(stream *s, uint32_t *ret)
{
    return stream_read_bytes(s, ret, 4);
}

int stream_read_uint16_t(stream *s, uint16_t *ret)
{
    return stream_read_bytes(s, ret, 2);
}

int stream_read_uint8_t(stream *s, uint8_t *ret)
{
    return stream_read_bytes(s, ret, 1);
}

int stream_read_int32_t(stream *s, int32_t *ret)
{
    return stream_read_bytes(s, ret, 4);
}

int stream_read_int16_t(stream *s, int16_t *ret)
{
    return stream_read_bytes(s, ret, 2);
}

int stream_read_int8_t(stream *s, int8_t *ret)
{
    return stream_read_bytes(s, ret, 1);
}
