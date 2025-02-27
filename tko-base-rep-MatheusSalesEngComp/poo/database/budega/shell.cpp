#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
using namespace std;

struct Pessoa {
    string nome;
    Pessoa(string nome): nome(nome) {};
};
class Budega {
    vector<shared_ptr<Pessoa>> caixas;
    list<shared_ptr<Pessoa>> espera;
public:

    Budega(int qtd = 0): caixas(qtd, nullptr) {}
    
    void call(int indice) {
        if (caixas[indice] != nullptr) {
            cout << "fail: caixa ocupado\n";
            return;
        }

        if (espera.empty()) {
            cout << "fail: sem clientes\n";
            return;
        }

        caixas[indice] = espera.front();
        espera.pop_front();       
    }

    void finish(int indice) {
        if (indice > (int)caixas.size()-1){
            cout << "fail: caixa inexistente\n";
            return;
        }
        
        if (caixas[indice] == nullptr){
            cout << "fail: caixa vazio\n";
            return;
        }
        
        caixas[indice] = nullptr;
        
    }
   
    string str() {
        stringstream ss;
        ss << "Caixas: [";
        int i = 0;
        for (auto elem : caixas) {
            ss << (i++ != 0 ? ", " : "");
            if (elem != nullptr) {
                ss << elem->nome;
            } else {
                ss << "-----";
            }
        }
        ss << "]\nEspera: [";

        int n = espera.size();
        int count = 0;
        for (auto elem : espera) {
            ss << elem->nome;
            if (++count < n) ss << ", ";
        }

        ss << "]";
        return ss.str();
    }


    void chegar(shared_ptr<Pessoa> pessoa) {
        espera.push_back(pessoa);  
    }
};



// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "") << f(*it);
    }
    return ss.str();
}

int main() {
    Budega budega;
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
            cout << budega.str() << '\n';
        } 
        else if (cmd == "init") { 
            int qtd_caixas;
            ss >> qtd_caixas;
            budega = Budega(qtd_caixas);
        } 
        else if (cmd == "arrive") { 
            string nome;
            ss >> nome;
            Pessoa pessoa(nome);
            budega.chegar(make_shared<Pessoa> (nome));
        } else if (cmd == "call") { 
            int indice;
            ss >> indice;
            budega.call(indice);
        } 
        else if (cmd == "finish") { 
            int indice;
            ss >> indice;
            budega.finish(indice);
        } 
        else {
            cout << "fail: comando invalido\n";
        }
    }
    return 0;
}
