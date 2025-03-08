#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <memory>

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

class Operation {
private:
    int index;
    Label label;
    int value;
    int balance;

public:
    Operation(int index=0, Label label = Label(""), int value=0, int balance=0)
        : index(index), label(label), value(value), balance(balance) {}

    int getIndex() const { return index; }
    Label getLabel() const { return label; }
    int getValue() const { return value; }
    int getBalance() const { return balance; }
};

class BalanceManager {
private:
    int balance;
    list<Operation> extract;
    int nextId;

public:
    BalanceManager(): balance(0), nextId(0) {}

    int getBalance() const { return balance; }

    void addOperation(Label label, int value) {
        switch (label.getType()) {
            case Label::DEPOSIT:
                if (value < 0) {
                    cout << "fail: invalid value" << endl;
                    return;
                }
                balance += value;
                break;
            case Label::WITHDRAW:
                if (value > balance) {
                    cout << "fail: insufficient balance" << endl;
                    return;
                }
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
                    auto lastOp = extract.back();
                    if (lastOp.getLabel().getType() != Label::REVERSE) {
                        balance += lastOp.getValue();
                        extract.push_back(Operation(nextId++, Label("REVERSE"), lastOp.getValue(), balance));
                    }
                }
                return;
            case Label::ERROR:
                return;
        }
        extract.push_back(Operation(nextId++, label, value, balance));
    }

    list<Operation> getExtract(int qtdOperacao) const {
        list<Operation> result;
        auto it = extract.rbegin();
        while (qtdOperacao-- > 0 && it != extract.rend()) {
            result.push_front(*it);
            ++it;
        }
        return result;
    }
};

class Account {
private:
    int id;
    BalanceManager balanceManager;

public:
    Account(int id=0) : id(id) {}

    int getId() const { return id; }
    
    void deposit(int value) { balanceManager.addOperation(Label("DEPOSIT"), value); }
    void fee(int value) { balanceManager.addOperation(Label("FEE"), value); }
    void withdraw(int value) { balanceManager.addOperation(Label("WITHDRAW"), value); }
    void reverse(int index) { balanceManager.addOperation(Label("REVERSE"), index); }
    
    const BalanceManager& getBalanceManager() const { return balanceManager; }
    
    string toString() const {
        stringstream ss;
        ss << "account:" << id << " balance:" << balanceManager.getBalance() << endl;
        return ss.str();
    }
};

int main() {
    Account account;
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
            int number;
            ss >> number;
            account = Account(number);
        }
        else if (cmd == "show") {
            cout << account.toString();
        }
        else if (cmd == "deposit") {
            int value;
            ss >> value;
            account.deposit(value);
        }
        else if (cmd == "withdraw") {
            int value;
            ss >> value;
            account.withdraw(value);
        }
        else if (cmd == "fee") {
            int value;
            ss >> value;
            account.fee(value);
        }
        else if (cmd == "extract") {
            int qtd;
            ss >> qtd;
            account.getBalanceManager().getExtract(qtd);
        }
        else if (cmd == "reverse") {
            int index;
            ss >> index;
            account.reverse(index);
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
