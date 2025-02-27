#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <utility>
#include <sstream>

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

    void setCarga(int novaCarga) {
        if (novaCarga >= this->carga) {
            this->carga = 0;
        } else {
            this->carga = novaCarga;
        }
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
        cout << "(" + to_string(getCarga()) + "/" + to_string(getCapacidade()) + ")" << endl;
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
        cout << "Potência " << getPower() << endl;
    }
};

class Notebook {
private:
    bool ligar;
    shared_ptr<Bateria> bateria;
    shared_ptr<Carregador> carregador;
    int time_use;

public:

    Notebook(): ligar(false), bateria(nullptr), carregador(nullptr), time_use(0) {}

    bool getLigar () const { return ligar; }
    shared_ptr<Bateria> getBateria () const { return bateria; }
    shared_ptr<Carregador> getCarregador () const { return carregador; }

    void set_charger (shared_ptr<Carregador> newCarregador) {
        if (carregador) {
            cout << "fail: carregador já conectado\n";
            return;
        }
        carregador = newCarregador;
    }

    void rm_charger () {
        if (carregador == nullptr) {
            cout << "fail: Sem carregador\n";
            return;
        }
        cout << "Removido " << carregador->getPower() << "W\n";
        carregador = nullptr;
    }

    void set_battery (shared_ptr<Bateria> novaBateria) {
        bateria = novaBateria;
    }

    void rm_battery () {
        if(!bateria) {
            cout << "fail: Sem bateria\n";
            return;
        }
        cout << "Removido " << bateria->getCarga() << "/" << bateria->getCapacidade() << endl;
        bateria->setCapacidade(0);
        bateria->zerarCarga();
        bateria = nullptr;
    }

    void turn_on () {
        if ((bateria && (bateria->getCarga() > 0)) || carregador) {
            this->ligar = true;
            return;
        }
        cout << "fail: não foi possível ligar\n";
    }

    void turn_off () {
        this->ligar = false;
    }

    void use(int time) {
        if (!this->ligar) {
            cout << "fail: desligado\n";
            return;
        }
        if (bateria != nullptr && carregador != nullptr) {
            bateria->aumentoCarga(carregador->getPower()*time);
            time_use += time;
            return;
        }
        if (bateria != nullptr && carregador == nullptr) {
            if (time >= bateria->getCarga()) {
                cout << "fail: descarregou\n";
                time_use += time;
                time = bateria->getCarga();
                bateria->zerarCarga();
                this->ligar = false;
                
            } 
            else {
                bateria->setCarga(bateria->getCarga() - time);
                time_use += time;
            }
            return;
        }
        
        time_use += time;  
        return;
    }

    string show() {
        stringstream ss;
        if (!bateria && !carregador) {
            ss << "Notebook: desligado\n";
            return ss.str();
        }
        ss << "Notebook: " << (getLigar() ? "ligado por " + to_string(time_use) + " min" : "desligado")
           << (carregador ? ", Carregador " + to_string(carregador->getPower()) + "W" : "")
           << (bateria ? ", Bateria " + to_string(bateria->getCarga()) + "/" + to_string(bateria->getCapacidade()) + '\n': "\n");
        return ss.str();
    }

    void mostrar() {
        cout << show();
    }
};


int main() {
    Notebook notebook;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "show") {
            notebook.mostrar();
        }
        else if (cmd == "turn_on") {
            notebook.turn_on();
        }
        else if (cmd == "turn_off") {
            notebook.turn_off();
        }
        else if (cmd == "use") {
            int minutes;
            ss >> minutes;
            notebook.use(minutes);
        }
        else if (cmd == "set_charger") {
            int power;
            ss >> power;
            shared_ptr<Carregador> carregador = make_shared<Carregador>(power);
            notebook.set_charger(carregador);
        }
        else if (cmd == "rm_charger") {
            notebook.rm_charger();
        }
        else if (cmd == "set_battery") {
            int capacity;
            ss >> capacity;
            shared_ptr<Bateria> bateria = make_shared<Bateria>(capacity);
            notebook.set_battery(bateria);
        }
        else if (cmd == "rm_battery") {
            notebook.rm_battery();
        }
        else {
            cout << "fail: comando inválido\n";
        }
    }
}
