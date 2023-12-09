#pragma once
#include <iostream>
#include <string>
#include <ostream>

class IPrintable {
public:
  virtual std::string toString() const = 0;
};

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_WHITE    = 37,
        FG_DEFAULT  = 39,
        FG_BRIGHT_RED = 91,
        FG_BRIGHT_GREEN = 92,
        FG_BRIGHT_YELLOW = 93,
        FG_BRIGHT_BLUE = 94,
        FG_BRIGHT_WHITE = 97,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

namespace console {
  void success(std::string message);
  void info(std::string message);
  void warning(std::string message);
  void error(std::string message);

  void fatal(std::runtime_error error);

  void success(const IPrintable& message);
  void info(const IPrintable& message);
  void warning(const IPrintable& message);
  void error(const IPrintable& message);
};
