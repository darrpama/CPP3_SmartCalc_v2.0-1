#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "Controller.h"

enum Choice
{
    SUM = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    RES = 5,
    EXIT = 0,
    NONE = -1
};

class ConsoleView
{
    private:
        s21::Controller *controller;
    public:
        s21::ConsoleView(Controller *c):controller(c){};
        void displayMenu();
        int performChoice();
        double performNumericInput();
        void startEventLoop();
};

#endif
