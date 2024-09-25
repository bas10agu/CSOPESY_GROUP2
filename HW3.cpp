#include <iostream>
#include <unordered_map>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Screen {
    string processName;
    int currentLine;
    int totalLines;
    time_t creationTime;

    Screen() : currentLine(0), totalLines(100), creationTime(time(0)) {}

    Screen(const string& name) : processName(name), currentLine(0), totalLines(100), creationTime(time(0)) {}
};

unordered_map<string, Screen> screens;
string currentScreen = "";

void color(int n);
void menu();
void enter();
void clear();
void screenCreate(const string& name);
void screenRestore(const string& name);
void handleScreenCommands(const string& input);
void listScreens();
void displayMainMenu();
void displayScreen(const Screen& screen);

void color(int n) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}

// Display Title Main Menu
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

HELLO, WELCOME TO GROUP 2'S CSOPESY COMMANDLINE!
TYPE 'exit' TO QUIT, 'clear' TO CLEAR THE SCREEN
===============================================================
    )" << endl;
}

void enter() {
    color(7);
    if (currentScreen.empty()) {
        cout << "Enter a command: ";
    }
    else {
        cout << "[" << currentScreen << "]$ ";
    }
}

// Clear Screen
void clear() {
    system("cls");
    if (currentScreen.empty()) {
        menu();
    }
    else {
        displayScreen(screens[currentScreen]);
    }
}

// Display Main Menu
void displayMainMenu() {
    cout << "\nAvailable commands:\n";
    cout << " - initialize\n";
    cout << " - screen -s <name> (create new screen)\n";
    cout << " - screen -r <name> (restore screen)\n";
    cout << " - screen -ls (list all screens)\n";
    cout << " - scheduler-test\n";
    cout << " - scheduler-stop\n";
    cout << " - report-util\n";
    cout << " - clear\n";
    cout << " - exit\n";
    cout << endl;
}

// Create Screen
void screenCreate(const string& name) {
    if (screens.find(name) != screens.end()) {
        cout << "Screen with name '" << name << "' already exists.\n";
        return;
    }

    screens[name] = Screen(name);
    currentScreen = name;
    displayScreen(screens[name]);
}

// Display Screen
void displayScreen(const Screen& screen) {
    system("cls");
    cout << "Screen Name: " << screen.processName << "\n";
    cout << "Current Line: " << screen.currentLine << " / " << screen.totalLines << "\n";

    tm localTime;
    localtime_s(&localTime, &screen.creationTime);
    ostringstream oss;
    oss << put_time(&localTime, "%m/%d/%Y, %I:%M:%S %p");
    cout << "Created At: " << oss.str() << "\n\n";
}

// Display Existing Screen
void screenRestore(const string& name) {
    auto it = screens.find(name);
    if (it == screens.end()) {
        cout << "Screen '" << name << "' does not exist.\n";
        return;
    }

    currentScreen = name;
    displayScreen(it->second);
}

// List Screens
void listScreens() {
    if (screens.empty()) {
        cout << "No active screens.\n";
    }
    else {
        cout << "Active screens:\n";
        for (const auto& screen : screens) {
            if (screen.first == currentScreen) {
                cout << screen.first << " (attached)\n";
            }
            else {
                cout << screen.first << "\n";
            }
        }
    }
}

// Screen Commands
void handleScreenCommands(const string& input) {
    istringstream iss(input);
    string command, option, name;
    iss >> command >> option >> name;

    if (command == "screen") {
        if (option == "-s" && !name.empty()) {
            screenCreate(name);
        }
        else if (option == "-r" && !name.empty()) {
            screenRestore(name);
        }
        else if (option == "-ls") {
            listScreens();
        }
        else {
            cout << "Invalid screen command. Usage:\n";
            cout << "  screen -s <name> (create new screen)\n";
            cout << "  screen -r <name> (restore screen)\n";
            cout << "  screen -ls (list all screens)\n";
        }
    }
    else {
        cout << "Unknown command. Type 'screen -ls' for screen commands.\n";
    }
}

// Main command handler
void readCommand(const string& command) {
    if (command == "exit") {
        if (!currentScreen.empty()) {
            currentScreen.clear();
            clear();
        }
        else {
            exit(0);
        }
    }
    else if (command.find("screen") == 0) {
        handleScreenCommands(command);
    }
    else if (command == "initialize") {
        cout << "Initialize command recognized. Doing something.\n\n";
    }
    else if (command == "scheduler-test") {
        cout << "Scheduler test command recognized. Doing something.\n\n";
    }
    else if (command == "scheduler-stop") {
        cout << "Scheduler stop command recognized. Doing something.\n\n";
    }
    else if (command == "report-util") {
        cout << "Report util command recognized. Doing something.\n\n";
    }
    else if (command == "clear") {
        clear();
    }
    else {
        cout << "Command not recognized: " << command << endl;
        displayMainMenu();
    }
}

void mainCommandLoop() {
    string command;

    while (true) {
        enter();
        getline(cin, command);
        readCommand(command);
    }
}
int main() {
    menu();
    mainCommandLoop();
    return 0;
}