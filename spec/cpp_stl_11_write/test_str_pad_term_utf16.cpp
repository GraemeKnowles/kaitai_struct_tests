// Multi-byte (UTF-16) terminators in fixed-size fields: not supported by the
// Java read-write target, so there is no Java counterpart of this test.
#include "helpers_write.h"
#include "str_pad_term_utf16.h"

using namespace ks_write_test;

BOOST_AUTO_TEST_CASE(test_str_pad_term_utf16_from_scratch) {
    std::unique_ptr<str_pad_term_utf16_t> r(new str_pad_term_utf16_t());
    r->set_str_term(std::string("a\xc8\x80" "b"));
    r->set_str_term_include(std::string("c\xc8\x80" "d\0", 5));
    r->set_str_term_and_pad(std::string("e\xc8\x80" "f"));
    r->_check();
    // the original file has junk after the terminators, so compare what is
    // read back instead of the bytes
    std::string out = write_to_buffer(r.get(), 29);
    BOOST_CHECK_EQUAL(to_hex(out),
        "61 00 00 02 62 00 00 00 00 00 "
        "63 00 00 02 64 00 00 00 00 00 "
        "65 00 00 02 66 00 00 00 2b");
    kaitai::kstream ks(out);
    str_pad_term_utf16_t r2(&ks);
    r2._read();
    BOOST_CHECK_EQUAL(r2.str_term(), r->str_term());
    BOOST_CHECK_EQUAL(r2.str_term_include(), r->str_term_include());
    BOOST_CHECK_EQUAL(r2.str_term_and_pad(), r->str_term_and_pad());
}

BOOST_AUTO_TEST_CASE(test_str_pad_term_utf16_check_include_shorter_without_terminator) {
    std::unique_ptr<str_pad_term_utf16_t> r(new str_pad_term_utf16_t());
    r->set_str_term(std::string("a"));
    r->set_str_term_include(std::string("c\xc8\x80" "d")); // shorter than 10 bytes, no terminator
    r->set_str_term_and_pad(std::string("e"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_include");
}

BOOST_AUTO_TEST_CASE(test_str_pad_term_utf16_check_last_byte_is_pad) {
    std::unique_ptr<str_pad_term_utf16_t> r(new str_pad_term_utf16_t());
    r->set_str_term(std::string("a"));
    r->set_str_term_include(std::string("c\0", 2));
    // 8 bytes, no room for the terminator in 9, and the last byte (U+2B00 ->
    // 00 2b) would be stripped as padding
    r->set_str_term_and_pad(std::string("abc\xe2\xac\x80"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "str_term_and_pad");
}

BOOST_AUTO_TEST_CASE(test_str_pad_term_utf16_no_room_for_terminator) {
    std::unique_ptr<str_pad_term_utf16_t> r(new str_pad_term_utf16_t());
    r->set_str_term(std::string("a"));
    r->set_str_term_include(std::string("c\0", 2));
    r->set_str_term_and_pad(std::string("abcd")); // 8 bytes: only padding fits
    r->_check();
    std::string out = write_to_buffer(r.get(), 29);
    BOOST_CHECK_EQUAL(to_hex(out.substr(20)), "61 00 62 00 63 00 64 00 2b");
    kaitai::kstream ks(out);
    str_pad_term_utf16_t r2(&ks);
    r2._read();
    BOOST_CHECK_EQUAL(r2.str_term_and_pad(), std::string("abcd"));
}
