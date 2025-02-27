#pragma once
#include "fn.hpp"
#include <iostream>

using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    Person(string name, int age): name(name), age(age){}

    string getName() { return this->name;}
    int getAge() { return this->age; }

    string str() const {
        return fn::format("{}:{}", name, age);
    }
};

ostream& operator<<(ostream &os, const Person& person) {
        return os << person.str();
}

class Motorcycle {
private:
    shared_ptr<Person> person {nullptr};
    int power {1};
    int time {0};

public:

    Motorcycle(int power = 1): power(power) {}

    void insertPerson(shared_ptr<Person> person){
        if (this->person != nullptr) {
            fn::write("fail: busy motorcycle");
            return;
        }
        this->person = person;
    }

    shared_ptr<Person> remove() {
        if (this->person == nullptr) {
            fn::write("fail: empty motorcycle");
            return nullptr;
        }
        auto backup = this->person;
        this->person = nullptr;
        return backup;
    }


    void buyTime(int time) {
        this->time += time;
    }

    void drive(int time) {
        if (this->time == 0) {
            fn::write("fail: buy time first");
            return;
        }
        
        if (this->person == nullptr) {
            fn::write("fail: empty motorcycle");
            return;
        }

        if (this->person->getAge() > 10) {
            fn::write("fail: too old to drive");
            return;
        }

        if (this->time < time) {
            fn::print("fail: time finished after {} minutes\n", this->time);
            this->time = 0;
            return;
        }
        this->time -= time;
    }

    string honk() const {
        auto saida = "P"s;
        for( int i =0; i < (int) this->power; i++) {
            saida += 'e';
        }
        return saida + "m";
    }
    string str() const {
        string name("empty");
        if (this->person != nullptr ){
            name = this->person->str();
        }
        return fn::format ("power:{}, time:{}, person:({})", this->power, this->time, name);
    } 


};
ostream& operator<<(ostream &os, const Motorcycle& motorcycle) {
    return os << motorcycle.str();
}

class Student{

    Motorcycle motorcycle;
public:
    
    Student(int power = 1) {
         this->motorcycle = Motorcycle(power);
    }

    void enter(string name, int age) {
        auto person = make_shared<Person>(name, age);
        motorcycle.insertPerson(person);
    }

    void leave() {
        auto person = motorcycle.remove();
        fn::write(person == nullptr ? "---" : person->str());
    }

    void honk() const {
        fn::write(motorcycle.honk());
    }

    void buy(int time) {
        motorcycle.buyTime(time);
    }

    void drive(int time) {
        motorcycle.drive(time);
    }

    void show() const {
        fn::write(motorcycle);
    }
};