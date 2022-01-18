// Copyright (c) 2022 Josh Arenson

#include <catch2/catch.hpp>

#include <algorithm>
#include <string>

// Under test
#include <ja/filesystem/path.hpp>
#include <private/ja/filesystem/path_impl_ja.hpp>

using namespace ja::filesystem;

TEST_CASE("Path::Basename", "[unit]") {
  const std::string kPrefix = "tripas";
  const std::string kSuffix = "menudo";

  SECTION("Basic basename") {
    auto p0 = Path(kPrefix).Join(kSuffix);
    REQUIRE(p0.Basename().ToString() == kSuffix);
  }

  SECTION("Empty path") {
    Path p0;
    REQUIRE(p0.Basename().ToString().empty());
  }

  SECTION("Single path no slashes") {
    Path p0(kPrefix);
    REQUIRE(p0.Basename().ToString() == kPrefix);
  }

  SECTION("Single path leading slash") {
    const auto prefix = PathImpl::kPathSeparator() + kPrefix;
    Path p0(prefix);
    // Leading slash is removed
    REQUIRE(p0.Basename().ToString() == kPrefix);
  }
}

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

  //  If a component is an absolute path, all previous components are thrown away and joining continues from the absolute path component.
  SECTION("Prefix ending and suffix leading") {
    Path p0(kPrefix + PathImpl::kPathSeparator());
    auto p1 = p0.Join(PathImpl::kPathSeparator() + kSuffix);
    REQUIRE(p1.Normpath() == PathImpl::kPathSeparator() + kSuffix);
  }
}

TEST_CASE("PathImplJa::Normpath", "[unit]") {

  const std::string kPrefix = "lengua";
  const std::string kSuffix = "taco";
  const std::string kExpected =
      Path(kPrefix).Join(Path(kSuffix).ToString()).ToString();

  SECTION("Empty path returns empty path") {
    PathImplJa path("");
    REQUIRE(path.Normpath().empty());
  }

  SECTION("Path 2 consecutive separators") {
    auto prefix =
        kPrefix + PathImpl::kPathSeparator() + PathImpl::kPathSeparator();
    PathImplJa path(prefix + kSuffix);
    REQUIRE(path.Normpath() == kExpected);
  }

  SECTION("Path 3 consecutive separators") {
    auto prefix = kPrefix + PathImpl::kPathSeparator() +
                  PathImpl::kPathSeparator() + PathImpl::kPathSeparator();
    PathImplJa path(prefix + kSuffix);
    REQUIRE(path.Normpath() == kExpected);
  }

  SECTION("Path ending in separator has it removed") {
    const std::string prefix = "taco";
    PathImplJa path(prefix + PathImpl::kPathSeparator());
    REQUIRE(path.Normpath() == prefix);
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
    const std::string expected =
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
    REQUIRE(p3.Normpath() == expected);
  }
}

TEST_CASE("Path::Split", "[integ][python]") {
  const std::string kPrefix = "taco";
  const std::string kSuffix = "birria";

 SECTION("Straightforward split") {
    auto p0 = Path(kPrefix).Join(kSuffix);
    auto pair = p0.Split();
    REQUIRE(pair.first == kPrefix);
    REQUIRE(pair.second == kSuffix);
  }

  SECTION("Empty path") {
    Path p0;
    auto pair = p0.Split();
    REQUIRE(pair.first.empty());
    REQUIRE (pair.second.empty());
  }

  SECTION("Leading slash remains with 2 parts") {
    auto p0 = Path(PathImpl::kPathSeparator() + kPrefix).Join(kSuffix);
    auto pair = p0.Split();
    REQUIRE(pair.first == PathImpl::kPathSeparator() + kPrefix);
    REQUIRE(pair.second == kSuffix);
  }

  SECTION("Leading slash splits with one part") {
    Path p0(PathImpl::kPathSeparator() + kPrefix);
    auto pair = p0.Split();
    REQUIRE(pair.first == PathImpl::kPathSeparator());
    REQUIRE(pair.second == kPrefix);
  }

  SECTION("Double slash") {
    Path p0(kPrefix + PathImpl::kPathSeparator() + PathImpl::kPathSeparator() +
            kSuffix);
    Path p1(PathImpl::kPathSeparator() + kPrefix + PathImpl::kPathSeparator() +
            PathImpl::kPathSeparator() + kSuffix);
    auto pair0 = p0.Split();
    auto pair1 = p1.Split();

    REQUIRE(pair0.first == kPrefix);
    REQUIRE(pair0.second == kSuffix);
    REQUIRE(pair1.first == PathImpl::kPathSeparator() + kPrefix);
    REQUIRE(pair1.second == kSuffix);
  }
}