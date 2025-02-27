#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
int cont=0;
using namespace std;

class Bateria {
private:
    int carga;
    int capacidade;

public:
    
    Bateria(int capacidade = 0): carga(capacidade), capacidade(capacidade) {}

    int getCarga () const { return carga; }
    int getCapacidade () const { return capacidade; }

    void setCapacidade(int novaCapacidade) {
        this->capacidade = novaCapacidade;
    }

    void setCarga (int novaCarga) {
        if (novaCarga > this->carga) {
            this->carga = 0;
            return;
        }
        this->carga -= novaCarga;
    }

    void aumentoCarga (int power) {
        this->carga += power;
        if (this->carga > this->capacidade) {
            this->carga = this->capacidade;
        }
    }

    void zerarCarga() {
        this->carga = 0;
    }

    void mostrar() {
        cout <<  cont << "-    (" + to_string(getCarga()) + "/" + to_string(getCapacidade()) + ")" << endl;
        cont++;
    }
};

class Carregador {
private:
    int power;

public:
    Carregador(int power = 0): power(power) {}

    int getPower () const { return power; }

    void setPower (int newPower) {
        this->power = newPower;
    }

    void mostrar () {
        cout << cont << "-    Potência " << getPower() << endl;
        cont++;
    }
};

class Notebook {
private:
    bool ligar;
    shared_ptr<Bateria> bateria; 
    shared_ptr<Carregador> carregador;

public:

    Notebook(): ligar(false), bateria(nullptr), carregador(nullptr) {}

    bool getLigar () const { return ligar; }
    shared_ptr<Bateria> getBateria () const { return bateria; }
    shared_ptr<Carregador> getCarregador () const { return carregador; }

    void setCarregador (shared_ptr<Carregador> newCarregador) {
        carregador = newCarregador;
    }

    void setBateria (shared_ptr<Bateria> novaBateria) {
        bateria = novaBateria;
    }

    void rmBateria () {
        bateria->setCapacidade(0);
        bateria->zerarCarga();
        bateria = nullptr;
        this->ligar = false;
        cout << cont << "-    Bateria removida\n";
        cont++; 
    }


    void setLigar () {
        if ((bateria && (bateria->getCarga() > 0)) || carregador) {
            this->ligar = true;
            return;
        }
        cout << cont << "-    Sem bateria ou carga\n";
        cont++;
    }

    void setDesligar () {
        this->ligar = false;
        cout << cont << "-    notbook desligado\n";
        cont++;
    }

    void usar (int time) {
        if (this->ligar) {
            if (!carregador) {   
                if (time > bateria->getCarga()) {
                    time = bateria->getCarga();
                    this->ligar = false;    
                }
                else {
                    bateria->setCarga(time);
                }
            }
            else {
                bateria->aumentoCarga(carregador->getPower() * time);
            }    
            cout << cont << "-    Usando por " << time << "\n";
            cont++; 
            
            return;
        }
        cout << cont << "-    Erro: ligue o notebook primeiro\n";
        cont++;
    }

    string print() {
        stringstream ss;
        ss << cont << "-    Status: " << (getLigar() ? "Ligado, " : "Desligado, ") << "Bateria: " + (bateria ? to_string(bateria->getCarga()) + "/" + to_string(bateria->getCapacidade()) + ", " : "Nenhuma, ") << "Carregador: " << (carregador ? "Conectado\n" : "Desconectado\n");
        cont++;
        return ss.str();
    }

    void mostrar() {
        cout << print();
    }

};

int main() {
    Notebook notebook;

    notebook.mostrar();   
    notebook.setLigar();
    notebook.usar(10);
    auto bateria = make_shared<Bateria>(50);
    bateria->mostrar();
    notebook.setBateria(bateria);
    notebook.mostrar();
    notebook.setLigar();
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();   
    notebook.rmBateria();
    bateria->mostrar();
    notebook.mostrar();
    auto carregador = make_shared<Carregador> (2);
    carregador->mostrar();
    notebook.setCarregador(carregador);
    notebook.mostrar();
    notebook.setLigar();
    notebook.mostrar();
    auto bateria2 = make_shared<Bateria> (100);
    notebook.mostrar();
    notebook.setBateria(bateria2);
    notebook.mostrar();

    notebook.usar(10);
    notebook.mostrar();
}

