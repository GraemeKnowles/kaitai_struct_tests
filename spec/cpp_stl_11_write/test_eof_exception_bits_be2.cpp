// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEofExceptionBitsBe2.java

#include "helpers_write.h"
#include "eof_exception_bits_be2.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

static std::unique_ptr<eof_exception_bits_be2_t> make() {
    std::unique_ptr<eof_exception_bits_be2_t> r(new eof_exception_bits_be2_t());
    r->set_pre_bits(0x01);
    r->set_fail_bits(0x85fe /* 0b01000010_11111111_0 */);
    r->_check();
    return r;
}

BOOST_AUTO_TEST_CASE(test_eof_exception_bits_be2_bb) {
    std::unique_ptr<eof_exception_bits_be2_t> r = make();
    kaitai::kstream io(std::string(3, '\0'));
    BOOST_CHECK_THROW(r->_write__seq(&io), std::ios_base::failure);
    BOOST_CHECK_EQUAL(io.pos(), 1);
}

// Java: RandomAccessFileKaitaiStream; here a kstream over a std::fstream
BOOST_AUTO_TEST_CASE(test_eof_exception_bits_be2_file) {
    std::unique_ptr<eof_exception_bits_be2_t> r = make();
    ks_write_test::scratch_file f("specwrite_eof_exception_bits_be2.bin", 3);
    kaitai::kstream io(&f.fs);
    BOOST_CHECK_EXCEPTION(r->_write__seq(&io), std::ios_base::failure,
        [](const std::ios_base::failure& e) {
            return ks_write_test::starts_with(e.what(), "requested to write 3 bytes, but only 2 bytes left in the stream");
        });
    BOOST_CHECK_EQUAL(io.pos(), 1);
}
