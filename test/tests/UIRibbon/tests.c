#include "parser_uiribbon.h"

void _ok(int expr, const char *message, const char *file, int line)
{
    if (!expr)
        printf("%s:%d - %s", file, line, message);
}

#define ok(expr, message) \
    _ok(expr, message, __FILE__, __LINE__)

#define ASSERT(expr) \
    ok(expr, "Assert failed")

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

static int test_tabs(void)
{
    type_uiribbon uiribbon;

    CHECK(parse_from_testdata("count_tabs", &uiribbon));
    ASSERT(uiribbon.unk6.ribbon.block1[0].block_type == UIRIBBON_BLOCK_TYPE_RIBBON_TABS);
    ASSERT(uiribbon.unk6.ribbon.block1[0].block_tabs.tab_type == UIRIBBON_TAB_TYPE_NORMAL);
    ASSERT(uiribbon.unk6.ribbon.block1[0].block_tabs.block_normal.count_tabs == 6);

    return 0;
}

static int test_sizeinfo(void)
{
    type_uiribbon uiribbon;
    type_group_elements_info *group_elements_info;
    type_control_block_generic *blocks;

    /* Size */

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__small_small_small", &uiribbon));
    ASSERT(uiribbon.unk6.ribbon_tab_info[0].count_groupinfo == 1);
    group_elements_info = &uiribbon.unk6.ribbon_tab_info[0].groupinfo[0].group_elements_info;
    ASSERT(group_elements_info->sub_count == 1);
    ASSERT(group_elements_info->subcontents[0].block_type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(group_elements_info->subcontents[0].block.count_blocks == 4);
    blocks = group_elements_info->subcontents[0].block.blocks;
    ASSERT(blocks[0].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK37);
    ASSERT(blocks[0].block_37.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_SMALL);
    ASSERT(blocks[1].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK9);
    ASSERT(blocks[2].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK36);
    ASSERT(blocks[3].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_ID);
    ASSERT(blocks[3].block_id.uint16_t == 10003);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_small_small", &uiribbon));
    ASSERT(uiribbon.unk6.ribbon_tab_info[0].count_groupinfo == 1);
    group_elements_info = &uiribbon.unk6.ribbon_tab_info[0].groupinfo[0].group_elements_info;
    ASSERT(group_elements_info->sub_count == 1);
    ASSERT(group_elements_info->subcontents[0].block_type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(group_elements_info->subcontents[0].block.count_blocks == 5);
    blocks = group_elements_info->subcontents[0].block.blocks;
    ASSERT(blocks[0].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK37);
    ASSERT(blocks[0].block_37.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE);
    ASSERT(blocks[1].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_MAYBE_SIZEDEFINITION_OVERRIDE_IMAGESIZE);
    ASSERT(blocks[1].block_imagesize.sizedefinition_imagesize_override == UIRIBBON_SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLANDMEDIUMARESMALL);
    ASSERT(blocks[2].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK9);
    ASSERT(blocks[3].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK36);
    ASSERT(blocks[4].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_ID);
    ASSERT(blocks[4].block_id.uint16_t == 10003);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_small", &uiribbon));
    ASSERT(uiribbon.unk6.ribbon_tab_info[0].count_groupinfo == 1);
    group_elements_info = &uiribbon.unk6.ribbon_tab_info[0].groupinfo[0].group_elements_info;
    ASSERT(group_elements_info->sub_count == 1);
    ASSERT(group_elements_info->subcontents[0].block_type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(group_elements_info->subcontents[0].block.count_blocks == 5);
    blocks = group_elements_info->subcontents[0].block.blocks;
    ASSERT(blocks[0].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK37);
    ASSERT(blocks[0].block_37.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE);
    ASSERT(blocks[1].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_MAYBE_SIZEDEFINITION_OVERRIDE_IMAGESIZE);
    ASSERT(blocks[1].block_imagesize.sizedefinition_imagesize_override == UIRIBBON_SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLISSMALL);
    ASSERT(blocks[2].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK9);
    ASSERT(blocks[3].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK36);
    ASSERT(blocks[4].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_ID);
    ASSERT(blocks[4].block_id.uint16_t == 10003);

    CHECK(parse_from_testdata("sizeinfo_size_largetosmall__large_large_large", &uiribbon));
    ASSERT(uiribbon.unk6.ribbon_tab_info[0].count_groupinfo == 1);
    group_elements_info = &uiribbon.unk6.ribbon_tab_info[0].groupinfo[0].group_elements_info;
    ASSERT(group_elements_info->sub_count == 1);
    ASSERT(group_elements_info->subcontents[0].block_type == UIRIBBON_TYPE_CONTROL_BUTTON);
    ASSERT(group_elements_info->subcontents[0].block.count_blocks == 4);
    blocks = group_elements_info->subcontents[0].block.blocks;
    ASSERT(blocks[0].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK37);
    ASSERT(blocks[0].block_37.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE);
    ASSERT(blocks[1].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK9);
    ASSERT(blocks[2].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_UNK36);
    ASSERT(blocks[3].block_type == UIRIBBON_CONTROL_BLOCK_TYPE_ID);
    ASSERT(blocks[3].block_id.uint16_t == 10003);

    return 0;
}

int main()
{
    CHECK(test_tabs());
    CHECK(test_sizeinfo());

    return 0;
}
