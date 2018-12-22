#include "parser_uiribbon.h"

typedef int bool;

typedef struct
{
    bool sizeLarge;
    bool labelvisible;
    bool imagevisible;
} uiribbon_sizedefinition;

typedef struct
{
    uiribbon_sizedefinition large;
    uiribbon_sizedefinition medium;
    uiribbon_sizedefinition small;
} uiribbon_sizedefinitions;

typedef struct
{
    enum_type_control type;
    int id;
    uiribbon_sizedefinitions *size_definitions;
} uiribbon_control;

typedef struct
{
    int count_controls;
    uiribbon_control *controls;
} uiribbon_group;

typedef struct
{
    int count_groups;
    uiribbon_group *groups;
} uiribbon_tab;

typedef struct
{
    int count_tabs;
    uiribbon_tab *tabs;

} uiribbon_main;

void transform_uiribbon(type_uiribbon *src, uiribbon_main *ret);
