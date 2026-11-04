// Ported from spec/java/src/io/kaitai/struct/specwrite/TestSwitchManualIntSize.java

#include "helpers_write.h"
#include "switch_manual_int_size.h"

BOOST_AUTO_TEST_CASE(test_switch_manual_int_size_check_switch_bytes_size_mismatch) {
    std::unique_ptr<switch_manual_int_size_t::chunk_t> chunk(new switch_manual_int_size_t::chunk_t());
    chunk->set_code(0x33);
    chunk->set_size(3);
    // should cause the consistency check to fail because it's 2 bytes, not 3
    // (C++ keeps byte-array cases of a switch in `_raw_body`)
    chunk->set__raw_body(std::string("\x10\x20", 2));
    // Java: "Check failed: body, expected: 3, actual: 2". C++ reports the
    // member that holds the bytes, `raw(body)`.
    BOOST_CHECK_EXCEPTION(chunk->_check(), kaitai::consistency_error,
        [](const kaitai::consistency_error& e) {
            return std::string(e.what()) == "check failed: raw(body): expected 3, actual 2";
        });
}

BOOST_AUTO_TEST_CASE(test_switch_manual_int_size_read_write_roundtrip) {
    ks_write_test::roundtrip<switch_manual_int_size_t>("switch_tlv.bin");
}
