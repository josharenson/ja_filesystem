// Copyright (c) 2022 Josh Arenson

// Test framework dependencies
#include <catch2/catch.hpp>
#include <catch/fakeit.hpp>

#include <utility>
#include <vector>

// Under test
#include <ja/filesystem/path.hpp>
#include <private/ja/filesystem/path_impl.hpp>

namespace ja { namespace filesystem {
class TestPath : public Path {
public:
    explicit TestPath(std::unique_ptr<PathImpl> pimpl)
    : Path(std::move(pimpl)) {}
};
}}

using namespace ja::filesystem;

TEST_CASE("Path API", "[unit]") {

  fakeit::Mock<PathImpl> mockPath;
  fakeit::Fake(Dtor(mockPath));
  fakeit::When(Method(mockPath, Abspath)).Do([] {
    return nullptr;
  });
  fakeit::When(Method(mockPath, Copy)).Do([] {
    return nullptr;
  });
  fakeit::Fake(Method(mockPath, Exists));
  fakeit::When(Method(mockPath, Join)).Do([](const std::string &) {
    return nullptr;
  });
  fakeit::Fake(Method(mockPath, Normpath));
  fakeit::Fake(Method(mockPath, Split));

  std::unique_ptr<PathImpl> mockPathPtr(&mockPath.get());

  SECTION("Abspath calls pimpl") {
    TestPath path(std::move(mockPathPtr));
    path.Abspath();
    fakeit::Verify(Method(mockPath, Abspath));
  }

  SECTION("Exists calls pimpl") {
    TestPath path(std::move(mockPathPtr));
    path.Exists();
    fakeit::Verify(Method(mockPath, Exists));
  }

  SECTION("Join calls pimpl") {
    TestPath path(std::move(mockPathPtr));
    path.Join("");
    fakeit::Verify(Method(mockPath, Join));
  }

  SECTION("Normpath calls pimpl") {
    TestPath path(std::move(mockPathPtr));
    path.Normpath();
    fakeit::Verify(Method(mockPath, Normpath));
  }

  SECTION("Split calls pimpl") {
    TestPath path(std::move(mockPathPtr));
    path.Split();
    fakeit::Verify(Method(mockPath, Split));
  }
}
