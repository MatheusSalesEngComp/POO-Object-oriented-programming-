#include <iostream>
#include <sstream>

class Chinela {
private:
    int tamanho;

public:
    Chinela() : tamanho(0) {}

    int getTamanho() const { return tamanho; }

    void setTamanho(int valor) {
        if ((valor < 20) || (valor > 50)) {
            std::cout << "Erro! Tamanho inválido.\n";
        } else {
            this->tamanho = valor;
        }
    }

    std::string printarTela() const {
        std::stringstream ss;
        ss << "Número: " << getTamanho() << "\n";
        return ss.str();
    }

    void mostrar() const {
        std::cout << printarTela() << "\n";
    }
};

int main() {
    Chinela chinela;
    int veri;

    while (true) {
        std::cout << "Tamanho: ";
        std::cin >> veri;

        chinela.setTamanho(veri);

        if (chinela.getTamanho() == 0) {
            break;
        }

        chinela.mostrar();
    }

    return 0;
}
