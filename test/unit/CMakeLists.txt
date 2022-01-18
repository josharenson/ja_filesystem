add_executable(UnitTestRunner
    test_bootstrap.cpp
    test_path.cpp
    test_path_ja.cpp
)

target_include_directories(UnitTestRunner
    PRIVATE
    ${CMAKE_SOURCE_DIR}/FakeIt/single_header
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(UnitTestRunner
    PRIVATE
    Catch2::Catch2
    Static
)
