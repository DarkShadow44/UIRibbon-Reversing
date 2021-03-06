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
  - id: len_commands
    type: u2
    doc: 'Length of entries in <Application.Commands>'
  - id: unknown77
    type: u2
  - id: commands
    type: application_command
    repeat: expr
    repeat-expr: len_commands
  - id: unknown5
    contents: [13, 3, 0]
  - id: unk_len1
    type: u2
  - id: unknown6
    type: u1
  - id: contextual_tabs
    doc: '<Application.Views> <Ribbon> <Ribbon.ContextualTabs>'
    type: xml_element
  - id: unknown7
    size: 3
  - id: tab_len
    type: u2
  - id: tabs
    type: xml_element
    repeat: expr
    repeat-expr: tab_len
  - id: unknown8a
    size: 5
  - id: unknown8b
    type: xml_element_nosub
  - id: unknown8c
    type: xml_element_nosub

  # - id: unknown11
  #   contents: [0x18, 0x01, 0x00, 0x01, 0x00, 0x16, 0x00, 0x13, 0x00, 0x10, 0x2A, 0x00, 0x06, 0x01, 0x01, 0x00, 0x03, 0x5C]
  # - id: unknown12
  #   contents: [0x11, 0x01, 0x04, 0x44, 0x00, 0x80, 0x44, 0x05, 0x01, 0x01, 0x01, 0x0B, 0x04, 0x00, 0x3E, 0x79, 0x03, 0x00, 0x00, 0x3E, 0x98, 0x03, 0x00, 0x00, 0x3e]
  # - id: unk_len3
  #   type: u4
  # - id: unknown13
  #   contents: [0x16, 0x00, 0x25, 0x00, 0x10, 0x41, 0x02, 0x01, 0x18, 0x01, 0x42, 0x01, 0x00, 0x16, 0x00, 0x14, 0x00, 0x10, 0x34, 0x02, 0x04, 0x01, 0x01, 0x00, 0x02, 0x8C, 0xFE, 0x00, 0x00, 0x01, 0x04, 0x09]
  # - id: unknown14
  #   contents: [0x00, 0x80, 0x40, 0x05, 0x00, 0x01, 0x04, 0x44, 0x00, 0x80, 0x44, 0x05, 0x01, 0x18, 0x01, 0x3E, 0x03, 0x00, 0x16, 0x00, 0x18, 0x00, 0x10, 0xA9, 0x01, 0x03, 0x01, 0x01, 0x00, 0x02, 0x94, 0xFE]
  # - id: unknown15
  #   contents: [0x00, 0x00, 0x01, 0x01, 0x41, 0x2B, 0x01, 0x18, 0x01, 0x3E, 0x13, 0x00, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04]
  # - id: unknown16
  #   contents: [0x00, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x01, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01]
  # - id: unknown17
  #   contents: [0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x02, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x03]
  # - id: unknown18
  #   contents: [0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x04, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00]
  # - id: unknown19
  #   contents: [0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x05, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x06, 0x16]
  # - id: unknown20
  #   contents: [0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x07, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02]
  # - id: unknown21
  #   contents: [0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x08, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x09, 0x16, 0x00]
  # - id: unknown22
  #   contents: [0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x0A, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95]
  # - id: unknown23
  #   contents: [0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x0B, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04, 0x0d]
  # - id: unknown24
  #   contents: [0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B, 0x04]
  # - id: unknown25
  #   contents: [0x0E, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01, 0x0B]
  # - id: unknown26
  #   contents: [0x04, 0x0F, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01, 0x01]
  # - id: unknown27
  #   contents: [0x0B, 0x04, 0x10, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00, 0x01]
  # - id: unknown28
  #   contents: [0x01, 0x0B, 0x04, 0x11, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00, 0x00]
  # - id: unknown29
  #   contents: [0x01, 0x01, 0x0B, 0x04, 0x12, 0x16, 0x00, 0x06, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x95, 0xFE, 0x00]
  # - id: unknown30
  #   contents: [0x00, 0x01, 0x01, 0x0B, 0x04, 0x13, 0x16, 0x00, 0x18, 0x00, 0x10, 0x3C, 0x00, 0x02, 0x01, 0x01, 0x41, 0x2B, 0x01, 0x18]
  # - id: unknown31
  #   contents: [0x01, 0x3E, 0x02, 0x00, 0x16, 0x00, 0x0F, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x81, 0xFE, 0x00, 0x00]
  # - id: unknown32
  #   contents: [0x01, 0x01, 0x0B, 0x04, 0x00, 0x16, 0x00, 0x0F, 0x00, 0x10, 0x15, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x80, 0xFE, 0x00]
  # - id: unknown33
  #   contents: [0x00, 0x01, 0x01, 0x33, 0x04, 0x00, 0x16, 0x00, 0x18, 0x00, 0x10, 0x2A, 0x00, 0x02, 0x01, 0x01, 0x41, 0x2B, 0x01, 0x18]
  # - id: unknown34
  #   contents: [0x01, 0x3E, 0x01, 0x00, 0x16, 0x00, 0x06, 0x00, 0x10, 0x18, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x98, 0xFE, 0x00, 0x00]
  # - id: unknown35
  #   contents: [0x01, 0x04, 0x3F, 0x00, 0x00, 0x44,  0x05, 0x01]
  # - id: unk_len4
  #   type: u4
  # - id: unknown36
  #   type: unk_substream1
  #   size: unk_len4
  # - id: unknown40
  #   contents: [0x39, 0x05, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x00, 0x00, 0x00, 0x3A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00]
  # - id: unknown41
  #   contents: [0x5C, 0x11, 0x00, 0x00, 0x00, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x71, 0x17, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x03, 0x00, 0x00]
  # - id: unknown42
  #   contents: [0x72, 0x17, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x18, 0x27, 0x00, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00]
  # - id: unknown43
  #   contents: [0x19, 0x27, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x1A, 0x27, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00]
  # - id: unknown44
  #   contents: [0x7A, 0xFE, 0x01, 0x00, 0x00, 0x00, 0xBC, 0x03, 0x00, 0x00]
  # - id: unknown45
  #   type: unk_type1
  #   repeat: expr
  #   repeat-expr: unknown36.len_recent
  # - id: unknown50
  #   contents: [0x81, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x8C, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00]
  # - id: unknown51
  #   contents: [0x94, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x35, 0x01, 0x00, 0x00, 0x95, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x4F, 0x01, 0x00, 0x00]
  # - id: unknown52
  #   contents: [0x95, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00, 0x95, 0xFE, 0x02, 0x00, 0x00, 0x00, 0x79, 0x01, 0x00, 0x00]
  # - id: unknown53
  #   contents: [0x95, 0xFE, 0x03, 0x00, 0x00, 0x00, 0x8E, 0x01, 0x00, 0x00, 0x95, 0xFE, 0x04, 0x00, 0x00, 0x00, 0xA3, 0x01, 0x00, 0x00]
  # - id: unknown54
  #   contents: [0x95, 0xFE, 0x05, 0x00, 0x00, 0x00, 0xB8, 0x01, 0x00, 0x00, 0x95, 0xFE, 0x06, 0x00, 0x00, 0x00, 0xCD, 0x01, 0x00, 0x00]
  # - id: unknown55
  #   contents: [0x95, 0xFE, 0x07, 0x00, 0x00, 0x00, 0xE2, 0x01, 0x00, 0x00, 0x95, 0xFE, 0x08, 0x00, 0x00, 0x00, 0xF7, 0x01, 0x00, 0x00]
  # - id: unknown56
  #   contents: [0x95, 0xFE, 0x09, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x95, 0xFE, 0x0A, 0x00, 0x00, 0x00, 0x21, 0x02, 0x00, 0x00]
  # - id: unknown57
  #   contents: [0x95, 0xFE, 0x0B, 0x00, 0x00, 0x00, 0x36, 0x02, 0x00, 0x00, 0x95, 0xFE, 0x0D, 0x00, 0x00, 0x00, 0x4B, 0x02, 0x00, 0x00]
  # - id: unknown58
  #   contents: [0x95, 0xFE, 0x0E, 0x00, 0x00, 0x00, 0x60, 0x02, 0x00, 0x00, 0x95, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x75, 0x02, 0x00, 0x00]
  # - id: unknown59
  #   contents: [0x95, 0xFE, 0x10, 0x00, 0x00, 0x00, 0x8A, 0x02, 0x00, 0x00, 0x95, 0xFE, 0x11, 0x00, 0x00, 0x00, 0x9F, 0x02, 0x00, 0x00]
  # - id: unknown60
  #   contents: [0x95, 0xFE, 0x12, 0x00, 0x00, 0x00, 0xB4, 0x02, 0x00, 0x00, 0x95, 0xFE, 0x13, 0x00, 0x00, 0x00, 0xC9, 0x02, 0x00, 0x00]
  # - id: unknown61
  #   contents: [0x98, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x03, 0x00, 0x00]

