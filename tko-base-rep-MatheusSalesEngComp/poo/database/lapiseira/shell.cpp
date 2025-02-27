#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <iomanip>
using namespace std;

class Grafite {
private:
    float thickness;
    string hardness;
    int size;

public:
    Grafite(float thickness = 0.0, string hardness = "", int size = 0)
        : thickness(thickness), hardness(hardness), size(size) {}

    float getThickness() { return thickness; }
    string getHardness() { return hardness; }
    int getSize() { return size; }

    int getUsagePerSheet() {
        if (hardness == "HB") return 1;
        if (hardness == "2B") return 2;
        if (hardness == "4B") return 4;
        if (hardness == "6B") return 6;
        return 0;
    }

    void reduceSize(int amount) { size = max(10, size - amount); }

    string str() {
        stringstream ss;
        ss << fixed << setprecision(1) << thickness;
        return "[" + ss.str() + ":" + hardness + ":" + to_string(size) + "]";
    }
};

class Lapiseira {
private:
    float thickness;
    shared_ptr<Grafite> bico;
    list<shared_ptr<Grafite>> tambor;

public:
    Lapiseira(float thickness = 0) : thickness(thickness) {}

    void insert(shared_ptr<Grafite> grafite) {
        if (grafite->getThickness() != this->thickness) {
            cout << "fail: calibre incompatível\n";
            return;
        }
        tambor.push_back(grafite);
    }

    void pull() {
        if (bico) {
            cout << "fail: ja existe grafite no bico\n";
            return;
        }
        if (tambor.empty()) {
            cout << "fail: tambor vazio\n";
            return;
        }
        bico = tambor.front();
        tambor.pop_front();
    }

    void remove() {
        if (!bico) {
            cout << "fail: nao existe grafite no bico\n";
            return;
        }
        bico = nullptr;
    }

    void writePage() {
        if (!bico) {
            cout << "fail: nao existe grafite no bico\n";
            return;
        }
        if (bico->getSize() <= 10) {
            cout << "fail: tamanho insuficiente\n";
            remove();
            return;
        }
        
        if (bico->getSize() - bico->getUsagePerSheet() < 10) {
            cout << "fail: folha incompleta\n";
            bico->reduceSize(bico->getSize() - 10); 
            return;
        }
        bico->reduceSize(bico->getUsagePerSheet());

    }

    string str() {
        stringstream ss;
        ss << fixed << setprecision(1) << thickness;
        string tambor_str = "<";
        for (auto g : tambor) {
            tambor_str += g->str();
        }
       // for (auto i = tambor.begin(); i != tambor.end(); i++) tambor_str += (*i)->str();
        tambor_str += ">";
        return "calibre: " + ss.str() + ", bico: " + (bico ? bico->str() : "[]") + ", tambor: " + (tambor.empty() ? "<>" : tambor_str);
    }
};

int main() {
    Lapiseira lapiseira;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << lapiseira.str() << endl;
        } else if (cmd == "init") {
            float calibre;
            ss >> calibre;
            lapiseira = Lapiseira(calibre);
        } else if (cmd == "insert") {
            float calibre;
            string dureza;
            int tamanho;
            ss >> calibre >> dureza >> tamanho;
            lapiseira.insert(make_shared<Grafite>(calibre, dureza, tamanho));
        } else if (cmd == "remove") {
            lapiseira.remove();
        } else if (cmd == "pull") {
            lapiseira.pull();
        } else if (cmd == "write") {
            lapiseira.writePage();
        } else {
            cout << "fail: comando invalido\n";
        }
    }
}
