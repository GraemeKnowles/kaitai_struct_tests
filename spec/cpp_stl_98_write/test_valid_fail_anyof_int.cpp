// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestValidFailAnyofInt.java

#include "helpers_write.h"
#include "valid_fail_anyof_int.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

// NB: the error message must not contain the "at pos X: " part because
// _check() is not supposed to access `_io` at all (even if it happens
// to be set, as in the "old io" case)
static void assert_check_valid_fail(valid_fail_anyof_int_t* r) {
    BOOST_CHECK_EXCEPTION(r->_check(), kaitai::validation_not_any_of_error<uint8_t>,
        [](const kaitai::validation_not_any_of_error<uint8_t>& e) { return std::string(e.what()) == "/seq/0: validation failed: not any of the list"; });
}

BOOST_AUTO_TEST_CASE(test_valid_fail_anyof_int_check_bad_valid_no_io) {
    std::auto_ptr<valid_fail_anyof_int_t> r(new valid_fail_anyof_int_t());
    r->set_foo(0x50);
    assert_check_valid_fail(r.get());
}

BOOST_AUTO_TEST_CASE(test_valid_fail_anyof_int_check_bad_valid_old_io) {
    std::ifstream ifs("src/fixed_struct.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::auto_ptr<valid_fail_anyof_int_t> r(new valid_fail_anyof_int_t(&ks));
    BOOST_CHECK_THROW(r->_read(), kaitai::validation_not_any_of_error<uint8_t>);
    assert_check_valid_fail(r.get());
}
