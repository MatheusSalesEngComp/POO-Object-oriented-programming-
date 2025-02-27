#pragma once
#include "fn.hpp"

class Student {
private:
    int hour;
    int minute;
    int second;

public:
    Student(int hour = 0, int minute = 0, int second = 0) {
        if (hour < 0 || hour > 23) {
            fn::write("fail: hora invalida");
            this->hour = 0;
        } else {
            this->hour = hour;
        }

        if (minute < 0 || minute > 59) {
            fn::write("fail: minuto invalido");
            this->minute = 0;
        } else {
            this->minute = minute;
        }

        if (second < 0 || second > 59) {
            fn::write("fail: segundo invalido");
            this->second = 0;
        } else {
            this->second = second;
        }
    }

    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    void setHour(int hour) {
        if (hour >= 0 && hour <= 23) {
            this->hour = hour;
        } else {
            fn::write("fail: hora invalida");
        }
    }

    void setMinute(int minute) {
        if (minute >= 0 && minute <= 59) {
            this->minute = minute;
        } else {
            fn::write("fail: minuto invalido");
        }
    }

    void setSecond(int second) {
        if (second >= 0 && second <= 59) {
            this->second = second;
        } else {
            fn::write("fail: segundo invalido");
        }
    }

    void nextSecond() {
        second++;
        if (second > 59) {
            second = 0;
            minute++;
            if (minute > 59) {
                minute = 0;
                hour++;
                if (hour > 23) {
                    hour = 0;
                }
            }
        }
    }

    void show() const {
        std::cout << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << minute << ":"
                  << std::setw(2) << std::setfill('0') << second << std::endl;
    }
};
