#include "shared.h"

int stream_from_testdata(char *name, stream *s)
{
    const test_data *test = get_test_data(name);
    CHECK(test == NULL, "Failed to get test data");

    s->start = s->pos = 0;
    s->max = test->bml_len;
    s->data = test->bml_data;
    return 0;
}

int main()
{
    type_main ribbon;
    stream s;

    CHECK(stream_from_testdata("size_largetosmall__small_small_small", &s), "Failed to get test data")

    CHECK(read_type_main(&s, &ribbon), "Failed to parse file");

   return 0;
}
