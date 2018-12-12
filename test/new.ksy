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
    size: unk5 #!! breaks stuff

types:

  type_unk4:
    seq:
    - id: unk21
      contents: [6, 1, 1, 0x0b]
    - id: unk22
      contents: [9, 0, 0x16, 0, 0x25, 0, 0x10]
    - id: len4 # 22 bigger for each <Button> in <QuickAccessToolbar.ApplicationDefaults>
      type: u2
    - id: quick_ribbon_info
      type: quick_ribbon
      size: len4
    - id: check
      contents: [0x1a, 0, 0x10, 0x12, 0, 2, 1, 1, 0, 4]
    
  application_views:
    seq:
    - id: unk20
      contents: [0x00, 0x00, 0x16, 0x00, 0x24, 0x00, 0x10]
    - id: unk_len1
      type: u2
    - id: unk4
      type: type_unk4
      size: unk_len1
  

  quick_ribbon_button:
    seq:
    - id: unk1
      contents: [22, 0]
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