// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestValidFailExpr.java

#include "helpers_write.h"
#include "valid_fail_expr.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

// NB: the error message must not contain the "at pos X: " part because
// _check() is not supposed to access `_io` at all (even if it happens
// to be set, as in the "old io" case)
static void assert_check_valid_fail(valid_fail_expr_t* r) {
    BOOST_CHECK_EXCEPTION(r->_check(), kaitai::validation_expr_error<int16_t>,
        [](const kaitai::validation_expr_error<int16_t>& e) { return std::string(e.what()) == "/seq/1: validation failed: not matching the expression"; });
}

BOOST_AUTO_TEST_CASE(test_valid_fail_expr_check_bad_valid_no_io) {
    std::auto_ptr<valid_fail_expr_t> r(new valid_fail_expr_t());
    r->set_foo(1);
    r->set_bar(-190);
    assert_check_valid_fail(r.get());
}

BOOST_AUTO_TEST_CASE(test_valid_fail_expr_check_bad_valid_old_io) {
    std::ifstream ifs("src/nav_parent_switch.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::auto_ptr<valid_fail_expr_t> r(new valid_fail_expr_t(&ks));
    BOOST_CHECK_THROW(r->_read(), kaitai::validation_expr_error<int16_t>);
    assert_check_valid_fail(r.get());
}
