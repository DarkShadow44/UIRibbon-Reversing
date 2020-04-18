#include "uiribbon_transformer.h"

/* FIXME: Proper assert structure */
/* FIXME: maybe macro to make iterating over blocks shorter... */
/* FIXME: Extract all in methods for fewer loops? */
/* structs to combine count and array ? */
/* Transform ALL menugroups with majoritem/smallitems in mind */
/* Fixme - generic reader and stuff */

#define ASSERT(cond) \
    if (!(cond)) {\
        printf("Assert failed: %s, %d\n", __FILE__, __LINE__); \
        return; \
    }

uiribbon_control_type transform_control_type(type_control *src_control)
{
    int i, j;
    bool is_colorpicker = FALSE;
    bool is_checkbox = FALSE;

    switch (src_control->block_type)
    {
    case ENUM_TYPE_CONTROL_BUTTON:
        return UIRIBBON_CONTROL_TYPE_BUTTON;
    case ENUM_TYPE_CONTROL_CHECKBOX:
        for (i = 0; i < src_control->blocks.count_blocks; i++)
        {
            type_tree_entry *src_block = &src_control->blocks.blocks[i];
            if (src_block->entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY && src_block->property.block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_IS_CHECKBOX)
            {
                is_checkbox = src_block->property.is_checkbox;
            }
        }
        if (is_checkbox)
            return UIRIBBON_CONTROL_TYPE_CHECKBOX;
        return UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON;
    case ENUM_TYPE_CONTROL_DROPDOWNBUTTON:
        return UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON;
    case ENUM_TYPE_CONTROL_GALLERY:
        for (i = 0; i < src_control->blocks.count_blocks; i++)
        {
            type_tree_entry *src_block = &src_control->blocks.blocks[i];
            if (src_block->entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY && src_block->property.block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TYPE)
            {
                switch(src_block->property.gallery_type)
                {
                case ENUM_GALLERY_TYPE_COMBO:
                case ENUM_GALLERY_TYPE_DROPDOWNLIST:
                    return UIRIBBON_CONTROL_TYPE_COMBOBOX;
                case ENUM_GALLERY_TYPE_DROPDOWNSPLIT:
                    for (j = 0; j < src_control->blocks.count_blocks; j++)
                    {
                        if (src_control->blocks.blocks[j].entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY && src_control->blocks.blocks[j].property.block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE)
                            is_colorpicker = TRUE;
                    }
                    if (is_colorpicker)
                        return UIRIBBON_CONTROL_TYPE_DROPDOWNCOLORPICKER;
                    return UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY;
                case ENUM_GALLERY_TYPE_DROPDOWNBUTTON:
                    return UIRIBBON_CONTROL_TYPE_DROPDOWNGALLERY;
                case ENUM_GALLERY_TYPE_INRIBBON:
                    return UIRIBBON_CONTROL_TYPE_INRIBBONGALLERY;
                default:
                    return -1;
                }
            }
        }
        break;
    case ENUM_TYPE_CONTROL_MENUGROUP:
        return UIRIBBON_CONTROL_TYPE_GROUP;
    case ENUM_TYPE_CONTROL_SPLITBUTTON:
        return UIRIBBON_CONTROL_TYPE_SPLITBUTTON;
    case ENUM_TYPE_CONTROL_SPINNER:
        return UIRIBBON_CONTROL_TYPE_SPINNER;
    }
    return -1;
}

void transform_control_combobox(type_uiribbon *root, type_control *src_control, uiribbon_control_combobox *ret_control)
{
    int i;

    ret_control->fontcontrol_string_for_width[0] = 0;
    ret_control->fontcontrol_show_truetype_only = 0;
    ret_control->fontcontrol_show_vertical = 0;

    ret_control->is_editable = FALSE;
    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_control->blocks.blocks[i].property;

        if (src_control->blocks.blocks[i].entry_type != ENUM_TREE_ENTRY_TYPE_PROPERTY)
            continue;

        switch(src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT:
            ret_control->is_editable = TRUE;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_AUTOCOMPLETE_ENABLED:
            ret_control->has_autocomplete = src_block->autocomplete_enabled;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER:
            ret_control->has_vertical_resize = src_block->gallery_gripper != ENUM_GALLERY_GRIPPER_NONE;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MIN:
            ret_control->fontcontrol_fontsize_min = src_block->fontcontrol_fontsize_min;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_FONTSIZE_MAX:
            ret_control->fontcontrol_fontsize_max = src_block->fontcontrol_fontsize_max;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_VERTICALFONTS:
            ret_control->fontcontrol_show_vertical = src_block->fontcontrol_verticalfonts;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_TRUETYPEONLY:
            ret_control->fontcontrol_show_truetype_only = src_block->fontcontrol_truetypeonly;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_STR:
            {
                int index = src_block->fontcontrol_str;
                type_string *str = &root->strings.strings[index];
                ASSERT(str->size_str + 1 < sizeof(ret_control->fontcontrol_string_for_width));
                ret_control->fontcontrol_string_for_width[str->size_str] = 0; /* Add null terminator since the strings are lacking them */
                memcpy(ret_control->fontcontrol_string_for_width, str->str, str->size_str);
            }
            break;
        default:
            break;
        }
    }
}

uiribbon_chipsize transform_chipsize(type_tree_entry_number *src_block)
{
    switch (src_block->dropdowncolorpicker_chipsize)
    {
    case ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_SMALL:
        return UIRIBBON_CHIPSIZE_SMALL;
    case ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_MEDIUM:
        return UIRIBBON_CHIPSIZE_MEDIUM;
    case ENUM_DROPDOWNCOLORPICKER_CHIPSIZE_LARGE:
        return UIRIBBON_CHIPSIZE_LARGE;
    }
    return -1;
}

