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

    auto *pythonArgument = PyTuple_New((signed)args.size());
    for (int i = 0; i < args.size(); i++) {
        auto *pArg = PyUnicode_FromString(args[i].c_str());
        PyTuple_SetItem(pythonArgument, i, pArg);
    }

    auto *pValue = PyObject_CallObject(pFunc, pythonArgument);

    auto *repr = PyObject_Repr(pValue);
    auto *str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    Py_Finalize();
    std::string result(bytes);
    // Erase and pop_back remove surrounding single-quotes
    result.erase(0, 1);
    result.pop_back();
    return result;
}
#endif

#if defined(HAS_PYTHON)
TEST_CASE("Path::Abspath == Python", "[integ][python]") {
    SECTION("Empty returns pwd") {
        auto pwd = CallPython("abspath", {{""}});
        Path p0;
        auto p1 = p0.Abspath();
        REQUIRE(pwd == p1.Normpath());
    }
}
#endif

/*#if defined(HAS_PYTHON)
TEST_CASE("Path::Basename == Python", "[integ][python]") {

    SECTION("Basic basename") {
        const std::string prefix = "carnitas";
        const std::string suffix = "torta";
        Path _(prefix);
        auto p0 = _.Join(suffix);
        auto p1 = p0.Basename();
        auto pythonSays = CallPython("basename", {{p1.Normpath()}});
        REQUIRE(pythonSays == p1.Normpath());
    }

    SECTION("Empty path") {
        Path p0;
        auto pythonSays = CallPython("basename", {{""}});
        REQUIRE(pythonSays == p0.Normpath());
    }

    SECTION("Single path no slashes") {
        Path p0("taco");
        auto pythonSays = CallPython("basename", {{"taco"}});
        REQUIRE(pythonSays == p0.Normpath());
    }

    SECTION("Single path leading slash") {
        const auto prefix = PathImpl::kPathSeparator() + "taco";
        Path p0(prefix);
        auto pythonSays = CallPython("basename", {{prefix}});
        REQUIRE(pythonSays == p0.ToString());
    }
}
#endif*/

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
        auto pythonSays = CallPython("join", {{kPrefix}, {kSuffix}});
        REQUIRE(pythonSays == p1.Normpath());
    }

    SECTION("Leading separator only") {
        Path p0(PathImpl::kPathSeparator() + kPrefix);
        auto p1 = p0.Join(kSuffix);
        auto pythonSays = CallPython("join", {{PathImpl::kPathSeparator() + kPrefix},{kSuffix}});
        REQUIRE(pythonSays == p1.Normpath());
    }

    SECTION("Leading and trailing separators prefix") {
        auto prefix = PathImpl::kPathSeparator() + kPrefix + PathImpl::kPathSeparator();
        Path p0(prefix);
        auto p1 = p0.Join(kSuffix);
        auto pythonSays = CallPython("join",{{prefix}, {kSuffix}});
        REQUIRE(pythonSays == p1.Normpath());
    }

    //  If a component is an absolute path, all previous components are thrown away and joining continues from the absolute path component.
    SECTION("Prefix ending and suffix leading") {
        auto prefix = kPrefix + PathImpl::kPathSeparator();
        auto suffix = PathImpl::kPathSeparator() + kSuffix;
        Path p0(prefix);
        auto p1 = p0.Join(suffix);
        auto pythonSays = CallPython("join", {{prefix}, {suffix}});
        REQUIRE(pythonSays == p1.Normpath());
    }
}
#endif

#if defined(HAS_PYTHON)
TEST_CASE("Path::Split == Python", "[integ][python]") {

  auto TuplizePythonStr = [](const std::string &str){
    std::string head = str.substr(0, str.find_last_of(','));
    head.erase(0, 1); // leading '
    head.pop_back(); // trailing '

    auto leadingChars = strlen("'', ");
    std::string tail = str.substr(head.size() + leadingChars);
    tail.erase(0, 1);
    tail.pop_back();
    return std::make_pair(head, tail);
  };

  const std::string kPrefix = "horchata";
  const std::string kSuffix = "tamarindo";

  SECTION("Straightforward split") {
    auto path = Path(kPrefix).Join(kSuffix);
    auto pair = path.Split();
    auto pythonSays = TuplizePythonStr(
        CallPython("split", {kPrefix + PathImpl::kPathSeparator() + kSuffix}));

    REQUIRE(pair.first == pythonSays.first);
    REQUIRE(pair.second == pythonSays.second);
  }

  SECTION("Empty path") {
    Path path;
    auto pair = path.Split();
    auto pythonSays = TuplizePythonStr(CallPython("split", {{""}}));

    REQUIRE(pair.first == pythonSays.first);
    REQUIRE(pair.second == pythonSays.second);
  }

  SECTION("Leading slash splits with one part") {
    Path p0(PathImpl::kPathSeparator() + kPrefix);
    auto pair = p0.Split();
    auto pythonSays = TuplizePythonStr(
        CallPython("split", {{PathImpl::kPathSeparator() + kPrefix}}));

    REQUIRE(pair.first == pythonSays.first);
    REQUIRE(pair.second == pythonSays.second);
  }

  SECTION("Double slash") {
    auto prefix0 = kPrefix + PathImpl::kPathSeparator() + PathImpl::kPathSeparator() +
                   kSuffix;
    Path p0(prefix0);
    auto pair0 = p0.Split();

    auto pythonSays0 = TuplizePythonStr(CallPython("split", {{prefix0}}));
    REQUIRE(pair0.first == pythonSays0.first);
    REQUIRE(pair0.second == pythonSays0.second);

    auto prefix1 = PathImpl::kPathSeparator() + kPrefix +
                   PathImpl::kPathSeparator() + PathImpl::kPathSeparator() +
                   kSuffix;
    Path p1(prefix1);
    auto pair1 = p1.Split();

    auto pythonSays1 = TuplizePythonStr(CallPython("split", {{prefix1}}));
    REQUIRE(pair1.first == pythonSays1.first);
    REQUIRE(pair1.second == pythonSays1.second);
  }
}
#endif