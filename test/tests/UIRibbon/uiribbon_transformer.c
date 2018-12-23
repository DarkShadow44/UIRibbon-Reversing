#include "uiribbon_transformer.h"

int transform_id(type_id *id)
{
    switch(id->flag)
    {
    case 2:
        return id->block_2;
    case 3:
        return id->block_3;
    case 4:
        return id->block_4;
    }
    return -1;
}

uiribbon_control_type transform_control_type(enum_type_control type)
{
    switch (type)
    {
    case UIRIBBON_TYPE_CONTROL_BUTTON:
        return UIRIBBON_TRANSFORMED_CONTROL_TYPE_BUTTON;
    }
    return -1;
}

void transform_control(type_control *src_control, uiribbon_control *ret_control)
{
    int i;

    ret_control->type = transform_control_type(src_control->block_type);
    ret_control->size_definitions = NULL;
    for (i = 0; i < src_control->block.count_blocks; i++)
    {
        type_control_block_generic *src_block = &src_control->block.blocks[i];
        switch (src_block->block_type)
        {
        case UIRIBBON_CONTROL_BLOCK_TYPE_ID:
            ret_control->id = transform_id(&src_block->block_id);
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.sizeLarge = src_block->block_sizedefinition_imagesize.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE;
            ret_control->size_definitions->medium.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            ret_control->size_definitions->small.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGESIZE_MIXED:
            if (src_block->block_sizedefinition_imagesize_mixed.sizedefinition_imagesize_mixed == UIRIBBON_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLISSMALL)
            {
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            else if(src_block->block_sizedefinition_imagesize_mixed.sizedefinition_imagesize_mixed == UIRIBBON_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLANDMEDIUMARESMALL)
            {
                ret_control->size_definitions->medium.sizeLarge = 0;
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.labelvisible = src_block->block_sizedefinition_labelvisible.sizedefinition_labelvisible == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.labelvisible = ret_control->size_definitions->large.labelvisible;
            ret_control->size_definitions->small.labelvisible = ret_control->size_definitions->large.labelvisible;
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_LABELVISIBLE_MIXED:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.labelvisible = 1;
            if (src_block->block_sizedefinition_labelvisible_mixed.sizedefinition_labelvisible_mixed == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALL)
            {
                ret_control->size_definitions->medium.labelvisible = 1;
                ret_control->size_definitions->small.labelvisible = 0;
            }
            else if (src_block->block_sizedefinition_labelvisible_mixed.sizedefinition_labelvisible_mixed == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALLANDMEDIUM)
            {
                ret_control->size_definitions->medium.labelvisible = 0;
                ret_control->size_definitions->small.labelvisible = 0;
            }

            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_IMAGEVISIBLE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));

            ret_control->size_definitions->large.imagevisible = src_block->block_sizedefinition_imagevisible.sizedefinition_imagevisible == UIRIBBON_SIZEDEFINITION_IMAGEVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.imagevisible = ret_control->size_definitions->large.imagevisible;
            ret_control->size_definitions->small.imagevisible = ret_control->size_definitions->large.imagevisible;
            break;
        }
    }
}

void transform_sizedefinition_group(type_uiribbon *root, type_sizedefinition *src, uiribbon_sizedefinition_group *ret)
{
    int i;

    ret->count_orders = src->count_commands;
    ret->orders = malloc(sizeof(uiribbon_sizedefinition_group_order) * ret->count_orders);
    for (i = 0; i < ret->count_orders; i++)
    {
        uiribbon_sizedefinition_group_order *ret_order = &ret->orders[i];
        type_sizedefinitions_command *src_order = &src->commands[i];

        if (src_order->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_COMMAND)
        {
            ret_order->is_special = 0;
            ret_order->command_id = src->commands[i].command_id;
        }
        else if (src_order->flags_command == UIRIBBON_SIZEDEFINITIONS_COMMAND_SPECIAL)
        {
            char special;
            ret_order->is_special = 1;
            special = root->strings.strings[src_order->string_id].str[0];
            switch(special)
            {
            case '{':
                ret_order->special_command = UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_OPEN_GROUP;
                break;
            case '}':
                ret_order->special_command = UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_CLOSE_GROUP;
                break;
            case '|':
                ret_order->special_command = UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_VISIBLE_SEPARATOR;
                break;
            case ':':
                ret_order->special_command = UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_INVISIBLE_SEPARATOR;
                break;
            case ';':
                ret_order->special_command = UIRIBBON_TRANSFORMED_SIZEINFO_ORDER_BREAK;
                break;
            }
        }
    }
}

void transform_group(type_uiribbon *root, type_group_info *src_group, uiribbon_group *ret_group)
{
    int i;
    ret_group->id = transform_id(&src_group->id);
    ret_group->count_controls = src_group->group_elements_info.sub_count;
    ret_group->controls = malloc(sizeof(uiribbon_control) * ret_group->count_controls);

    for (i = 0; i < ret_group->count_controls; i++)
    {
        transform_control(&src_group->group_elements_info.subcontents[i], &ret_group->controls[i]);
    }

    ret_group->sizedefinition_orders = NULL;
    if (src_group->group_elements_info.unk10 == 5)
    {
        ret_group->sizedefinition_orders = malloc(sizeof(uiribbon_sizedefinitions_orders));
        transform_sizedefinition_group(root, &src_group->group_elements_info.sizedefinition_large, &ret_group->sizedefinition_orders->large);
        transform_sizedefinition_group(root, &src_group->group_elements_info.sizedefinition_medium, &ret_group->sizedefinition_orders->medium);
        transform_sizedefinition_group(root, &src_group->group_elements_info.sizedefinition_small, &ret_group->sizedefinition_orders->small);
    }
}

void transform_tabs_ext(type_uiribbon *root, type_tab_extended *src_ext, uiribbon_tab *ret_tab)
{
    int i;

    ret_tab->count_groups = src_ext->count_groupinfo;
    ret_tab->groups = malloc(sizeof(uiribbon_group) * ret_tab->count_groups);

    for (i = 0; i < ret_tab->count_groups; i++)
    {
        transform_group(root, &src_ext->groupinfo[i], &ret_tab->groups[i]);
    }
}

void transform_tabs(type_uiribbon *root, type_ribbon_tabs_normal *tabs_normal, uiribbon_main *ret)
{
    int i;

    ret->count_tabs = tabs_normal->count_tabs;
    ret->tabs = malloc(sizeof(uiribbon_tab) * ret->count_tabs);
    for (i = 0; i < ret->count_tabs; i++)
    {
        uiribbon_tab *ret_tab = &ret->tabs[i];
        type_tab *src_tab = &tabs_normal->tabs[i];

        ret_tab->id = transform_id(&src_tab->id);

        transform_tabs_ext(root, &src_tab->ext, ret_tab);
    }

}

void transform_uiribbon(type_uiribbon *src, uiribbon_main *ret)
{
    int i;

    for (i = 0; i < src->unk6.ribbon.count_blocks; i++)
    {
        type_block_generic *src_block = &src->unk6.ribbon.block1[i];
        if (src_block->block_type == UIRIBBON_BLOCK_TYPE_RIBBON_TABS)
        {
            if(src_block->block_type == UIRIBBON_BLOCK_TYPE_RIBBON_TABS)
            {
                if (src_block->block_ribbon_tabs.tab_type == UIRIBBON_TAB_TYPE_NORMAL)
                {
                    transform_tabs(src, &src_block->block_ribbon_tabs.block_normal, ret);
                }
            }
        }
    }
}
