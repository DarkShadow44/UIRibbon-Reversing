#include "uiribbon_transformer.h"

void _ok(int expr, const char *message, const char *file, int line)
{
    if (!expr)
        printf("%s:%d - %s", file, line, message);
}

#define ok(expr, message) \
    _ok(expr, message, __FILE__, __LINE__)

#define ASSERT(expr) \
    ok(expr, "Assert failed")

int _parse_from_testdata(char *name, uiribbon_main *ret, const char *file, int line)
{
    stream s;
    int error;
    type_uiribbon uiribbon;
    const test_data *test = get_test_data(name);

    _ok(test != NULL, "Failed to get test data", file, line);
    if (!test)
        return 1;

    s.start = s.pos = 0;
    s.max = test->bml_len;
    s.data = test->bml_data;

    error = read_type_uiribbon(&s, &uiribbon);
    _ok(error == 0, "Failed to parse file", file, line);

    transform_uiribbon(&uiribbon, ret);
    return error;
}

#define parse_from_testdata(name, ret) \
    _parse_from_testdata(name, ret, __FILE__, __LINE__)

static int test_tabs(void)
{
    /* uiribbon_main uiribbon;

    CHECK(parse_from_testdata("count_tabs", &uiribbon)); needs dynamic tab ext solved first
    ASSERT(uiribbon.count_tabs == 6); */

    return 0;
}

static int test_sizeinfo(void)
{
    uiribbon_main uiribbon;
    uiribbon_control *control;

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__small_small_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 0);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_small_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 0);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_small", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 0);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_large", &uiribbon));
    ASSERT(uiribbon.count_tabs == 1);
    ASSERT(uiribbon.tabs[0].count_groups == 1);
    ASSERT(uiribbon.tabs[0].groups[0].count_controls == 1);
    control = &uiribbon.tabs[0].groups[0].controls[0];
    ASSERT(control->id == 10003);
    ASSERT(control->type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(control->size_definitions != NULL);
    ASSERT(control->size_definitions->large.sizeLarge == 1);
    ASSERT(control->size_definitions->medium.sizeLarge == 1);
    ASSERT(control->size_definitions->small.sizeLarge == 1);

    return 0;
}



int main()
{
    CHECK(test_tabs());
    CHECK(test_sizeinfo());

    return 0;
}
