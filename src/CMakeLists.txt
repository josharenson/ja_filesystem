include(CheckIncludeFiles)

set(LIBRARY_NAME Static)
string(TOUPPER ${LIBRARY_NAME} LIBRARY_TYPE)

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE}
    filesystem/file.cpp
    filesystem/file_impl_ja.cpp
    filesystem/path.cpp
    filesystem/path_impl.cpp
    filesystem/path_impl_ja.cpp
)

CHECK_INCLUDE_FILES("sys/stat.h" HAS_SYS_STAT_H)
if (HAS_SYS_STAT_H)
    target_compile_definitions(${LIBRARY_NAME}
        PRIVATE
        -DHAS_SYS_STAT_H
    )
endif(HAS_SYS_STAT_H)

target_include_directories(Static PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
