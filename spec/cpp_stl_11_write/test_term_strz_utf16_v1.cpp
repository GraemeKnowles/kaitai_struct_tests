// Multi-byte (UTF-16) terminators: not supported by the Java read-write target,
// so there is no Java counterpart of this test.
#include "helpers_write.h"
#include "term_strz_utf16_v1.h"

using namespace ks_write_test;

// "aȀb", "cȀd", "eȀf" (U+0200)
static const std::string S1("a\xc8\x80" "b");
static const std::string S2("c\xc8\x80" "d");
static const std::string S3_INCL("e\xc8\x80" "f\0", 5);

BOOST_AUTO_TEST_CASE(test_term_strz_utf16_v1_from_scratch) {
    std::unique_ptr<term_strz_utf16_v1_t> r(new term_strz_utf16_v1_t());
    r->set_s1(S1);
    r->set_s2(S2);
    r->set_term(0);
    r->set_s3(S3_INCL);
    assert_equal_to_full_file(r.get(), "term_strz_utf16.bin");
}

BOOST_AUTO_TEST_CASE(test_term_strz_utf16_v1_check_contains_terminator) {
    std::unique_ptr<term_strz_utf16_v1_t> r(new term_strz_utf16_v1_t());
    r->set_s1(std::string("a\0b", 3)); // UTF-16LE: 61 00 [00 00] 62 00
    r->set_s2(S2);
    r->set_term(0);
    r->set_s3(S3_INCL);
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s1");
}

BOOST_AUTO_TEST_CASE(test_term_strz_utf16_v1_check_include_without_terminator) {
    std::unique_ptr<term_strz_utf16_v1_t> r(new term_strz_utf16_v1_t());
    r->set_s1(S1);
    r->set_s2(S2);
    r->set_term(0);
    r->set_s3(std::string("e\xc8\x80" "f"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "s3");
}