uiribbon_colortemplate transform_colortemplate(type_tree_entry_number *src_block)
{
    switch (src_block->dropdowncolorpicker_colortemplate)
    {
    case ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_THEME_COLORS:
        return UIRIBBON_COLORTEMPLATE_THEME;
    case ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_STANDARD_COLORS:
        return UIRIBBON_COLORTEMPLATE_STANDARD;
    case ENUM_DROPDOWNCOLORPICKER_COLORTEMPLATE_HIGHLIGHT_COLORS:
        return UIRIBBON_COLORTEMPLATE_HIGHLIGHT;
    }
    return -1;
}

void transform_control_dropdowncolorpicker(type_control *src_control, uiribbon_control_dropdowncolorpicker *ret_control)
{
    int i;

    ret_control->chipsize = UIRIBBON_CHIPSIZE_SMALL;
    ret_control->columns = 10;
    ret_control->has_autocolor_button = TRUE;
    ret_control->has_nocolor_button = TRUE;
    ret_control->recent_color_rows = 1;
    ret_control->standard_color_rows = 1;
    ret_control->theme_color_rows = 6;
    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_control->blocks.blocks[i].property;

        if (src_control->blocks.blocks[i].entry_type != ENUM_TREE_ENTRY_TYPE_PROPERTY)
            continue;

        switch(src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLORTEMPLATE:
            ret_control->colortemplate = transform_colortemplate(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_CHIPSIZE:
            ret_control->chipsize = transform_chipsize(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_COLUMNS:
            ret_control->columns = src_block->dropdowncolorpicker_columns;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_AUTOCOLOR_BUTTON:
            ret_control->has_autocolor_button = src_block->dropdowncolorpicker_has_autocolor_button;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_HAS_NOCOLOR_BUTTON:
            ret_control->has_nocolor_button = src_block->dropdowncolorpicker_has_nocolor_button;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_RECENT_COLOR_ROWS:
            ret_control->recent_color_rows = src_block->dropdowncolorpicker_recent_color_rows;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_STANDARD_COLOR_ROWS:
            ret_control->standard_color_rows = src_block->dropdowncolorpicker_standard_rows;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_DROPDOWNCOLORPICKER_THEME_COLOR_ROWS:
            ret_control->theme_color_rows = src_block->dropdowncolorpicker_theme_color_rows;
            break;
        default:
            break;
        }
    }
}

enum_gallery_elements_type transform_gallery_elements_type(type_tree_entry_number *src_block)
{
    switch (src_block->gallery_elements_type)
    {
    case ENUM_GALLERY_ELEMENTS_TYPE_COMMANDS:
        return UIRIBBON_GALLERY_ELEMENTS_TYPE_COMMANDS;
    case ENUM_GALLERY_ELEMENTS_TYPE_ITEMS:
        return UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS;
    }
    return -1;
}

enum_gallery_menulayout transform_gallery_menulayout(type_tree_entry_number *src_block)
{
    switch (src_block->gallery_menulayout)
    {
    case ENUM_GALLERY_MENULAYOUT_FLOW:
        return UIRIBBON_GALLERY_MENULAYOUT_FLOW;
    case ENUM_GALLERY_MENULAYOUT_VERTICAL:
        return UIRIBBON_GALLERY_MENULAYOUT_VERTICAL;
    case ENUM_GALLERY_MENULAYOUT_SPECIAL:
        return UIRIBBON_GALLERY_MENULAYOUT_SPECIAL;
    }
    return -1;
}

enum_gallery_gripper transform_gallery_gripper(type_tree_entry_number *src_block)
{
    switch (src_block->gallery_gripper)
    {
    case ENUM_GALLERY_GRIPPER_NONE:
        return UIRIBBON_GALLERY_GRIPPER_NONE;
    case ENUM_GALLERY_GRIPPER_VERTICAL:
        return UIRIBBON_GALLERY_GRIPPER_VERTICAL;
    case ENUM_GALLERY_GRIPPER_CORNER:
        return UIRIBBON_GALLERY_GRIPPER_CORNER;
    }
    return -1;
}

enum_gallery_text_position transform_gallery_textposition(type_tree_entry_number *src_block)
{
    switch (src_block->gallery_text_position)
    {
    case ENUM_GALLERY_TEXT_POSITION_LEFT:
        return UIRIBBON_GALLERY_TEXT_POSITION_LEFT;
    case ENUM_GALLERY_TEXT_POSITION_RIGHT:
        return UIRIBBON_GALLERY_TEXT_POSITION_RIGHT;
    case ENUM_GALLERY_TEXT_POSITION_TOP:
        return UIRIBBON_GALLERY_TEXT_POSITION_TOP;
    case ENUM_GALLERY_TEXT_POSITION_BOTTOM:
        return UIRIBBON_GALLERY_TEXT_POSITION_BOTTOM;
    case ENUM_GALLERY_TEXT_POSITION_OVERLAY:
        return UIRIBBON_GALLERY_TEXT_POSITION_OVERLAY;
    case ENUM_GALLERY_TEXT_POSITION_HIDE:
        return UIRIBBON_GALLERY_TEXT_POSITION_HIDE;
    }
    return -1;
}

void transform_control_gallery_generic(type_control *src_control, uiribbon_control_gallery_generic *ret_control)
{
    int i;

    ret_control->elements_type = UIRIBBON_GALLERY_ELEMENTS_TYPE_ITEMS; /* FIXME: is this the correct default? */
    ret_control->text_position = UIRIBBON_GALLERY_TEXT_POSITION_LEFT; /* FIXME: is this the correct default? */

    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_control->blocks.blocks[i].property;

        if (src_control->blocks.blocks[i].entry_type != ENUM_TREE_ENTRY_TYPE_PROPERTY)
            continue;

        switch(src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MENULAYOUT:
            ret_control->menulayout = transform_gallery_menulayout(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_GRIPPER:
            ret_control->gripper = transform_gallery_gripper(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_TEXT_POSITION:
            ret_control->text_position = transform_gallery_textposition(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_META_INFO:
            ret_control->elements_type = transform_gallery_elements_type(src_block);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_HAS_LARGE_ITEMS:
            ret_control->has_large_items = src_block->gallery_has_large_items;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_WIDTH:
            ret_control->item_width = src_block->gallery_item_width;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ITEM_HEIGHT:
            ret_control->item_height = src_block->gallery_item_height;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_ROWS:
            ret_control->rows = src_block->gallery_rows;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_COLUMNS:
            ret_control->columns = src_block->gallery_columns;
            break;
        default:
            break;
        }
    }
}

void transform_control_inribbongallery(type_control *src_control, uiribbon_control_inribbongallery *ret_control)
{
    int i;

    ret_control->max_rows = 1;

    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_control->blocks.blocks[i].property;

        if (src_control->blocks.blocks[i].entry_type != ENUM_TREE_ENTRY_TYPE_PROPERTY)
            continue;

        switch(src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS:
            ret_control->max_columns = src_block->gallery_max_columns;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_ROWS:
            ret_control->max_rows = src_block->gallery_max_rows;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MAX_COLUMNS_MEDIUM:
            ret_control->max_columns_medium = src_block->gallery_max_columns_medium;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_MEDIUM:
            ret_control->min_columns_medium = src_block->gallery_min_columns_medium;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_GALLERY_MIN_COLUMNS_LARGE:
            ret_control->min_columns_large = src_block->gallery_min_columns_large;
            break;
        default:
            break;
        }
    }
}

void transform_control(type_uiribbon *root, type_control *src_control, uiribbon_control *ret_control);

uiribbon_control *find_button_item(uiribbon_control *control)
{
    int i;
    for (i = 0; i < control->count_subcontrols; i++)
    {
        uiribbon_control *subcontrol = &control->subcontrols[i];

        if (subcontrol->type == UIRIBBON_CONTROL_TYPE_BUTTON
            || subcontrol->type == UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON
            || subcontrol->type == UIRIBBON_CONTROL_TYPE_CHECKBOX)
        {
            return subcontrol;
        }
    }
    for (i = 0; i < control->count_subcontrols; i++)
    {
        uiribbon_control *button_item = find_button_item(&control->subcontrols[i]);
        if (button_item != NULL)
            return button_item;
    }
    return NULL;
}

void transform_control_splitbutton(type_uiribbon *root, type_control *src_control, uiribbon_control *ret_control)
{
    int i;
    uiribbon_control *buttonitem;

    ret_control->control_info.splitbutton.buttonitem = malloc(sizeof(uiribbon_control));

    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_array *src_block = &src_control->blocks.blocks[i].array;

        if (src_control->blocks.blocks[i].entry_type != ENUM_TREE_ENTRY_TYPE_ARRAY)
            continue;

        if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM)
        {
            ASSERT(src_block->content_subcontrols.count_subcontrols == 1);
            transform_control(root, &src_block->content_subcontrols.subcontrols[0], ret_control->control_info.splitbutton.buttonitem);
            return;
        }
    }

    buttonitem = find_button_item(ret_control);
    *ret_control->control_info.splitbutton.buttonitem = *buttonitem;
}

