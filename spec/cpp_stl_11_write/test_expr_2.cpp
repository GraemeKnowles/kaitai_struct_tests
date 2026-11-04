// Ported from spec/java/src/io/kaitai/struct/specwrite/TestExpr2.java

#include "helpers_write.h"
#include "expr_2.h"

BOOST_AUTO_TEST_CASE(test_expr_2_edit) {
    std::ifstream ifs("src/str_encodings.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::unique_ptr<expr_2_t> r(new expr_2_t(&ks));
    r->_read();

    int old_len_mod = r->str2()->len_mod();
    int old_str2_rest_avg = r->str2()->rest()->avg();

    r->str2()->set_str(std::string("Kaitai Struct \xe3\x82\xab")); // "Kaitai Struct カ"
    r->str2()->_invalidate_len_mod();
    int str2_size = r->str2()->str().size(); // UTF-8 byte length
    r->str2()->set_len_orig(str2_size + 3);
    BOOST_CHECK_NE(r->str2()->len_mod(), old_len_mod);
    BOOST_CHECK_EQUAL(r->str2()->len_mod(), str2_size);

    r->str2()->rest()->set_byte0(0xfa);
    r->str2()->rest()->_invalidate_avg();
    r->str2()->rest()->set_byte1(0x44);
    r->str2()->rest()->set_byte2(0x88);
    BOOST_CHECK_NE(r->str2()->rest()->avg(), old_str2_rest_avg);

    // Java's dumpStruct() calls _check() on every object
    r->_fetch_instances();
    r->str1()->rest()->_check();
    r->str1()->_check();
    r->str2()->rest()->_check();
    r->str2()->_check();
    r->_check();

    kaitai::kstream new_io(std::string(
        2 + // str1.len_orig
        r->str1()->len_mod() + // str1.str
        3 + // str1.rest
        2 + // str2.len_orig
        r->str2()->len_mod() + // str2.str
        3, // str2.rest
        '\0'
    ));
    r->_write(&new_io);
    new_io.seek(0);

    // Java compares object dumps; compare the fields instead
    expr_2_t new_r(&new_io);
    new_r._read();
    expr_2_t::mod_str_t* const objs[][2] = {
        {r->str1(), new_r.str1()},
        {r->str2(), new_r.str2()},
    };
    for (int i = 0; i < 2; i++) {
        expr_2_t::mod_str_t* o = objs[i][0];
        expr_2_t::mod_str_t* n = objs[i][1];
        BOOST_CHECK_EQUAL(n->len_orig(), o->len_orig());
        BOOST_CHECK_EQUAL(n->str(), o->str());
        BOOST_CHECK_EQUAL(n->len_mod(), o->len_mod());
        BOOST_CHECK_EQUAL(n->rest()->byte0(), o->rest()->byte0());
        BOOST_CHECK_EQUAL(n->rest()->byte1(), o->rest()->byte1());
        BOOST_CHECK_EQUAL(n->rest()->byte2(), o->rest()->byte2());
        BOOST_CHECK_EQUAL(n->rest()->avg(), o->rest()->avg());
    }
    BOOST_CHECK_EQUAL(new_r.str1_avg(), r->str1_avg());
    BOOST_CHECK_EQUAL(new_r.str1_len_mod(), r->str1_len_mod());
}

BOOST_AUTO_TEST_CASE(test_expr_2_read_write_roundtrip) {
    ks_write_test::roundtrip<expr_2_t>("str_encodings.bin");
}
