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

typedef struct _stream
{
    int start;
    int pos;
    int max;
    const char *data;
} stream;

typedef struct _type_main
{
    int k;
} type_main;

int read_type_main(stream *s, type_main *ret);
