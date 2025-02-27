#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
#include<map>

using namespace std;
template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return prefix + ss.str() + suffix;
}


class Coin {
private:
    double value;
    int volume;
    string label;
    
    Coin(double value = 0.0, int volume = 0, string label = "")
        : value(value), volume(volume), label(label) {}

public:
    static Coin C10() { return Coin(0.10, 1, "10"); }
    static Coin C25() { return Coin(0.25, 2, "25"); }
    static Coin C50() { return Coin(0.50, 3, "50"); }
    static Coin C100() { return Coin(1.00, 4, "100"); }

    double getValue() const { return value; }
    int getVolume() const { return volume; }
    string getLabel() const { return label; }

    string str() const {
        stringstream ss;
        ss << fixed << setprecision(2) << value;
        ss << ":" + to_string(getVolume());  
        return ss.str();
    }
};


class Item {
private:
    string label;
    int volume;
public:
    Item(int volume=0, string label="")
        : label(label), volume(volume) {}

    string getLabel() const { return label; }
    int getVolume() const { return volume; }

    void setLabel(const string& label) { this->label = label; }
    void setVolume(int volume) { this->volume = volume; }

    string str() const {
        stringstream ss;
        ss << getLabel() << ":" << getVolume();
        return ss.str();
    }
    


};

class Pig {
private:
    bool broken;
    vector<shared_ptr<Coin>> coins;
    vector<shared_ptr<Item>> items;
    int volumeMax;
    double sum = 0.00;
    int currentVolume = 0;

public:
    Pig(int volumeMax = 0) : broken(false), volumeMax(volumeMax) {}

    bool isbroken() {
        currentVolume = 0;
        return broken = true;
    }

    void addCoin(string value) {
        if (broken) {
            cout << "fail: the pig is broken" << endl;
            return;
        }

        shared_ptr<Coin> coin;
    
        if (value == "10") {coin = make_shared<Coin>(Coin::C10());} 
        else if (value == "25") {coin = make_shared<Coin>(Coin::C25());}
        else if (value == "50") {coin = make_shared<Coin>(Coin::C50());} 
        else if (value == "100") {coin = make_shared<Coin>(Coin::C100());} 
        else {
            cout << "fail: invalid coin" << endl;
            return;
        }

        if (currentVolume + coin->getVolume() > volumeMax) {
            cout << "fail: the pig is full" << endl;
            return;
        }

        coins.push_back(coin);  
        currentVolume += coin->getVolume();  
        sum += coin->getValue(); 
    }

    void addItem (int volume, string label) {
        if (broken) {
            cout << "fail: the pig is broken" << endl;
            return;
        }        

        if (volume + currentVolume > volumeMax) {
            cout << "fail: the pig is full"<< endl;
            return;
        }

        
        shared_ptr<Item> item;

        item = make_shared<Item> (volume, label);

        items.push_back(item);

        currentVolume += item->getVolume();  

    }

    void extractItems() {
    
        if (!broken){
            cout << "fail: you must break the pig first\n[]\n";
            return;
        }

        cout << map_join(items, [](shared_ptr<Item> i) { return i->str();}) << endl;
        items.clear();
    }

    void extractCoins() {
    
        if (!broken){
            cout << "fail: you must break the pig first\n[]\n";
            return;
        }

        cout << map_join(coins, [](shared_ptr<Coin> c) { return c->str();}) << endl;
        coins.clear();
        sum = 0.00;
    }

    string str() const {
        stringstream ss;
        ss << "state=" << (broken ? "broken" : "intact") << " : ";
        
        ss << "coins=" << map_join(coins, [](shared_ptr<Coin> c) { return c->str(); }) << " : ";
        ss << "items=" << map_join(items, [](shared_ptr<Item> i) { return i->str(); }) << " : ";
        
        ss << "value=" << fixed << setprecision(2) << sum << " : volume=" << currentVolume << "/" << volumeMax;

        return ss.str();
    }

};

    



int main() {
    Pig pig;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int volumeMax;
            ss >> volumeMax;
            pig = Pig(volumeMax);
        } else if (cmd == "show") {
            cout << pig.str()<< endl;
        } else if (cmd == "break") {
            pig.isbroken();
        } else if (cmd == "addCoin") {
            string label;
            ss >> label;
            pig.addCoin(label);
        } else if (cmd == "addItem") {
            string label;
            int volume;
            ss >> label >> volume;
            pig.addItem(volume, label);
        } else if (cmd == "extractItems") {
            pig.extractItems();
        } else if (cmd == "extractCoins") {
            pig.extractCoins();
        } else {
            cout << "fail: invalid command\n";
        }
    }
}
