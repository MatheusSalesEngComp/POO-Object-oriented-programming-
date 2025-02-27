#include <iostream>
#include <vector>
using namespace std;

class Teste {
private:
    vector<int> vetor; // Vetor dinâmico, que pode ter tamanho variável
public:
    Teste(int x = 0): vetor(x) {}  // Inicializa o vetor com o tamanho x
    void print() const {
        cout << "Teste(" << vetor << ")" << endl;
        cout << "Tamanho do vetor: " << vetor.size() << endl;
    }
};

int main() {
    Teste teste(5);  // Teste com vetor de tamanho 5
    teste.print();    // Deve imprimir "Teste(5)" e "Tamanho do vetor: 5"
    cout << "qxcode\n";
}
