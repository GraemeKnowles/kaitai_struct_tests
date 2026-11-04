// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestInstanceStd.java

#include "helpers_write.h"
#include "instance_std.h"

BOOST_AUTO_TEST_CASE(test_instance_std_check_shorter_header) {
    std::auto_ptr<instance_std_t> r(new instance_std_t());
    r->set_header(std::string("1234"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "header");
}

BOOST_AUTO_TEST_CASE(test_instance_std_check_longer_header) {
    std::auto_ptr<instance_std_t> r(new instance_std_t());
    r->set_header(std::string("123456"));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "header");
}

// Java calls dumpStruct(), which invokes all getters and then _check()
BOOST_AUTO_TEST_CASE(test_instance_std_check_empty_header_via_dump) {
    std::auto_ptr<instance_std_t> r(new instance_std_t());
    r->set_header(std::string(""));
    BOOST_CHECK_EQUAL(r->header(), std::string(""));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "header");
}

BOOST_AUTO_TEST_CASE(test_instance_std_write) {
    std::auto_ptr<instance_std_t> r(new instance_std_t());
    r->set_header(std::string("Hello"));
    r->_check();

    kaitai::kstream io(std::string(2 + 5, '\0'));
    r->_write(&io);
    io.seek(0);

    // Java compares object dumps; compare the only field instead
    instance_std_t new_r(&io);
    new_r._read();
    BOOST_CHECK_EQUAL(new_r.header(), r->header());
}

BOOST_AUTO_TEST_CASE(test_instance_std_read_write_roundtrip) {
    ks_write_test::roundtrip<instance_std_t>("str_encodings.bin");
}
