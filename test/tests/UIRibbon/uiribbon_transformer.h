#include "parser_uiribbon.h"

typedef int bool;

typedef enum
{
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_OPEN_GROUP = 0,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_CLOSE_GROUP = 1,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR = 2,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_INVISIBLE_SEPARATOR = 3,
    UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK = 4,
} uiribbon_sizedefinition_group_order_command;

typedef enum
{
    UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON = 0,
} uiribbon_control_type;

typedef struct
{
    bool sizeLarge;
    bool labelvisible;
    bool imagevisible;
} uiribbon_sizedefinition_control;

typedef struct
{
    uiribbon_sizedefinition_control large;
    uiribbon_sizedefinition_control medium;
    uiribbon_sizedefinition_control small;
} uiribbon_sizedefinitions_control;

typedef struct
{
    bool is_special;
    union
    {
        int command_id;
        uiribbon_sizedefinition_group_order_command special_command;
    };
} uiribbon_sizedefinition_group_order;

typedef struct
{
    int count_orders;
    uiribbon_sizedefinition_group_order *orders;

} uiribbon_sizedefinition_group;

typedef struct
{
    uiribbon_sizedefinition_group large;
    uiribbon_sizedefinition_group medium;
    uiribbon_sizedefinition_group small;
} uiribbon_sizedefinitions_orders;

typedef struct
{
    uiribbon_control_type type;
    int id;
    uiribbon_sizedefinitions_control *size_definitions;
} uiribbon_control;

typedef struct
{
    int id;
    int count_controls;
    uiribbon_control *controls;
    uiribbon_sizedefinitions_orders *sizedefinition_orders;
} uiribbon_group;

typedef struct
{
    int id;
    int count_groups;
    uiribbon_group *groups;
} uiribbon_tab;

typedef struct
{
    int id;
    int count_tabs;
    uiribbon_tab *tabs;
} uiribbon_tabgroup;


typedef struct
{
    int count_tabs;
    uiribbon_tab *tabs;
    int count_contexttabgroups;
    uiribbon_tabgroup *contexttabgroups;
} uiribbon_main;

void transform_uiribbon(type_uiribbon *src, uiribbon_main *ret);
