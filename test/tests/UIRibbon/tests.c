#include "parser_uiribbon.h"

void _ok(int expr, const char *message, const char *file, int line)
{
    if (!expr)
        printf("%s:%d - %s", file, line, message);
}

#define ok(expr, message) \
    _ok(expr, message, __FILE__, __LINE__)

int _parse_from_testdata(char *name, type_uiribbon *ret, const char *file, int line)
{
    stream s;
    int error;
    const test_data *test = get_test_data(name);
    _ok(test != NULL, "Failed to get test data", file, line);
    if (!test)
        return 1;

    s.start = s.pos = 0;
    s.max = test->bml_len;
    s.data = test->bml_data;

    error = read_type_uiribbon(&s, ret);
    _ok(error == 0, "Failed to parse file", file, line);
    return error;
}

#define parse_from_testdata(name, ret) \
    _parse_from_testdata(name, ret, __FILE__, __LINE__)

int main()
{
    type_uiribbon uiribbon;

    CHECK(parse_from_testdata("count_tabs", &uiribbon));
    ok(uiribbon.unk6.ribbon.block1[0].block_type == BLOCK_TYPE_RIBBON_TABS, "Wrong blocktype");
    ok(uiribbon.unk6.ribbon.block1[0].block_tabs.tab_type == TAB_TYPE_NORMAL, "Wrong blocktype");
    ok(uiribbon.unk6.ribbon.block1[0].block_tabs.block_normal.count_tabs == 6, "Wrong count");

    return 0;
}
