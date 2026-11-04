// Ported from spec/java/src/io/kaitai/struct/specwrite/TestCastToTop.java

#include "helpers_write.h"
#include "cast_to_top.h"

BOOST_AUTO_TEST_CASE(test_cast_to_top_inst_disabled) {
    std::unique_ptr<cast_to_top_t> r(new cast_to_top_t());
    r->set_code(0x77);

    std::unique_ptr<cast_to_top_t> s(new cast_to_top_t(nullptr, r.get(), r->_root()));
    s->set_code(0xa8);
    // `cast_to_top.ksy` is an infinitely recursive format, so it's necessary to break
    // the infinite recursion by disabling the `header` instance here.
    s->set_header__enabled(false);
    s->_check();

    r->set_header(std::move(s));
    r->_check();

    kaitai::kstream io(std::string(2, '\0'));
    r->_write(&io);
    BOOST_CHECK_EQUAL(ks_write_test::to_hex(io.to_byte_array()), "77 a8");
}

// The automatic roundtrip (not skipped in Java) is not ported: reading
// fixed_struct.bin and fetching instances recurses infinitely through
// `header` (see the comment above).
