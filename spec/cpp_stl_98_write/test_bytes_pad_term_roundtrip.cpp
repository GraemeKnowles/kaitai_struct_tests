// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestBytesPadTermRoundtrip.java

#include "helpers_write.h"
#include "bytes_pad_term_roundtrip.h"

// NOTE: here it makes sense to prefer a manual test over the automatic
// roundtrip, because the roundtrip can't always recognize whether the
// `pad-right` is correct (i.e. whether the serialized field is padded correctly)
BOOST_AUTO_TEST_CASE(test_bytes_pad_term_roundtrip) {
    std::auto_ptr<bytes_pad_term_roundtrip_t> r(new bytes_pad_term_roundtrip_t());
    r->set_str_pad(std::string("str1"));
    r->set_str_term(std::string("str2foo"));
    r->set_str_term_and_pad(std::string("str+++3bar+++"));
    r->set_str_term_include(std::string("str4baz@"));
    ks_write_test::assert_equal_to_full_file(r.get(), "str_pad_term.bin");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_roundtrip_read_write_roundtrip) {
    ks_write_test::roundtrip<bytes_pad_term_roundtrip_t>("str_pad_term.bin");
}
