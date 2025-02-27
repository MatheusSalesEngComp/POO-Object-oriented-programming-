    #include <iostream>
    #include <vector>
    #include <list>
    #include <map>
    #include <sstream>
    #include <iomanip>
    #include <unordered_map>
    #include<memory>

    using namespace std;


    class Label {
    public:
        enum Type {
            DEPOSIT,
            FEE,
            OPENING,
            REVERSE,
            WITHDRAW,
            ERROR
        };

    private:
        Type type;
        static const map<string, Type> stringToEnum;
        static const map<Type, string> enumToString;

    public:
        Label(string label = "ERROR") {
            auto it = stringToEnum.find(label);
            type = (it != stringToEnum.end()) ? it->second : ERROR;
        }

        string getLabel() const {
            return enumToString.at(type);
        }

        Type getType() const {
            return type;
        }
    };

    const map<string, Label::Type> Label::stringToEnum = {
        {"DEPOSIT", Label::DEPOSIT},
        {"FEE", Label::FEE},
        {"OPENING", Label::OPENING},
        {"REVERSE", Label::REVERSE},
        {"WITHDRAW", Label::WITHDRAW},
        {"ERROR", Label::ERROR}
    };

    const map<Label::Type, string> Label::enumToString = {
        {Label::DEPOSIT, "DEPOSIT"},
        {Label::FEE, "FEE"},
        {Label::OPENING, "OPENING"},
        {Label::REVERSE, "REVERSE"},
        {Label::WITHDRAW, "WITHDRAW"},
        {Label::ERROR, "ERROR"}
    };

class Operation{
private:
    int index;
    Label label;
    int value;
    int balance;

public:
    Operation(int index=0, Label label = Label(""), int value=0, int balance=0)
        : index(index), label(label), value(value), balance(balance) {}

    int getIndex() const {
        return index;
    }

    Label getLabel() const {
        return label;
    }

    int getValue() const {
        return value;
    }

    int getBalance() const {
        return balance;
    }

    string toString () {
        stringstream ss;
        ss << getIndex() << " " << label.getLabel() << " " << getValue() << " " << getBalance() << endl;
        return ss.str();
    } 
};


class BalanceManager{
private:
    int balance;
    list<Operation> extract;
    int nextId;

public:
    BalanceManager(): balance(0), nextId(0) {}

    int addOperation(Label label, int value) {
        switch (label.getType()) {
            case Label::DEPOSIT:
                if (value < 0) return -1;
                balance += value;
                break;

            case Label::WITHDRAW:
                if (value > balance) return -1;
                balance -= value;
                break;

            case Label::FEE:
                balance -= value;
                break;

            case Label::OPENING:
                balance = value;
                break;

            case Label::REVERSE:
                if (!extract.empty()) {
                    Operation lastOp = extract.back();
                    if (lastOp.getLabel().getType() != Label::REVERSE) {
                        balance = lastOp.getBalance() - lastOp.getValue();
                        extract.push_back(Operation(nextId++, Label("REVERSE"), lastOp.getValue(), balance));
                    }
                }
                break;

            case Label::ERROR:
                return -1;

            default:
                return -1;
        }

        extract.push_back(Operation(nextId++, label, value, balance));
        return 0; 
    }

    



};


int main() {
    BalanceManager manager;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        
        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int number{};
            ss >> number;

        }
        else if (cmd == "show") {
            // TODO
        }
        else if (cmd == "deposit") {
            // float value{};
            // ss >> value;
        }
        else if (cmd == "withdraw") {
            // float value{};
            // ss >> value;
        }
        else if (cmd == "fee") {
            // float value{};
            // ss >> value;
        }
        else if (cmd == "extract") {
            // int qtd{};
            // ss >> qtd;
        }
        else if (cmd == "reverse") {
            // int index{};
            // while(ss >> index) {
            // }
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
