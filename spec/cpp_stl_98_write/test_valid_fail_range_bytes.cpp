// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestValidFailRangeBytes.java

#include "helpers_write.h"
#include "valid_fail_range_bytes.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

// NB: the error message must not contain the "at pos X: " part because
// _check() is not supposed to access `_io` at all (even if it happens
// to be set, as in the "old io" case)
static void assert_check_valid_fail(valid_fail_range_bytes_t* r) {
    BOOST_CHECK_EXCEPTION(r->_check(), kaitai::validation_greater_than_error<std::string>,
        [](const kaitai::validation_greater_than_error<std::string>& e) { return std::string(e.what()) == "/seq/0: validation failed: not in range"; });
}

BOOST_AUTO_TEST_CASE(test_valid_fail_range_bytes_check_bad_valid_no_io) {
    std::auto_ptr<valid_fail_range_bytes_t> r(new valid_fail_range_bytes_t());
    r->set_foo(std::string("\x50\x41", 2));
    assert_check_valid_fail(r.get());
}

BOOST_AUTO_TEST_CASE(test_valid_fail_range_bytes_check_bad_valid_old_io) {
    std::ifstream ifs("src/fixed_struct.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::auto_ptr<valid_fail_range_bytes_t> r(new valid_fail_range_bytes_t(&ks));
    BOOST_CHECK_THROW(r->_read(), kaitai::validation_greater_than_error<std::string>);
    assert_check_valid_fail(r.get());
}
