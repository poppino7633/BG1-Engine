#include "include/log.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier bright_red(Color::FG_BRIGHT_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier bright_green(Color::FG_BRIGHT_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier bright_yellow(Color::FG_BRIGHT_YELLOW);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier bright_blue(Color::FG_BRIGHT_BLUE);
Color::Modifier white(Color::FG_WHITE);
Color::Modifier bright_white(Color::FG_BRIGHT_WHITE);
Color::Modifier def(Color::FG_DEFAULT);

void console::success(std::string message) {
  std::cout << bright_green << "SUCCESS: " << green << message << def
            << std::endl;
}

void console::info(std::string message) {
  std::cout << bright_white << "INFO: " << white << message << def << std::endl;
}

void console::warning(std::string message) {
  std::cout << bright_yellow << "WARNING: " << yellow << message << def
            << std::endl;
}

void console::error(std::string message) {
  std::cout << bright_red << "ERROR: " << red << message << def << std::endl;
}


void console::success(const IPrintable &message) {
  success(message.toString());
}

void console::info(const IPrintable &message) { info(message.toString()); }

void console::warning(const IPrintable &message) {
  warning(message.toString());
}

void console::error(const IPrintable &message) { error(message.toString()); }
