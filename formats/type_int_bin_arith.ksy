meta:
  id: type_int_bin_arith
  endian: le
  bit-endian: le
seq:
  - id: s1_val
    type: s1
  - id: s2_val
    type: s2
  - id: s4_val
    type: s4
  - id: s8_val
    type: s8

  - id: u1_val
    type: u1
  - id: u2_val
    type: u2
  - id: u4_val_msb_set
    type: u4
  - id: u4_val_msb_clear
    type: u4
  - id: u8_val_msb_set
    type: u8
  - id: u8_val_msb_clear
    type: u8

  - id: b08_val
    type: b8
  - id: b16_val
    type: b16
  - id: b32_val
    type: b32
  - id: b64_val
    type: b64
  - id: b31_val
    type: b31
  - id: b63_val
    type: b63
instances:
  # Mixing operand types: types narrower than 32 bits are promoted to `s4`,
  # except that `u1` and `u2` are promoted to `u4` when combined with `u4`,
  # and to `u8` when combined with `u8`. The narrower operand is then
  # converted to the type of the wider one. An integer literal takes the
  # type of the other operand if its value fits into it.
  add_u4_u4:
    # The operands fit into `s4`, but the result only fits into `u4`, which is
    # the result type
    value: u4_val_msb_clear + u4_val_msb_clear
  add_u4_u1:
    # `u1_val` is promoted to `u4`, not to `s4` (which couldn't be mixed with
    # `u4`)
    value: u4_val_msb_set + u1_val
  sub_u4_u1:
    # `u1_val` is promoted to `u4`, and the result has the most significant
    # bit set
    value: u4_val_msb_set - u1_val
  add_u8_u8:
    # The operands fit into `s8`, but the result only fits into `u8`, which is
    # the result type
    value: u8_val_msb_clear + u8_val_msb_clear
  add_u8_u2:
    # `u2_val` is promoted to `u8`
    value: u8_val_msb_set + u2_val
  add_u8_lit:
    # The literal takes the type of the other operand (`u8`), and the result
    # (`2**63`) doesn't fit into `s8`
    value: u8_val_msb_clear + 3
  sub_u8_lit:
    # The literal takes the type of the other operand (`u8`)
    value: u8_val_msb_set - 1
  add_lit_u4:
    # The literal is on the left, and it takes the type of the other operand
    # (`u4`)
    value: 1 + u4_val_msb_set
  sub_lit_u8:
    # The literal is on the left, and its value only fits into `u8`
    value: 0xffff_ffff_ffff_ffff - u8_val_msb_set
  add_u4_lit_s8:
    # The literal doesn't fit into `u4`, so it keeps its own type `s8`, which
    # is also the result type
    value: u4_val_msb_set + 0x1_0000_0000
  add_s8_s4:
    # `s4_val` must stay negative when converted to `s8`
    value: s8_val + s4_val
  sub_s8_u4:
    # `u4_val_msb_set` must stay positive when converted to `s8`
    value: s8_val - u4_val_msb_set
  add_u1_u1:
    # The result type is `s4`, so the result (506) doesn't have to fit into
    # `u1`
    value: u1_val + u1_val
  mul_s1_s2:
    # The result type is `s4`, so the result (4194304) doesn't have to fit
    # into `s2`
    value: s1_val * s2_val

  # Multiplication, division and modulo: the dividends of `/` and `%` are
  # deliberately not divisible by the divisors, because an exact division
  # could give the right result even with a wrong implementation (e.g. one
  # that divides via floats). Most unsigned dividends have the most
  # significant bit set, which would make them negative if they were
  # treated as signed.
  mul_u4_lit:
    # The operands fit into `s4`, but the result only fits into `u4`, which is
    # the result type
    value: u4_val_msb_clear * 2
  mul_u8_lit:
    # The operands fit into `s8`, but the result only fits into `u8`, which is
    # the result type
    value: u8_val_msb_clear * 2
  mul_s8_lit:
    # The result type is `s8`, and the result is negative
    value: s8_val * 3
  div_u4_lit:
    value: u4_val_msb_set / 7
  div_u8_msb_set_lit:
    value: u8_val_msb_set / 7
  div_u8_msb_clear_lit:
    # The dividend doesn't have the most significant bit set, so a signed
    # division gives the right result, but a division via floats doesn't:
    # the result is too large to be represented exactly as a `double`
    value: u8_val_msb_clear / 7
  mod_u4_lit:
    value: u4_val_msb_set % 10
  mod_u8_msb_set_lit:
    value: u8_val_msb_set % 7
  mod_u8_msb_clear_lit:
    # The dividend doesn't have the most significant bit set, so a signed
    # modulo gives the right result, but a modulo via floats doesn't: the
    # quotient is too large to be represented exactly as a `double`
    value: u8_val_msb_clear % 7
  mod_s8_lit:
    # The dividend is negative, but the result is non-negative (in `0..999`),
    # unlike `%` in C
    value: s8_val % 1000

  # Bit-sized integers: in expressions, `b1`..`b31` follow the same rules as
  # `u1` and `u2` (see above), because all their values fit into `s4`.
  # `b32` follows the rules of `u4`, and `b33`..`b64` those of `u8`. Most
  # cases use the widths at these boundaries (`b31`/`b32`, `b63`/`b64`).
  add_b31_u4:
    # The operands fit into `s4`, but the result only fits into `u4`, which is
    # the result type
    value: b31_val + u4_val_msb_clear
  add_b32_u1:
    # `u1_val` is promoted to `u4`
    value: b32_val + u1_val
  sub_u4_b16:
    # `b16_val` is promoted to `u4`
    value: u4_val_msb_set - b16_val
  add_s8_b08:
    # `b08_val` is promoted to `s8`
    value: s8_val + b08_val
  add_s4_b31:
    # `b31_val` is promoted to `s4` (every `b31` value fits into it), so it can
    # be mixed with a signed operand
    value: s4_val + b31_val
  add_b64_lit:
    # The operands fit into `s8`, but the result (`2**63`) only fits into
    # `u8`, which is the result type
    value: b64_val + 3
  add_b63_lit:
    # `b63_val` is promoted to `u8`, so the result (`2**63`) isn't limited to
    # 63 bits
    value: b63_val + 4
