cmake_minimum_required(VERSION 3.20)
project(TLog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR .)

set(TLOG_SOURCES
    "${SOURCE_DIR}/TLog.cpp"
)

add_library(TLog STATIC ${TLOG_SOURCES})

# Installation de la librairie
install(TARGETS TLog
        EXPORT TLogTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES "${SOURCE_DIR}/TLog.hpp"
        DESTINATION include/TLog)

install(EXPORT TLogTargets
        FILE TLogConfig.cmake
        NAMESPACE TLog::
        DESTINATION lib/cmake/WebcamTLog)