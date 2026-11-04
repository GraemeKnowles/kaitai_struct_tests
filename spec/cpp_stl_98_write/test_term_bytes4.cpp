// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestTermBytes4.java

#include "helpers_write.h"
#include "term_bytes4.h"

BOOST_AUTO_TEST_CASE(test_term_bytes4_check_is_eof_after_include_term_missing) {
    std::auto_ptr<term_bytes4_t> r(new term_bytes4_t());

    std::auto_ptr<term_bytes4_t::s1_type_t> s1(new term_bytes4_t::s1_type_t(0, r.get(), r->_root()));
    s1->set_value(std::string("foo"));
    s1->_check();
    r->set_s1(s1.release());

    r->set_skip_term1(0x7c);

    std::auto_ptr<term_bytes4_t::s2_type_t> s2(new term_bytes4_t::s2_type_t(0, r.get(), r->_root()));
    s2->set_value(std::string("bar"));
    s2->_check();
    r->set_s2(s2.release());

    r->set_skip_term2(0x7c);

    std::auto_ptr<term_bytes4_t::s3_type_t> s3(new term_bytes4_t::s3_type_t(0, r.get(), r->_root()));
    // this field with `include: true` and `eos-error: false` does not end with the terminator,
    // but there is 1 byte left in the stream => consistency error
    s3->set_value(std::string("ba"));
    s3->_check();
    r->set_s3(s3.release());

    r->_check();

    // Java: "Check failed: value, expected: 0, actual: 1"
    KS_CHECK_CONSISTENCY_ERROR_MSG(
        {
            kaitai::kstream io(std::string(3 + 1 + 3 + 1 + 3, '\0'));
            r->_write(&io);
        },
        "check failed: value: expected end of stream, 1 bytes left"
    );
}

BOOST_AUTO_TEST_CASE(test_term_bytes4_read_write_roundtrip) {
    ks_write_test::roundtrip<term_bytes4_t>("term_strz.bin");
}
