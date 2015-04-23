#include "menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

char Menu::getMenu()
{
    return menu;
}

void Menu::setMenu()
{
    std::cout<<"valaszon menut"<<std::endl;
    std::cin>>menu;
//    std::cout<<"\tezt adtad meg: "<<menu<<std::endl;
}

void Menu::start(Table t){
    while(t.Hand.size()!=0){//
        std::cout<<"huzas/passz: 1"<<std::endl;
        std::cout<<"dobas: 2"<<std::endl;
        std::cout<<"uno: 3"<<std::endl<<std::endl;
    //    std::cout<<"valaszon menut"<<std::endl;
        do {
            setMenu();
    //        std::cout<<"\tezt adtad meg: "<<menu<<std::endl;
        } while (menu != '1' && menu != '2' && menu != '3');

        switch (menu) {
            case '1':
                t.Draw();
                break;
            case '2':
                t.PlayClient();
                break;
            case '3':
                t.SayUno();
                break;
        }
    };//
}


