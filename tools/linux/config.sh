#!/bin/sh

# run from root folder
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_EXECUTABLE=ON \
    -DENABLE_CLANG_TIDY=ON \
    -DENABLE_CLANG_FORMAT=ON \
    -DENABLE_DOXYGEN=ON \
    # -DUSE_SANITIZER=Address,Leak \
    # -DENABLE_CODE_COVERAGE=ON