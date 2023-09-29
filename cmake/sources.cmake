set(HEADERS
    include/tmp/tmp.hpp
)

set(SOURCES
    src/tmp/tmp.cpp
)

set(EXE_SOURCES
    src/main.cpp
    ${SOURCES}
)

# inside test directory
set(TEST_SOURCES
    mainTest.cpp
    tmpTest.cpp
)
