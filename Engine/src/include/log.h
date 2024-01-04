#pragma once
#include <iostream>
#include <ostream>
#include <string>

class IPrintable {
public:
  virtual std::string toString() const = 0;
};

namespace Color {
enum Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_WHITE = 37,
  FG_DEFAULT = 39,
  FG_BRIGHT_RED = 91,
  FG_BRIGHT_GREEN = 92,
  FG_BRIGHT_YELLOW = 93,
  FG_BRIGHT_BLUE = 94,
  FG_BRIGHT_WHITE = 97,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_BLUE = 44,
  BG_DEFAULT = 49
};
class Modifier {
  Code code;

public:
  Modifier(Code pCode) : code(pCode) {}
  friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
    return os << "\033[" << mod.code << "m";
  }
};
} // namespace Color

namespace console {
void success(std::string message);
void info(std::string message);
void warning(std::string message);
void error(std::string message);

template<typename T>
void fatal(std::string message) {
  Color::Modifier def(Color::FG_DEFAULT);
  std::cout << def;
  throw T(message);
};

void success(const IPrintable &message);
void info(const IPrintable &message);
void warning(const IPrintable &message);
void error(const IPrintable &message);
}; // namespace console
