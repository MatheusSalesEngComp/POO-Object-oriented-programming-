#include "fn.hpp"

using namespace std;

class Toalha {
private:
    string cor;
    string tamanho;
    int umidade;

public:
    Toalha(string &cor, string tamanho) : cor(cor), umidade(0) {
        if (tamanho != "P" && tamanho != "M" && tamanho != "G") {
            throw invalid_argument("Tamanho inválido! Deve ser P, M ou G.");
        }
        this->tamanho = tamanho;
    }

    string getCor() const { return cor; }
    string getTamanho() const { return tamanho; }
    int getUmidade() const { return umidade; }

    void setCor(string novaCor) {
        this->cor = novaCor;
    }
    void setTamanho(string novoTamanho) {
        this->tamanho = novoTamanho;
    }
    void setUmidade(int novaUmidade) {
        this->umidade = novaUmidade;
    }

    void Enxugar(int novaUmidade) {
        if (this->tamanho == "P" && ((this->umidade + novaUmidade) >= 10)) {
            this->umidade = 10;
            cout << "toalha encharcada\n";
            return;
        } else if (this->tamanho == "M" && ((this->umidade + novaUmidade) >= 20)) {
            this->umidade = 20;
            cout << "toalha encharcada\n";
            return;
        } else if (this->tamanho == "G" && ((this->umidade + novaUmidade) >= 30)) {
            this->umidade = 30;
            cout << "toalha encharcada\n";
            return;
        }
        this->umidade += novaUmidade;
    }

    void Torcer() {
        this->umidade = 0;
    }

    int pegarMaximoUmidade() {
        if (this->tamanho == "P") return 10;
        if (this->tamanho == "M") return 20;
        if (this->tamanho == "G") return 30;
        return 0;
    }

    bool estaSeca() {
        return getUmidade() == 0;
    }

    string mostrar() const {
        return "Cor: " + getCor() + 
               ", Tamanho: " + getTamanho() + 
               ", Umidade: " + to_string(getUmidade());
    }
};

class Adapter {
private:
    shared_ptr<Toalha> toalha;

public:
    Adapter() : toalha(nullptr) {}

    void criar(const string &cor, const string &tamanho) {
        auto novaToalha = make_shared<Toalha>(const_cast<string&>(cor), tamanho);
        toalha = novaToalha;
    }

    void enxugar(int quantidade) {
        toalha->Enxugar(quantidade);
    }

    void seca() {
        if (toalha->estaSeca()) {
            fn::write("sim");
        } else {
            fn::write("nao");
        }
    }

    void torcer() {
        toalha->Torcer();
    }

    void mostrar() const {
        fn::write(toalha->mostrar());
    }
};

int main() {
    Adapter adapter;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end"    ) { break;                           }
        else if (args[0] == "criar"  ) { adapter.criar(args[1], args[2]); }
        else if (args[0] == "enxugar") { adapter.enxugar(+args[1]);       }
        else if (args[0] == "seca"   ) { adapter.seca();                  }
        else if (args[0] == "torcer" ) { adapter.torcer();                }
        else if (args[0] == "mostrar") { adapter.mostrar();               }
        else                           { fn::write("comando invalido");   }
    }
}
