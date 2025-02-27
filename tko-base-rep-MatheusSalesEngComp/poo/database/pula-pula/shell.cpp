#include <iostream>
#include <memory>
#include <sstream>
#include <list>
#include <vector>
using namespace std;

class Kid {
private:
    string name;
    int age;
public:
    Kid(string name = "", int age=0) : name(name), age(age) {}
    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(string name) { this->name = name; }
    void setAge(int age) { this->age = age; }


    string str() const {
        stringstream ss;
        ss << name << ":" << age;
        return ss.str();
    }
};

class Trampoline {
private:
    list<shared_ptr<Kid>> wait;
    list<shared_ptr<Kid>> jump;
public:
    void arrive(shared_ptr<Kid> kid) {
        wait.push_back(kid);
    }

    void enter() {
        if (wait.empty()) {
            return;
        }
        jump.push_back(wait.front());
        wait.pop_front();
    }

    void leave() {
        if (jump.empty()) {
            return;
        }
        wait.push_back(jump.front());
        jump.pop_front();
    }

    void remove (string name) {

        for(auto i = wait.begin(); i != wait.end() ; i++) { //forma de percorrer a lista de shared_ptr através de list
            if((*i)->getName() == name) {
                wait.erase(i);
                return;
            }
        }

        for (auto i = jump.begin(); i != jump.end(); i++) {
            if ((*i)->getName() == name) {
                jump.erase(i);
                return;
            }
        }

        cout << "fail: " << name << " nao esta no pula-pula\n";
    }
    string show() {
        stringstream ss;
        ss << "[";
        bool first = true;
        for (auto it = wait.rbegin(); it != wait.rend(); ++it) {
            if (!first) ss << ", ";
            ss << (*it)->str();
            first = false;
        }
        ss << "] => [";
        first = true;
        
        for (auto it = jump.rbegin(); it != jump.rend(); ++it) {
            if (!first) ss << ", ";
            ss << (*it)->str();
            first = false;
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
    Trampoline trampoline;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << trampoline.show() << endl;
        } else if (cmd == "arrive") {
            string name;
            int age;
            ss >> name >> age;
            trampoline.arrive(make_shared<Kid>(name, age));
        } else if (cmd == "enter") {
            trampoline.enter();
        } else if (cmd == "leave") {
            trampoline.leave();
        } else if (cmd == "remove") {
            string name;
            ss >> name;
            trampoline.remove(name);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}
