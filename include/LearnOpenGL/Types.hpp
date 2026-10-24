/*
 Copyright (c) 2026 Viktor Paraj

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <initializer_list>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#if defined(__has_include)
#if __has_include(<format>)
#include <format>
#endif
#endif

/**
 *  @class String Types.h <Types.h>
 *  @brief  Shorthand for std::string with chainable mutators and helpers.
 *
 *  @headerfile Types.h
 */
class String : public std::string {
 public:
  using std::string::basic_string;

  String() = default;
  String(const std::string& s) : std::string(s) {}
  String(std::string&& s) : std::string(std::move(s)) {}
  // Copy/move construction and assignment are implicitly generated and
  // already return String&.

  // --- Assignment -----------------------------------------------------------
  // Deliberately NOT `using std::string::operator=` (returns std::string&).
  template <typename T, typename = std::enable_if_t<
                            !std::is_same_v<std::decay_t<T>, String> &&
                            std::is_assignable_v<std::string&, T&&>>>
  String& operator=(T&& rhs) {
    std::string::operator=(std::forward<T>(rhs));
    return *this;
  }
  String& operator=(std::initializer_list<char> il) {
    std::string::operator=(il);
    return *this;
  }

  // Deliberately NOT `using std::string::operator+=`: a using-declaration
  // brings in non-template overloads that beat this template for most
  // arguments ("x", 'c', std::string) and return std::string&.
  template <typename T, typename = decltype(std::declval<std::string&>() +=
                                            std::declval<const T&>())>
  String& operator+=(const T& rhs) {
    std::string::operator+=(rhs);
    return *this;
  }
  String& operator+=(std::initializer_list<char> il) {
    std::string::operator+=(il);
    return *this;
  }

  // --- Chaining mutators ----------------------------------------------------
  // For each chaining member: if the base version returns std::string&,
  // return *this as String&. Otherwise (iterator overloads, etc.) pass the
  // result through unchanged.
#define MYPROJ_STRING_CHAIN(name)                                       \
  template <typename... Args>                                           \
  decltype(auto) name(Args&&... args) {                                 \
    using R = decltype(std::string::name(std::forward<Args>(args)...)); \
    if constexpr (std::is_same_v<R, std::string&>) {                    \
      std::string::name(std::forward<Args>(args)...);                   \
      return static_cast<String&>(*this);                               \
    } else {                                                            \
      return std::string::name(std::forward<Args>(args)...);            \
    }                                                                   \
  }

  MYPROJ_STRING_CHAIN(append)
  MYPROJ_STRING_CHAIN(assign)
  MYPROJ_STRING_CHAIN(insert)
  MYPROJ_STRING_CHAIN(erase)
  MYPROJ_STRING_CHAIN(replace)

#undef MYPROJ_STRING_CHAIN

  // A braced list can't be deduced by the variadic templates above.
  String& append(std::initializer_list<char> il) {
    std::string::append(il);
    return *this;
  }
  String& assign(std::initializer_list<char> il) {
    std::string::assign(il);
    return *this;
  }

  String substr(size_type pos = 0, size_type n = npos) const {
    return String(std::string::substr(pos, n));
  }

  // --- Helpers (non-mutating, return String so they chain) ------------------
  static constexpr const char* kWhitespace = " \t\n\r\f\v";

  String ltrim() const {
    const auto i = find_first_not_of(kWhitespace);
    return i == npos ? String() : substr(i);
  }
  String rtrim() const {
    const auto i = find_last_not_of(kWhitespace);
    return i == npos ? String() : substr(0, i + 1);
  }
  String trim() const { return ltrim().rtrim(); }

  /// ASCII-only case conversion.
  String to_lower() const {
    String r(*this);
    for (char& c : r)
      c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return r;
  }
  String to_upper() const {
    String r(*this);
    for (char& c : r)
      c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return r;
  }

