#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Espiral {
private:
    string nome;
    int qnt;
    float preco;

public:
    Espiral(string nome = "", int qnt = 0, float preco = 0) : nome(nome), qnt(qnt), preco(preco) {}

    string getNome() const {
        return nome;
    }   
    
    int getQnt() const {
        return qnt;
    }

    float getPreco() const {
        return preco;
    }   

    void setNome(string nome) {this->nome = nome;}
    void setQnt(int qnt) {this->qnt = qnt;}
    void setPreco(float preco) {this->preco = preco;}

     string str() {
        stringstream ss;
        ss << "[" 
           << setw(8) << setfill(' ') << nome 
           << " : " << qnt << " U : " 
           << fixed << setprecision(2) << preco
           << " RS]";
        return ss.str();
    }

};

class Maquina {
private:
    vector<Espiral> espirais;
    float saldo;
    float lucro;
public: 
    Maquina(int n_espirais = 0)
        : espirais(n_espirais, Espiral("empty", 0, 0)), saldo(0), lucro(0) {}

    void setEspirais(int index, string nome, int qnt, float preco) {
        if (index < 0 || (size_t)index >= espirais.size()) {
            cout << "fail: indice nao existe\n";
            return;
        }
        espirais[index] = Espiral(nome, qnt, preco);
    }

    void setSaldo(float saldo) {
        this->saldo += saldo;
    }

    void setLucro(float lucro) {
        this->lucro = lucro;
    }

    void limpar(int index) {
        if (index < 0 || (size_t)index >= espirais.size()) {
            cout << "Indice invalido";
            return;
        }
        espirais[index].setNome("empty");
        espirais[index].setQnt(0);
        espirais[index].setPreco(0);
    }

    void comprar(int index) {
        if (index < 0 || (size_t)index >= espirais.size()) {
            cout << "fail: indice nao existe\n";
            return;
        }
        if (espirais[index].getQnt() == 0) {
            cout << "fail: espiral sem produtos\n";
            return;
        }
        if (saldo < espirais[index].getPreco()) {
            cout << "fail: saldo insuficiente\n";
            return;
        }
        cout << "voce comprou um " << espirais[index].getNome() << endl;
        saldo -= espirais[index].getPreco();
        lucro += espirais[index].getPreco();
        espirais[index].setQnt(espirais[index].getQnt() - 1);
    }

    void troco() {
        cout << "voce recebeu " << fixed << setprecision(2) << saldo << " RS\n" ;
        saldo = 0;
    }

    string str() {
        stringstream ss;
        ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
        for (size_t i = 0; i < espirais.size(); i++) {
            ss << i << " " << espirais[i].str() << endl;
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }
};    

template<typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}


int main() {
    Maquina maquina;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try {
            if (cmd == "show") {
                cout << maquina.str() << endl;
            } else if (cmd == "init") {
                int n_espirais {};
                ss >> n_espirais;
                maquina = Maquina(n_espirais);
            } else if (cmd == "limpar") {
                int indice {};
                ss >> indice;
                maquina.limpar(indice);
            } else if (cmd == "dinheiro") {
                int value {};
                ss >> value;
                maquina.setSaldo(value);
            } else if (cmd == "comprar") {
                int index {};
                ss >> index;
                maquina.comprar(index);
            } else if (cmd == "set") {
                int index {};
                string name;
                int qtd {};
                double price {};
                ss >> index >> name >> qtd >> price;
                maquina.setEspirais(index, name, qtd, price);
            } else if (cmd == "troco") {
                maquina.troco();
            } else if (cmd == "end") {
                break;
            } else {
                cout << "comando invalido" << endl;
            }
        } catch (const char* e) {
            cout << e << endl;
        }
    }
    return 0;
}
