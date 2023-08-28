#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../Controller/Controller.h"

namespace s21 {

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
        Controller *controller;
    public:
        ConsoleView(Controller *c):controller(c){};
        void displayMenu();
        int performChoice();
        double performNumericInput();
        void startEventLoop();
};


}  // namespace s21

#endif
