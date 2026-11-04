#include <boost/test/unit_test.hpp>
#include "expr_io_eof_bits.h"
#include <iostream>
#include <fstream>
#include <vector>

BOOST_AUTO_TEST_CASE(test_expr_io_eof_bits) {
    std::ifstream ifs("src/nav_parent_switch.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    expr_io_eof_bits_t* r = new expr_io_eof_bits_t(&ks);
    r->_read();
    BOOST_CHECK_EQUAL(r->foo(), 5167);
    BOOST_CHECK_EQUAL(r->bar(), 15);
    BOOST_CHECK(r->_is_null_baz());
    BOOST_CHECK_EQUAL(r->align(), std::string("", 0));
    BOOST_CHECK(r->_is_null_qux());

    delete r;
}
