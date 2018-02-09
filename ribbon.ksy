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
    contents: [2, 31, 0, 0, 0, 1, 2, 1]
  - id: unknown_str1_len
    type: u2
  - id: unknown_str1
    type: str
    size: unknown_str1_len
  - id: unknown3
    contents: [1]
  - id: unknown_str2_len
    type: u2
  - id: unknown_str2
    type: str
    size: unknown_str2_len
  - id: unknown4
    contents: [15]
  - id: len_commands
    type: u4
    dec: 'Length of entries in <Application.Commands>'
  - id: commands
    type: application_command
    repeat: expr
    repeat-expr: len_commands
  - id: unknown5
    contents: [13, 3, 0]
  - id: unk_len1
    type: u2
  - id: unknown6
    type: u2
  - id: unknown7
    contents: [22, 0]
  - id: unknown8
    contents: [36, 0]
  - id: unknown9
    contents: [16]
  - id: unk_len2
    type: u2
  - id: unknown10
    contents: [4, 1, 1, 0x0b, 9, 0, 0x18, 1, 2]
  - id: len_tabs
    type: u2
    doc: 'The number of tabs inside <Application.Views> <Ribbon> <Ribbon.Tabs>'
  - id: tabs
    type: ribbon_tab
    repeat: expr
    repeat-expr: len_tabs

types:
  ribbon_tab:
    seq:
      - id: unknown1
        type: u2
      - id: unknown2
        type: u2
      - id: unknown3
        type: u2
      - id: unknown4
        type: u2
      - id: unknown5
        type: u2
      - id: unknown6
        type: u2
      - id: command_name
        type: u2
      - id: unknown8
        type: u2
      - id: unknown9
        type: u1
      - id: unknown10
        type: u2
  application_command:
    seq:
      - id: command_id
        type: u4
      - id: unknown3
        type: u1
      - id: unknown4
        type: u1
      - id: resource_id_keytip
        type: u4
