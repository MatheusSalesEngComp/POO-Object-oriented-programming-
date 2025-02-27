#pragma once
#include "fn.hpp"
using namespace std;
struct Animal { 
    string especie;
    string barulho;
    int idade;

    
    Animal(string especie, string barulho): especie(especie), barulho(barulho), idade(0)  {}

    string fazerBarulho() {
        if (this->idade == 0) {
            return "---"; 
        } else if (this->idade == 4) {
            return "RIP"; 
        }
        return barulho;
    }


    void envelhecer(int add) {
        if (this->idade >= 4) {
            cout << "warning: " << especie << " morreu" << endl;
            return;
        }

        idade += add;
        if (this->idade > 4) {
            this->idade = 4;
        }

        if (idade == 4) {
            cout << "warning: " << especie << " morreu" << endl;
        }
    }


    string str() {
        return fn::format("{}:{}:{}", especie, idade, barulho);
    }

    
};

struct Student {
    Animal animal;

    Student(string especie = "", string barulho = "") : animal(especie, barulho) {}

    void grow(int nivel) {
        animal.envelhecer(nivel);
    }

    void noise() {
        cout << animal.fazerBarulho() << endl;
    }

    void show() {
        cout << animal.str() << endl;
    }
};


struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        cout << "Debug ativado" << endl;
    }
};
