#include "uiribbon_transformer.h"

void transform_tabs(type_ribbon_tabs_normal *tabs_normal, uiribbon_main *ret)
{
    ret->count_tabs = tabs_normal->count_tabs;
    ret->tabs = malloc(sizeof(uiribbon_tab) * ret->count_tabs);
}

void transform_control(type_control *src_control, uiribbon_control *ret_control)
{
    int i;

    ret_control->type = src_control->block_type;
    ret_control->size_definitions = NULL;
    for (i = 0; i < src_control->block.count_blocks; i++)
    {
        type_control_block_generic *src_block = &src_control->block.blocks[i];
        switch (src_block->block_type)
        {
        case UIRIBBON_CONTROL_BLOCK_TYPE_ID:
            switch (src_block->block_id.flag)
            {
            case 4:
                ret_control->id = src_block->block_id.uint8_t;
                break;
            case 3:
                ret_control->id = src_block->block_id.uint16_t;
                break;
            }
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_UNK37:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions));
            ret_control->size_definitions->large.sizeLarge = src_block->block_37.sizedefinition_imagesize == UIRIBBON_SIZEDEFINITION_IMAGESIZE_LARGE;
            ret_control->size_definitions->medium.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            ret_control->size_definitions->small.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_SIZEDEFINITION_OVERRIDE_IMAGESIZE:
            if (src_block->block_imagesize.sizedefinition_imagesize_override == UIRIBBON_SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLISSMALL)
            {
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            else if(src_block->block_imagesize.sizedefinition_imagesize_override == UIRIBBON_SIZEDEFINITION_IMAGESIZE_OVERRIDE_SMALLANDMEDIUMARESMALL)
            {
                ret_control->size_definitions->medium.sizeLarge = 0;
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_UNK9:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions));
            ret_control->size_definitions->large.labelvisible = src_block->block_9.sizedefinition_labelvisible == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.labelvisible = ret_control->size_definitions->large.labelvisible;
            ret_control->size_definitions->small.labelvisible = ret_control->size_definitions->large.labelvisible;
            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_UNK6:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions));
            ret_control->size_definitions->large.labelvisible = 1;
            if (src_block->block_6.sizedefinition_labelvisible_override == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_OVERRIDE_OVERRIDESMALL)
            {
                ret_control->size_definitions->medium.labelvisible = 1;
                ret_control->size_definitions->small.labelvisible = 0;
            }
            else if (src_block->block_6.sizedefinition_labelvisible_override == UIRIBBON_SIZEDEFINITION_LABELVISIBLE_OVERRIDE_OVERRIDESMALLANDMEDIUM)
            {
                ret_control->size_definitions->medium.labelvisible = 0;
                ret_control->size_definitions->small.labelvisible = 0;
            }

            break;
        case UIRIBBON_CONTROL_BLOCK_TYPE_UNK36:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions));

            ret_control->size_definitions->large.imagevisible = src_block->block_36.sizedefinition_imagevisible == UIRIBBON_SIZEDEFINITION_IMAGEVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.imagevisible = ret_control->size_definitions->large.imagevisible;
            ret_control->size_definitions->small.imagevisible = ret_control->size_definitions->large.imagevisible;
            break;
        }
    }
}

void transform_tabs_ext(type_tab_extended *tabs_ext, uiribbon_main *ret)
{
    int i, j, k;

    for (i = 0; i < ret->count_tabs; i++)
    {
        uiribbon_tab *ret_tab = &ret->tabs[i];
        type_tab_extended *src_tab = &tabs_ext[i];

        ret_tab->count_groups = src_tab->count_groupinfo;
        ret_tab->groups = malloc(sizeof(uiribbon_group) * ret_tab->count_groups);

        for (j = 0; j < ret_tab->count_groups; j++)
        {
            uiribbon_group *ret_group = &ret_tab->groups[j];
            type_group_info *src_group = &src_tab->groupinfo[j];

            ret_group->count_controls = src_group->group_elements_info.sub_count;
            ret_group->controls = malloc(sizeof(uiribbon_control) * ret_group->count_controls);

            for (k = 0; k < ret_group->count_controls; k++)
            {
                transform_control(&src_group->group_elements_info.subcontents[k], &ret_group->controls[k]);
            }

        }
    }
}

void transform_uiribbon(type_uiribbon *src, uiribbon_main *ret)
{
    int i;

    for (i = 0; i < src->unk6.ribbon.unk0; i++)
    {
        type_block_generic *src_block = &src->unk6.ribbon.block1[i];
        if (src_block->block_type == UIRIBBON_BLOCK_TYPE_RIBBON_TABS)
        {
            if(src_block->block_type == UIRIBBON_BLOCK_TYPE_RIBBON_TABS)
            {
                if (src_block->block_tabs.tab_type == UIRIBBON_TAB_TYPE_NORMAL)
                {
                    transform_tabs(&src_block->block_tabs.block_normal, ret);
                }
            }
        }
    }

    transform_tabs_ext(src->unk6.ribbon_tab_info, ret);
}
