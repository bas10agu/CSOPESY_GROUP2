#include <cstdlib>
#include <windows.h>
#include <iostream>
using namespace std;

void color(int n) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}

void menu() {
    color(13);
    cout << R"(
===============================================================
 _______  _______  _______  _______  _______  _______  __   __ 
|       ||       ||       ||       ||       ||       ||  | |  |
|       ||  _____||   _   ||    _  ||    ___||  _____||  |_|  |
|       || |_____ |  | |  ||   |_| ||   |___ | |_____ |       |
|      _||_____  ||  |_|  ||    ___||    ___||_____  ||_     _|
|     |_  _____| ||       ||   |    |   |___  _____| |  |   |  
|_______||_______||_______||___|    |_______||_______|  |___|  
AGUSTINES    --   DEPASUCAT     --     ESTEBAN     --  PADILLA

HELLO, WELCOME TO  GROUP 2'S CSOPESY COMMANDLINE!
TYPE 'exit' TO QUIT, 'clear' TO CLEAR THE SCREEN

===============================================================
        )" << endl;
}

void enter() {
    color(7);
    cout << "Enter a command: ";
}

void clear() {
    system("cls");
    menu();
}


int main() {

    string command;
    menu();

    while (true) {
        enter();
        cin >> command;

        if (command == "initialize") {
            cout << "Initialize command recognized. Doing something." << endl;
            cout << endl;
        }
        else if (command == "screen") {
            cout << "Screen command recognized. Doing something." << endl;
            cout << endl;
        }
        else if (command == "scheduler-test") {
            cout << "Scheduler test command recognized. Doing something." << endl;
            cout << endl;
        }
        else if (command == "scheduler-stop") {
            cout << "Scheduler stop command recognized. Doing something." << endl;
            cout << endl;
        }
        else if (command == "report-util") {
            cout << "Report util command recognized. Doing something." << endl;
            cout << endl;
        }
        else if (command == "clear") {
            clear();
        }
        else if (command == "exit") {
            exit(0);
        }
        else {
            cout << "Command not accepted: " << command << endl;
            cout << endl;
        }

    }

    return 0;
}