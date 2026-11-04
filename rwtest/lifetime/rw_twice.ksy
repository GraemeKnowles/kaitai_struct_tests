meta:
  id: rw_twice
  endian: le
seq:
  - id: len
    type: u1
  - id: body
    size: 4
    type: inner
  - id: items
    size: 2
    type: item
    repeat: expr
    repeat-expr: 2
instances:
  tail:
    io: body._io
    pos: 3
    type: u1
types:
  inner:
    seq:
      - id: a
        type: u2
    instances:
      b:
        pos: 2
        type: u2
  item:
    seq:
      - id: x
        type: u1
    instances:
      y:
        pos: 1
        type: u1
