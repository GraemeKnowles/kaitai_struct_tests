// Generated from ../cpp_stl_11_write by rwtest/to98.py: edit the C++11 version.
// Ported from spec/java/src/io/kaitai/struct/specwrite/TestOpaqueExternalType02Parent.java

#include "helpers_write.h"
#include "opaque_external_type_02_parent.h"

// The Java test only has the automatic roundtrip.

BOOST_AUTO_TEST_CASE(test_opaque_external_type_02_parent_read_write_roundtrip) {
    ks_write_test::roundtrip<opaque_external_type_02_parent_t>("term_strz.bin");
}