void transform_subcontrols(type_uiribbon *root, type_subcontrols *src_block, int *out_count_subcontrols, uiribbon_control **out_subcontrols)
{
    int i;
    int count_subcontrols;
    uiribbon_control *subcontrols;

    count_subcontrols = src_block->count_subcontrols;
    *out_count_subcontrols = count_subcontrols;
    *out_subcontrols  = NULL;

    if (count_subcontrols == 0)
        return;

    subcontrols = malloc(sizeof(uiribbon_control) * count_subcontrols);
    *out_subcontrols = subcontrols;

    for (i = 0; i < count_subcontrols; i++)
    {
        transform_control(root, &src_block->subcontrols[i], &subcontrols[i]);
    }
}

static uiribbon_subcontrol_type make_control_subtype(int id)
{
    if (id >= 62000 && id <= 62099)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_TYPE;

    if (id >= 62300 && id <= 62399)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_SIZE;

    if (id >= 63100 && id <= 63199)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_HIGHLIGHT;

    if (id >= 63200 && id <= 63299)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_COLOR;

    if (id >= 62100 && id <= 62199)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_ITALIC;

    if (id >= 62200 && id <= 62299)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_UNDERLINE;

    if (id >= 62400 && id <= 62499)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_BOLD;

    if (id >= 62600 && id <= 62699)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_STRIKETHROUGH;

    if (id >= 62700 && id <= 62799)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_SUPERSCRIPT;

    if (id >= 62800 && id <= 62899)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_SUBSCRIPT;

    if (id >= 62900 && id <= 62999)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_BIGGER;

    if (id >= 63000 && id <= 63099)
        return UIRIBBON_SUBCONTROL_TYPE_FONT_SMALLER;

    return UIRIBBON_SUBCONTROL_TYPE_NONE;
}

