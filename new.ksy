doc-ref: https://docs.microsoft.com/en-us/windows/desktop/windowsribbon/windowsribbon-element-ribbon
#doc-ref: https://www.codeproject.com/Articles/62534/Article

#consolidate tab and menu
#maybe reuse block structure blocks
#move up application menu without breaking
#write tests?! - C++ mit xml und binary embedded in source file, 1 source file

#find out how sizedefinitions come into command_blocks
#find out how placement changes maybesize in command_blocks


#add doc to everything known
#missing groups in sizedefinition

#test against mspaint ribbon! + wordpad + samples

#make group as children in splitbutton?! (test if can have sizedefinitions)

#cleanup names


meta:
  id: uiribbon
  file-extension: bml
  endian: le
  encoding: ASCII

seq:
  - id: unknown1
    contents: [0, 18, 0, 0, 0, 0, 0, 1, 0]
  - id: magic
    contents: "SCBin"
  - id: length_this_file
    type: u4
  - id: unknown2
    contents: [2]
  - id: size_strings
    type: u4
  - id: strings
    type: type_strings
    size: size_strings - 4
  - id: count_command_resources
    type: u4
  - id: command_resources
    type: type_resource
    repeat: expr
    repeat-expr: count_command_resources
  - id: nodes
    type: type_tree_entry
    repeat: until
    repeat-until: _.entry_type == enum_tree_entry_type::node

enums:

  enum_resource_type:
    1: labeltitle
    2: labeldescription
    3: smallhighcontrastimage
    4: largehighcontrastimage
    5: smallimage
    6: largeimage
    7: keytip
    8: tooltiptitle
    9: tooltipdescription

  enum_tab_type:
    0: applicationmenu
    2: normal
    3: context
    5: help

  enum_sizedefinitions_command:
    2: command_internal
    3: command
    9: special

  enum_type_control:
    15: button
    13: spinner
    20: dropdownbutton
    6: checkbox
    25: otherinfo
    21: gallery
    18: splitbutton
    24: menugroup
    26: tab
    7: group
    27: tabgroup
    5: minitoolbar
    4: contextpopup
    19: applicationmenu
    37: quickaccess
    38: subgroup

  enum_sizedefinition_imagesize:
    0: small
    1: large

  enum_sizedefinition_labelvisible:
    0: hidden
    1: visible
  
  enum_sizedefinition_imagevisible:
    0: hidden
    1: visible

  enum_sizedefinition_imagesize_mixed:
    2: smallissmall
    3: smallandmediumaresmall
  
  enum_sizedefinition_labelvisible_mixed:
    2: overridesmall
    3: overridesmallandmedium

  enum_dropdowncolorpicker_colortemplate:
    0: theme_colors
    1: standard_colors
    2: highlight_colors

  enum_dropdowncolorpicker_chipsize:
    1: small
    2: medium
    3: large

  enum_tree_entry_type:
    1:  property
    13: command_ext
    16: command_container
    24: array
    22: node
    62: ext
    0x3b: sizeinfo

  enum_control_block_type_number:
    0: id
    6: sizedefinition_labelvisible_mixed
    8: sizedefinition_imagesize_mixed
    9: sizedefinition_labelvisible
    36: sizedefinition_imagevisible
    37: sizedefinition_imagesize
    93: autocomplete_enabled
    70: gallery_type
    110: dropdowncolorpicker_colortemplate
    111: dropdowncolorpicker_chipsize
    112: dropdowncolorpicker_columns
    116: dropdowncolorpicker_has_autocolor_button
    117: dropdowncolorpicker_has_nocolor_button
    115: dropdowncolorpicker_recent_color_rows
    114: dropdowncolorpicker_standard_color_rows
    113: dropdowncolorpicker_theme_color_rows
    68: meta_info
    38: gallery_has_large_items
    87: gallery_item_height
    88: gallery_item_width
    78: gallery_text_position
    71: gallery_menulayout
    73: gallery_gripper
    76: gallery_rows
    77: gallery_columns
    74: gallery_max_rows
    75: gallery_max_columns
    119: gallery_min_columns_large
    120: gallery_max_columns_medium
    121: gallery_min_columns_medium
    63: is_checkbox
    65: id_reference
    64: enable_pinning
    79: fontcontrol_str # id in strings - maximum number of 'I' that fit into fontcontrol
    48: fontcontrol_fontsize_min
    49: fontcontrol_fontsize_max
    44: fontcontrol_parent_commandid
    46: fontcontrol_truetypeonly
    47: fontcontrol_verticalfonts

  enum_control_block_type_special:
    62: subcomponents
    67: sizedefinition_order_large
    68: sizedefinition_order_medium
    69: sizedefinition_order_small
    72: buttonitem
    86: gallery_subcontrols
    0: application_menu
    2: tabs_normal
    3: tabs_context
    66: quickaccess
    5: tabs_help
    10: contextpopups

  enum_boolean:
    0: bool_false
    1: bool_true

  enum_gallery_type:
    0: inribbon
    1: dropdownbutton
    2: dropdownlist
    3: combo
    4: dropdownsplit

  enum_gallery_elements_type:
    0: items
    1: commands

  enum_gallery_text_position:
    0: bottom
    1: right
    2: top
    3: left
    4: overlay
    5: hide

  enum_gallery_menulayout:
    0: special
    1: vertical
    2: flow

  enum_gallery_gripper:
    0: none
    1: vertical
    2: corner

