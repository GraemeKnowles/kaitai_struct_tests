// Ported from spec/java/src/io/kaitai/struct/specwrite/TestBytesEosPadTerm.java

#include "helpers_write.h"
#include "bytes_eos_pad_term.h"

// Java: BytesEosPadTerm.setStrPad() etc. helpers
static void set_str_pad(bytes_eos_pad_term_t* r, const std::string& value) {
    std::unique_ptr<bytes_eos_pad_term_t::str_pad_type_t> s(new bytes_eos_pad_term_t::str_pad_type_t(nullptr, r, r->_root()));
    s->set_value(value);
    s->_check();
    r->set_str_pad(std::move(s));
}

static void set_str_term(bytes_eos_pad_term_t* r, const std::string& value) {
    std::unique_ptr<bytes_eos_pad_term_t::str_term_type_t> s(new bytes_eos_pad_term_t::str_term_type_t(nullptr, r, r->_root()));
    s->set_value(value);
    s->_check();
    r->set_str_term(std::move(s));
}

static void set_str_term_and_pad(bytes_eos_pad_term_t* r, const std::string& value) {
    std::unique_ptr<bytes_eos_pad_term_t::str_term_and_pad_type_t> s(new bytes_eos_pad_term_t::str_term_and_pad_type_t(nullptr, r, r->_root()));
    s->set_value(value);
    s->_check();
    r->set_str_term_and_pad(std::move(s));
}

static void set_str_term_include(bytes_eos_pad_term_t* r, const std::string& value) {
    std::unique_ptr<bytes_eos_pad_term_t::str_term_include_type_t> s(new bytes_eos_pad_term_t::str_term_include_type_t(nullptr, r, r->_root()));
    s->set_value(value);
    s->_check();
    r->set_str_term_include(std::move(s));
}

static void check(bytes_eos_pad_term_t* r) {
    const std::string buf("12345678901234567890");
    if (r->str_pad() == nullptr)
        set_str_pad(r, buf);
    if (r->str_term() == nullptr)
        set_str_term(r, buf);
    if (r->str_term_and_pad() == nullptr)
        set_str_term_and_pad(r, buf);
    if (r->str_term_include() == nullptr)
        set_str_term_include(r, buf);
    r->_check();
    kaitai::kstream io(std::string(80, '\0'));
    r->_write(&io);
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_max_lengths) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("12345678901234567890"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_min_lengths) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string(""));
    set_str_term(r.get(), std::string(""));
    set_str_term_and_pad(r.get(), std::string(""));
    set_str_term_include(r.get(), std::string("@"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_longer_str_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("123456789012345678901"));
    BOOST_CHECK_THROW(check(r.get()), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_last_byte_str_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("@@@@@@@@@@@@@@@@@@@?"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("12345678901234567890"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_last_byte_str_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("123456789012345678@"));
    // Java expects "str_pad"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_longer_str_term) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("123456789012345678901"));
    BOOST_CHECK_THROW(check(r.get()), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_has_terminator1_str_term) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    // Java expects "str_term"; the check runs in the inner type, whose field is `value`
    // the terminator check is in _check(), which set_*() already calls
    KS_CHECK_CONSISTENCY_ERROR({ set_str_term(r.get(), std::string("123456789012@4567890")); check(r.get()); }, "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_has_terminator2_str_term) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    // Java expects "str_term"; the check runs in the inner type, whose field is `value`
    // the terminator check is in _check(), which set_*() already calls
    KS_CHECK_CONSISTENCY_ERROR({ set_str_term(r.get(), std::string("1234567890123456789@")); check(r.get()); }, "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_longer_str_term_and_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("123456789012345678901"));
    BOOST_CHECK_THROW(check(r.get()), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_has_terminator_str_term_and_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    // Java expects "str_term_and_pad"; the check runs in the inner type, whose field is `value`
    // the terminator check is in _check(), which set_*() already calls
    KS_CHECK_CONSISTENCY_ERROR({ set_str_term_and_pad(r.get(), std::string("@2345678901234567890")); check(r.get()); }, "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_last_byte1_str_term_and_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("+++++++++++++++++++"));
    set_str_term_include(r.get(), std::string("12345678901234567890"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_last_byte2_str_term_and_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("+++++++++++++++++++0"));
    set_str_term_include(r.get(), std::string("12345678901234567890"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_last_byte_str_term_and_pad) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("1234567890123456789+"));
    // Java expects "str_term_and_pad"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_longer_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("123456789012345678901"));
    BOOST_CHECK_THROW(check(r.get()), std::ios_base::failure);
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_empty_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string(""));
    // Java expects "str_term_include"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_bad_no_terminator_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("123"));
    // Java expects "str_term_include"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_terminator1_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("12@"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_early_terminator1_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("1@@"));
    // Java expects "str_term_include"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_good_terminator2_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("1234567890123456789@"));
    check(r.get());
}

BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_check_early_terminator2_str_term_include) {
    std::unique_ptr<bytes_eos_pad_term_t> r(new bytes_eos_pad_term_t());
    set_str_pad(r.get(), std::string("12345678901234567890"));
    set_str_term(r.get(), std::string("12345678901234567890"));
    set_str_term_and_pad(r.get(), std::string("12345678901234567890"));
    set_str_term_include(r.get(), std::string("123456789012345678@@"));
    // Java expects "str_term_include"; the check runs in the inner type, whose field is `value`
    KS_CHECK_CONSISTENCY_ERROR(check(r.get()), "value");
}
BOOST_AUTO_TEST_CASE(test_bytes_eos_pad_term_read_write_roundtrip) {
    ks_write_test::roundtrip<bytes_eos_pad_term_t>("str_pad_term.bin");
}
