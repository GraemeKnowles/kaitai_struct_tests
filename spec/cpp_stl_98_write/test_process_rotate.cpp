// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestProcessRotate.java

#include "helpers_write.h"
#include "process_rotate.h"

BOOST_AUTO_TEST_CASE(test_process_rotate) {
    // NOTE: unlike the automatic roundtrip test, the `_raw_*` fields are not set in this
    // manual test, so "cheating" by just writing them is impossible
    std::auto_ptr<process_rotate_t> r(new process_rotate_t());
    r->set_buf1(std::string("Hello"));
    r->set_buf2(std::string("World"));
    r->set_key(1);
    r->set_buf3(std::string("There"));
    ks_write_test::assert_equal_to_full_file(r.get(), "process_rotate.bin");
}

BOOST_AUTO_TEST_CASE(test_process_rotate_check_size_mismatch_check) {
    std::auto_ptr<process_rotate_t> r(new process_rotate_t());
    r->set_buf1(std::string("Hello"));
    r->set_buf2(std::string("Way too long"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "buf2");
}

// Java: the size mismatch of `buf2` may be caught either in _check() or in _write()
BOOST_AUTO_TEST_CASE(test_process_rotate_check_size_mismatch_check_or_write) {
    std::auto_ptr<process_rotate_t> r(new process_rotate_t());
    r->set_buf1(std::string("Hello"));
    r->set_buf2(std::string("Way too long"));
    r->set_key(1);
    r->set_buf3(std::string("There"));
    KS_CHECK_CONSISTENCY_ERROR(
        {
            r->_check();
            kaitai::kstream io(std::string(5 + 5 + 1 + 5, '\0'));
            r->_write(&io);
        },
        "buf2"
    );
}

BOOST_AUTO_TEST_CASE(test_process_rotate_read_write_roundtrip) {
    ks_write_test::roundtrip<process_rotate_t>("process_rotate.bin");
}
