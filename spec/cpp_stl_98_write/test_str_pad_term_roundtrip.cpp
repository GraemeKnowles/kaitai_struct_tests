// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestStrPadTermRoundtrip.java

#include "helpers_write.h"
#include "str_pad_term_roundtrip.h"

BOOST_AUTO_TEST_CASE(test_str_pad_term_roundtrip) {
    std::auto_ptr<str_pad_term_roundtrip_t> r(new str_pad_term_roundtrip_t());
    r->set_str_pad(std::string("str1"));
    r->set_str_term(std::string("str2foo"));
    r->set_str_term_and_pad(std::string("str+++3bar+++"));
    r->set_str_term_include(std::string("str4baz@"));
    ks_write_test::assert_equal_to_full_file(r.get(), "str_pad_term.bin");
}

BOOST_AUTO_TEST_CASE(test_str_pad_term_roundtrip_read_write_roundtrip) {
    ks_write_test::roundtrip<str_pad_term_roundtrip_t>("str_pad_term.bin");
}
