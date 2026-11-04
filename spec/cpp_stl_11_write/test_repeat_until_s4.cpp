// Ported from spec/java/src/io/kaitai/struct/specwrite/TestRepeatUntilS4.java

#include "helpers_write.h"
#include "repeat_until_s4.h"

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_check_bad_no_entries) {
    std::unique_ptr<repeat_until_s4_t> r(new repeat_until_s4_t());
    std::unique_ptr<std::vector<int32_t>> entries(new std::vector<int32_t>());
    r->set_entries(std::move(entries));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "entries");
}

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_check_good_one_entry) {
    std::unique_ptr<repeat_until_s4_t> r(new repeat_until_s4_t());
    std::unique_ptr<std::vector<int32_t>> entries(new std::vector<int32_t>());
    entries->push_back(-1);
    r->set_entries(std::move(entries));
    r->set_afterall(std::string(""));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_check_bad_early_until_entry) {
    std::unique_ptr<repeat_until_s4_t> r(new repeat_until_s4_t());
    std::unique_ptr<std::vector<int32_t>> entries(new std::vector<int32_t>());
    entries->push_back(-3);
    entries->push_back(275000);
    entries->push_back(-1);
    entries->push_back(0);
    entries->push_back(-1);
    r->set_entries(std::move(entries));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "entries");
}

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_check_bad_no_until_entry) {
    std::unique_ptr<repeat_until_s4_t> r(new repeat_until_s4_t());
    std::unique_ptr<std::vector<int32_t>> entries(new std::vector<int32_t>());
    entries->push_back(-3);
    entries->push_back(275000);
    entries->push_back(-2);
    entries->push_back(0);
    r->set_entries(std::move(entries));
    KS_CHECK_CONSISTENCY_ERROR(r->_check(), "entries");
}

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_check_good_until_entry) {
    std::unique_ptr<repeat_until_s4_t> r(new repeat_until_s4_t());
    std::unique_ptr<std::vector<int32_t>> entries(new std::vector<int32_t>());
    entries->push_back(-3);
    entries->push_back(275000);
    entries->push_back(-2);
    entries->push_back(0);
    entries->push_back(-1);
    r->set_entries(std::move(entries));
    r->set_afterall(std::string(""));
    r->_check();
}

BOOST_AUTO_TEST_CASE(test_repeat_until_s4_read_write_roundtrip) {
    ks_write_test::roundtrip<repeat_until_s4_t>("repeat_until_s4.bin");
}
