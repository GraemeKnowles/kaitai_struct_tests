#include "rw_twice.h"
#include <cassert>
#include <iostream>
int main() {
    std::string in("\x07\x01\x02\x03\x04\x0a\x0b\x0c\x0d", 9);
    kaitai::kstream ks(in);
    rw_twice_t r(&ks);
    r._read();
    r._fetch_instances();
    std::string outs[2];
    for (int k = 0; k < 2; k++) {
        r._check();
        kaitai::kstream out(std::string(in.size(), '\0'));
        r._write(&out);
        outs[k] = out.to_byte_array();
        // use children after writing: their streams were replaced by write substreams
        assert(r.body()->_io()->size() == 4);
        assert(r.body()->b() == 0x0403);
        assert(r.tail() == 4);
        assert(r.items()->at(1)->y() == 0x0d);
        assert(r.items()->at(1)->_io()->size() == 2);
    }
    assert(outs[0] == in && outs[1] == in);
    // modify and write again
    r.body()->set_a(0x1234);
    r.body()->_check();
    r._check();
    kaitai::kstream out(std::string(in.size(), '\0'));
    r._write(&out);
    std::string o = out.to_byte_array();
    assert(o[1] == 0x34 && o[2] == 0x12);
    std::cout << "ok\n";
}
