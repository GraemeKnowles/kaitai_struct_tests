// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestBytesPadTerm.java

#include "helpers_write.h"
#include "bytes_pad_term.h"


BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_max_lengths) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_min_lengths) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string(""));
    r->set_str_term(std::string(""));
    r->set_str_term_and_pad(std::string(""));
    r->set_str_term_include(std::string("@"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_longer_str_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_pad");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_last_byte_str_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("@@@@@@@@@@@@@@@@@@@?"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_last_byte_str_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("123456789012345678@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_pad");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_longer_str_term) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_has_terminator1_str_term) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("123456789012@4567890"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_has_terminator2_str_term) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("1234567890123456789@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_longer_str_term_and_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_and_pad");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_has_terminator_str_term_and_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("@2345678901234567890"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_and_pad");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_last_byte1_str_term_and_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("+++++++++++++++++++"));
    r->set_str_term_include(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_last_byte2_str_term_and_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("+++++++++++++++++++0"));
    r->set_str_term_include(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_last_byte_str_term_and_pad) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("1234567890123456789+"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_and_pad");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_longer_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_empty_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string(""));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_bad_no_terminator_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("123"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_terminator1_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("12@"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_early_terminator1_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("1@@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_good_terminator2_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("1234567890123456789@"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_check_early_terminator2_str_term_include) {
    std::auto_ptr<bytes_pad_term_t> r(new bytes_pad_term_t());
    r->set_str_pad(std::string("12345678901234567890"));
    r->set_str_term(std::string("12345678901234567890"));
    r->set_str_term_and_pad(std::string("12345678901234567890"));
    r->set_str_term_include(std::string("123456789012345678@@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}
BOOST_AUTO_TEST_CASE(test_bytes_pad_term_read_write_roundtrip) {
    ks_write_test::roundtrip<bytes_pad_term_t>("str_pad_term.bin");
}
