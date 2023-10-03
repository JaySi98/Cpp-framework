set(HEADERS
    include/core/logs/log_message.hpp
    include/core/logs/logger.hpp
)

set(SOURCES
    src/core/logs/log_message.cpp
    src/core/logs/logger.cpp
)

set(EXE_SOURCES
    src/main.cpp
    ${SOURCES}
)

# inside test directory
set(TEST_SOURCES
    mainTest.cpp
)
