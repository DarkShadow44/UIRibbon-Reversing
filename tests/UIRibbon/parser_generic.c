#include "parser_generic.h"

int stream_read_make_substream(stream *s, stream *ret, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");

    ret->start = s->start + s->pos;
    ret->pos = 0;
    ret->max = ret->start + len;
    ret->data = s->data;

    s->pos += len;
    return 0;
}

int stream_read_make_substream_instance(stream *s_root, stream *ret, int pos, int len)
{
    CHECK2(pos < 0 || pos > s_root->max, "End of stream");
    CHECK2(len < 0 || pos + len > s_root->max, "End of stream");

    ret->start = pos;
    ret->pos = 0;
    ret->max = pos + len;
    ret->data = s_root->data;
    return 0;
}

int stream_read_bytes(stream *s, void *data, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");
    memcpy(data, s->data + s->start + s->pos, len);
    s->pos += len;
    return 0;
}

int stream_read_skip_bytes(stream *s, int len)
{
    CHECK2(s->pos + len >= s->max, "End of stream");
    s->pos += len;
    return 0;
}

int _stream_read_expect_bytes(stream *s, const void *data, int len)
{
    void *tmp = malloc(len);
    CHECK(stream_read_bytes(s, tmp, len));
    CHECK2(memcmp(data, tmp, len), "Byte arrays don't match");

    free(tmp);
    return 0;
}

int stream_read_uint32_t(stream *s_root, stream *s, uint32_t *data)
{
    return stream_read_bytes(s, data, 4);
}

int stream_read_uint16_t(stream *s_root, stream *s, uint16_t *data)
{
    return stream_read_bytes(s, data, 2);
}

int stream_read_uint8_t(stream *s_root, stream *s, uint8_t *data)
{
    return stream_read_bytes(s, data, 1);
}

int stream_read_int32_t(stream *s_root, stream *s, int32_t *data)
{
    return stream_read_bytes(s, data, 4);
}

int stream_read_int16_t(stream *s_root, stream *s, int16_t *data)
{
    return stream_read_bytes(s, data, 2);
}

int stream_read_int8_t(stream *s_root, stream *s, int8_t *data)
{
    return stream_read_bytes(s, data, 1);
}

int stream_write_get_position_absolute(stream *s)
{
    return s->start + s->pos;
}

int stream_write_get_length(stream *s)
{
    return s->pos;
}

int stream_write_make_substream(stream *s, stream *ret)
{
    ret->start = s->start + s->pos;
    ret->pos = 0;
    ret->max = s->max;
    ret->data = s->data;
    return 0;
}

int stream_write_merge_substream(stream *s, stream *sub)
{
    s->data = sub->data;
    s->max = sub->max;
    s->pos += s->pos;
    return 0;
}

int stream_write_bytes(stream *s, const void *data, int length, stream_write_stage stage)
{
    if (s->start + s->pos + length >= s->max)
    {
        s->data = realloc(s->data, s->max * 2);
        s->max *= 2;
    }

    memcpy(s->data + s->start + s->pos, data, length);
    s->pos += length;
    return 0;
}

int stream_write_uint32_t(stream *s_root, stream *s, uint32_t *data, stream_write_stage stage)
{
    return stream_write_bytes(s, data, 4, stage);
}

int stream_write_uint16_t(stream *s_root, stream *s, uint16_t *data, stream_write_stage stage)
{
     return stream_write_bytes(s, data, 2, stage);
}

int stream_write_uint8_t(stream *s_root, stream *s, uint8_t *data, stream_write_stage stage)
{
     return stream_write_bytes(s, data, 1, stage);
}

int stream_write_int32_t(stream *s_root, stream *s, int32_t *data, stream_write_stage stage)
{
     return stream_write_bytes(s, data, 4, stage);
}

int stream_write_int16_t(stream *s_root, stream *s, int16_t *data, stream_write_stage stage)
{
     return stream_write_bytes(s, data, 2, stage);
}

int stream_write_int8_t(stream *s_root, stream *s, int8_t *data, stream_write_stage stage)
{
     return stream_write_bytes(s, data, 1, stage);
}
