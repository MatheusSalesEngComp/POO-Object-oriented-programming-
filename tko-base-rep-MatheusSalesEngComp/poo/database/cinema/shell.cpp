#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

class Cliente{
private:
    string id;
    string phone;
public:
    Cliente(string id ="", string phone = 0): id(id), phone(phone) {}

    string getId(){return id;}
    string getPhone(){return phone;}

    void setId(string id){this->id = id;}
    void setPhone(string phone){this->phone = phone;}

    string str(){
        stringstream ss;
        ss << id << ":" << phone;
        return ss.str();
    }

};

class Cinema {
private:
    vector<shared_ptr<Cliente>> clientes;
    vector<string> cadeiras;
    bool ocupado;
public:
    Cinema(int qtd = 0): cadeiras(qtd, "-") ,ocupado(false){}

    bool reservar(string id, string phone, int index){
        if(index < 0 || index >= (int) cadeiras.size()){
            cout << "fail: cadeira nao existe" << endl;
            return false;
        }
        if(cadeiras[index] != "-"){
            cout << "fail: cadeira ja esta ocupada" << endl;
            return false;
        }
        for(size_t i = 0; i < clientes.size() ; i++) {  
            if(clientes[i]->getId() == id){
                cout << "fail: cliente ja esta no cinema" << endl;
                return false;
            }
        }
        clientes.emplace_back(make_shared<Cliente>(id, phone));
        cadeiras[index] = clientes.back()->str();

        return true;
    }

    void cancel(string id){
        
        string phone = "";
        for (auto cliente : clientes) {
            if (cliente->getId() == id) {
                phone = cliente->getPhone();
                break;
            }
        }
        string aux = id + ":" + phone;

        int index = 0;
        for(size_t i = 0; i < cadeiras.size(); i++){
            if(cadeiras[i] == aux){
                index = 1;
                cadeiras[i] = "-";
                for(int j = 0; j < (int) clientes.size(); j++){
                    if(clientes[j]->getId() == id){
                        clientes.erase(clientes.begin() + j);
                    }
                }
            }
        }
        if (index == 0) {
            cout << "fail: cliente nao esta no cinema" << endl;
        }
    }


    string show() {
        stringstream ss;

        ss << "[";
        for (size_t i = 0; i < cadeiras.size(); i++) {
            if (i > 0) {
                ss << " "; 
            }
            ss << cadeiras[i];
        }
        ss << "]";
        return ss.str();
    }
};

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

int main() {
    Cinema  cinema;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;    
        } else if (cmd == "show") {
            cout << cinema.show() << endl;
        } else if (cmd == "init") {
            int qtd;
            ss >> qtd;
            cinema = Cinema(qtd);
        } else if (cmd == "reserve") {
            string id; 
            string phone;
            int index;
            ss >> id >> phone >> index;
            cinema.reservar(id, phone, index);
        } else if (cmd == "cancel") {
            string id;
            ss >> id;
            cinema.cancel(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}