  /// Split on a (possibly multi-char) delimiter. An empty delimiter yields the
  /// whole string as one piece.
  std::vector<String> split(std::string_view delim,
                            bool keep_empty = true) const {
    std::vector<String> out;
    if (delim.empty()) {
      if (keep_empty || !empty()) out.push_back(*this);
      return out;
    }
    size_type pos = 0;
    for (;;) {
      const size_type next = find(delim, pos);
      String piece = substr(pos, next == npos ? npos : next - pos);
      if (keep_empty || !piece.empty()) out.push_back(std::move(piece));
      if (next == npos) break;
      pos = next + delim.size();
    }
    return out;
  }
  std::vector<String> split(char delim, bool keep_empty = true) const {
    return split(std::string_view(&delim, 1), keep_empty);
  }

  template <typename Range>
  static String join(const Range& parts, std::string_view sep) {
    String r;
    bool first = true;
    for (const auto& p : parts) {
      if (!first) r.append(sep);
      first = false;
      r.append(p);
    }
    return r;
  }

  // Pre-C++20 / pre-C++23 fallbacks; std::string provides these otherwise.
#ifndef __cpp_lib_starts_ends_with
  bool starts_with(std::string_view p) const noexcept {
    return size() >= p.size() && compare(0, p.size(), p) == 0;
  }
  bool starts_with(char c) const noexcept { return !empty() && front() == c; }
  bool starts_with(const char* p) const {
    return starts_with(std::string_view(p));
  }
  bool ends_with(std::string_view p) const noexcept {
    return size() >= p.size() && compare(size() - p.size(), p.size(), p) == 0;
  }
  bool ends_with(char c) const noexcept { return !empty() && back() == c; }
  bool ends_with(const char* p) const { return ends_with(std::string_view(p)); }
#endif
#ifndef __cpp_lib_string_contains
  bool contains(std::string_view p) const noexcept { return find(p) != npos; }
  bool contains(char c) const noexcept { return find(c) != npos; }
  bool contains(const char* p) const { return find(p) != npos; }
#endif

  /// printf-style formatting (works in any language mode).
#if defined(__GNUC__) || defined(__clang__)
  __attribute__((format(printf, 1, 2)))
#endif
  static String format(const char* fmt, ...) {
    va_list ap, ap2;
    va_start(ap, fmt);
    va_copy(ap2, ap);
    const int n = std::vsnprintf(nullptr, 0, fmt, ap);
    va_end(ap);
    String r;
    if (n > 0) {
      r.resize(static_cast<size_type>(n));
      std::vsnprintf(r.data(), static_cast<size_t>(n) + 1, fmt, ap2);
    }
    va_end(ap2);
    return r;
  }

#ifdef __cpp_lib_format
  /// std::format wrapper (C++20 with <format>).
  template <typename... Args>
  static String fmt(std::format_string<Args...> f, Args&&... args) {
    return String(std::format(f, std::forward<Args>(args)...));
  }
#endif

  // --- operator+ ------------------------------------------------------------
  friend String operator+(String a, const String& b) {
    a += b;
    return a;
  }
  friend String operator+(String a, std::string b) {
    a += b;
    return a;
  }
  friend String operator+(std::string a, const String& b) {
    String r(std::move(a));
    r += b;
    return r;
  }
  friend String operator+(String a, const char* b) {
    a += b;
    return a;
  }
  friend String operator+(const char* a, const String& b) {
    String r(a);
    r += b;
    return r;
  }
  // Templates constrained to exactly `char` so that ints (and other types that
  // convert implicitly to char) do not become addable.
  template <typename C, typename = std::enable_if_t<std::is_same_v<C, char>>>
  friend String operator+(String a, C b) {
    a += b;
    return a;
  }
  template <typename C, typename = std::enable_if_t<std::is_same_v<C, char>>>
  friend String operator+(C a, const String& b) {
    String r(1, a);
    r += b;
    return r;
  }
};

namespace std {
template <>
struct hash<String> : hash<string> {};
}  // namespace std
