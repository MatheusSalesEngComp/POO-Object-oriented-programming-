#pragma once
#include "fn.hpp"

struct Car {
    int pass;
    int passMax;
    int gas;
    int gasMax;
    int km;

    Car(): pass(0), passMax(2),  gas(0), gasMax(100), km(0) {}

    void enter () {
        if (pass == passMax) {
            std::cout << "fail: limite de pessoas atingido" << std::endl; 
            return;
        }
        this-> pass++;
    }

    void leave () {
        if (pass == 0) {
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
            return;
        }
        this-> pass--;
    }    

    int fuel (int q) {
        if (gas < gasMax) {
            this-> gas += q;
        }

        if (gas >= gasMax) {
            this-> gas = gasMax;
        }

        return gas;
    }

    void drive (int q) {
        if (pass == 0) {
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
            return;
        }
        
        if (gas == 0) {
            std::cout << "fail: tanque vazio" << std::endl;
            return;
        }

        

        if (gas >= q) {
            this-> km += q;
            this-> gas -= q;
        }

        if (gas < q) {
            this->km += gas;
            std::cout << "fail: tanque vazio apos andar" << " " << gas << " km" << std::endl;
            this->gas = 0;
        }
    } 

    std::string str() {
        return fn::format("pass: {}, gas: {}, km: {}", pass, gas, km);
    }
};


struct Student {
    Car car;
    Student() {
    
    }

    void enter() {
        car.enter();
    }
    void leave() {
        car.leave();
    }
    void fuel(int q) {
        car.fuel(q);
        (void) q;
    }
    void drive(int q) {
        car.drive(q);
        (void) q;
    }
    void show() {
        std::cout << car.str() << std::endl;
    }
};

struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        std::cout << "Debug ativado" << std::endl;
    }
};
