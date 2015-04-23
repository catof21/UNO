#include "table.h"

Table::Table()
{

}

Table::~Table()
{

}

 void Table::Print()
{
   std::cout<<"a hivo lap:\t";
   playedCard.Print();                              //kiirja a hívó lapot
   std::cout<<std::endl<<std::endl<<"A kezedben levo lapok::"<<std::endl;
   for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
       i->Print();                                  //kilistázza a kézben lévő lapokat
   }
   std::cout<<std::endl;
}


void Table::Draw()
{
    std::cout << "most huzol: "<<std::endl;
    //TODO Hívja meg a server Table::Draw() függvényét, és adja vissza az állást
    this->Print();                                    //megjeleníti az asztalt
}

void Table::Play()
{
    std::cout << "most dobsz: "<<std::endl;
    if(Hand.size()!=0){                                 //ha nincs lap a kezünkben, nem tudunk mit megjátszani
        char c, n;
        std::cout<<"A dobando lap szine:"<<std::endl;   //meg kel adni a megjátszandó lap színét
        std::cin>>c;
        std::cout<<"A dobando lap szama:"<<std::endl;
        std::cin>>n;                                    //és számát
        std::list<Card>::iterator j = Hand.end();       //ezel az iterátorral elenőrizhető lesz, hogy  akézben van-e a kiválasztott lap
        std::list<Card>::iterator i = Hand.begin();     //végigmegy a
        while(i != Hand.end()){                         //kézben lévő lapokon
            if(i->getColor()==c && i->getNumber()==n){  //egyezést keres a megadott paraméterekkel
                j=i;                                    //ha megvan, a jelzésre használt iterátor értékéül adja
//                std::cout<<"Megtalaltam a lapot"<<std::endl;
            }
            i++;
        }
        if(j==Hand.end()){                              //megvizsgálja a jelzésr ehasznált iterátort
            std::cout<<"Ninc silyen lap a kezedben. Kerlek adj meg masikat!"<<std::endl;
            Play();                                     //ha ninc sa kézben, meghívja ujra  függvényt, így új adatok adhatok meg
        }else{                                          //ha a kézben van
            //TODO Hívja meg a server Table::Play() függvényét, és adja vissza az állást
            this->Print();                              //megjeleníti az asztalt
        }
    }

}

void Table::SayUno(){
    if(Hand.size()!=1){
        std::cout<<"Nem mondhatod be, hogy UNO!"<<std::endl;    //üzenetet ad a bemondás sikerteklenségéről
    }
    else{
        std::cout<<"Bemondtad, hogy UNO!"<<std::endl;           //üzenetet ad a bemondás sikeréről
        //TODO: küldjön üzenetet a servernek a bemonmdásról
    }
}


