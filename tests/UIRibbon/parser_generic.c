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
    ret->allocated = s->allocated;
    ret->data = s->data;
    ret->parent = s;
    ret->is_instance = 0;
    return 0;
}

int stream_write_make_substream_instance(stream *s_root, stream *ret, int pos)
{
    ret->start = pos;
    ret->pos = 0;
    ret->max = s_root->max;
    ret->allocated = s_root->allocated;
    ret->data = s_root->data;
    ret->parent = s_root;
    ret->is_instance = 1;

    return 0;
}

static void stream_update_pos(stream *s, int offset_pos)
{
    int new_max = s->start + s->pos + offset_pos;
    stream *current = s;
    while (current != NULL)
    {
        current->pos += offset_pos;
        current->data = s->data;
        current->allocated = s->allocated;

        if (new_max > current->max)
            current->max = new_max;

         /* Don't relay pos offset from instance stream up*/
        if (current->is_instance)
            offset_pos = 0;

        current = current->parent;
    }
}

int stream_write_bytes(stream *s, const void *data, int length, stream_write_stage stage, BOOL from_instance)
{
    if (stage == STREAM_WRITE_STAGE_WRITE)
    {
        if (s->start + s->pos + length >= s->allocated)
        {
            int new_len = (s->allocated + length) * 2;
            s->data = realloc(s->data, new_len);
            s->allocated = new_len;
        }

        memcpy(s->data + s->start + s->pos, data, length);
    }

    if ((from_instance && stage != STREAM_WRITE_STAGE_DRYRUN_SEQUENCE) || (!from_instance && stage != STREAM_WRITE_STAGE_DRYRUN_INSTANCE))
    {
         stream_update_pos(s, length);
    }

    return 0;
}

int stream_write_uint32_t(stream *s_root, stream *s, uint32_t *data, stream_write_stage stage, BOOL from_instance)
{
    return stream_write_bytes(s, data, 4, stage, from_instance);
}

int stream_write_uint16_t(stream *s_root, stream *s, uint16_t *data, stream_write_stage stage, BOOL from_instance)
{
     return stream_write_bytes(s, data, 2, stage, from_instance);
}

int stream_write_uint8_t(stream *s_root, stream *s, uint8_t *data, stream_write_stage stage, BOOL from_instance)
{
     return stream_write_bytes(s, data, 1, stage, from_instance);
}

int stream_write_int32_t(stream *s_root, stream *s, int32_t *data, stream_write_stage stage, BOOL from_instance)
{
     return stream_write_bytes(s, data, 4, stage, from_instance);
}

int stream_write_int16_t(stream *s_root, stream *s, int16_t *data, stream_write_stage stage, BOOL from_instance)
{
     return stream_write_bytes(s, data, 2, stage, from_instance);
}

int stream_write_int8_t(stream *s_root, stream *s, int8_t *data, stream_write_stage stage, BOOL from_instance)
{
     return stream_write_bytes(s, data, 1, stage, from_instance);
}
