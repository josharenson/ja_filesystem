add_executable(UnitTestRunner
    test_bootstrap.cpp
    test_file_ctor.cpp
)

target_include_directories(UnitTestRunner
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(UnitTestRunner
    PRIVATE
    Catch2::Catch2
    Static
)
