#include "table.h"
#include <QDebug>

Table::Table()
{
    uno=false;
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

int Table::Play(QChar n, QChar c)
{
    int playable;
    if(Hand.size()!=0){

        std::list<Card>::iterator j = Hand.end();       //létrehoz egy iterátort ami a keze első elemére mutat
        std::list<Card>::iterator i = Hand.begin();     //létrehoz egy iterátort ami a keze utolsó elemére mutat
        while(i != Hand.end()){                         //végigmegy a kézen
            if(i->getColor()==c && i->getNumber()==n){  //ha megtalálta a lapot
                j=i;                                    //a j-t átállítja ugy, hogy erre a lapra mutasson
//                std::cout<<"Megtalaltam a lapot"<<std::endl;
            }
            i++;                                        //növeli i-t
        }
        if(j==Hand.end()){                              //ha j a kéz végére mutat, akkor nem találta meg, azaz nincs a kezében
//            std::cout<<"Nincs ilyen lap a kezedben. Kerlek adj meg masikat!"<<std::endl;
//            Play();                                   //újra meghívja ezt a függvényt, hogy új lapot választhasson a játék
            playable=1;
        }else{
            if(action==true){                           //ha a kézben van a alap, és az előző lap action lap volt
                if(n==playedCard.getNumber()){          //és a szám megyegyezik a hívott lap számával
                    if(n=='F'){                         //és a lap a joker huzz négyet
                        int j=0;                        //akkor megnézzi, hogy  a választott színből van-e a kézben
                        std::list<Card>::iterator i = Hand.begin();
                        for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
                            if(playedCard.getColor2()==i->getColor()){
                                j++;
                            }
                        }
                        if(j==0){                       //ha nincs
//                            std::cout<<"válassz színt!"<<std::endl; //bekéri, a válsztott színt
//                            char c2;
//                            std::cin>>c2;                           //és menti
//                            Play(c, n, c2);                         //meghívja a server Play() függvényét
                            playable = 0;

                        }else{                                      //ha vana  kezünkben a választott színből, akkor nem tehetjük ki ezt a lapot
                            std::cout<<"Nem hivhatod ki ezt a lapot, mert van hivo szinu lapod!"<<std::endl;
                            playable = 2;
                        }
                    }else{                                            //ha nem F, akkor további feltétel nélkül kijátszhatja a lapo
//                        Play(c, n, c);                              //meghívja a server Play() függvényét
                          playable = 0;
                    }
                }else{                                              //ha nem megfelelő a szín, nem játszahtja kia  lapot
                    std::cout<<"A hivott akciolapra csak ugyan olyan akciolapot tehetsz. Ha nincs nalad ilyen lap, valaszd a huzas/passz menut!"<<std::endl;
                    playable=3;

                }
            }else{                                                  //ha nem kell a korábbi lap utasításait betartanunk (vagy nem akciólap, vagy az előz játékosra vonatkozott
                if(c=='W'){                                         //ha a lap joker
                    if(n=='I'){                                     //és joker lap
//                        std::cout<<"válassz színt!"<<std::endl;     //bekéri a választott színt
//                        char c2;
//                        std::cin>>c2;                               //ezt menti
//                        Play(c, n, c2);                             //meghívja a server Play() függvényét
                        playable = 0;
                    }else{                                          //ha joker húzz négyet
                        int j=0;
                        std::list<Card>::iterator i = Hand.begin(); //akkor megnézzi, hogy  a választott színből van-e a kézben
                        for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
                            if(playedCard.getColor2()==i->getColor()){
                                j++;
                                qDebug() << playedCard.getColor2()<<" PH "<< i->getColor();
                            }
                          //  Card c = *i;
                          //  c.Print();
                          //  std::cout<<" ";
                        }
                        if(j==0){                                    //hivott lap c2 = c
//                            std::cout<<"válassz színt!"<<std::endl;
//                            char c2;
//                            std::cin>>c2;
//                            Play(c, n, c2);
                            playable = 0;
                        }else{
                            std::cout<<"Nem hivhatod ki ezt a lapot, mert van a hivo szinu lapod!"<<std::endl;
                            playable = 2;
                        }
                    }
                }else{                                              //ha nem joker lap
                    if(playedCard.getColor2()==c || playedCard.getNumber()==n){ //megnézi, hogy a színe, vagy a száma megegyezik-e a hívott lapéval
//                        Play(c, n, c);                                          //akkor megnézzi, hogy  a választott színből van-e a kézben
                        playable=0;
                    }else{                                                      //ha sem a szín, sem a száma nem egyezik meg, a lap nem játszható ki
                        std::cout<<"Nem hivhatod ki ezt a lapot, mert sem a szine sem a szama nem egyezik meg a hívo lapeval!"<<std::endl;
                        playable=4;
                    }
                }
            }
        }
    }
//    std::cout<<"jartam a PlayClient() fuggvenyben"<<std::endl;      //
    return playable;
}

int Table::SayUno(){
    if(Hand.size()!=1){
        std::cout<<"Nem mondhatod be, hogy UNO!"<<std::endl;    //üzenetet ad a bemondás sikerteklenségéről
        return 1;
    }
    else{
        std::cout<<"Bemondtad, hogy UNO!"<<std::endl;           //üzenetet ad a bemondás sikeréről
        uno=false;
        return 0;
    }
}

bool Table::getUno(){
    return uno;
}

void Table::setUno(bool b){
    uno=b;
}
