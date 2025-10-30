rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
./interpreter_tests
lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,version
lcov --remove coverage.info '/usr/*' '*/external/*' '*/googletest/*' --output-file coverage.info
genhtml coverage.info --output-directory coverage-report

