//
// Created by seth on 5/10/17.
//

#include <display.hpp>
#include <locale.h>

ncurses::ColorScheme::ColorScheme(const std::vector<int> &scheme_) : scheme(scheme_) {
  start_color();
  int index = 0;
  for (const auto &color : scheme) {
    init_pair(index++, COLOR_BLACK, color);
  }
}

ncurses::Color::Color(int n) {
  attron(COLOR_PAIR(n));
  attron(A_BOLD);
}

ncurses::Color::~Color() {
  attroff(COLOR_PAIR(n));
  attroff(A_BOLD);
}


void ncurses::n_chars(int n, const char *c) {
  std::string s(c, n);
  addstr(s.c_str());
}

void ncurses::n_strings(int n, std::string s) {
  while (n-- > 0) {
    addstr(s.c_str());
  }
}

void ncurses::end_line() { addch('\n'); }

std::string ncurses::positioned(const std::string &content, uint32_t width, int offset) {
  if (content.length() >= width) {
    return content;
  } else {
    auto left = std::string(offset, ' ');
    auto right = std::string(width - (content.length() + offset), ' ');
    auto line = left + content + right;
    return line;
  }
}

std::string ncurses::centered(const std::string &content, uint32_t width) {
  auto offset = (width - content.length()) / 2;
  return positioned(content, width, offset);
}

std::string ncurses::aligned_right(const std::string &content, uint32_t width) {
  auto offset = width - content.length();
  return positioned(content, width, offset);
}

std::string ncurses::aligned_left(const std::string &content, uint32_t width) {
  return positioned(content, width, 0);
}

void ncurses::printline(const std::string &content, uint32_t width,
                        Aligned alignment) {
  std::string s;
  switch (alignment) {
    case Aligned::right: {
      s = aligned_right(content, width);
      break;
    }
    case Aligned::left: {
      s = aligned_left(content, width);
      break;
    }
    case Aligned::center: {
      s = centered(content, width);
      break;
    }
  }
  addstr(s.c_str());
}


ncurses::Environment::Environment() {
  initscr();
  setlocale(LC_ALL, "");
  cbreak();
  noecho();
  keypad(stdscr, true);
}

ncurses::Environment::~Environment() { endwin(); }