types:
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
      - id: num_subitems
        type: u2
  xml_element:
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
      - id: num_subitems
        type: u2
      - id: subitems
        type: xml_element
        repeat: expr
        repeat-expr: num_subitems
        if: num_subitems != 0x8000
  xml_element_nosub:
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
      - id: num_subitems
        type: u2
  application_command:
    seq:
      - id: command_id
        type: u4
      - id: unknown3
        type: u1
      - id: unknown4
        type: u1
      - id: resource_id_label
        type: u4
      - id: unknown5
        type: u1
        if: (unknown3 & 2) != 0
      - id: resource_id_keytip
        type: u4
        if: (unknown3 & 2) != 0
  unk_substream1:
    doc: 'Related to <Application.Views> <Ribbon> <Ribbon.ApplicationMenu> <ApplicationMenu> <ApplicationMenu.RecentItems> <RecentItems MaxCount = X />'
    seq:
      - id: unknown2
        contents: [0x07, 0x00, 0x18, 0x01, 0x3E, 0x00, 0x00, 0x07, 0x00, 0x18, 0x01, 0x3E, 0x00, 0x00, 0x07, 0x00, 0x18, 0x01, 0x3E, 0x00]
      - id: unknown3
        contents: [0x00, 0x07, 0x00, 0x18, 0x01, 0x3E, 0x00, 0x00, 0x07, 0x00, 0x18, 0x01, 0x3E, 0x00, 0x00, 0x07, 0x00, 0x18, 0x01, 0x3E]
      - id: unknown4
        contents: [0x00, 0x00, 0x07, 0x00, 0x18, 0x01, 0x3E, 0x00, 0x00, 0x1F, 0x00, 0x18, 0x01, 0x3E, 0x01, 0x00, 0x16, 0x00, 0x18, 0x00]
      - id: unknown5
        contents: [0x10, 0x18, 0x00, 0x03, 0x01, 0x01, 0x41, 0x2B, 0x01, 0x01, 0x01, 0x00, 0x03, 0x72, 0x17, 0x18, 0x01, 0x3E, 0x00, 0x00]
      - id: unknown6
        size: 16
      - id: unknown7
        contents: [0x01, 0x0B, 0x04, 0x00, 0x01, 0x01, 0x41, 0x2B, 0x01, 0x01, 0x01, 0x00, 0x03, 0x71, 0x17, 0x18, 0x01, 0x3E ]
      - id: len_recent
        doc: 'Seems to be RecentItems MaxCount = X'
        type: u2
      - id: unknown_rest
        size-eos: true
  unk_type1:
    seq:
      - id: unknown1
        size: 10
