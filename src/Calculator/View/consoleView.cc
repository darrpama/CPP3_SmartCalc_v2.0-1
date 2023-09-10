#include "ConsoleView.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void s21::ConsoleView::displayMenu()
{
    std::cout << "=========" << std::endl;
    std::cout << " M E N U " << std::endl;
    std::cout << "=========" << std::endl;
    std::cout << "1. Add a number" << std::endl;
    std::cout << "2. Subtract a number" << std::endl;
    std::cout << "3. Multiplicate a number" << std::endl;
    std::cout << "4. Divide a number" << std::endl;
    std::cout << "5. Reset a number" << std::endl;
    std::cout << "0. Quit" << std::endl << std::endl;
}

int s21::ConsoleView::performChoice()
{
    int choice;
    std::cout << "Input a menu item digit: ";
    std::cin >> choice;
    return choice;
} 

double s21::ConsoleView::performNumericInput()
{    
    double number;
    std::cout << "Input a decimal number: ";
    std::cin >> number;
    return number;
} 

void s21::ConsoleView::startEventLoop()
{
    while (true) 
    {
      double result{};
        displayMenu();

        std::cout << "Current result is: " << result << std::endl;
    }
}