types:

  type_id:
    seq:
    - id: flag
      type: u1
    - id: id
      type:
        switch-on: flag
        cases:
          2: s4
          3: s2
          4: s1
          9: s1
          43: s1

  type_string:
    seq:
      - id: unk1
        contents: [1]
      - id: size_str
        type: u2
      - id: str
        type: str
        size: size_str
    -webide-representation: '{str}'

  type_strings:
    seq:
      - id: unk1
        contents: [1]
      - id: count_strings
        type: u1
      - id: strings
        type: type_string
        repeat: expr
        repeat-expr: count_strings
      - id: unk2
        type: u1
    -webide-representation: '{strings}'

  type_resource_generic:
    seq:
    - id: resource_type
      type: u1
      enum: enum_resource_type
    - id: resource_id
      type: u4
    - id: mindpi
      type: u2
      if: resource_type == enum_resource_type::largeimage or resource_type == enum_resource_type::smallimage
          or resource_type == enum_resource_type::largehighcontrastimage
          or resource_type == enum_resource_type::smallhighcontrastimage

  type_resource:
    seq:
    - id: command_id 
      type: u4
    - id: count_resources
      type: u1
    - id: resources
      type: type_resource_generic
      repeat: expr
      repeat-expr: count_resources

  type_tree_entry_node:
    seq:
    - id: unk56
      type: u1
    - id: type
      type: u2
      enum: enum_type_control
    - id: unk3
      type: u1
    - id: size_node
      type: u2
    - id: count_children
      type: u1
    - id: children
      type: type_tree_entry
      repeat: expr
      repeat-expr: count_children


  type_sizedefinitions_order_command:
    seq:
    - id: flags_command
      type: u1
      enum: enum_sizedefinitions_command
    - id: string_id
      type: u1
      doc: 'Id in global string table'
      if: flags_command == enum_sizedefinitions_command::special
    - id: command_id
      type: u2
      if: flags_command == enum_sizedefinitions_command::command
    - id: unk2
      type: u4
      if: flags_command == enum_sizedefinitions_command::command_internal

  type_tree_entry_number_variable:
    seq:
    - id: id
      type: type_id

  type_tree_entry_number_long:
    seq:
    - id: unk1
      type: u4
    - id: value1
      type: u1

  type_tree_entry_number:
    seq:
    - id: block_len
      type: u1
    - id: block_type
      enum: enum_control_block_type_number
      type: u1
    - id: content_number
      type: type_tree_entry_number_variable
      if: block_len == 1
    - id: content_long
      type: type_tree_entry_number_long
      if: block_len == 4
    instances:
      id:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::id
      sizedefinition_labelvisible_mixed:
        value: content_number.id.id
        enum: enum_sizedefinition_labelvisible_mixed
        if: block_type == enum_control_block_type_number::sizedefinition_labelvisible_mixed
      sizedefinition_labelvisible:
        value: content_long.value1
        enum: enum_sizedefinition_labelvisible
        if: block_type == enum_control_block_type_number::sizedefinition_labelvisible
      sizedefinition_imagevisible:
        value: content_long.value1
        enum: enum_sizedefinition_imagevisible
        if: block_type == enum_control_block_type_number::sizedefinition_imagevisible
      sizedefinition_imagesize:
        value: content_long.value1
        enum: enum_sizedefinition_imagesize
        if: block_type == enum_control_block_type_number::sizedefinition_imagesize
      sizedefinition_imagesize_mixed:
        value: content_number.id.id
        enum: enum_sizedefinition_imagesize_mixed
        if: block_type == enum_control_block_type_number::sizedefinition_imagesize_mixed
      autocomplete_enabled:
        value: content_long.value1
        enum: enum_boolean
        if: block_type == enum_control_block_type_number::autocomplete_enabled
      gallery_type:
        value: content_number.id.id
        enum: enum_gallery_type
        if: block_type == enum_control_block_type_number::gallery_type
      dropdowncolorpicker_colortemplate:
        value: content_number.id.id
        enum: enum_dropdowncolorpicker_colortemplate
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_colortemplate
      dropdowncolorpicker_chipsize:
        value: content_number.id.id
        enum: enum_dropdowncolorpicker_chipsize
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_chipsize
      dropdowncolorpicker_columns:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_columns
      dropdowncolorpicker_has_autocolor_button:
        value: content_long.value1
        enum: enum_boolean
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_has_autocolor_button
      dropdowncolorpicker_has_nocolor_button:
        value: content_long.value1
        enum: enum_boolean
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_has_nocolor_button
      dropdowncolorpicker_recent_color_rows:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_recent_color_rows
      dropdowncolorpicker_standard_rows:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_standard_color_rows
      dropdowncolorpicker_theme_color_rows:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::dropdowncolorpicker_theme_color_rows
      gallery_elements_type:
        value: content_number.id.id
        enum: enum_gallery_elements_type
        if: block_type == enum_control_block_type_number::meta_info and block_len == 1
      gallery_has_large_items:
        value: content_long.value1
        enum: enum_boolean
        if: block_type == enum_control_block_type_number::gallery_has_large_items
      gallery_item_height:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_item_height
      gallery_item_width:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_item_width
      gallery_text_position:
        value: content_number.id.id
        enum: enum_gallery_text_position
        if: block_type == enum_control_block_type_number::gallery_text_position
      gallery_menulayout:
        value: content_number.id.id
        enum: enum_gallery_menulayout
        if: block_type == enum_control_block_type_number::gallery_menulayout
      gallery_gripper:
        value: content_number.id.id
        enum: enum_gallery_gripper
        if: block_type == enum_control_block_type_number::gallery_gripper
      gallery_rows:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_rows
      gallery_columns:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_columns
      gallery_max_rows:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_max_rows
      gallery_max_columns:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_max_columns
      gallery_min_columns_large:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_min_columns_large
      gallery_max_columns_medium:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_max_columns_medium
      gallery_min_columns_medium:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::gallery_min_columns_medium
      is_checkbox:
        value: content_long.value1
        if: block_type == enum_control_block_type_number::is_checkbox
      scalepolicy:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::meta_info and block_len == 1
        doc: |
          This is calculated the following way:
          sum(basevalue1 * position1 + basevalue2 * position2 + ...)
          basevalues: large(0), popup(1), small(16), medium(256)
          e.g. large-medium-small = 0*1 + 256*2 + 16*3 = 560
      scalepolicy_medium:
        value: scalepolicy / 256
        if: block_type == enum_control_block_type_number::meta_info and block_len == 1
      scalepolicy_small:
        value: (scalepolicy % 256) / 16
        if: block_type == enum_control_block_type_number::meta_info and block_len == 1
      scalepolicy_popup:
        value: (scalepolicy % 16) / 1
        if: block_type == enum_control_block_type_number::meta_info and block_len == 1
      id_reference:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::id_reference
      enable_pinning:
        value: content_long.value1
        if: block_type == enum_control_block_type_number::enable_pinning
      fontcontrol_str:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::fontcontrol_str
      fontcontrol_fontsize_min:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::fontcontrol_fontsize_min
      fontcontrol_fontsize_max:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::fontcontrol_fontsize_max
      fontcontrol_parent_commandid:
        value: content_number.id.id
        if: block_type == enum_control_block_type_number::fontcontrol_parent_commandid
      fontcontrol_truetypeonly:
        value: content_long.value1
        if: block_type == enum_control_block_type_number::fontcontrol_truetypeonly
      fontcontrol_verticalfonts:
        value: content_long.value1
        if: block_type == enum_control_block_type_number::fontcontrol_verticalfonts

  type_tree_entry_array:
    seq:
    - id: block_len
      type: u1
    - id: block_type
      enum: enum_control_block_type_special
      type: u1
    - id: count_children
      type: u2
    - id: children
      type: type_tree_entry
      repeat: expr
      repeat-expr: count_children

  type_tree_entry:
    seq:
    - id: entry_type
      type: u1
      enum: enum_tree_entry_type
    - id: property
      type: type_tree_entry_number
      if: entry_type == enum_tree_entry_type::property
    - id: array
      type: type_tree_entry_array
      if: entry_type == enum_tree_entry_type::array
    - id: node
      type: type_tree_entry_node
      if: entry_type == enum_tree_entry_type::node
    - id: ext_pos
      type: u4
      if: entry_type == enum_tree_entry_type::ext
    - id: sizeinfo
      type: type_sizedefinitions_order_command
      if: entry_type == enum_tree_entry_type::sizeinfo
    - id: command_container
      type: type_command_container
      if: entry_type == enum_tree_entry_type::command_container
    - id: command_ext
      if: entry_type == enum_tree_entry_type::command_ext
      type: type_command_ext2
    instances:
     ext:
       io: _root._io
       type: type_tree_entry_ext
       pos: ext_pos
       if: entry_type == enum_tree_entry_type::ext

  type_tree_entry_ext:
    seq:
    - id: len_ext
      type: u2
    - id: block
      type: type_tree_entry

  type_command:
    seq:
      - id: command_id
        type: u2
      - id: unk1
        size: 3
      - id: unk3b
        type: u1
      - id: unk4
        size: 2
      - id: size_str
        type: u2
      - id: str
        type: str
        #encoding: utf-16 - disabled, doesn't play nice with ksdump
        size: size_str

  type_command_container:
    seq:
    - id: container_len
      type: u4
    - id: commands_len
      type: u4
    - id: commands
      type: type_command
      repeat: expr
      repeat-expr: commands_len

  type_command_ext5:
    seq:
    - id: command_id
      type: u2
    - id: count
      type: u2
      doc: 'command ids can be used multiple times, this is an index to differentiate between them'
    - id: unk3
      contents: [0, 0]
    - id: offset
      type: u2
      doc: 'offset, starting from beginning, references start of control that uses this id'
    - id: unk5
      contents: [0, 0]

  type_command_ext4:
    seq:
    - id: blocks
      repeat: eos
      type: type_command_ext5

  type_command_ext3:
    seq:
    - id: size_commands
      type: u2
    - id: unk2
      type: u2
    - id: unk3
      size: size_commands - 4
      type: type_command_ext4

  type_command_ext2:
    seq:
      - id: unknown3
        contents: [03, 0]
      - id: command_ext_pos
        type: u4
    instances:
      ext:
        io: _root._io
        pos: command_ext_pos
        type: type_command_ext3
