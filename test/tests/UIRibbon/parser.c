#include "shared.h"

int read_type_string(stream *s, type_string *ret)
{
    CHECK(stream_skip_bytes(s, 1), "");
    CHECK(stream_read_uint16(s, &ret->size_str), "");
    ret->str = malloc(ret->size_str);
    CHECK(stream_read_bytes(s, ret->str, ret->size_str), "");
    return 0;
}

int read_type_strings(stream *s, type_strings *ret)
{
    int i;

    CHECK(stream_skip_bytes(s, 3), "");
    CHECK(stream_read_uint8(s, &ret->count_strings), "");
    ret->strings = malloc(sizeof(type_string) * ret->count_strings);
    for (i = 0; i < ret->count_strings; i++)
    {
         CHECK(read_type_string(s, &ret->strings[i]), "");
    }
    return 0;
}

int read_type_main(stream *s, type_main *ret)
{
    char unk1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
    char magic[] = {0x53, 0x43, 0x42, 0x69, 0x6E}; /* SCBin */
    uint16_t size_strings;
    stream stream_strings;


    CHECK(stream_expect_bytes(s, unk1), "");
    CHECK(stream_expect_bytes(s, magic), "Signature wrong");
    CHECK(stream_read_uint32(s, &ret->length_this_file), "");
    CHECK(stream_skip_bytes(s, 1), "");
    CHECK(stream_read_uint16(s, &size_strings), "");
    CHECK(stream_make_substream(s, &stream_strings, size_strings), "");
    CHECK(read_type_strings(&stream_strings, &ret->strings), "");

    return 0;
}

