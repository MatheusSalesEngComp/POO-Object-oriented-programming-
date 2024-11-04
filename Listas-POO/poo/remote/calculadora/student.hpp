#pragma once
#include "fn.hpp"
struct Calculator{
    int battery;
    int batteryMax;
    float display;

    Calculator(int batteryMax = 0): battery(0), batteryMax(batteryMax), display(0.0f){}
    

    void charge(int value) {
        this->battery += value;
        if ((this->battery) > (this->batteryMax)) {
            this->battery = this->batteryMax;
        }

    }

    void sum(int a, int b) {
        if (this->battery == 0) {
            std::cout << "fail: bateria insuficiente" << std::endl;
            return;
        }

        this->display = a+b;
        this->battery--;
    }

    void div(float num, float den) {
        if (this->battery == 0) {
            std::cout << "fail: bateria insuficiente" << std::endl;
            return;
        }
        if (den == 0) {
            std::cout << "fail: divisao por zero" << std::endl;
            this->battery--;
            return;
        }

        this->display = num / den;
        this->battery--;
    }

    std::string str(){
        return fn::format("display = {%.2f}, battery = {}",display, battery);
    }
};
class Student {
    Calculator c;
public:
    Student() {
        c = Calculator(0);
    }
    void show() {
        std::cout << c.str() << std::endl;
    }
    void init(int batteryMax) {
        c = Calculator(batteryMax);
        (void) batteryMax;
    }
    void charge(int value) {
        c.charge(value);
        // // ACT!
        (void) value;
    }
    void sum(int a, int b) {
        c.sum(a, b);
        // // ACT!
        (void) a;
        (void) b;
    }
    void div(float num, float den) {
        c.div(num, den);
        // // ACT!
        (void) num;
        (void) den;
    }
};
