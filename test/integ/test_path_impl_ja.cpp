// Test Framework
#include <catch2/catch.hpp>

// System Dependencies
#include <string>

// Project Dependencies
#include <ja/filesystem/file.hpp>

// Under Test
#include <ja/filesystem/path.hpp>
#include <private/ja/filesystem/path_impl_ja.hpp>

using namespace ja::filesystem;

#if defined(HAS_PYTHON)
#include <Python.h>
std::string CallPython(const std::string &func,
        const std::vector<std::string> &args={}) {
    Py_Initialize();

    auto *pName = PyUnicode_FromString("os.path");
    auto *pModule = PyImport_Import(pName);
    auto *pDict = PyModule_GetDict(pModule);
    auto *pFunc = PyDict_GetItemString(pDict, func.c_str());
    REQUIRE(pFunc);

    auto *pythonArgument = PyTuple_New();
    auto *pArg1 = PyUnicode_FromString(arg.c_str());
    PyTuple_SetItem(pythonArgument, 0, pArg1);

    auto *pValue = PyObject_CallObject(pFunc, pythonArgument);

    auto *repr = PyObject_Repr(pValue);
    auto *str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    Py_Finalize();
    std::string result(bytes);
    return result;
}
#endif

TEST_CASE("PathImplJa::Ctor", "[integ][bootstrap]") {
    SECTION("Can compile") {
        PathImplJa p("/tmp/carne_asada.taco");
    }
}

#if defined(HAS_PYTHON)
TEST_CASE("Path::Abspath == Python", "[integ][python]") {
    SECTION("Empty returns pwd") {
        // Erase and pop_back remove surrounding single-quotes
        auto pwd = CallPython("abspath").erase(0,1);
        pwd.pop_back();
        Path p0;
        auto p1 = p0.Abspath();
        REQUIRE(pwd == p1.Normpath());
    }
}
#endif

TEST_CASE("Path::Exists", "[integ]") {

    const std::string kFilepath = "/tmp/lengua.taco";
    File f(kFilepath, "w");

    SECTION("Returns true if file exists") {
        REQUIRE(Path(kFilepath).Exists());
    }

    SECTION("Returns false if file doesn't exist") {
        REQUIRE_FALSE(Path(kFilepath + ".fake").Exists());
    }

    f.Remove();
}

#if defined(HAS_PYTHON)
TEST_CASE("Path::Join == Python", "[integ][python]") {
    const std::string kPrefix = "burrito";
    const std::string kSuffix = "california";
    SECTION("Straightforward join") {
        Path p0(kPrefix);
        auto p1 = p0.Join(kSuffix);
        auto pythonSays 
    }
}
#endif

TEST_CASE("Path::Join", "[unit]") {
    const std::string kPrefix = "taco";
    const std::string kSuffix = "suadero";
    const std::string kExpected = kPrefix + PathImpl::kPathSeparator() + kSuffix;

    SECTION("Straightforward join") {
        Path p0(kPrefix);
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == kExpected);
    }

    SECTION("Leading separator only") {
        Path p0(PathImpl::kPathSeparator() + kPrefix);
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == PathImpl::kPathSeparator() + kExpected);
    }

    SECTION("Leading and trailing separators prefix") {
        Path p0(PathImpl::kPathSeparator() + kPrefix + PathImpl::kPathSeparator());
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == PathImpl::kPathSeparator() + kExpected);
    }

    SECTION("Prefix ending and suffix leading") {
        Path p0(kPrefix + PathImpl::kPathSeparator());
        auto p1 = p0.Join(PathImpl::kPathSeparator() + kSuffix);
        REQUIRE(p1.Normpath() == kExpected);
    }
}

TEST_CASE("Path::operator=", "[unit]") {
    SECTION("Normalized paths are the same after assignment") {
        Path p0("p0");
        Path p1("p1");

        // Precondition
        REQUIRE_FALSE(p0.Normpath() == p1.Normpath());

        // Test
        p0 = p1;

        // Post condition
        REQUIRE(p0.Normpath() == p1.Normpath());
    }
}

TEST_CASE("Path::operator+=", "[unit]") {

    const std::string kPrefix = "taco";
    const std::string kSuffix = "suadero";
    const std::string kExpected = kPrefix + PathImpl::kPathSeparator() + kSuffix;

    SECTION("Straightforward join") {
        Path p0(kPrefix);
        Path p1(kSuffix);
        p0 += p1;
        REQUIRE(p0.Normpath() == kExpected);
    }
}

TEST_CASE("Path::operator+", "[unit]") {

    const std::string kPrefix = "taco";
    const std::string kSuffix = "suadero";
    const std::string kExpected = kPrefix + PathImpl::kPathSeparator() + kSuffix;

    SECTION("Straightforward join") {
        Path p0(kPrefix);
        Path p1(kSuffix);
        Path p2 = p0 + p1;

        REQUIRE(p0.Normpath() == kPrefix);
        REQUIRE(p1.Normpath() == kSuffix);
        REQUIRE(p2.Normpath() == kExpected);
    }

    SECTION("Empty lhs") {
        Path p0;
        Path p1(kPrefix);
        auto p2 = p0 + p1;

        REQUIRE(p0.Normpath().empty());
        REQUIRE(p1.Normpath() == kPrefix);
        REQUIRE(p2.Normpath() == kPrefix);
    }

    SECTION("Empty rhs") {
        Path p0(kPrefix);
        Path p1;

        auto p2 = p0 + p1;
        REQUIRE(p2.Normpath() == p0.Normpath());
        REQUIRE(p2.Normpath() == kPrefix);
    }

    SECTION("Multiple adds") {
        const std::string kExpected =
            kPrefix +
            PathImpl::kPathSeparator() +
            "grande" +
            PathImpl::kPathSeparator() +
            kSuffix;

        Path p0(kPrefix);
        Path p1("grande");
        Path p2(kSuffix);

        auto p3 = p0 + p1 + p2;
        REQUIRE(p0.Normpath() == kPrefix);
        REQUIRE(p1.Normpath() == "grande");
        REQUIRE(p2.Normpath() == kSuffix);
        REQUIRE(p3.Normpath() == kExpected);
    }
}
