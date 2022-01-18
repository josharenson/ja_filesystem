include(FindPython)

add_executable(IntegTestRunner
    test_bootstrap.cpp
    test_file_impl_ja.cpp
    test_path_impl_ja.cpp
)

find_package(Python COMPONENTS Development)
if(Python_Development.Embed_FOUND)
    message("Found a local python interpreter - integration tests will use this")
    list(APPEND COMPILE_DEFINITIONS -DHAS_PYTHON)
    set(PYTHON_LIB "Python::Python")
endif(Python_Development.Embed_FOUND)

target_compile_definitions(IntegTestRunner
    PRIVATE
    ${COMPILE_DEFINITIONS}
)

target_include_directories(IntegTestRunner
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(IntegTestRunner
    PRIVATE
    Catch2::Catch2
    ${PYTHON_LIB}
    Static
)
