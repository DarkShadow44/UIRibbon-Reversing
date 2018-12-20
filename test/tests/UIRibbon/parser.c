#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expr, err) \
   if (expr) { printf("%s:%d - %s\n", __FILE__, __LINE__, err); return 1; }

typedef struct _stream
{
    int start;
    int pos;
    int max;
    char *data;
} stream;

int stream_read_bytes(stream *s, char* ret, int len)
{
    CHECK (s->pos + len >= s->max, "End of stream");
    memcpy(ret, s->data + s->pos, len);
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


typedef struct _type_main
{
    int k;
} type_main;


int read_type_main(stream *s, type_main *ret)
{
    char unk1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
    CHECK(stream_expect_bytes(s, unk1), "Byte arrays don't match");

    return 0;
}

int stream_from_file(char *path, stream *s)
{
    FILE *file;

    s->start = 0;
    s->pos = 0;

    file = fopen(path, "r");
    CHECK(file == NULL, "Failed to open file");

    fseek(file, 0, SEEK_END);
    s->max = ftell(file);
    fseek(file, 0, SEEK_SET);

    s->data = malloc(s->max);
    fread(s->data, s->max, 1, file);

    fclose(file);
    return 0;
}

int main()
{
    type_main ribbon;
    stream s;

    CHECK(stream_from_file("../x.bml", &s), "Failed to read file")

    CHECK(read_type_main(&s, &ribbon), "Failed to parse file");

   return 0;
}
