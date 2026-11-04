#include "foo.h"
#include <cassert>
#include <fstream>
#include <memory>

int main() {
    {
        std::ofstream("in.bin", std::ios::binary) << std::string("\x01\x03" "FOO", 5);
    }
    // --- README example 1 ---
    std::ifstream ifs("in.bin", std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    foo_t foo(&ks);
    foo._read();
    foo._fetch_instances(); // load parse instances that should be written too

    foo.set_version(2);
    foo._check();           // required after every modification

    kaitai::kstream out(std::string(ks.size(), '\0'));
    foo._write(&out);
    std::string bytes = out.to_byte_array();
    // ---
    assert(bytes == std::string("\x02\x03" "FOO", 5));

    // --- README example 2 ---
    foo_t foo2;
    foo2.set_version(1);
    foo2.set_len_header(3);
    std::unique_ptr<foo_t::header_t> hdr(new foo_t::header_t(nullptr, &foo2, &foo2));
    hdr->set_magic(std::string("BAR"));
    hdr->_check();
    foo2.set_header(std::move(hdr));
    foo2._check();

    kaitai::kstream out2(std::string(5, '\0'));
    foo2._write(&out2);
    // ---
    assert(out2.to_byte_array() == std::string("\x01\x03" "BAR", 5));
    return 0;
}
