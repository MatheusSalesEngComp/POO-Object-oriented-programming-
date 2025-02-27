#include <iostream>
#include <memory>
#include <utility> 
#include <sstream>
using namespace std;

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Grafite {
private:
    double thickness;
    string hardness;
    int size;

public:
    Grafite(double thickness = 0.0, string hardness = "", int size = 0) 
        : thickness(thickness), hardness(hardness), size(size) {}

    float getThickness() { return this->thickness; }
    int getUsagePerSheet() {
        if (hardness == "HB") { return 1; }
        if (hardness == "2B") { return 2; }
        if (hardness == "4B") { return 4; }
        if (hardness == "6B") { return 6; }
        return 0;
    }

    int getSize() { return size; }
    
    void setSize(int size) { this->size = size; }
    void setHardness(string hardness) { this->hardness = hardness; }
    void setThickness(double thickness) { this->thickness = thickness; }

    void reduceSize(int amount) { size = max(10, size - amount); }

    string str() { 
        stringstream oss;
        oss << fixed << setprecision(1) << thickness;
        
        return oss.str() + ":" + hardness + ":" + to_string(size); 
    }
};

class Lapiseira {
private:
    shared_ptr<Grafite> grafite;
    double thickness;

public:
    Lapiseira(double initThickness = 0) : thickness(initThickness) {}

    void insert(shared_ptr<Grafite> newGrafite) {

        if (newGrafite->getThickness() != this->thickness) {
            cout << "fail: calibre incompativel\n";
            return;
        }
        if (grafite) {
            cout << "fail: ja existe grafite\n";
            return;
        }
        
        grafite = newGrafite;
        thickness = grafite->getThickness();
    }

    void remove() {
        if (!grafite) {
            cout << "fail: nao existe grafite" << endl;
            return;
        }
        grafite = nullptr;
    }

    void writePage() {
        if (!grafite) {
            cout << "fail: nao existe grafite" << endl;
            return;
        }
        if (grafite->getSize() <= 10) {
            cout << "fail: tamanho insuficiente" << endl;
            return;
        }
        int usage = grafite->getUsagePerSheet();
        if (grafite->getSize() - usage < 10) {
            cout << "fail: folha incompleta" << endl;
            grafite->reduceSize(usage);
        } else {
            grafite->reduceSize(usage);
        }
    }

    string str() {
        stringstream oss;
        oss << fixed << setprecision(1) << thickness;

        if (grafite) {
            return "calibre: " + oss.str() + ", grafite: [" + grafite->str() + "]";
        } else {
            return "calibre: " + oss.str() + ", grafite: null";
        }
        
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
        } 
        else if (cmd == "show") { 
            cout << lapiseira.str() << endl;
        }
        else if (cmd == "init") { 
            float thickness;
            ss >> thickness;
            lapiseira = Lapiseira(thickness);
        }
        else if (cmd == "insert") { 
            float thickness;
            string hardness;
            int size;
            ss >> thickness >> hardness >> size;
            Grafite grafite(thickness, hardness, size);
            lapiseira.insert(make_shared<Grafite>(grafite));
        }
        else if (cmd == "remove") { 
            lapiseira.remove();
        }
        else if (cmd == "write") {
            lapiseira.writePage(); 
        }
        else {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}
