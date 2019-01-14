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


meta:
  id: ribbon
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
    type: u2
  - id: strings
    type: type_strings
    size: size_strings - 2
  - id: count_command_resources
    type: u2
  - id: unknown3
    contents: [0, 0]
  - id: command_resources
    type: type_resource
    repeat: expr
    repeat-expr: count_command_resources
  - id: unk44
    contents: [0x10]
  - id: size_command_container
    type: u4
  - id: command_container
    type: type_command_container
    size: size_command_container - 4
  - id: len_unk6
    type: u2
  - id: unklen6
    type: u2
  - id: unk6
    type: application_views
    #size: unk5 - count_command_resources * 10 - 500 # 10 = size for resources - not properly calculated yet

enums:

  enum_block_type:
    0x18: ribbon_tabs
    0x16: ribbon_quickaccesstoolbar

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
    3: command
    9: special

  enum_type_control:
    15: button
    20: dropdownbutton
    6: checkbox
    25: otherinfo
    21: combobox
    18: splitbutton

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

  enum_control_block_type:
    0: id
    6: sizedefinition_labelvisible_mixed
    8: sizedefinition_imagesize_mixed
    9: sizedefinition_labelvisible
    4: unk4
    24: subcomponents
    36: sizedefinition_imagevisible
    37: sizedefinition_imagesize
    93: autocomplete_enabled
    73: vertical_resize
    70: unk1
    71: editable
    87: unk3
    88: unk5
    63: unk6