void transform_control(type_uiribbon *root, type_control *src_control, uiribbon_control *ret_control)
{
    int i;
    ret_control->parent_id = -1;
    ret_control->type = transform_control_type(src_control);
    ret_control->size_definitions = NULL;
    ret_control->count_subcontrols = 0;
    ret_control->subcontrols = NULL;
    for (i = 0; i < src_control->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_control->blocks.blocks[i].property;
        type_tree_entry_array *src_block_special = &src_control->blocks.blocks[i].array;
        int entry_type = src_control->blocks.blocks[i].entry_type;
        if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
        {
            if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS
                || src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_GALLERY_SUBCONTROLS)
            {
                transform_subcontrols(root, &src_block_special->content_subcontrols, &ret_control->count_subcontrols, &ret_control->subcontrols);
            }
            continue;
        }

        switch (src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_FONTCONTROL_PARENT_COMMANDID:
            ret_control->parent_id = src_block->fontcontrol_parent_commandid;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID:
            ret_control->id = src_block->id;
            ret_control->subtype = make_control_subtype(src_block->id);
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.sizeLarge = src_block->sizedefinition_imagesize == ENUM_SIZEDEFINITION_IMAGESIZE_LARGE;
            ret_control->size_definitions->medium.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            ret_control->size_definitions->small.sizeLarge = ret_control->size_definitions->large.sizeLarge;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGESIZE_MIXED:
            if (src_block->sizedefinition_imagesize_mixed == ENUM_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLISSMALL)
            {
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            else if(src_block->sizedefinition_imagesize_mixed == ENUM_SIZEDEFINITION_IMAGESIZE_MIXED_SMALLANDMEDIUMARESMALL)
            {
                ret_control->size_definitions->medium.sizeLarge = 0;
                ret_control->size_definitions->small.sizeLarge = 0;
            }
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.labelvisible = src_block->sizedefinition_labelvisible == ENUM_SIZEDEFINITION_LABELVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.labelvisible = ret_control->size_definitions->large.labelvisible;
            ret_control->size_definitions->small.labelvisible = ret_control->size_definitions->large.labelvisible;
            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_LABELVISIBLE_MIXED:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));
            ret_control->size_definitions->large.labelvisible = 1;
            if (src_block->sizedefinition_labelvisible_mixed == ENUM_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALL)
            {
                ret_control->size_definitions->medium.labelvisible = 1;
                ret_control->size_definitions->small.labelvisible = 0;
            }
            else if (src_block->sizedefinition_labelvisible_mixed == ENUM_SIZEDEFINITION_LABELVISIBLE_MIXED_OVERRIDESMALLANDMEDIUM)
            {
                ret_control->size_definitions->medium.labelvisible = 0;
                ret_control->size_definitions->small.labelvisible = 0;
            }

            break;
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_SIZEDEFINITION_IMAGEVISIBLE:
            if (!ret_control->size_definitions)
                ret_control->size_definitions = malloc(sizeof(uiribbon_sizedefinitions_control));

            ret_control->size_definitions->large.imagevisible = src_block->sizedefinition_imagevisible == ENUM_SIZEDEFINITION_IMAGEVISIBLE_VISIBLE;
            ret_control->size_definitions->medium.imagevisible = ret_control->size_definitions->large.imagevisible;
            ret_control->size_definitions->small.imagevisible = ret_control->size_definitions->large.imagevisible;
            break;
        default:
            break;
        }
    }

    switch(ret_control->type)
    {
    case UIRIBBON_CONTROL_TYPE_BUTTON:
    case UIRIBBON_CONTROL_TYPE_CHECKBOX:
    case UIRIBBON_CONTROL_TYPE_DROPDOWNBUTTON:
    case UIRIBBON_CONTROL_TYPE_GROUP:
    case UIRIBBON_CONTROL_TYPE_SPINNER:
    case UIRIBBON_CONTROL_TYPE_TOGGLEBUTTON:
        break;

    case UIRIBBON_CONTROL_TYPE_COMBOBOX:
        transform_control_combobox(root, src_control, &ret_control->control_info.combobox);
        break;

    case UIRIBBON_CONTROL_TYPE_DROPDOWNCOLORPICKER:
        transform_control_dropdowncolorpicker(src_control, &ret_control->control_info.dropdowncolorpicker);
        break;

    case UIRIBBON_CONTROL_TYPE_DROPDOWNGALLERY:
        transform_control_gallery_generic(src_control, &ret_control->control_info.dropdowngallery);
        break;

    case UIRIBBON_CONTROL_TYPE_INRIBBONGALLERY:
        transform_control_gallery_generic(src_control, &ret_control->control_info.inribbongallery.generic);
        transform_control_inribbongallery(src_control, &ret_control->control_info.inribbongallery);
        break;

    case UIRIBBON_CONTROL_TYPE_SPLITBUTTONGALLERY:
         transform_control_gallery_generic(src_control, &ret_control->control_info.splitbuttongallery);
         break;

    case UIRIBBON_CONTROL_TYPE_SPLITBUTTON:
        transform_control_splitbutton(root, src_control, ret_control);
        break;
    }
}

void transform_sizedefinition_order(type_uiribbon *root, type_sizedefinition_order *src, uiribbon_sizedefinition_group *ret)
{
    int i;

    ret->count_orders = src->count_commands;
    ret->orders = malloc(sizeof(uiribbon_sizedefinition_group_order) * ret->count_orders);
    for (i = 0; i < ret->count_orders; i++)
    {
        uiribbon_sizedefinition_group_order *ret_order = &ret->orders[i];
        type_sizedefinitions_order_command *src_order = &src->commands[i];

        if (src_order->flags_command == ENUM_SIZEDEFINITIONS_COMMAND_COMMAND)
        {
            ret_order->is_special = 0;
            ret_order->command_id = src->commands[i].command_id;
        }
        else if (src_order->flags_command == ENUM_SIZEDEFINITIONS_COMMAND_SPECIAL)
        {
            char special;
            ret_order->is_special = 1;
            special = root->strings.strings[src_order->string_id].str[0];
            switch(special)
            {
            case '{':
                ret_order->special_command = UIRIBBON_SIZEINFO_ORDER_OPEN_GROUP;
                break;
            case '}':
                ret_order->special_command = UIRIBBON_SIZEINFO_ORDER_CLOSE_GROUP;
                break;
            case '|':
                ret_order->special_command = UIRIBBON_SIZEINFO_ORDER_VISIBLE_SEPARATOR;
                break;
            case ':':
                ret_order->special_command = UIRIBBON_SIZEINFO_ORDER_INVISIBLE_SEPARATOR;
                break;
            case ';':
                ret_order->special_command = UIRIBBON_SIZEINFO_ORDER_BREAK;
                break;
            }
        }
    }
}


void transform_sizedefinition_orders(type_uiribbon *root, enum_control_block_type_special type, type_sizedefinition_order *src, uiribbon_group *ret_group)
{
    if (!ret_group->sizedefinition_orders)
    {
        ret_group->sizedefinition_orders = malloc(sizeof(uiribbon_sizedefinitions_orders));
        memset(ret_group->sizedefinition_orders, 0, sizeof(uiribbon_sizedefinitions_orders));
    }

    switch (type)
    {
    case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE:
        transform_sizedefinition_order(root, src, &ret_group->sizedefinition_orders->large);
        break;
    case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM:
        transform_sizedefinition_order(root, src, &ret_group->sizedefinition_orders->medium);
        break;
    case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL:
       transform_sizedefinition_order(root, src, &ret_group->sizedefinition_orders->small);
        break;
    default:
        break;
    }
}

