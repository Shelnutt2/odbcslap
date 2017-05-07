//
// Created by Seth Shelnutt on 5/7/17.
//

#ifndef PROJECT_TIMER_HPP
#define PROJECT_TIMER_HPP

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    ~Timer(){};
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

#endif //PROJECT_TIMER_HPP
