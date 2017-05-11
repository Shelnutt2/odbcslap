//
// Created by seth on 5/10/17.
//

#ifndef PROJECT_DISPLAY_HPP
#define PROJECT_DISPLAY_HPP

#include <curses.h>

#include <cstdlib>
#include <memory>
#include <vector>
#include <string>

namespace ncurses {

    class ColorScheme {
    public:
        ColorScheme(const std::vector<int>& scheme_);
        std::vector<int> scheme;
    };

    class Color {
    public:
        Color(int n);
        ~Color();

    private:
        int n;
    };

    void n_chars(int n, const char *c);
    void n_strings(int n, std::string s);

    void end_line();
    std::string positioned(const std::string& content, uint32_t width, int offset);
    std::string centered(const std::string& content, uint32_t width);
    std::string aligned_right(const std::string& content, uint32_t width);
    std::string aligned_left(const std::string& content, uint32_t width);
    enum class Aligned { right, left, center };

    void printline(const std::string& content, uint32_t width = 0,
                   Aligned alignment = Aligned::left);

    struct Environment {
        Environment();
        ~Environment();
    };
}  // namespace ncurses

#endif //PROJECT_DISPLAY_HPP
