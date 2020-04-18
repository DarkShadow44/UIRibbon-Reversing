#include "uiribbon_transformer.h"

static void *alloc_zero(int size)
{
    return calloc(size, 1);
}

static void make_block_id(int id, type_control_block *ret)
{
    ret->meta_type = ENUM_CONTROL_BLOCK_META_PROPERTY;
    ret->content_number.block_len = 1;
    ret->content_number.block_type = ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID;
    ret->content_number.content_number.id.flag = 3;
    ret->content_number.content_number.id.id = id;
}

static void transform_control(uiribbon_control *control, type_control *ret)
{
    ret->unk2 = 16;
    switch(control->type)
    {
    case UIRIBBON_CONTROL_TYPE_BUTTON:
        ret->block_type = ENUM_TYPE_CONTROL_BUTTON;
        ret->blocks.count_blocks = 1;
        ret->blocks.blocks = alloc_zero(sizeof(type_control_block) * ret->blocks.count_blocks);
        make_block_id(control->id, &ret->blocks.blocks[0]);
        break;
    }
}

static void make_block_subcontrols(uiribbon_control *controls, int controls_count, type_control_block *ret)
{
    int i;

    ret->meta_type = ENUM_CONTROL_BLOCK_META_ARRAY;
    ret->content_special.block_len = 1;
    ret->content_special.block_type = ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS;
    ret->content_special.content_subcontrols.count_subcontrols = controls_count;
    ret->content_special.content_subcontrols.subcontrols = alloc_zero(sizeof(type_control) * controls_count);
    for (i = 0; i < controls_count; i++)
    {
        transform_control(&controls[i], &ret->content_special.content_subcontrols.subcontrols[i]);
    }
}

static void transform_group(uiribbon_group *group, type_control *ret)
{
    ret->block_type = ENUM_TYPE_CONTROL_GROUP;
    ret->blocks.count_blocks = 2;
    ret->blocks.blocks = alloc_zero(sizeof(type_control_block) * ret->blocks.count_blocks);
    make_block_id(group->id, &ret->blocks.blocks[0]);
    ret->blocks.blocks[1].meta_type = ENUM_CONTROL_BLOCK_META_ARRAY;
    ret->blocks.blocks[1].content_special.block_len = 1;
    ret->blocks.blocks[1].content_special.block_type = ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS;
    ret->blocks.blocks[1].content_special.content_subcontrols.count_subcontrols = 1;
    ret->blocks.blocks[1].content_special.content_subcontrols.subcontrols = alloc_zero(sizeof(type_control));

    ret = &ret->blocks.blocks[1].content_special.content_subcontrols.subcontrols[0]; /* Inner group */

    ret->unk2 = 16;
    ret->block_type = ENUM_TYPE_CONTROL_SUBGROUP;
    ret->blocks.count_blocks = 2;
    ret->blocks.blocks = alloc_zero(sizeof(type_control_block) * 2);
    make_block_subcontrols(group->controls, group->count_controls, &ret->blocks.blocks[0]);

    ret->blocks.blocks[1].meta_type = ENUM_CONTROL_BLOCK_META_PROPERTY;
    ret->blocks.blocks[1].content_number.block_len = 1;
    ret->blocks.blocks[1].content_number.block_type = ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE;
    ret->blocks.blocks[1].content_number.content_number.id.flag = 4;
    ret->blocks.blocks[1].content_number.content_number.id.id = 9; /* FIXME: Unknown why, but changes layout */
}

void patch_ribbon(type_uiribbon *uiribbon)
{
    uiribbon_group new_group = {0};
    uiribbon_control new_control = {0};

    new_control.id = 10003;
    new_control.type = UIRIBBON_CONTROL_TYPE_BUTTON;

    new_group.id = 10005;
    new_group.controls = alloc_zero(sizeof(uiribbon_control) * 2);
    new_group.controls[0] = new_group.controls[1] = new_control;
    new_group.count_controls = 2;

    /* tabs */
    uiribbon->root_block.block_inline.quick_ribbon_info.blocks[1].content_special.content_subcontrols.count_subcontrols = 1;
    /* groups */
    uiribbon->root_block.block_inline.quick_ribbon_info.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].ext->block.content_special.content_subcontrols.count_subcontrols = 1;

    transform_group(&new_group, &uiribbon->root_block.block_inline.quick_ribbon_info.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].ext->block.content_special.content_subcontrols.subcontrols[0]);


    uiribbon->command_ext.ext->unk3.blocks_count = 1;
}


