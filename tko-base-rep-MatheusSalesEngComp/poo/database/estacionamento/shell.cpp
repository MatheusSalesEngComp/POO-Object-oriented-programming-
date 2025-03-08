#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iomanip>

using namespace std;

class Veiculo {
protected:
    string id;
    string tipo;
    int entrada;

public:
    Veiculo(string id="", string tipo="") : id(id), tipo(tipo), entrada(0) {}
    virtual ~Veiculo() {}

    int getEntrada() const { return entrada; }
    string getId() const { return id; }
    string getTipo() const { return tipo; }

    void setEntrada(int entrada) {
        this->entrada = entrada;
    }

    virtual double calcularValor(int horaSaida) const = 0;

    virtual string toString() const {
        stringstream ss;
        ss << setw(10) << setfill('_') << tipo << " : "
           << setw(10) << setfill('_') << id << " : "
           << entrada;
        return ss.str();
    }
};

class Bicicleta : public Veiculo {
public:
    Bicicleta(string id="") : Veiculo(id, "Bike") {}

    double calcularValor(int tempo) const override {
        (void) tempo;
        return 3;
    }
};

class Carro : public Veiculo {
public:
    Carro(string id="") : Veiculo(id, "Carro") {}

    double calcularValor(int tempo) const override {
        return tempo / 10 < 5 ? 5 : tempo / 10;
    }
};

class Moto : public Veiculo {
public:
    Moto(string id="") : Veiculo(id, "Moto") {}

    double calcularValor(int tempo) const override {
        return tempo / 20;
    }
};

class Estacionamento {
private:
    vector<shared_ptr<Veiculo>> veiculos;
    int horaAtual;

public:
    Estacionamento() : horaAtual(0) {}

    void adicionarVeiculo(shared_ptr<Veiculo> veiculo) {
        veiculo->setEntrada(horaAtual);
        veiculos.push_back(veiculo);
    }

    void removerVeiculo(const string& id) {
        for (auto it = veiculos.begin(); it != veiculos.end(); ++it) {
            if ((*it)->getId() == id) {
                veiculos.erase(it);
                break;
            }
        }
    }
    shared_ptr<Veiculo> procurarVeiculo(const string& id) const {
        for (const auto& veiculo : veiculos) {
            if (veiculo->getId() == id) {
                return veiculo;
            }
        }
        return nullptr;
    }
    
    void Pagar(string id){
        shared_ptr<Veiculo> veiculo = procurarVeiculo(id);
            
            if (veiculo) {
                double valor = calcularValor(id, getHoraAtual());
                cout << fixed << setprecision(2)
                    << veiculo->getTipo() << " chegou " << veiculo->getEntrada() 
                    << " saiu " << getHoraAtual() 
                    << ". Pagar R$ " << valor << endl;
                removerVeiculo(id);
            } else {
                cout << "fail: veículo não encontrado" << endl;
            }
    }

    double calcularValor(const string& id, int horaSaida) const {
        for (const auto& veiculo : veiculos) {
            if (veiculo->getId() == id) {
                return veiculo->calcularValor(horaSaida - veiculo->getEntrada());
            }
        }
        return 0.0;
    }

    void mostrarVeiculos() const {
        for (const auto& veiculo : veiculos) {
            cout << veiculo->toString() << endl;
        }
        cout << "Hora atual: " << horaAtual << endl;
    }

    void setHoraAtual(int hora) {
        horaAtual += hora;
    }

    int getHoraAtual() const {
        return horaAtual;
    }
};

int main() {
    Estacionamento estacionamento;
    
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            estacionamento.mostrarVeiculos();
        } else if (cmd == "estacionar") {
            string tipo, id;
            ss >> tipo >> id;
            if (tipo == "carro") {
                estacionamento.adicionarVeiculo(make_shared<Carro>(id));
            } else if (tipo == "moto") {
                estacionamento.adicionarVeiculo(make_shared<Moto>(id));
            } else if (tipo == "bike") {
                estacionamento.adicionarVeiculo(make_shared<Bicicleta>(id));
            }
        } else if (cmd == "tempo") {
            int tempo;
            ss >> tempo;
            estacionamento.setHoraAtual(tempo);
        } else if (cmd == "pagar") {
            string id;
            ss >> id;
            estacionamento.Pagar(id);
        }
        else {
            cout << "fail: comando inválido" << endl;
        }
    }
}
