#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <table.h>


class Menu
{
private:
    char menu;
public:
    Menu();
    ~Menu();
    char getMenu();
    void setMenu();
    void start(Table t);
};

#endif // MENU_H

