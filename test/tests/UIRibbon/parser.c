#include "shared.h"



int stream_read_bytes(stream *s, char* ret, int len)
{
    CHECK (s->pos + len >= s->max, "End of stream");
    memcpy(ret, s->data + s->start + s->pos, len);
    s->pos += len;
    return 0;
}


int _stream_expect_bytes(stream *s, char *data, int len)
{
    char *tmp = malloc(len);
    CHECK(stream_read_bytes(s, tmp, len), "Failed to read bytes");
    CHECK(memcmp(data, tmp, len), "Byte arrays don't match");

    free(tmp);
    return 0;
}

#define stream_expect_bytes(s, data) \
    _stream_expect_bytes(s, data, sizeof(data))

int read_type_main(stream *s, type_main *ret)
{
    char unk1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
    CHECK(stream_expect_bytes(s, unk1), "Byte arrays don't match");

    return 0;
}

