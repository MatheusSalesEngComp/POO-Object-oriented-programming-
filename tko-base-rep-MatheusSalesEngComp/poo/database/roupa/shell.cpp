#include "fn.hpp"
#include <memory>
using namespace std;

class Roupa {
private:
    string tamanho;

public:

    Roupa(): tamanho("") {}

    string getTamanho() { return this->tamanho; }

    void size (string novoTamanho) {
        if ((novoTamanho != "PP") && (novoTamanho != "P") && 
            (novoTamanho != "M") && (novoTamanho != "G") && 
            (novoTamanho != "GG") && (novoTamanho != "XG")) {
                cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG\n";
        }
        else {
            this->tamanho = novoTamanho;
        }
    }

    string mostrar() {
        stringstream ss;
        ss << (getTamanho().empty() ? "size: ()\n" : "size: (" + getTamanho() + ")" + "\n"); 
        return ss.str();
    } 

    void show () {
        cout << mostrar();
    }
};

class Adapter {
    Roupa roupa;
public:
    Adapter() {
    }
    void size(const string& size) {
        roupa.size(size);
    }
    void show() {
        roupa.show();
    }
};

int main() {
    Adapter adapter;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")  { break;                         }
        else if (args[0] == "size") { adapter.size(args[1]);         }
        else if (args[0] == "show") { adapter.show();                }
        else                        { fn::write("Comando inválido"); }
    }
}