types:

  type_id:
    seq:
    - id: flag
      type: u1
    - id: id
      type:
        switch-on: flag
        cases:
          2: u4
          3: u2
          4: u1

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
        contents: [0, 0, 1]
      - id: count_strings
        type: u1
      - id: strings
        type: type_string
        repeat: expr
        repeat-expr: count_strings
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

  type_tab:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: unk3a
      type: u1
    - id: unk3b
      type: u1
    - id: unk4
      type: u2
    - id: unk5
      type: u2
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk7a
      type: u1
    - id: offset_ext
      type: u2
    - id: unk8
      type: u1
    - id: unk9
      type: u1
    instances:
      ext:
        io: _root._io
        pos: offset_ext + 3
        type: type_tab_extended

  type_tabgroup:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: unk3a
      type: u1
    - id: unk3b
      type: u1
    - id: unk4
      type: u2
    - id: unk5
      type: u2
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk7
      type: u1
    - id: unk8
      type: u2
    - id: count_tabs
      type: u2
    - id: tabs
      type: type_tab
      repeat: expr
      repeat-expr: count_tabs

  type_ribbon_tabs_normal:
    seq:
    - id: count_tabs
      type: u2
    - id: tabs
      type: type_tab
      repeat: expr
      repeat-expr: count_tabs

  type_ribbon_tabs_context:
    seq:
    - id: count_tabgroups
      type: u2
    - id: tabgroups
      type: type_tabgroup
      repeat: expr
      repeat-expr: count_tabgroups

  type_block_tabs:
    seq:
    - id: unk1a
      type: u1
    - id: tab_type
      type: u1
      enum: enum_tab_type
    - id: tabs
      type:
        switch-on: tab_type
        cases:
          enum_tab_type::help:   type_ribbon_tabs_normal
          enum_tab_type::normal: type_ribbon_tabs_normal
          enum_tab_type::context: type_ribbon_tabs_context
          enum_tab_type::applicationmenu: type_ribbon_tabs_applicationmenu

  type_block_quickaccess:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: len4 # 22 bigger for each <Button> in <QuickAccessToolbar.ApplicationDefaults>
      type: u2
    - id: quick_ribbon_info
      type: quick_ribbon
      size: len4 - 7


  type_block_generic:
    seq:
    - id: block_type
      type: u1
      enum: enum_block_type
    - id: tabs
      type:
        switch-on: block_type
        cases:
          enum_block_type::ribbon_tabs: type_block_tabs
          enum_block_type::ribbon_quickaccesstoolbar: type_block_quickaccess

  type_ribbon_tabs_applicationmenu:
    seq:
    - id: unk2
      type: u1
    - id: unk3
      type: u2
    - id: unk4
      type: u2
    - id: unk5
      type: u2
    - id: unk6
      type: u2
    - id: unk7
      type: u1
    - id: unk8
      type: u2
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk11
      type: u2
    - id: unk12
      type: u2
    - id: unk13
      type: u2
    - id: unk14
      type: u2
    - id: unk15
      type: u1
    - id: unk16
      size: 5
    - id: unk17 #offset? changes with sizedefinition
      type: u4
    - id: unk18
      size: 1
    - id: unk19 #offset? changes with sizedefinition
      type: u4
    - id: unk20
      size: 1
    - id: unk21 #offset? changes with sizedefinition
      type: u4

  type_ribbon:
    seq:
    - id: count_blocks
      type: u1
    - id: unk1
      contents: [1, 1, 0x0b, 9, 0]
    - id: block1
      type: type_block_generic
      repeat: expr
      repeat-expr: count_blocks

  block_unk1:
    seq:
    - id: rest
      size: 10
      
  type_sizeinfo_maybe:
    seq:
    - id: unk0
      type: u1
    - id: check1
      contents: [1, 4, 37, 0, 128, 65, 5]
    - id: unk0c
      type: u2
    - id: unk0b
      type: u2
    - id: unk2a
      type: u1
    - id: unk2b
      type: u1
    - id: unk2c
      type: u1
    - id: unk1   #ofsset maybe? 3 bigger when _parent-len_unk1 3 bigger
      type: u1
    - id: unk1e1
      size: 3
      if: unk1 == 4
    - id: unk2
      type: u1
    - id: unk3
      type: u1
    - id: unk4
      type: u1
    - id: unk5
      type: u1
    - id: unk6
      type: u1
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk11
      type: u1

  type_sizedefinitions_command:
    seq:
    - id: unk1
      type: u1
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

  type_sizedefinition:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u1
    - id: count_commands
      type: u2
    - id: commands
      type: type_sizedefinitions_command
      repeat: expr
      repeat-expr: count_commands

  type_group_elements_info:
    seq:
    - id: unk10 #2 if own size, 3 otherwise
      type: u1
    - id: check2b
      contents: [1, 1]
    - id: unk1b
      type: u2
    - id: unk2
      type: u1
    - id: check2c
      contents: [1, 4, 66, 0, 0x40, 0x44, 5, 0]
      if: unk10 == 3 and unk2 == 9
    - id: unk1c
      type: u2
    - id: unk1d
      type: u1
    - id: sub_count
      type: u2
    - id: subcontents
      type: type_control
      repeat: expr
      repeat-expr: sub_count
    - id: sizedefinition_large
      type: type_sizedefinition
      if: unk10 == 5
    - id: sizedefinition_medium
      type: type_sizedefinition
      if: unk10 == 5
    - id: sizedefinition_small
      type: type_sizedefinition
      if: unk10 == 5
    - id: unk6
      size: 3

  type_scalingpolicy:
    seq:
    - id: unk1a
      type: u1
    - id: unk1b
      type: u1
    - id: scale_value
      type: type_id
      doc: |
        This is calculated the following way:
        sum(basevalue1 * position1 + basevalue2 * position2 + ...)
        basevalues: large(0), popup(1), small(16), medium(256)
        e.g. large-medium-small = 0*1 + 256*2 + 16*3 = 560
    - id: unk3
      type: u1
    instances:
      priority_medium:
        value: scale_value.id / 256
      priority_small:
        value: (scale_value.id % 256) / 16
      priority_popup:
        value: (scale_value.id % 16) / 1

  type_group_info:
    seq:
    - id: unk1
      type: u2
    - id: len_unk1 # same as size_group_elements_info, just a bit bigger
      type: u2
    - id: unk3
      type: u2
    - id: unk4
      type: u2
    - id: id
      type: type_id
    - id: unk20a
      type: u1
    - id: scalingpolicy
      type: type_scalingpolicy
      if: unk20a == 1
    - id: unk20b
      type: u1
    - id: unk12
      type: u2
    - id: unk21
      type: u2
    - id: unk10
      type: u2
    - id: unk11
      type: u2
    - id: size_group_elements_info
      type: u2
    - id: group_elements_info
      type: type_group_elements_info
      size: size_group_elements_info - 4

  type_tab_extended:
    seq:
    - id: unk_id1
      type: u2
    - id: count_groupinfo
      type: u2
    - id: unk2
      type: u2
    - id: unk3
      type: u1
    - id: groupinfo
      type: type_group_info
      repeat: expr
      repeat-expr: count_groupinfo

  type_unk1_extended:
    seq:
    - id: unk_id1
      type: u2
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: unk3
      type: u2
    - id: unk4
      type: u2
    - id: unk5
      type: u2
    - id: unk6
      type: u2
    - id: unk7
      type: u2
    - id: unk8
      type: u2
  
  type_control_block_subcomponents:
    seq:
    - id: unk1
      type: u2
    - id: count_elements
      type: u2
    # - id: elements
    #   type: type_control
    #   repeat: expr
    #   repeat-expr: count_elements
  
  type_control_block_sizedefinition_labelvisible_mixed:
    seq:
    - id: unk1
      type: u1
    - id: sizedefinition_labelvisible_mixed
      type: u1
      enum: enum_sizedefinition_labelvisible_mixed
    - id: unk3
      type: u1
    - id: unk4
      type: u1

  type_control_block_sizedefinition_imagesize_mixed:
    seq:
    - id: unk1
      type: u1
    - id: sizedefinition_imagesize_mixed
      type: u1
      enum: enum_sizedefinition_imagesize_mixed
    - id: unk3
      type: u1
    - id: unk4
      type: u1

  type_control_block_sizedefinition_imagevisible:
    seq:
    - id: unk1
      size: 4
    - id: sizedefinition_imagevisible
      type: u1
      enum: enum_sizedefinition_imagevisible
    - id: unk3
      type: u1
    - id: unk4
      type: u1
  
  type_control_block_sizedefinition_labelvisible:
    seq:
    - id: unk1
      size: 4
    - id: sizedefinition_labelvisible
      type: u1
      enum: enum_sizedefinition_labelvisible
    - id: unk3
      type: u1
    - id: unk4
      type: u1

  type_control_block_sizedefinition_imagesize:
    seq:
    - id: unk1
      size: 4
    - id: sizedefinition_imagesize
      type: u1
      enum: enum_sizedefinition_imagesize
    - id: unk3
      type: u1
    - id: unk4
      type: u1

  type_control_block_unk4:
    seq:
    - id: unk1
      type: u4

  type_control_block_info4:
    seq:
    - id: unk1
      type: u1
    - id: value_bool
      type: u1
    - id: unk2
      type: u1
    - id: unk3
      type: u1

  type_control_block_info7:
    seq:
    - id: unk1
      type: u4
    - id: value_bool
      type: u1
    - id: unk2
      type: u1
    - id: unk3
      type: u1

  type_control_block_generic:
    seq:
    - id: block_type
      type: u1
      enum: enum_control_block_type
    - id: block
      type:
        switch-on: block_type
        cases:
          enum_control_block_type::id: type_id
          enum_control_block_type::sizedefinition_labelvisible_mixed: type_control_block_sizedefinition_labelvisible_mixed
          enum_control_block_type::sizedefinition_imagesize_mixed: type_control_block_sizedefinition_imagesize_mixed
          enum_control_block_type::sizedefinition_labelvisible: type_control_block_sizedefinition_labelvisible
     #     4: type_control_block_4
          enum_control_block_type::subcomponents: type_control_block_subcomponents
          enum_control_block_type::sizedefinition_imagevisible: type_control_block_sizedefinition_imagevisible
          enum_control_block_type::sizedefinition_imagesize: type_control_block_sizedefinition_imagesize
          enum_control_block_type::unk1: type_control_block_unk4
          enum_control_block_type::editable: type_control_block_unk4
          enum_control_block_type::unk3: type_control_block_unk4
          enum_control_block_type::unk5: type_control_block_unk4
          enum_control_block_type::autocomplete_enabled: type_control_block_info7
          enum_control_block_type::vertical_resize: type_control_block_info4
          enum_control_block_type::unk6: type_control_block_info7
  
  type_control_blocks:
    seq:
    - id: count_blocks
      type: u1
    - id: unk1
      type: u2
      if: count_blocks > 0
    - id: blocks
      type: type_control_block_generic
      repeat: expr
      repeat-expr: count_blocks
    - id: blocks_bytes
      size-eos: true

  type_control:
    seq:
    - id: unk1
      type: u2
    - id: block_type
      type: u2
      enum: enum_type_control
    - id: unk2
      type: u1
    - id: size_block
      type: u2
    - id: block
      size: size_block - 7
      type: type_control_blocks

  type_menugroup_extended:
    seq:
    - id: unk_id1
      type: u2
    - id: menu_items_len
      type: u2
    - id: items
      type: type_control
      repeat: expr
      repeat-expr: menu_items_len
    - id: unk1
      type: u4
    - id: unk2
      type: u4
    - id: unk3
      type: u4
    - id: unk4
      type: u2

  type_recent2:
    seq:
    - id: unk1
      type: u4
    - id: unk2
      type: u4
    - id: unk3
      type: u4
    - id: own_index
      type: u1
    - id: unk4b
      type: u1
    - id: unk4c
      type: u2
    - id: unk5
      type: u4
    - id: unk6
      type: u4
    - id: unk7
      type: u4
    - id: unk8
      type: u4
    - id: unk9
      type: u4
    - id: unk10
      type: u1

  type_recent1:
    seq:
    - id: unk_id1
      type: u2
    - id: recent_len # <RecentItems MaxCount="XXX" />
      type: u2
    - id: elements
      type: type_recent2
      repeat: expr
      repeat-expr: recent_len

  type_command_ext:
    seq:
    - id: own_index_maybe
      type: u2
    - id: unk0
      type: u2
    - id: unk1a  #offset? changes with sizedefinition
      type: u2
    - id: unk2
      type: u2
    - id: command_id
      type: u2

  application_views:
    seq:
    - id: unk20
      contents: [0x00, 0x00, 0x16, 0x00, 0x24, 0x00, 0x10]
    - id: ribbon_len
      type: u2
    - id: ribbon
      type: type_ribbon
      size: ribbon_len
    # - id: ribbon_tab_info
    #   type: type_tab_extended
    #   repeat: expr
    #   repeat-expr: 1  #ribbon.tabs count
    # - id: ribbon_tab_contextual_info
    #   type: type_tab_extended
    #   repeat: expr
    #   repeat-expr: 0  #ribbon.contextualtabs count
    # - id: unk_ext1
    #   type: type_unk1_extended
    # - id: applicationmenu_menugroups_ext
    #   type: type_menugroup_extended
    #   repeat: expr
    #   repeat-expr: 0 #number of menugroups in application menu
    # - id: check10
    #   contents: [4, 1, 1, 0x0b, 4, 0, 1, 1, 0x41, 0x2b]
    # - id: unk10
    #   type: u1
    # - id: check11
    #   contents: [1, 1, 0, 3]
    # - id: unk12
    #   type: u1
    # - id: check12
    #   contents: [0x27, 0x18]
    # - id: recent
    #   type: type_recent1
    # - id: check13
    #   contents: [7, 0, 0x18]
    # - id: command_ext
    #   type: type_command_ext
    #   repeat: expr
    #   repeat-expr: 46 # number or commands that are actually used + recent + unknown

  quick_ribbon_button:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: unk3
      type: u2
    - id: unk4
      type: u2
    - id: unk5
      type: u2
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk6
      contents: [1, 4]
    - id: unk7
      type: u2
    - id: unk8
      type: u2
    - id: unk9
      type: u2

  quick_ribbon:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u1
    - id: unk100
      type: u1
    - id: id
      type: type_id
    - id: unk3
      type: u2
    - id: unk4
      type: u1
    - id: unk5_len # count of elements in QuickAccessToolbar.ApplicationDefaults?
      type: u2
    - id: entries
      type: quick_ribbon_button
      repeat: expr
      repeat-expr: unk5_len

  type_command:
    seq:
      - id: command_id
        type: u2
      - id: unk1
        contents: [0, 0, 0]
      - id: unk3b
        type: u1
      - id: unk4
        contents: [0, 0x10]
      - id: size_str
        type: u2
      - id: str
        type: str
        #encoding: utf-16 - disabled, doesn't play nice with ksdump
        size: size_str

  type_command_container:
    seq:
    - id: commands_len
      type: u4
    - id: commands
      type: type_command
      repeat: expr
      repeat-expr: commands_len