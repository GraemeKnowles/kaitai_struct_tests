// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEosExceptionBytes.java

#include "helpers_write.h"
#include "eos_exception_bytes.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

BOOST_AUTO_TEST_CASE(test_eos_exception_bytes) {
    std::auto_ptr<eos_exception_bytes_t> r(new eos_exception_bytes_t());
    std::auto_ptr<eos_exception_bytes_t::data_t> data(new eos_exception_bytes_t::data_t(0, r.get(), r->_root()));
    data->set_buf(std::string("\x00\xff\xfe\xfd\xfc\xfb\xfa", 7));
    data->_check();
    r->set_envelope(data.release());
    r->_check();
    // Java: java.nio.BufferOverflowException
    kaitai::kstream io(std::string(12, '\0'));
    BOOST_CHECK_THROW(r->_write(&io), std::ios_base::failure);
}
