// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestProcessToUser.java

#include "helpers_write.h"
#include "process_to_user.h"

BOOST_AUTO_TEST_CASE(test_process_to_user) {
    // NOTE: unlike the automatic roundtrip test, the `_raw_*` fields are not set in this
    // manual test, so "cheating" by just writing them is impossible
    std::auto_ptr<process_to_user_t> r(new process_to_user_t());
    std::auto_ptr<process_to_user_t::just_str_t> buf1(new process_to_user_t::just_str_t(0, r.get(), r->_root()));
    buf1->set_str(std::string("Hello"));
    buf1->_check();
    r->set_buf1(buf1.release());
    r->_check();

    std::string expected = ks_write_test::read_file("src/process_rotate.bin").substr(0, 5);
    BOOST_CHECK_EQUAL(ks_write_test::to_hex(ks_write_test::write_to_buffer(r.get(), expected.size())), ks_write_test::to_hex(expected));
}

BOOST_AUTO_TEST_CASE(test_process_to_user_read_write_roundtrip) {
    ks_write_test::roundtrip<process_to_user_t>("process_rotate.bin");
}