/* Skip over useless group inside tab group */
void transform_subcontrols_group(type_uiribbon *root, type_subcontrols *src_block, uiribbon_group *ret_group)
{
    int i;

    ASSERT(src_block->count_subcontrols == 1);

    for (i = 0; i < src_block->subcontrols[0].blocks.count_blocks; i++)
    {
        type_tree_entry_array *src_block_special = &src_block->subcontrols[0].blocks.blocks[i].array;
        int entry_type = src_block->subcontrols[0].blocks.blocks[i].entry_type;
        if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
        {
            switch (src_block_special->block_type)
            {
            case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS:
                transform_subcontrols(root, &src_block_special->content_subcontrols, &ret_group->count_controls, &ret_group->controls);
                break;
            case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_LARGE:
            case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_MEDIUM:
            case ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SIZEDEFINITION_ORDER_SMALL:
                transform_sizedefinition_orders(root, src_block_special->block_type, &src_block_special->sizedefinition_order, ret_group);
                break;
            default:
                break;
            }
        }
    }
}

void transform_group(type_uiribbon *root, type_control *src_group, uiribbon_group *ret_group)
{
    int i;

    ret_group->count_controls = 0;
    ret_group->controls = NULL;
    ret_group->sizedefinition_orders = NULL;
    for (i = 0; i < src_group->blocks.count_blocks; i++)
    {
        type_tree_entry_number *src_block = &src_group->blocks.blocks[i].property;
        type_tree_entry_array *src_block_special = &src_group->blocks.blocks[i].array;
        int entry_type = src_group->blocks.blocks[i].entry_type;

        if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY && src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
        {
            transform_subcontrols_group(root, &src_block_special->content_subcontrols, ret_group);
            continue;
        }

        switch (src_block->block_type)
        {
        case ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID:
            ret_group->id = src_block->id;
            break;
        default:
            break;
        }
    }
}

void transform_scalepolicies(type_subcontrols *src_ext, uiribbon_tab *ret_tab)
{
    int i, j, k, pos;
    int count_scalepolicies = 0;
    for (i = 0; i < ret_tab->count_groups; i++)
    {
        type_control *src_group = &src_ext->subcontrols[i];

        if (src_group->block_type != ENUM_TYPE_CONTROL_GROUP)
            continue;

        for (j = 0; j < src_group->blocks.count_blocks; j++)
        {
            type_tree_entry_number *src_block = &src_group->blocks.blocks[j].property;
            int entry_type = src_group->blocks.blocks[j].entry_type;

            if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
            {
                if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
                {
                    if (src_block->scalepolicy_medium > 0)
                        count_scalepolicies++;
                    if (src_block->scalepolicy_small > 0)
                        count_scalepolicies++;
                    if (src_block->scalepolicy_popup > 0)
                        count_scalepolicies++;
                }
            }
        }
    }

    ret_tab->count_scalepolicies = count_scalepolicies;
    ret_tab->scalepolicies = malloc(sizeof(uiribbon_scalingpolicy) * ret_tab->count_scalepolicies);
    pos = 0;
    for (k = 0; k < 16; k++)
    {
        uiribbon_scalingpolicy *ret_scalingpolicy = &ret_tab->scalepolicies[pos];
        for (i = 0; i < ret_tab->count_groups; i++)
        {
            type_control *src_group = &src_ext->subcontrols[i];
            int group_id = -1;

            if (src_group->block_type != ENUM_TYPE_CONTROL_GROUP)
                continue;

            for (j = 0; j < src_group->blocks.count_blocks; j++)
            {
                type_tree_entry_number *src_block = &src_group->blocks.blocks[j].property;
                int entry_type = src_group->blocks.blocks[j].entry_type;
                if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY && src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                    group_id = src_block->id;
            }

            for (j = 0; j < src_group->blocks.count_blocks; j++)
            {
                type_tree_entry_number *src_block = &src_group->blocks.blocks[j].property;
                int entry_type = src_group->blocks.blocks[j].entry_type;

                if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
                {
                    if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_META_INFO)
                    {
                        if (src_block->scalepolicy_medium == k + 1)
                        {
                            ret_scalingpolicy->group_id = group_id;
                            ret_scalingpolicy->scale_type = UIRIBBON_SCALE_TO_MEDIUM;
                            pos++;
                        }
                        else if (src_block->scalepolicy_small == k + 1)
                        {
                            ret_scalingpolicy->group_id = group_id;
                            ret_scalingpolicy->scale_type = UIRIBBON_SCALE_TO_SMALL;
                            pos++;
                        }
                        else if (src_block->scalepolicy_popup == k + 1)
                        {
                            ret_scalingpolicy->group_id = group_id;
                            ret_scalingpolicy->scale_type = UIRIBBON_SCALE_TO_POPUP;
                            pos++;
                        }
                    }
                }
            }
        }
    }
}

void transform_tabs_ext(type_uiribbon *root, type_subcontrols *src_ext, uiribbon_tab *ret_tab)
{
    int i;

    ret_tab->count_groups = src_ext->count_subcontrols;
    ret_tab->groups = malloc(sizeof(uiribbon_group) * ret_tab->count_groups);

    for (i = 0; i < ret_tab->count_groups; i++)
    {
        transform_group(root, &src_ext->subcontrols[i], &ret_tab->groups[i]);
    }

    transform_scalepolicies(src_ext, ret_tab);
}

