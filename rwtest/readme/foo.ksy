meta:
  id: foo
  endian: le
seq:
  - id: version
    type: u1
  - id: len_header
    type: u1
  - id: header
    size: len_header
    type: header
types:
  header:
    seq:
      - id: magic
        size: 3
