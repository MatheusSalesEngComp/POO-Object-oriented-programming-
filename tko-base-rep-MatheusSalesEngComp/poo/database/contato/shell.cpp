#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <stdlib.h>
#include <list>
#include<ctype.h>


using namespace std;

class Fone {
private:
    string id;
    string number;
    bool valid;

public:
    Fone(string name="", string number=""): id(name), number(number), valid(false) {}

    bool isValid(string number) {
        for (char c : number) {
            if (!(isdigit(c) || c == '.' || c == '(' || c == ')')) {
                return false; 
            }
        }
        return true; 
    }


    string getId () const {return id;}
    string getNumber () const {return number;}
    
    void setId (string &newName) {id = newName;}
    void setNumber (string &newNumber) {number = newNumber;}
    
    string str () {
        stringstream ss;
        ss << getId() << ":" << getNumber();
        return ss.str();
    }

};




class Contato {
private:
    bool favorited;
    list<Fone> fones;
    string name;
public:
    Contato(string name=""): favorited(false), name(name) {}

    void addFone (string id, string number) {
        auto fone = Fone(id, number);
        if (!fone.isValid(number)) {
            cout << "fail: invalid number\n";
            return;
        }
        fones.push_back(fone);
    }   

    void rmFone(int index){
        int count = 0;
        for (auto it = fones.begin(); it != fones.end(); it++){
            if(count == index){
                fones.erase(it);
                return;
            }
            count++;
        }
    }
    
    bool tfav () {
        if (!favorited) {return favorited = true;}
        return favorited = false;
    }

    string str() {
        stringstream ss;
        if (!favorited) {ss << "- ";}
        else{ss << "@ ";}
        
        ss << name << " [";

        int count = 0;
        for (auto it = fones.begin(); it != fones.end(); ++it) {
            ss << (count++ ? ", " : "") << it->str(); 
        }

        ss << "]\n";
        return ss.str();
    }

};


int main()
{
    Contato contato;
    while (true)
    {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }
        else if (cmd == "init")
        {
            string name;
            ss >> name;
            contato = Contato(name);
        }
        else if (cmd == "add"){
            string id, number;
            ss >> id >> number;
            contato.addFone(id,number);

        }
        else if (cmd == "rm")
        {
            int index{};
            ss >> index;
            contato.rmFone(index);
        }
        else if (cmd == "tfav")
        {
            contato.tfav();
        }
        else if (cmd == "show")
        {
            cout << contato.str();
        }
        else
        {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}

template <class CONTAINER, class FUNC>
string map_join(const CONTAINER &cont, FUNC func, string sep = " ")
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : sep) << func(*it);
    }
    return ss.str();
}