void transform_tabs(type_uiribbon *root, type_subcontrols *src_tabs, int *out_count_tabs, uiribbon_tab **out_tabs)
{
    int i, j;

    int count = src_tabs->count_subcontrols;
    uiribbon_tab *tabs = malloc(sizeof(uiribbon_tab) * count);

    *out_count_tabs = count;
    *out_tabs = tabs;

    for (i = 0; i < count; i++)
    {
        uiribbon_tab *ret_tab = &tabs[i];
        type_control *src_tab = &src_tabs->subcontrols[i];

        for (j = 0; j < src_tab->blocks.count_blocks; j++)
        {
            type_tree_entry_ext *src_block_ext = src_tab->blocks.blocks[j].ext;
            type_tree_entry_number *src_block = &src_tab->blocks.blocks[j].property;
            enum_tree_entry_type entry_type = src_tab->blocks.blocks[j].entry_type;

            if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
            {
                if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                {
                     ret_tab->id = src_block->id;
                }
            }

            if (entry_type == ENUM_TREE_ENTRY_TYPE_EXT)
            {
                /* FIXME: Not hard assert, just warn? */
                ASSERT(src_block_ext->block.entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY);
                ASSERT(src_block_ext->block.array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                transform_tabs_ext(root, &src_block_ext->block.array.content_subcontrols, ret_tab);
            }
        }
    }

}

void transform_contexttabs(type_uiribbon *root, type_subcontrols *src, uiribbon_main *ret)
{
    int i, j;

    ret->count_contexttabgroups = src->count_subcontrols;
    ret->contexttabgroups = malloc(sizeof(uiribbon_tabgroup) * ret->count_contexttabgroups);
    for (i = 0; i < ret->count_contexttabgroups; i++)
    {
        uiribbon_tabgroup *ret_tabgroup = &ret->contexttabgroups[i];
        type_control *src_tabgroup = &src->subcontrols[i];

        for (j = 0; j < src_tabgroup->blocks.count_blocks; j++)
        {
            type_tree_entry_array *src_block_special = &src_tabgroup->blocks.blocks[j].array;
            type_tree_entry_number *src_block = &src_tabgroup->blocks.blocks[j].property;
            enum_tree_entry_type entry_type = src_tabgroup->blocks.blocks[j].entry_type;

            if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
            {
                if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                {
                    ret_tabgroup->id = src_block->id;
                }
            }

            if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
            {
                if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                {
                    transform_tabs(root, &src_block_special->content_subcontrols, &ret->contexttabgroups[i].count_tabs, &ret->contexttabgroups[i].tabs);
                }
            }

        }
    }
}

void transform_command_images(enum_resource_type type, type_resource *src_resource, int *ret_count, uiribbon_command_image **ret_images)
{
    int i;
    int count = 0;
    for (i = 0; i < src_resource->count_resources; i++)
    {
        if (src_resource->resources[i].resource_type == type)
            count++;
    }

    *ret_images = malloc(sizeof(uiribbon_command_image) * count);
    *ret_count = count;
    count = 0;
    for (i = 0; i < src_resource->count_resources; i++)
    {
        type_resource_generic *src_resource_generic = &src_resource->resources[i];
        if (src_resource_generic->resource_type == type)
        {
            (*ret_images)[count].id_image = src_resource_generic->resource_id;
            (*ret_images)[count].min_dpi = src_resource_generic->mindpi;
            count++;
        }
    }
}

void transform_command_resources(int command_id, type_uiribbon *src, uiribbon_command *ret_command)
{
    int i, j;

    ret_command->id_keytip = -1;
    ret_command->id_label_title = -1;
    ret_command->id_label_description = -1;
    ret_command->id_toopltip_title = -1;
    ret_command->id_tooltip_description = -1;
    ret_command->count_images_large = 0;
    ret_command->count_images_small = 0;
    ret_command->count_images_large_high_contrast = 0;
    ret_command->count_images_small_high_contrast = 0;
    ret_command->images_small = NULL;
    ret_command->images_large = NULL;
    ret_command->images_small_high_contrast = NULL;
    ret_command->images_large_high_contrast = NULL;

    for (i = 0; i < src->count_command_resources; i++)
    {
        type_resource *src_resource = &src->command_resources[i];
        if (src_resource->command_id == command_id)
        {
            for (j = 0; j < src_resource->count_resources; j++)
            {
                type_resource_generic *src_resource_generic = &src_resource->resources[j];
                switch(src_resource_generic->resource_type)
                {
                case ENUM_RESOURCE_TYPE_KEYTIP:
                    ret_command->id_keytip = src_resource_generic->resource_id;
                    break;
                case ENUM_RESOURCE_TYPE_LABELTITLE:
                    ret_command->id_label_title = src_resource_generic->resource_id;
                    break;
                case ENUM_RESOURCE_TYPE_LABELDESCRIPTION:
                    ret_command->id_label_description = src_resource_generic->resource_id;
                    break;
                case ENUM_RESOURCE_TYPE_TOOLTIPTITLE:
                    ret_command->id_toopltip_title = src_resource_generic->resource_id;
                    break;
                case ENUM_RESOURCE_TYPE_TOOLTIPDESCRIPTION:
                    ret_command->id_tooltip_description = src_resource_generic->resource_id;
                    break;
                case ENUM_RESOURCE_TYPE_SMALLIMAGE:
                case ENUM_RESOURCE_TYPE_LARGEIMAGE:
                case ENUM_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE:
                case ENUM_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE:
                    break;
                }
            }
            transform_command_images(ENUM_RESOURCE_TYPE_LARGEIMAGE, src_resource, &ret_command->count_images_large, &ret_command->images_large);
            transform_command_images(ENUM_RESOURCE_TYPE_SMALLIMAGE, src_resource, &ret_command->count_images_small, &ret_command->images_small);
            transform_command_images(ENUM_RESOURCE_TYPE_LARGEHIGHCONTRASTIMAGE, src_resource, &ret_command->count_images_large_high_contrast, &ret_command->images_large_high_contrast);
            transform_command_images(ENUM_RESOURCE_TYPE_SMALLHIGHCONTRASTIMAGE, src_resource, &ret_command->count_images_small_high_contrast, &ret_command->images_small_high_contrast);
        }
    }
}

void transform_commands(type_uiribbon *src, uiribbon_main *ret)
{
    int i;

    ret->count_commands = src->command_container.commands_len;
    ret->commands = malloc(sizeof(uiribbon_command) * ret->count_commands);
    for (i = 0; i < ret->count_commands; i++)
    {
        type_command *src_command = &src->command_container.commands[i];
        uiribbon_command *ret_command = &ret->commands[i];
        ret_command->id = src_command->command_id;

        transform_command_resources(ret_command->id, src, ret_command);
    }
}

void transform_menugroups(type_uiribbon *root, type_subcontrols *src, uiribbon_menugroup_container *ret)
{
    int i, j;

    ret->count_menugroups = src->count_subcontrols;
    ret->menugroups = malloc(sizeof(uiribbon_menugroup) * ret->count_menugroups);

    for (i = 0; i < ret->count_menugroups; i++)
    {
        type_control *src_control = &src->subcontrols[i];
        uiribbon_menugroup *ret_menugroup = &ret->menugroups[i];

        ret_menugroup->item_class = UIRIBBON_MENU_ITEM_CLASS_STANDARD_ITEMS;

        for (j = 0; j < src_control->blocks.count_blocks; j++)
        {
            type_tree_entry_array *src_block_special = &src_control->blocks.blocks[j].array;
            type_tree_entry_number *src_block = &src_control->blocks.blocks[j].property;
            enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

            if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
            {
                if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                {
                    ret_menugroup->id = src_block->id;
                }

                if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE)
                {
                    type_string *str = &root->strings.strings[src_block->id_reference];
                    int len = 10 < str->size_str ? 10 : str->size_str;

                    if (strncmp(str->str, "MajorItems", len) == 0)
                        ret_menugroup->item_class  = UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS;
                }
            }

            if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
            {
                if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                {
                    transform_subcontrols(root, &src_block_special->content_subcontrols, &ret_menugroup->count_controls, &ret_menugroup->controls);
                }
            }
        }
    }
}

