// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEosExceptionU4.java

#include "helpers_write.h"
#include "eos_exception_u4.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

BOOST_AUTO_TEST_CASE(test_eos_exception_u4) {
    std::auto_ptr<eos_exception_u4_t> r(new eos_exception_u4_t());
    std::auto_ptr<eos_exception_u4_t::data_t> data(new eos_exception_u4_t::data_t(0, r.get(), r->_root()));
    data->set_prebuf(std::string("\x00\xff\xfe", 3));
    data->set_fail_int(3000500200UL);
    data->_check();
    r->set_envelope(data.release());
    r->_check();
    // Java: java.nio.BufferOverflowException
    kaitai::kstream io(std::string(12, '\0'));
    BOOST_CHECK_THROW(r->_write(&io), std::ios_base::failure);
}
