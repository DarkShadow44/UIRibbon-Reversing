#include "uiribbon_transformer.h"

static void *alloc_zero(int size)
{
    return calloc(size, 1);
}

static void make_block_id(int id, type_control_block *ret)
{
    ret->meta_type = ENUM_CONTROL_BLOCK_META_NUMBER;
    ret->content_number.block_len = 1;
    ret->content_number.block_type = ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID;
    ret->content_number.content_number.id.flag = 3;
    ret->content_number.content_number.id.id = id;
}

static void transform_control(uiribbon_control *control, type_control *ret)
{
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

void patch_ribbon(type_uiribbon *uiribbon)
{
    uiribbon_control new_control = {0};
    new_control.id = 10003;
    new_control.type = UIRIBBON_CONTROL_TYPE_BUTTON;

    /* tabs */
    uiribbon->unk6.ribbon.blocks[1].content_special.content_subcontrols.count_subcontrols = 1;
    /* groups */
    uiribbon->unk6.ribbon.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].ext->block.content_special.content_subcontrols.count_subcontrols = 1;
    uiribbon->unk6.ribbon.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].ext->block.content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[2].content_special.content_subcontrols.count_subcontrols = 1;

    transform_control(&new_control, &uiribbon->unk6.ribbon.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].ext->block.content_special.content_subcontrols.subcontrols[0].blocks.blocks[1].content_special.content_subcontrols.subcontrols[0].blocks.blocks[2].content_special.content_subcontrols.subcontrols[0]);



    uiribbon->command_ext.ext->unk3.blocks_count = 1;
}


