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
  - id: str_list_len
    type: u2
  - id: strs
    type: str_list
    size: str_list_len - 2
  - id: unknown3
    contents: [0, 0, 0, 0, 0x10]
  - id: command_container_len
    type: u4
  - id: command_container
    type: type_command_container
    size: command_container_len - 4
  - id: len_unk6
    type: u2
  - id: unk5
    type: u2
  - id: unk6
    type: application_views
    size: unk5
    
enums:
  enum_block_type:
    0x18: ribbon_tabs
    0x16: ribbon_quickaccesstoolbar

types:
  type_tab:
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
    - id: flags
      type: u2
    - id: id_u1
      type: u1
      if: (flags & 0x400) != 0
    - id: id_u2
      type: u2
      if: (flags & 0x300) != 0
    - id: unk7
      type: u2
    - id: unk8
      type: u2
    - id: unk9
      type: u1
      
  type_block_tabs:
    seq:
    - id: unk1
      type: u2
    - id: count_tabs
      type: u2
    - id: tabs
      type: type_tab
      repeat: expr
      repeat-expr: count_tabs
  
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
      type: type_block_tabs
      if: block_type == enum_block_type::ribbon_tabs
    - id: quickaccess
      type: type_block_quickaccess
      if: block_type == enum_block_type::ribbon_quickaccesstoolbar
  
  type_unk_application_menu:
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
    - id: unk6
      type: u2
    - id: unk7
      type: u1
    - id: unk8
      type: u2
    - id: flags
      type: u2
    - id: id_u1
      type: u1
      if: (flags & 0x400) != 0
    - id: id_u2
      type: u2
      if: (flags & 0x300) != 0
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
    - id: rest
      size-eos: true

  type_ribbon:
    seq:
    - id: unk1
      contents: [6, 1, 1, 0x0b, 9, 0] # first numbre might be related to number of subelements of ribbon
    - id: block1
      type: type_block_generic
    - id: block2
      type: type_block_generic
    - id: block3
      type: type_block_generic
    - id: application_menu
      type: type_unk_application_menu
    
  block_unk1:
    seq:
    - id: rest
      size: 10

  type_tab_extended:
    seq:
    - id: unk_id1
      type: u2
    - id: unk1
      type: u2
    - id: unk2
      type: u2
    - id: unk3
      type: u1
  
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
      
  type_menu_item_ext:
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
    - id: flags
      type: u2
    - id: id_u1
      type: u1
      if: (flags & 0x400) != 0
    - id: id_u2
      type: u2
      if: (flags & 0x300) != 0
      
  type_menugroup_extended:
    seq:
    - id: unk_id1
      type: u2
    - id: menu_items_len
      type: u2
    - id: items
      type: type_menu_item_ext
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
    
  application_views:
    seq:
    - id: unk20
      contents: [0x00, 0x00, 0x16, 0x00, 0x24, 0x00, 0x10]
    - id: ribbon_len
      type: u2
    - id: ribbon
      type: type_ribbon
      size: ribbon_len
    - id: ribbon_tab_info
      type: type_tab_extended
      repeat: expr
      repeat-expr: 21  #ribbon.tabs count
    - id: ribbon_tab_contextual_info
      type: type_tab_extended
      repeat: expr
      repeat-expr: 18  #ribbon.contextualtabs count
    - id: unk_ext1
      type: type_unk1_extended
    - id: applicationmenu_menugroups_ext
      type: type_menugroup_extended
      repeat: expr
      repeat-expr: 3 #number of menugroups in application menu
    - id: check10
      contents: [4, 1, 1, 0x0b, 4, 0, 1, 1, 0x41, 0x2b]
    - id: check11
      contents: [1, 1, 1, 0, 3, 0x14, 0x27, 0x18]
    - id: recent
      type: type_recent1
  

  quick_ribbon_button:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      contents: [15, 0]
    - id: unk3
      contents: [0x10, 0x16]
    - id: unk4
      contents: [0, 2]
    - id: unk5
      contents: [1, 1]
    - id: flags
      type: u2
    - id: id_u1
      type: u1
      if: (flags & 0x400) != 0
    - id: id_u2
      type: u2
      if: (flags & 0x300) != 0
    - id: unk6
      contents: [1, 4]
    - id: unk7
      contents: [10, 0]
    - id: unk8
      contents: [0xc0, 0x40]
    - id: unk9
      contents: [5, 1]
  quick_ribbon:
    seq:
    - id: unk1
      type: u2
    - id: unk2
      type: u1
    - id: flags
      type: u2
    - id: id_u1
      type: u1
      if: (flags & 0x400) != 0
    - id: id_u2
      type: u2
      if: (flags & 0x300) != 0
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
    - id: rest
      size-eos: true
  type_unk1:
    seq:
    - id: offset1 #13 bigger for every <Button> in <MenuGroup> in <ApplicationMenu>
      type: u2
    - id: unk1
      size: 7
    instances:
      unk44:
        pos: offset1
        type: u4
  type_command:
    seq:
      - id: command_id
        type: u2
      - id: unk2
        type: u2
      - id: unk3
        type: u2
      - id: unk4
        type: u2
      - id: str_len
        type: u2
      - id: str
        type: str
        encoding: utf-16
        size: str_len
  type_unknown_container:
    seq:
    - id: unk1
      type: u2
  type_command_container:
    seq:
    - id: commands_len
      type: u4
    - id: commands
      type: type_command
      repeat: expr
      repeat-expr: commands_len
  type_string:
    seq:
      - id: unknown1
        type: u1
      - id: length
        type: u2
      - id: contents
        type: str
        size: length
  str_list:
    seq:
      - id: unknown1
        type: u2
      - id: unknown2
        type: u1
      - id: count
        type: u1
      - id: strings
        type: type_string
        repeat: expr
        repeat-expr: count
      - id: rest
        size-eos: true