#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <algorithm>  
using namespace std;

class Player {
private:
    int label;
    int pos;
    bool free;

public:
    Player(int label) : label(label), pos(0), free(true) {}

    int getLabel() { return label; }    
    int getPos() { return pos; }
    bool getFree() { return free; }
    
    void setLabel(int newLabel) { this->label = newLabel; }
    void setPos(int newPos) { this->pos = newPos; }
    void setFree(bool newFree) { this->free = newFree; }

    string str() {
        stringstream ss;     
        ss << "player" << label << ": ";
        return ss.str();
    }
};

class Board {
private:
    vector<Player> players;   
    vector<int> board; 
    vector<string> trapList;   
    int currentPlayerIndex;
    bool winner;


public:
    
    Board(int nPlayers = 0, int boardSize = 0) : board(boardSize+1), trapList(boardSize+1, ".") , currentPlayerIndex(0), winner(false) {
        for (int i = 0; i < nPlayers; i++) {
            players.emplace_back(i + 1); 
        }
    }
    

    void addTrap(int pos) {
        trapList[pos] = "x";
    }

    void play () {
        currentPlayerIndex += 1;
        if(currentPlayerIndex >= 2) {currentPlayerIndex = 0;}
    }

    void roll(int value) {
        Player& player = players[currentPlayerIndex];
        
        if (winner) {
            cout << "game is over" << endl;
            return;
        } 

        if (player.getFree()) {
            player.setPos(value+player.getPos());
            if (trapList[player.getPos()] == "x") {
                player.setFree(false);
            }
            if (player.getPos() >= (int)board.size()) {
                cout << "player" << player.getLabel() << " ganhou" << endl;
                player.setPos(board.size()-1);
                winner = true;
                return;
            }
            cout << "player" << player.getLabel() << " andou para " << player.getPos() << endl;
            if(player.getFree() == false){
                cout << "player" << player.getLabel() << " caiu em uma armadilha" << endl;
            }
        }
        else{
            if((value % 2 != 0)){
                cout << "player" << player.getLabel() << " continua preso" << endl;
                play();
                return;
            }
            else{
                player.setFree(true);
                cout << "player" << player.getLabel() << " se libertou" << endl;
                play(); 
                return;
            }
            cout << "player" << player.getLabel() << " está preso" << endl;

        }

        play();
    }

    string str() {
        stringstream ss;

        for (auto& player : players) {
            ss << player.str(); 
            board[0] = player.getLabel(); 
            for (int i = 0; i < (int)board.size(); i++) {
                if(i == player.getPos()) {
                    ss << player.getLabel();
                } 
                else {
                    ss << ".";
                }
            }
            ss << '\n';
        }
        ss<< "traps__: ";
        for (int i = 0; i < (int)trapList.size(); i++) {
            ss << trapList[i];
        }


        return ss.str();
    }
};



int main() {
    Board board;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int nJogadors, size;
            ss >> nJogadors >> size;
            board = Board(nJogadors, size);
        } else if (cmd == "addTrap") {
            int pos;
            ss >> pos;
            board.addTrap(pos);
        } else if (cmd == "roll") {
            int value;
            ss >> value;
            board.roll(value);
        } else if (cmd == "show") {
            cout << board.str() << endl;
        } else {
            cout << "fail: command not found" << endl;
        }

    }
    return 0;
}
