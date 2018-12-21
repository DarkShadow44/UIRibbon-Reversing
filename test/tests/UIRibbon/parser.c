#include "shared.h"

int read_type_string(stream *s, type_string *ret)
{
    CHECK(stream_skip_bytes(s, 1));
    CHECK(stream_read_uint16(s, &ret->size_str));
    ret->str = malloc(ret->size_str);
    CHECK(stream_read_bytes(s, ret->str, ret->size_str));
    return 0;
}

int read_type_strings(stream *s, type_strings *ret)
{
    int i;

    CHECK(stream_skip_bytes(s, 3));
    CHECK(stream_read_uint8(s, &ret->count_strings));
    ret->strings = malloc(sizeof(type_string) * ret->count_strings);
    for (i = 0; i < ret->count_strings; i++)
    {
         CHECK(read_type_string(s, &ret->strings[i]));
    }
    return 0;
}

int read_type_command_resource_single(stream *s, type_command_resource_single *ret)
 {
     uint8_t resource_type;
     CHECK(stream_read_uint8(s, &resource_type));
     ret->type = resource_type;
     CHECK(stream_read_uint32(s, &ret->resource_id));
     if (ret->type == RIBBON_RESOURCE_SMALLIMAGE
        || ret->type == RIBBON_RESOURCE_LARGEIMAGE
        || ret->type == RIBBON_RESOURCE_SMALLHIGHCONTRASTIMAGE
        || ret->type == RIBBON_RESOURCE_LARGEHIGHCONTRASTIMAGE)
     {
         CHECK(stream_read_uint16(s, &ret->mindpi));
     }
     return 0;
 }

int read_type_command_resources(stream *s, type_command_resources *ret)
{
    int i;
    CHECK(stream_read_uint32(s, &ret->command_id));
    CHECK(stream_read_uint8(s, &ret->count_resources));
    ret->resources = malloc(sizeof(type_command_resource_single) * ret->count_resources);
    for (i = 0; i < ret->command_id; i++)
    {
        CHECK(read_type_command_resource_single(s, &ret->resources[i]))
    }
    return 0;
}

int read_type_tab(stream *s, type_tab *ret)
{
    return 0;
}

int read_type_ribbon_tabs_normal(stream *s, type_ribbon_tabs_normal *ret)
{
    int i;

    CHECK(stream_read_uint16(s, &ret->count_tabs));
    ret->tabs = malloc(sizeof(type_tab) * ret->count_tabs);
    for (i = 0; i < ret->count_tabs; i++)
    {
        CHECK(read_type_tab(s, &ret->tabs[i]));
    }
    return 0;
}

int read_type_ribbon_tabs_context(stream *s, type_ribbon_tabs_context *ret)
{
    return 0;
}

int read_type_ribbon_tabs_applicationmenu(stream *s, type_ribbon_tabs_applicationmenu *ret)
{
    return 0;
}

int read_type_block_tabs(stream *s, type_block_tabs* ret)
{
    uint8_t tab_type;

    CHECK(stream_skip_bytes(s, 1));
    CHECK(stream_read_uint8(s, &tab_type));
    ret->tab_type = tab_type;
    switch (ret->tab_type)
    {
    case RIBBON_TAB_APPLICATIONMENU:
        CHECK(read_type_ribbon_tabs_applicationmenu(s, &ret->applicationmenu));
        break;
    case RIBBON_TAB_NORMAL:
    case RIBBON_TAB_HELP:
        CHECK(read_type_ribbon_tabs_normal(s, &ret->normal));
        break;
    case RIBBON_TAB_CONTEXT:
        CHECK(read_type_ribbon_tabs_context(s, &ret->context));
        break;
    }
    return 0;
}

int read_type_block_quickaccess(stream *s, type_block_quickaccess* ret)
{
    return 0;
}

int read_type_block_generic(stream *s, type_block_generic* ret)
{
    uint8_t block_type;
    CHECK(stream_read_uint8(s, &block_type));
    ret->block_type = block_type;
    switch (ret->block_type)
    {
    case RIBBON_BLOCK_TABS:
        CHECK(read_type_block_tabs(s, &ret->tabs));
        break;
    case RIBBON_BLOCK_QUICKACCESSTOOLBAR:
        CHECK(read_type_block_quickaccess(s, &ret->quickaccess));
        break;
    }
    return 0;
}

int read_type_ribbon(stream *s, type_ribbon *ret)
{
    char unk1[] = {1, 1, 0x0b, 9, 0};
    CHECK(stream_skip_bytes(s, 1));
    CHECK(stream_expect_bytes(s, unk1));
    CHECK(read_type_block_generic(s, &ret->block1));
    return 0;
}

int read_type_main(stream *s, type_main *ret)
{
    char unk1[] = {0, 18, 0, 0, 0, 0, 0, 1, 0};
    char magic[] = {0x53, 0x43, 0x42, 0x69, 0x6E}; /* SCBin */
    uint16_t size_strings;
    stream stream_strings;
    uint32_t size_command_container;
    stream stream_command_container;
    uint16_t size_ribbon;
    stream stream_ribbon;
    char unk2[] = {0x00, 0x00, 0x16, 0x00, 0x24, 0x00, 0x10};
    int i;


    CHECK(stream_expect_bytes(s, unk1));
    CHECK2(stream_expect_bytes(s, magic), "Signature wrong");
    CHECK(stream_read_uint32(s, &ret->length_this_file));
    CHECK(stream_skip_bytes(s, 1));
    CHECK(stream_read_uint16(s, &size_strings));
    CHECK(stream_make_substream(s, &stream_strings, size_strings - 2));
    CHECK(read_type_strings(&stream_strings, &ret->strings));
    CHECK(stream_read_uint16(s, &ret->count_command_resource));
    CHECK(stream_skip_bytes(s, 2));
    ret->command_resources = malloc(sizeof(type_command_resources) * ret->count_command_resource);
    for (i = 0; i< ret->count_command_resource; i++)
    {
        CHECK(read_type_command_resources(s, &ret->command_resources[i]));
    }
    CHECK(stream_skip_bytes(s, 1));
    CHECK(stream_read_uint32(s, &size_command_container));
    CHECK(stream_make_substream(s, &stream_command_container, size_command_container - 4));
    CHECK(stream_skip_bytes(s, 4));
    CHECK(stream_expect_bytes(s, unk2));
    CHECK(stream_read_uint16(s, &size_ribbon));
    CHECK(stream_make_substream(s, &stream_ribbon, size_ribbon));
    CHECK(read_type_ribbon(&stream_ribbon, &ret->ribbon));

    return 0;
}

