// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEofExceptionBytes.java

#include "helpers_write.h"
#include "eof_exception_bytes.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

static std::unique_ptr<eof_exception_bytes_t> make() {
    std::unique_ptr<eof_exception_bytes_t> r(new eof_exception_bytes_t());
    r->set_buf(std::string("\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\xff\xfe\xfd\xfc\xfb", 13));
    r->_check();
    return r;
}

BOOST_AUTO_TEST_CASE(test_eof_exception_bytes_bb) {
    std::unique_ptr<eof_exception_bytes_t> r = make();
    kaitai::kstream io(std::string(12, '\0'));
    BOOST_CHECK_THROW(r->_write(&io), std::ios_base::failure);
}

// Java: RandomAccessFileKaitaiStream; here a kstream over a std::fstream
BOOST_AUTO_TEST_CASE(test_eof_exception_bytes_file) {
    std::unique_ptr<eof_exception_bytes_t> r = make();
    ks_write_test::scratch_file f("specwrite_eof_exception_bytes.bin", 12);
    kaitai::kstream io(&f.fs);
    BOOST_CHECK_EXCEPTION(r->_write(&io), std::ios_base::failure,
        [](const std::ios_base::failure& e) {
            return ks_write_test::starts_with(e.what(), "requested to write 13 bytes, but only 12 bytes left in the stream");
        });
}
