// Copyright (c) 2022 Josh Arenson

#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ja { namespace filesystem {
class PathImpl;
class Path {
public:
  Path();
  explicit Path(std::string path);
  Path(const Path &other);
  Path(Path &&other) noexcept;

  ~Path();

  /**
   * Return a normalized absolutized version of this path. On most
   * platforms, this is equivalent to calling the function Normpath() as
   * follows: Normpath(Join(`pwd`, ToString())).
   *
   * NOTE: If `this` is an empty path, this function returns the current
   * working directory.
   *
   * @return A Path object representing `this` path's absolute path.
   */
  Path Abspath() const;

  /**
   * @return A Path of the base name of `this` path. This is the second element
   * of the pair returned by `this` path to the function Split(). Note that the
   * result of this function is different from the Unix basename program; where
   * basename for '/foo/bar/' returns 'bar', the Basename() function returns an
   * empty string ('').
   */
  Path Basename() const;

  /**
   * @return True if `this` refers to an existing path or an open file
   * descriptor. Returns False for broken symbolic links. On some platforms,
   * this function may return False if permission is not granted to execute
   * stat() on the requested file, even if the path physically exists.
   */
  bool Exists() const;

  /**
   * Append `suffix` to `this` intelligently.
   *
   * @param suffix - A string describing the suffix of the path.
   * @return The return value is the
   * concatenation of `this` and suffix with exactly one
   * directory separator following each non-empty part except the last,
   * meaning that the result will only end in a separator if the last part is
   * empty. If `suffix` is an absolute path, this function returns `suffix`.
   */
  Path Join(const std::string &suffix) const;

  /**
   * Normalize a pathname by collapsing redundant separators and up-level
   * references so that A//B, A/B/, A/./B and A/foo/../B all become A/B. This
   * string manipulation may change the meaning of a path that contains
   * symbolic links. On Windows, it converts forward slashes to backward
   * slashes.
   *
   * @return The normalized value of `this` path.
   */
  std::string Normpath() const;

  /**
   * Split `this` path into a pair, (head, tail) where tail is the last
   * pathname component and head is everything leading up to that. The tail part
   * will never contain a slash; if path ends in a slash, tail will be empty. If
   * there is no slash in path, head will be empty. If `this` path is empty,
   * both head and tail are empty. Trailing slashes are stripped from head
   * unless it is the root (one or more slashes only). In all cases, join(head,
   * tail) returns a path to the same location as path (but the strings may
   * differ).
   *
   * @return - A std::pair of strings where `first` is the head and `second` is
   * the tail.
   */
  std::pair<std::string, std::string> Split() const;

  std::string ToString() const;

  Path &operator=(Path other);
  Path &operator+=(const Path &rhs);

protected:
  explicit Path(std::unique_ptr<PathImpl> pimpl);

private:
  std::unique_ptr<PathImpl> pimpl_;
};

/**
 * This is essentially syntactic sugar for Path::Join. It allows chaining
 * multiple joins easily.
 *
 * @param lhs - A Path object representing the left hand side of the assignment
 * @param rhs - A Path object representing the right hand side of the assignment
 * @return Equivalent to lhs.Join(rhs);
 */
Path operator+(Path lhs, const Path &rhs);
}}