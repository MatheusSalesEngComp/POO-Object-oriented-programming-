#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

class Roupa {
private:
    string tamanho;

public:

    Roupa(): tamanho("") {}

    string getTamanho() { return this->tamanho; }

    void setTamanho (string novoTamanho) {
        if ((novoTamanho != "PP") && (novoTamanho != "P") && 
            (novoTamanho != "M") && (novoTamanho != "G") && 
            (novoTamanho != "GG") && (novoTamanho != "XG")) {
                cout << "Entrada inválida.\n";
        }
        else {
            this->tamanho = novoTamanho;
        }
    }

    string mostrar() {
        std::stringstream ss;
        ss << (getTamanho().empty() ? "None\n" : "Tamanho: " + getTamanho() + "\n" + "Parabens, você comprou uma roupa tamanho " + getTamanho() + "\n") ; 
        return ss.str();
    } 

    void print () {
        cout << mostrar();
    }
};

int main() {
    Roupa roupa;
    string entrada;
    while (true) {
        cout << "Digite seu tamanho de roupa: ";
        cin >> entrada;

        roupa.setTamanho(entrada);

        roupa.print();
    }
    return 0;
}

