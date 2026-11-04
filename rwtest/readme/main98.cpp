#include "foo.h"
#include <cassert>
#include <fstream>

int main() {
    {
        std::ofstream o("in.bin", std::ios::binary);
        o << std::string("\x01\x03" "FOO", 5);
    }
    std::ifstream ifs("in.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    foo_t foo(&ks);
    foo._read();
    foo._fetch_instances();
    foo.set_version(2);
    foo._check();
    kaitai::kstream out(std::string(ks.size(), '\0'));
    foo._write(&out);
    assert(out.to_byte_array() == std::string("\x02\x03" "FOO", 5));

    // --- README example (C++98) ---
    foo_t foo2;
    foo2.set_version(1);
    foo2.set_len_header(3);
    foo_t::header_t* hdr = new foo_t::header_t(0, &foo2, &foo2);
    hdr->set_magic(std::string("BAR"));
    hdr->_check();
    foo2.set_header(hdr);   // foo2 now owns hdr
    foo2._check();
    // ---
    kaitai::kstream out2(std::string(5, '\0'));
    foo2._write(&out2);
    assert(out2.to_byte_array() == std::string("\x01\x03" "BAR", 5));

    // replacing an owned object frees the old one
    foo_t::header_t* hdr2 = new foo_t::header_t(0, &foo2, &foo2);
    hdr2->set_magic(std::string("BAZ"));
    hdr2->_check();
    foo2.set_header(hdr2);
    foo2._check();
    kaitai::kstream out3(std::string(5, '\0'));
    foo2._write(&out3);
    assert(out3.to_byte_array() == std::string("\x01\x03" "BAZ", 5));
    // writing again (into a new stream) is fine too
    kaitai::kstream out4(std::string(5, '\0'));
    foo2._write(&out4);
    assert(out4.to_byte_array() == out3.to_byte_array());
    return 0;
}
