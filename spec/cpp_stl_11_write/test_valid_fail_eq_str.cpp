// Ported from spec/java/src/io/kaitai/struct/specwrite/TestValidFailEqStr.java

#include "helpers_write.h"
#include "valid_fail_eq_str.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

// NB: the error message must not contain the "at pos X: " part because
// _check() is not supposed to access `_io` at all (even if it happens
// to be set, as in the "old io" case)
static void assert_check_valid_fail(valid_fail_eq_str_t* r) {
    BOOST_CHECK_EXCEPTION(r->_check(), kaitai::validation_not_equal_error<std::string>,
        [](const kaitai::validation_not_equal_error<std::string>& e) { return std::string(e.what()) == "/seq/0: validation failed: not equal"; });
}

BOOST_AUTO_TEST_CASE(test_valid_fail_eq_str_check_bad_valid_no_io) {
    std::unique_ptr<valid_fail_eq_str_t> r(new valid_fail_eq_str_t());
    r->set_foo(std::string("PACK"));
    assert_check_valid_fail(r.get());
}

BOOST_AUTO_TEST_CASE(test_valid_fail_eq_str_check_bad_valid_old_io) {
    std::ifstream ifs("src/fixed_struct.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::unique_ptr<valid_fail_eq_str_t> r(new valid_fail_eq_str_t(&ks));
    BOOST_CHECK_THROW(r->_read(), kaitai::validation_not_equal_error<std::string>);
    assert_check_valid_fail(r.get());
}
