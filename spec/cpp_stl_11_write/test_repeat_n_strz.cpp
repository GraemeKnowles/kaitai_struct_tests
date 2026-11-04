// Ported from spec/java/src/io/kaitai/struct/specwrite/TestRepeatNStrz.java

#include "helpers_write.h"
#include "repeat_n_strz.h"

BOOST_AUTO_TEST_CASE(test_repeat_n_strz_check_mismatch) {
    std::unique_ptr<repeat_n_strz_t> r(new repeat_n_strz_t());
    r->set_qty(7);
    std::unique_ptr<std::vector<std::string>> lines(new std::vector<std::string>());
    lines->push_back("foo");
    lines->push_back("bar");
    r->set_lines(std::move(lines));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "lines");
}

// testCheckNull is not ported: Java expects a NullPointerException mentioning
// `lines` when it is unset; in C++, _check() would dereference a null
// std::unique_ptr (undefined behavior), so there is nothing safe to test.

BOOST_AUTO_TEST_CASE(test_repeat_n_strz_read_write_roundtrip) {
    ks_write_test::roundtrip<repeat_n_strz_t>("repeat_n_strz.bin");
}
