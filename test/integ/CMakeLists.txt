add_executable(IntegTestRunner
    test_bootstrap.cpp
    test_file_impl_ja.cpp
    test_path_impl_ja.cpp
)

target_include_directories(IntegTestRunner
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(IntegTestRunner
    PRIVATE
    Catch2::Catch2
    Static
)
