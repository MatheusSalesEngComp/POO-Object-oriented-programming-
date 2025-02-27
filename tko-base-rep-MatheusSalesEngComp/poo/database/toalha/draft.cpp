#include <iostream>
#include <sstream>
#include <memory>

class Toalha{
private: 
    std::string cor;
    char tamanho;
    int umidade;

    int getLimite () const {
        if (this->tamanho == 'P') { return 10; }
        if (this->tamanho == 'M') { return 20; }
        if (this->tamanho == 'G') { return 30; }
        return 0;
    }

public:
    
    Toalha(std::string cor, char tamanho, int umidade = 0): cor(cor), tamanho(tamanho), umidade(umidade) {
        if (this->umidade > getLimite()) { this->umidade = getLimite(); }
    }

    std::string getCor () const { return cor; }

    char getTamanho () const { return tamanho; }

    int getUmidade () const { return umidade; }

    void Enxugar(int humidade) {
        this->umidade += humidade;
        if (this->umidade >= getLimite()) { 
            this->umidade = getLimite();
            std::cout << "toalha encharcada\n";
        }
    }

    void Torcer () {
        this->umidade = 0; 
    }

    bool estSeca() {
        if (this->umidade == 0) {
            std::cout << "Está seca\n";
            return true;
        }

        else {
            std::cout << "Está molhada\n";
            return false;
        }
    }

     std::string printarTela() {
        std::stringstream ss;
        ss << "Cor: " << getCor() << "\n";

        ss << "Tamanho: " << getTamanho() << "\n";

        ss << "Umidade: " << getUmidade() << "\n";

        return ss.str();

    }
    void mostrar () {
        std::cout << printarTela() << '\n';
    }
};
int main() {
    Toalha toalha("Azul", 'P');
    toalha.mostrar();  // Azul P 0
    toalha.Enxugar(5);
    toalha.mostrar(); // Azul P 5
    toalha.estSeca(); // False
    toalha.Enxugar(5);
    toalha.mostrar();  // Azul P 10
    toalha.Enxugar(5); // msg: toalha encharcada
    toalha.mostrar();  // Azul P 10

    toalha.Torcer();
    toalha.mostrar(); //  # Azul P 0
    
    Toalha toalha2("Verde", 'G');
    
    toalha2.estSeca(); //# True
    toalha2.Enxugar(30);
    toalha2.mostrar();  //# Verde G 30
    toalha2.estSeca(); //# False
    toalha2.Enxugar(1); //  # msg: toalha encharcada
}

