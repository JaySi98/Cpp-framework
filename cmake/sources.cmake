set(HEADERS
    include/core/logs/log_data.hpp
    include/core/logs/log_message.hpp
    include/core/logs/logger_config.hpp
    include/core/logs/base_logger.hpp
    include/core/logs/logger.hpp
    include/core/logs/log_file.hpp
    include/core/logs/log_interface.hpp

    include/core/utility/weak_function.hpp
    include/core/utility/time.hpp
    include/core/utility/type_literal_map.hpp
)

set(SOURCES
    src/core/logs/log_data.cpp
    src/core/logs/log_message.cpp
    src/core/logs/base_logger.cpp
    src/core/logs/logger.cpp
    src/core/logs/log_file.cpp

    src/core/utility/time.cpp
)

set(EXE_SOURCES
    src/main.cpp
    ${SOURCES}
)

# inside test directory
set(TEST_SOURCES
    mainTest.cpp
)
