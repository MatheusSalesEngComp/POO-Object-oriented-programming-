#pragma once
#include "fn.hpp"

struct Time{
   // Time(): 
};

class Student {
private:
    Time time;
    int hour;
    int minute;
    int second;
public:
    Student(int hour = 0, int minute = 0, int second = 0) {
        (void) hour;
        (void) minute;
        (void) second;
        // this->time = Time(hour, minute, second);
    }

    void setHour(int hour) {
        (void) hour;
        // this->time.setHour(hour);
    }

    void setMinute(int minute) {
        (void) minute;
        // this->time.setMinute(minute);
    }
    void setSecond(int second) {
        (void) second;
        // this->time.setSecond(second);
    }

    void nextSecond() {
        // this->time.nextSecond();
    }
    
    void show() {
        // fn::write(time);
    }
};