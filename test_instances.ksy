meta:
  id: test
  endian: le

seq:
- id: unk1
  type: u1
- id: sub1
  type: type_t1
- id: unk2
  type: u1

types:
  type_t1:
    seq:
    - id: unk1
      type: u1
    - id: pos1
      type: u2
    instances:
      i1:
        io: _root._io
        type: type_t2
        pos: pos1

  type_t2:
    seq:
    - id: unk1
      type: u1
    - id: sub2
      type: type_t3
    - id: unk2
      type: u1

  type_t3:
    seq:
    - id: unk1
      type: u1
    - id: pos1
      type: u2
    instances:
      i2:
        io: _root._io
        pos: pos1
        type: type_t4

  type_t4:
    seq:
    - id: unk1
      type: u1
    - id: unk2
      type: u1 
