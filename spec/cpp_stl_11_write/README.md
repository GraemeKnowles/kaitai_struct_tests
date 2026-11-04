# C++11 read-write (serialization) tests

Hand-written tests for code generated with `-t cpp_stl --cpp-standard 11 -w`,
ported one-to-one from the Java tests in
`spec/java/src/io/kaitai/struct/specwrite/` that are not generated from KST.
Shared helpers are in `helpers_write.h`.

Differences from the Java tests:

* `testReadWriteRoundtrip` compares object dumps via reflection in Java. C++
  has no reflection, so `ks_write_test::roundtrip<T>()` instead checks that
  writing what was read, re-reading it and writing again gives the same bytes.
  As in Java, it is left out where the Java test skips it.
* Java `ConsistencyError` maps to `kaitai::consistency_error`. Its message is
  `check failed: <id>: <details>`; most tests check only `id()`.
* Java `BufferOverflowException` / EOF errors when writing map to
  `std::ios_base::failure`. `RandomAccessFileKaitaiStream` tests use a
  `kaitai::kstream` over a `std::fstream` on a scratch file.
* Validation error messages in C++ contain no values, so the expected message
  is `<path>: validation failed: <kind>`.
* Tests expecting `NullPointerException` for unset fields are not ported (an
  unset `std::unique_ptr` would be dereferenced).

Build and run with `rwtest/write_specs.py` (outside this repo): each test file
becomes its own executable, run with the working directory set to this
repository's root.
