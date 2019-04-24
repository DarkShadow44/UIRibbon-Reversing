#include "parser_generic.h"

int stream_read_make_substream(stream *s, stream *ret, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");

    ret->start = s->start + s->pos;
    ret->pos = 0;
    ret->max = ret->start + len;
    ret->contents = s->contents;

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
    ret->contents = s_root->contents;
    return 0;
}

int stream_read_bytes(stream *s, void *data, int len)
{
    CHECK2(s->start + s->pos + len > s->max, "End of stream");
    memcpy(data, s->contents->data + s->start + s->pos, len);
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

int stream_read_uint32_t(stream *s_root, stream *s, uint32_t *data, void *_root)
{
    return stream_read_bytes(s, data, 4);
}

int stream_read_uint16_t(stream *s_root, stream *s, uint16_t *data, void *_root)
{
    return stream_read_bytes(s, data, 2);
}

int stream_read_uint8_t(stream *s_root, stream *s, uint8_t *data, void *_root)
{
    return stream_read_bytes(s, data, 1);
}

int stream_read_int32_t(stream *s_root, stream *s, int32_t *data, void *_root)
{
    return stream_read_bytes(s, data, 4);
}

int stream_read_int16_t(stream *s_root, stream *s, int16_t *data, void *_root)
{
    return stream_read_bytes(s, data, 2);
}

int stream_read_int8_t(stream *s_root, stream *s, int8_t *data, void *_root)
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
    ret->contents = s->contents;
    ret->parent = s;
    return 0;
}

int stream_write_make_substream_instance(stream *s_root, stream *ret, int pos)
{
    ret->start = pos;
    ret->pos = 0;
    ret->max = s_root->max;
    ret->contents = s_root->contents;
    ret->parent = NULL;

    return 0;
}

static void stream_update_pos(stream *s, int offset_pos)
{
    int new_max = s->start + s->pos + offset_pos;
    stream *current = s;
    while (current != NULL)
    {
        if (new_max > current->max)
            current->max = new_max;
        current->pos += offset_pos;
        current = current->parent;
    }
}

int stream_write_bytes(stream *s, const void *data, int length, stream_write_stage stage, BOOL do_sequence, void *_root)
{
    if (stage == STREAM_WRITE_STAGE_WRITE)
    {
        stream_data *contents= s->contents;
        if (s->start + s->pos + length >= contents->allocated)
        {
            int new_len = (contents->allocated + length) * 2;
            contents->data= realloc(contents->data, new_len);
            contents->allocated = new_len;
        }

        memcpy(contents->data + s->start + s->pos, data, length);
    }

    if (stage == STREAM_WRITE_STAGE_WRITE || do_sequence)
    {
         stream_update_pos(s, length);
    }

    return 0;
}

int stream_write_uint32_t(stream *s_root, stream *s, uint32_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
    return stream_write_bytes(s, data, 4, stage, do_sequence, _root);
}

int stream_write_uint16_t(stream *s_root, stream *s, uint16_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
     return stream_write_bytes(s, data, 2, stage, do_sequence, _root);
}

int stream_write_uint8_t(stream *s_root, stream *s, uint8_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
     return stream_write_bytes(s, data, 1, stage, do_sequence, _root);
}

int stream_write_int32_t(stream *s_root, stream *s, int32_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
     return stream_write_bytes(s, data, 4, stage, do_sequence, _root);
}

int stream_write_int16_t(stream *s_root, stream *s, int16_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
     return stream_write_bytes(s, data, 2, stage, do_sequence, _root);
}

int stream_write_int8_t(stream *s_root, stream *s, int8_t *data, stream_write_stage stage, BOOL do_sequence, void *_root)
{
     return stream_write_bytes(s, data, 1, stage, do_sequence, _root);
}

stream *create_read_stream(const char *data, int len)
{
    stream *s = malloc(sizeof(stream));
    memset(s, 0, sizeof(stream));
    s->contents = malloc(sizeof(stream_data));
    s->contents->data = (char *)data;
    s->contents->allocated = len;
    s->max = len;

    return s;
}

stream *create_write_stream()
{
    stream *s = malloc(sizeof(stream));
    memset(s, 0, sizeof(stream));
    s->contents = malloc(sizeof(stream_data));
    s->contents->data = malloc(100);
    s->contents->allocated = 100;

    return s;
}

void destroy_read_stream(stream *s)
{
    free(s->contents);
    free(s);
}

void destroy_write_stream(stream *s)
{
    free(s->contents->data);
    free(s->contents);
    free(s);
}
