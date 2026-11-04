// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestStrEncodings.java

#include "helpers_write.h"
#include "str_encodings.h"

// testCheckNull is not ported: Java expects a NullPointerException for the
// unset `str2`; in C++ unset strings are just empty (checked below instead).
BOOST_AUTO_TEST_CASE(test_str_encodings_check_unset) {
    std::auto_ptr<str_encodings_t> r(new str_encodings_t());
    r->set_str1(std::string("woo"));
    r->set_len_of_1(3);
    r->set_len_of_2(15);
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str2");
}

BOOST_AUTO_TEST_CASE(test_str_encodings_check_mismatch) {
    std::auto_ptr<str_encodings_t> r(new str_encodings_t());
    r->set_str1(std::string("Some ASCII"));
    r->set_str2(std::string("\xe3\x81\x93\xe3\x82\x93\xe3\x81\xab\xe3\x81\xa1\xe3\x81\xaf")); // こんにちは
    r->set_str3(std::string("\xe3\x81\x93\xe3\x82\x93\xe3\x81\xab\xe3\x81\xa1\xe3\x81\xaf")); // こんにちは
    r->set_str4(std::string("\xe2\x96\x91\xe2\x96\x92\xe2\x96\x93")); // ░▒▓

    // To be auto-derived
    r->set_len_of_1(10);
    r->set_len_of_2(12); // should be 15
    r->set_len_of_3(10);
    r->set_len_of_4(3);

    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str2");
}

BOOST_AUTO_TEST_CASE(test_str_encodings_read_write_roundtrip) {
    ks_write_test::roundtrip<str_encodings_t>("str_encodings.bin");
}
