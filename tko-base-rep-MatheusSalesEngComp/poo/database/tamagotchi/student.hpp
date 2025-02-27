#include <iostream>
#include <string>
#include<memory>
#include "fn.hpp"

using namespace std;
class Pet {
private:
    int energyMax; 
    int hungryMax;
    int cleanMax;  
    int energy;
    int hungry;        
    int clean;     
    int age;       
    bool alive;    

public:
    Pet(int energyMax = 0, int hungryMax = 0, int cleanMax = 0)
        : energyMax(energyMax), hungryMax(hungryMax), cleanMax(cleanMax), energy(energyMax), hungry(hungryMax), clean(cleanMax), age(0), alive(true) {}

    int getMaxEnergy () {return this->energyMax;}
    int getMaxHungry () {return this->hungryMax;}
    int getMaxClean () {return this->cleanMax;}
    int getEnergy () {return this->energy;}
    int getHungry () {return this->hungry;}
    int getClean () {return this->clean;}
    int getAge () {return this->age;}
    bool getAlive () {return this->alive;}


    void setEnergy (int newEnergy) {
        if ((newEnergy + energy) <= 0) {
            energy = 0;
            cout << "fail: pet morreu de fraqueza\n";
            this->alive = false;
        }
        else if ((newEnergy + energy) > this->energyMax) {energy = this->energyMax;}
        else {this->energy += newEnergy;}
    }

    void setHungry (int newHungry) {
        if ((newHungry + hungry) <= 0) {
            hungry = 0;
            cout << "fail: pet morreu de fome\n";
            this->alive = false;
        }
        else if ((newHungry + hungry) > this->hungryMax) {hungry = this->hungryMax;}
        else {this->hungry += newHungry;}
    }

    void setClean (int newClean) {
        if ((newClean + clean) <= 0) {
            clean = 0; this->alive = false;
            cout << "fail: pet morreu de sujeira\n";
        }
        else if ((newClean + clean) > this->cleanMax) {clean = this->cleanMax;}
        else {this->clean += newClean;}
    }

    void setAge (int newAge) {
        this->age += newAge;
    }
    

    string str () {
        return fn::format("E:{}/{}, S:{}/{}, L:{}/{}", getEnergy(), energyMax, getHungry(), hungryMax, getClean(), cleanMax);
    }  
};
class Game {
private:
    int diamond;
    shared_ptr<Pet> pet;

public:
    Game(int energyMax = 0, int hungryMax = 0, int cleanMax = 0)
        : diamond(0), pet(make_shared<Pet>(energyMax, hungryMax, cleanMax)) {}

    int getDiamond () {return diamond;}

    void setDiamond (int newDiamond) {
        this->diamond = newDiamond;
    } 

    void play () {
        if(pet->getAlive() == false){cout << "fail: pet esta morto\n";}
        else{
            pet->setEnergy(-2);
            pet->setHungry(-1);
            pet->setClean(-3);
            this->diamond += 1;
            pet->setAge(1);
        }
        
    }
    
    void eat () {
        if(pet->getAlive() == false){cout << "fail: pet esta morto\n";}
        else{
            pet->setEnergy(-1);
            pet->setHungry(4);
            pet->setClean(-2);
            pet->setAge(1);
        }
    }

    void sleep () {
        if(pet->getAlive() == false){
            cout << "fail: pet esta morto\n";
            return;
        }
        int verification = pet->getMaxEnergy() - pet->getEnergy();
        
        if (verification >= 5){
            pet->setEnergy(pet->getMaxEnergy());
            pet->setHungry(-1);
            pet->setAge(verification);
        }       
        else { 
            cout << "fail: nao esta com sono\n";
        }
    }

    void shower () {
        if(pet->getAlive() == false){
            cout << "fail: pet esta morto\n";
            return;
        }
        pet->setEnergy(-3);
        pet->setHungry(-1);
        pet->setClean(pet->getMaxClean());
        pet->setAge(2);
    }
    
    string str() {
        return fn::format("{}, D:{}, I:{}", pet->str(), diamond, pet->getAge());
    }
};
class Student {
private:
    Game game; 
    
public:
    Student(int energy, int hungry, int clean) {
        (void)energy;
        (void)hungry;
        (void)clean;
        this->game = Game(energy, hungry, clean);
    }

    void show() {
        std::cout << this->game.str() << std::endl;
    }

    void play() {
        this->game.play();
    }

    void shower() {
        this->game.shower();
    }

    void eat() {
        this->game.eat();
    }

    void sleep() {
        this->game.sleep();
    }
};
