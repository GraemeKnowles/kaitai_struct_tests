// Helpers for the hand-written C++ read-write (serialization) tests, ported
// from spec/java/src/io/kaitai/struct/specwrite.
#ifndef KS_HELPERS_WRITE_H_
#define KS_HELPERS_WRITE_H_

#include <boost/test/unit_test.hpp>
#include "kaitai/kaitaistream.h"
#include "kaitai/exceptions.h"

#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

namespace ks_write_test {

inline std::string read_file(const std::string& path) {
    std::ifstream ifs(path.c_str(), std::ifstream::binary);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

inline std::string to_hex(const std::string& s) {
    static const char digits[] = "0123456789abcdef";
    std::string r;
    for (std::size_t i = 0; i < s.size(); i++) {
        unsigned char b = static_cast<unsigned char>(s[i]);
        if (i > 0) r += ' ';
        r += digits[b >> 4];
        r += digits[b & 0xf];
    }
    return r;
}

inline bool starts_with(const std::string& s, const std::string& prefix) {
    return s.compare(0, prefix.size(), prefix) == 0;
}

// Writes `r` into a new in-memory stream of `size` bytes, returns its contents.
template<class T>
std::string write_to_buffer(T* r, std::size_t size) {
    kaitai::kstream io(std::string(size, '\0'));
    r->_write(&io);
    return io.to_byte_array();
}

// Equivalent of CommonSpec.assertEqualToFullFile() in Java.
template<class T>
void assert_equal_to_full_file(T* r, const std::string& fn) {
    std::string expected = read_file("src/" + fn);
    r->_check();
    BOOST_CHECK_EQUAL(to_hex(write_to_buffer(r, expected.size())), to_hex(expected));
}

// Counterpart of CommonSpec.testReadWriteRoundtrip() in Java. C++ has no
// reflection to compare object dumps, so this checks that writing what was
// read, re-reading it and writing it again gives the same bytes.
template<class T>
void roundtrip(const std::string& fn) {
    std::ifstream ifs(("src/" + fn).c_str(), std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    std::unique_ptr<T> r(new T(&ks));
    r->_read();
    r->_fetch_instances();
    std::string out1 = write_to_buffer(r.get(), ks.size());

    kaitai::kstream ks2(out1);
    std::unique_ptr<T> r2(new T(&ks2));
    r2->_read();
    r2->_fetch_instances();
    std::string out2 = write_to_buffer(r2.get(), out1.size());
    BOOST_CHECK_EQUAL(to_hex(out2), to_hex(out1));
}

// Creates a file of `size` zero bytes and opens it for reading and writing
// (the counterpart of Java tests using RandomAccessFileKaitaiStream).
struct scratch_file {
    std::string path;
    std::fstream fs;
    scratch_file(const std::string& name, std::size_t size): path("/tmp/" + name) {
        {
            std::ofstream ofs(path.c_str(), std::ofstream::binary | std::ofstream::trunc);
            ofs << std::string(size, '\0');
        }
        fs.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    }
    ~scratch_file() {
        fs.close();
        std::remove(path.c_str());
    }
};

}

// Checks that `stmt` throws kaitai::consistency_error for field `field_id`
// (Java: expectedExceptionsMessageRegExp = "Check failed: <field_id>,.*").
#define KS_CHECK_CONSISTENCY_ERROR(stmt, field_id) \
    BOOST_CHECK_EXCEPTION(stmt, kaitai::consistency_error, \
        [](const kaitai::consistency_error& e) { return e.id() == (field_id); })

// Same, but also checks the whole message.
#define KS_CHECK_CONSISTENCY_ERROR_MSG(stmt, msg) \
    BOOST_CHECK_EXCEPTION(stmt, kaitai::consistency_error, \
        [](const kaitai::consistency_error& e) { return std::string(e.what()) == (msg); })

#endif
