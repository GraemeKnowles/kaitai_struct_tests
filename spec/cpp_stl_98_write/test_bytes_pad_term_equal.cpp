// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestBytesPadTermEqual.java

#include "helpers_write.h"
#include "bytes_pad_term_equal.h"


BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_max_lengths) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_min_lengths) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string(""));
    r->set_s2(std::string(""));
    r->set_s3(std::string(""));
    r->set_s4(std::string("."));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_longer_s1) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s1");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_has_terminator1_s1) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("123456789012@4567890"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s1");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_has_terminator2_s1) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("1234567890123456789@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s1");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_longer_s2) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s2");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_terminator1_s2) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("123456789012345678@"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_early_terminator1_s2) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("1234567890123456@8@"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s2");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_last_byte_s2) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("++++++++++++++++++9"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("12345678901234567890"));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_last_byte_s2) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("123456789012345678+"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s2");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_longer_s3) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s3");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_has_terminator1_s3) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("1234567890123456789+"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s3");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_has_terminator2_s3) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567+9"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s3");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_longer_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("123456789012345678901"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s4");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_empty_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string(""));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s4");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_bad_no_terminator_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("1234567890123456789"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s4");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_terminator1_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("123456789012345678."));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_early_terminator1_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string(".23456789012345678."));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s4");
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_good_terminator2_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("1234567890123456789."));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_check_early_terminator2_s4) {
    std::auto_ptr<bytes_pad_term_equal_t> r(new bytes_pad_term_equal_t());
    r->set_s1(std::string("12345678901234567890"));
    r->set_s2(std::string("12345678901234567890"));
    r->set_s3(std::string("12345678901234567890"));
    r->set_s4(std::string("123456789012345678.."));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s4");
}
BOOST_AUTO_TEST_CASE(test_bytes_pad_term_equal_read_write_roundtrip) {
    ks_write_test::roundtrip<bytes_pad_term_equal_t>("str_pad_term.bin");
}
