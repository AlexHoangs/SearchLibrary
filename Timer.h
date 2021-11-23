//
// Created by ALEX on 10/5/2021.
//

#ifndef SEARCHNEWBOOKS_TIMER_H
#define SEARCHNEWBOOKS_TIMER_H

#include <iostream>
#include <chrono>

class Timer {

public:

    //initialize objects for the timer
    std::chrono::high_resolution_clock::time_point start, end;

    // reset the timer as per the spec sheet
    void Reset()
    {
        start = end = {};
    }

    // print the timer as per the spec sheet
    void CurrentTime() {
        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        std::cout << "CPU time: " << elapsed_us << " microseconds" << std::endl;
    }

    // start the timer in constructor
    // currenttime() and now() is the same thing
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    // stop timer and find current time in destructor
    // destructor is used when the timer function has ended
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        // point to current time and run the function to find the amount of time elapsed
        this->CurrentTime();
    }
};


#endif //SEARCHNEWBOOKS_TIMER_H
