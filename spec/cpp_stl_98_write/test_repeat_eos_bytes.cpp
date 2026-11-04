// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestRepeatEosBytes.java

#include "helpers_write.h"
#include "repeat_eos_bytes.h"

BOOST_AUTO_TEST_CASE(test_repeat_eos_bytes_check_longer_io) {
    std::auto_ptr<repeat_eos_bytes_t> r(new repeat_eos_bytes_t());
    std::auto_ptr<std::vector<std::string> > records(new std::vector<std::string>());
    records->push_back(std::string("\xe8\xba\xaa\xaa\xaa", 5));
    records->push_back(std::string("\xfa\x9e\xb8\xaa\xaa", 5));
    records->push_back(std::string("\xaa\x55\x55\x55\x55", 5));
    r->set_records(records.release());
    r->_check();
    // Java: "Check failed: records, expected: 0, actual: 3"
    KS_CHECK_CONSISTENCY_ERROR_MSG(
        {
            kaitai::kstream io(std::string(15 + 3, '\0'));
            r->_write(&io);
        },
        "check failed: records: expected end of stream, 3 bytes left"
    );
}

BOOST_AUTO_TEST_CASE(test_repeat_eos_bytes_read_write_roundtrip) {
    ks_write_test::roundtrip<repeat_eos_bytes_t>("repeat_until_process.bin");
}
