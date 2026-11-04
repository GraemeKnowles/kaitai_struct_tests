// Ported from spec/java/src/io/kaitai/struct/specwrite/TestEofExceptionU4.java

#include "helpers_write.h"
#include "eof_exception_u4.h"

// testReadWriteRoundtrip is skipped in Java: parsing is expected to fail

static std::unique_ptr<eof_exception_u4_t> make() {
    std::unique_ptr<eof_exception_u4_t> r(new eof_exception_u4_t());
    r->set_prebuf(std::string("\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80", 9));
    r->set_fail_int(3000500200UL);
    r->_check();
    return r;
}

BOOST_AUTO_TEST_CASE(test_eof_exception_u4_bb) {
    std::unique_ptr<eof_exception_u4_t> r = make();
    kaitai::kstream io(std::string(12, '\0'));
    BOOST_CHECK_THROW(r->_write(&io), std::ios_base::failure);
}

// Java: RandomAccessFileKaitaiStream; here a kstream over a std::fstream
BOOST_AUTO_TEST_CASE(test_eof_exception_u4_file) {
    std::unique_ptr<eof_exception_u4_t> r = make();
    ks_write_test::scratch_file f("specwrite_eof_exception_u4.bin", 12);
    kaitai::kstream io(&f.fs);
    BOOST_CHECK_EXCEPTION(r->_write(&io), std::ios_base::failure,
        [](const std::ios_base::failure& e) {
            return ks_write_test::starts_with(e.what(), "requested to write 4 bytes, but only 3 bytes left in the stream");
        });
}
