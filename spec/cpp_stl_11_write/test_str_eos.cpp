// Ported from spec/java/src/io/kaitai/struct/specwrite/TestStrEos.java

#include "helpers_write.h"
#include "str_eos.h"

BOOST_AUTO_TEST_CASE(test_str_eos_check_longer_io) {
    std::unique_ptr<str_eos_t> r(new str_eos_t());
    r->set_str(std::string("Hello"));
    r->_check();
    // Java: "Check failed: str, expected: 0, actual: 2"
    KS_CHECK_CONSISTENCY_ERROR_MSG(
        {
            kaitai::kstream io(std::string(5 + 2, '\0'));
            r->_write(&io);
        },
        "check failed: str: expected end of stream, 2 bytes left"
    );
}

BOOST_AUTO_TEST_CASE(test_str_eos_read_write_roundtrip) {
    ks_write_test::roundtrip<str_eos_t>("term_strz.bin");
}