void transform_minitoolbar(type_uiribbon *root, type_subcontrols *src, int id, uiribbon_menugroup_container *ret)
{
    int i, j;

    for (i = 0; i < src->count_subcontrols; i++)
    {
        type_control *src_control = &src->subcontrols[i];

        if (src->subcontrols[i].block_type == ENUM_TYPE_CONTROL_MINITOOLBAR)
        {
            bool do_transform = FALSE;

            for (j = 0; j < src_control->blocks.count_blocks; j++)
            {
                type_tree_entry_number *src_block = &src_control->blocks.blocks[j].property;
                enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

                if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
                {
                    if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                    {
                        if (src_block->id == id)
                            do_transform = TRUE;
                    }
                }
            }

            if (do_transform)
            {
                for (j = 0; j < src_control->blocks.count_blocks; j++)
                {
                    type_tree_entry_array *src_block_special = &src_control->blocks.blocks[j].array;
                    enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

                    if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
                    {
                        if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                        {
                            transform_menugroups(root, &src_block_special->content_subcontrols, ret);
                        }
                    }
                }
                return;
            }
        }
    }
}

void transform_contextpopups(type_uiribbon *root, type_subcontrols *src, uiribbon_main *ret)
{
    int i, j;

    int count_contextmaps = 0;

    for (i = 0; i < src->count_subcontrols; i++)
    {
        if (src->subcontrols[i].block_type == ENUM_TYPE_CONTROL_CONTEXTPOPUP)
            count_contextmaps++;
    }

    ret->count_contextmaps = count_contextmaps;
    ret->contextmaps = malloc(sizeof(uiribbon_contextmap) * ret->count_contextmaps);

    count_contextmaps = 0;
    for (i = 0; i < src->count_subcontrols; i++)
    {
        type_control *src_control = &src->subcontrols[i];
        if (src_control->block_type == ENUM_TYPE_CONTROL_CONTEXTPOPUP)
        {
            int id_toolbar = -1;
            uiribbon_contextmap *ret_contextmap = &ret->contextmaps[count_contextmaps];

            count_contextmaps++;
            ret_contextmap->contextpopup.count_menugroups = 0;
            ret_contextmap->contextpopup.menugroups = NULL;
            ret_contextmap->minitoolbar.count_menugroups = 0;
            ret_contextmap->minitoolbar.menugroups = NULL;

            for (j = 0; j < src_control->blocks.count_blocks; j++)
            {
                type_tree_entry_array *src_block_special = &src_control->blocks.blocks[j].array;
                type_tree_entry_number *src_block = &src_control->blocks.blocks[j].property;
                enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

                if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
                {
                    if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID_REFERENCE)
                        id_toolbar = src_block->id_reference;
                    if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                        ret_contextmap->id = src_block->id;
                }

                if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
                {
                    if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                    {
                        transform_menugroups(root, &src_block_special->content_subcontrols, &ret_contextmap->contextpopup);
                    }
                }
            }

            if (id_toolbar != -1)
            {
                transform_minitoolbar(root, src, id_toolbar, &ret_contextmap->minitoolbar);
            }
        }
    }
}

