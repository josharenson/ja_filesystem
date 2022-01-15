add_library(Static
    filesystem/file.cpp
    filesystem/file_impl_ja.cpp
)

target_include_directories(Static PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
