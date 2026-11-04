#include <boost/test/unit_test.hpp>
#include "eof_exception_bits_be.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "kaitai/exceptions.h"

BOOST_AUTO_TEST_CASE(test_eof_exception_bits_be) {
    std::ifstream ifs("src/nav_parent_switch.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    eof_exception_bits_be_t* r = nullptr;
    BOOST_CHECK_THROW(
        r = new eof_exception_bits_be_t(&ks); r->_read(),
        std::ifstream::failure
    );

    delete r;
}