static void transform_applicationmenu_ext(type_uiribbon *root, type_tree_entry_ext *ext, uiribbon_applicationmenu *ret)
{
    int j, k;

    if (ext->block.entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
    {
        if (ext->block.array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
        {
            transform_menugroups(root, &ext->block.array.content_subcontrols, &ret->menugroups);

            /* Enforce major items for applicationmenu */
            for (j = 0; j < ret->menugroups.count_menugroups; j++)
            {
                ret->menugroups.menugroups[j].item_class = UIRIBBON_MENU_ITEM_CLASS_MAJOR_ITEMS;
            }

        }

        if (ext->block.array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_BUTTONITEM)
        {
            type_control *src_control;

            ret->recent.enable_pinning = TRUE;
            ret->recent.count = 10;

            if (ext->block.array.content_subcontrols.count_subcontrols != 1)
                   return;

            src_control = &ext->block.array.content_subcontrols.subcontrols[0];

            for (j = 0; j < src_control->blocks.count_blocks; j++)
            {
                type_tree_entry_array *src_block_special = &src_control->blocks.blocks[j].array;
                type_tree_entry_number *src_block = &src_control->blocks.blocks[j].property;
                enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

                if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
                {
                    if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                        ret->recent.id = src_block->id;
                }

                if (entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
                {
                     if (src_block_special->block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_SUBCOMPONENTS)
                     {
                         ret->recent.count = src_block_special->content_subcontrols.count_subcontrols;
                         if (ret->recent.count > 0)
                         {
                             type_control *sub_control = &src_block_special->content_subcontrols.subcontrols[0];
                             for (k = 0; k < sub_control->blocks.count_blocks; k++)
                             {
                                 type_tree_entry *sub_block = &sub_control->blocks.blocks[k];
                                 if (sub_block->entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
                                 {
                                     if (sub_block->property.block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ENABLE_PINNING)
                                     {
                                         ret->recent.enable_pinning = sub_block->property.enable_pinning;
                                     }
                                 }
                             }
                         }
                     }
                }
            }
        }
    }
}

static void transform_applicationmenu(type_uiribbon *root, type_subcontrols *src, uiribbon_applicationmenu *ret)
{
    int j;
    type_control *src_control;

    ASSERT(src->count_subcontrols == 1);
    src_control = &src->subcontrols[0];

    for (j = 0; j < src_control->blocks.count_blocks; j++)
    {
        type_tree_entry_ext *src_block_ext = src_control->blocks.blocks[j].ext;
        type_tree_entry_number *src_block = &src_control->blocks.blocks[j].property;
        enum_tree_entry_type entry_type = src_control->blocks.blocks[j].entry_type;

        if (entry_type == ENUM_TREE_ENTRY_TYPE_PROPERTY)
        {
            if (src_block->block_type == ENUM_CONTROL_BLOCK_TYPE_NUMBER_ID)
                ret->id = src_block->id;
        }

        if (entry_type == ENUM_TREE_ENTRY_TYPE_EXT)
        {
            transform_applicationmenu_ext(root, src_block_ext, ret);
        }
    }

}

void uiribbon_transform(type_uiribbon *src, uiribbon_main *ret)
{
    int i;

    memset(ret, 0, sizeof(uiribbon_main));

    transform_commands(src, ret);

    for (i = 0; i < src->root_node.node.children.count_blocks; i++)
    {
        type_tree_entry *src_block = &src->root_node.node.children.blocks[i];
        if (src_block->entry_type == ENUM_TREE_ENTRY_TYPE_ARRAY)
        {
            if (src_block->array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_TABS_NORMAL)
            {
                transform_tabs(src, &src_block->array.content_subcontrols, &ret->count_tabs, &ret->tabs);
            }

            if (src_block->array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_TABS_CONTEXT)
            {
                transform_contexttabs(src, &src_block->array.content_subcontrols, ret);
            }

            if (src_block->array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_CONTEXTPOPUPS)
            {
                transform_contextpopups(src, &src_block->array.content_subcontrols, ret);
            }

            if (src_block->array.block_type == ENUM_CONTROL_BLOCK_TYPE_SPECIAL_APPLICATION_MENU)
            {
                transform_applicationmenu(src, &src_block->array.content_subcontrols, &ret->applicationmenu);
            }
        }
    }
}

void free_command(uiribbon_command *src)
{
    free(src->images_small);
    free(src->images_large);
    free(src->images_small_high_contrast);
    free(src->images_large_high_contrast);
}

void free_control(uiribbon_control *src)
{
    int i;

    free(src->size_definitions);

    for (i = 0; i < src->count_subcontrols; i++)
    {
        free_control(&src->subcontrols[i]);
    }
    free(src->subcontrols);

    if (src->type == UIRIBBON_CONTROL_TYPE_SPLITBUTTON)
    {
        free_control(src->control_info.splitbutton.buttonitem);
        free(src->control_info.splitbutton.buttonitem);
    }
}

void free_sizedefinition_orders(uiribbon_sizedefinitions_orders *src)
{
    if (!src)
        return;
    free(src->small.orders);
    free(src->medium.orders);
    free(src->large.orders);
}

void free_group(uiribbon_group *src)
{
    int i;

    for(i = 0; i < src->count_controls; i++)
    {
        free_control(&src->controls[i]);
    }
    free(src->controls);

    free_sizedefinition_orders(src->sizedefinition_orders);
    free(src->sizedefinition_orders);
}

void free_tab(uiribbon_tab *src)
{
    int i;

    for (i = 0; i < src->count_groups; i++)
    {
        free_group(&src->groups[i]);
    }
    free(src->groups);
    free(src->scalepolicies);
}

void free_tabgroup(uiribbon_tabgroup *src)
{
    int i;

    for (i = 0; i < src->count_tabs; i++)
    {
        free_tab(&src->tabs[i]);
    }
    free(src->tabs);
}

void free_menugroup(uiribbon_menugroup *src)
{
    int i;

    for (i = 0; i < src->count_controls; i++)
    {
        free_control(&src->controls[i]);
    }
    free(src->controls);
}

void free_menugroup_container(uiribbon_menugroup_container *src)
{
    int i;

    for (i = 0; i < src->count_menugroups; i++)
    {
        free_menugroup(&src->menugroups[i]);
    }
    free(src->menugroups);
}

void free_contextmap(uiribbon_contextmap *src)
{
    free_menugroup_container(&src->contextpopup);
    free_menugroup_container(&src->minitoolbar);
}

void uiribbon_free(uiribbon_main *src)
{
    int i;

    for (i = 0; i < src->count_commands; i++)
    {
        free_command(&src->commands[i]);
    }
    free(src->commands);

    for (i = 0; i < src->count_tabs; i++)
    {
        free_tab(&src->tabs[i]);
    }
    free(src->tabs);

    for (i = 0; i < src->count_contexttabgroups; i++)
    {
        free_tabgroup(&src->contexttabgroups[i]);
    }
    free(src->contexttabgroups);

    for (i = 0; i < src->count_contextmaps; i++)
    {
        free_contextmap(&src->contextmaps[i]);
    }
    free(src->contextmaps);

    free_menugroup_container(&src->applicationmenu.menugroups);
}
