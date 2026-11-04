// Ported from spec/java/src/io/kaitai/struct/specwrite/TestOpaqueWithParam.java

#include "helpers_write.h"
#include "opaque_with_param.h"

// The Java test only has the automatic roundtrip.

BOOST_AUTO_TEST_CASE(test_opaque_with_param_read_write_roundtrip) {
    ks_write_test::roundtrip<opaque_with_param_t>("term_strz.bin");
}
