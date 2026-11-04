// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEofExceptionBitsLe.java

#include "helpers_write.h"
#include "eof_exception_bits_le.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

static std::auto_ptr<eof_exception_bits_le_t> make() {
    std::auto_ptr<eof_exception_bits_le_t> r(new eof_exception_bits_le_t());
    r->set_pre_bits(1 /* 0b000_0001 */);
    r->set_fail_bits(0xff84 /* 0b0_11111111_01000010_0 */);
    r->_check();
    return r;
}

BOOST_AUTO_TEST_CASE(test_eof_exception_bits_le_bb) {
    std::auto_ptr<eof_exception_bits_le_t> r = make();
    kaitai::kstream io(std::string(3, '\0'));
    BOOST_CHECK_THROW(r->_write__seq(&io), std::ios_base::failure);
    BOOST_CHECK_EQUAL(io.pos(), 1);
}

// Java: RandomAccessFileKaitaiStream; here a kstream over a std::fstream
BOOST_AUTO_TEST_CASE(test_eof_exception_bits_le_file) {
    std::auto_ptr<eof_exception_bits_le_t> r = make();
    ks_write_test::scratch_file f("specwrite_eof_exception_bits_le.bin", 3);
    kaitai::kstream io(&f.fs);
    BOOST_CHECK_EXCEPTION(r->_write__seq(&io), std::ios_base::failure,
        [](const std::ios_base::failure& e) {
            return ks_write_test::starts_with(e.what(), "requested to write 3 bytes, but only 2 bytes left in the stream");
        });
    BOOST_CHECK_EQUAL(io.pos(), 1);
}
