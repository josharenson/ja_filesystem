add_executable(UnitTestRunner
    test_bootstrap.cpp
)

target_link_libraries(UnitTestRunner
    PRIVATE Catch2::Catch2
)
