#include "uiribbon_transformer.h"

static void *alloc_zero(int size)
{
    return calloc(size, 1);
}

static void make_block_id(int id, type_tree_entry *ret)
{
    ret->entry_type = ENUM_TREE_ENTRY_TYPE_PROPERTY;
    ret->property.block_len = 1;
    ret->property.block_type = ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID;
    ret->property.content_number.id.flag = 3;
    ret->property.content_number.id.id = id;
}

static void transform_control(uiribbon_control *control, type_control *ret)
{
    ret->unk2 = 16;
    switch(control->type)
    {
    case UIRIBBON_CONTROL_TYPE_BUTTON:
        ret->block_type = ENUM_TYPE_CONTROL_BUTTON;
        ret->count_children = 1;
        ret->children = alloc_zero(sizeof(type_tree_entry) * ret->count_children);
        make_block_id(control->id, &ret->children[0]);
        break;
    }
}

static void make_block_subcontrols(uiribbon_control *controls, int controls_count, type_tree_entry *ret)
{
    int i;

    ret->entry_type = ENUM_TREE_ENTRY_TYPE_ARRAY;
    ret->array.block_len = 1;
    ret->array.block_type = ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS;
    ret->array.content_subcontrols.count_subcontrols = controls_count;
    ret->array.content_subcontrols.subcontrols = alloc_zero(sizeof(type_control) * controls_count);
    for (i = 0; i < controls_count; i++)
    {
        transform_control(&controls[i], &ret->array.content_subcontrols.subcontrols[i]);
    }
}

static void transform_group(uiribbon_group *group, type_control *ret)
{
    ret->block_type = ENUM_TYPE_CONTROL_GROUP;
    ret->count_children = 2;
    ret->children = alloc_zero(sizeof(type_tree_entry) * ret->count_children);
    make_block_id(group->id, &ret->children[0]);
    ret->children[1].entry_type = ENUM_TREE_ENTRY_TYPE_ARRAY;
    ret->children[1].array.block_len = 1;
    ret->children[1].array.block_type = ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS;
    ret->children[1].array.content_subcontrols.count_subcontrols = 1;
    ret->children[1].array.content_subcontrols.subcontrols = alloc_zero(sizeof(type_control));

    ret = &ret->children[1].array.content_subcontrols.subcontrols[0]; /* Inner group */

    ret->unk2 = 16;
    ret->block_type = ENUM_TYPE_CONTROL_SUBGROUP;
    ret->count_children = 2;
    ret->children = alloc_zero(sizeof(type_tree_entry) * 2);
    make_block_subcontrols(group->controls, group->count_controls, &ret->children[0]);

    ret->children[1].entry_type = ENUM_TREE_ENTRY_TYPE_PROPERTY;
    ret->children[1].property.block_len = 1;
    ret->children[1].property.block_type = ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE;
    ret->children[1].property.content_number.id.flag = 4;
    ret->children[1].property.content_number.id.id = 9; /* FIXME: Unknown why, but changes layout */
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
    uiribbon->root_node.node.children[1].array.content_subcontrols.count_subcontrols = 1;
    /* groups */
    uiribbon->root_node.node.children[1].array.content_subcontrols.subcontrols[0].children[1].ext->block.array.content_subcontrols.count_subcontrols = 1;

    transform_group(&new_group, &uiribbon->root_node.node.children[1].array.content_subcontrols.subcontrols[0].children[1].ext->block.array.content_subcontrols.subcontrols[0]);


    uiribbon->command_ext.ext->unk3.blocks_count = 1;
}


