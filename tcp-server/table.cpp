#include "table.h"
#include "QString"
#include <QDebug>

#define RANDOM_INTREVAL 4500;
#define DIRSTRIBUTED_CARD_NORMAL_GAME 7;
#define DIRSTRIBUTED_CARD_TEST_GAME 3;

using namespace std;

Table::Table(int cnt_players)
{
    std::cout<<"Beleptem a Table konstruktotraba"<<std::endl;


    numberOfDrawCards=1;
    action = false;

    Load(cnt_players);
}

Table::~Table()
{

}

void Table::Load(int cnt_players)
{
   // qDebug() <<"Normal jatek? [Y/N]";
    char gameType='Y';                      //for debug only!
   // cin>>gameType;
    std::map<int, Card> deck;               //ebbe kerülnek véletlenszerűen a lapok
    srand(time(NULL));                      //elindul a randomizálás
    char numbers[13]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'S', 'D', 'R'};
                                            //feltöltjük a lapok lehetséges értékeivel, hogy innen adhassunk értéket a lakop attributumának a példányosítás során
    char color[4]={'R', 'G', 'B', 'Y'};     //feltöltjük a lapok lehetséges színeivel, hogy innen adhassunk értékel a lakop attributumának a példányosítás során

    for(int i=0; i<4; i++){                  //beállítja a pédányosításhoz a színt
        for(int j=0; j<13; j++){            //0-tol R-ig innen kapja a számot a lap
            Card c;                             //példányost egy kértyalapot
            c.setNumber(numbers[j]);            //értéket ada számának
            c.setColor(color[i]);               //értéket ada színének
            c.setColor2(color[i]);              //joker lapoknál a választott szín, itt megegyezik a lap eredeti szinével
            int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
            while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
                k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
            }                                   //
            deck[k] = c;                        //ha nincs egyezés bekerül a map-be
        }
    }

    for(int i=0; i<4; i++){                 //négyzser lefut a joker lapok létrehozásához
        Card c;                             //példányost egy kértyalapot
        c.setNumber('I');                   //a szám értéke különböziok az eddigiektől
        c.setColor('W');                    //a szín értéke a joker lesz
        c.setColor2(color[i]);              //ezt at értéket kell átállítani a játékos választására a lap meghívásakor
        int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
        while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[k] = c;                        //ha nincs egyezés bekerül a map-be

        c.setNumber('F');                   //a szám értéke F, mert 4 lapot kell húzni a lap kijátszásakor
        c.setColor('W');                    //a szín értéke a joker lesz
        c.setColor2(color[i]);              //ezt at értéket kell átállítani a játékos választására a lap meghívásakor
        k = rand() % RANDOM_INTREVAL;       //random kulcsot ad a kártyalap mellé
        while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[k] = c;                        //ha nincs egyezés bekerül a map-be
    }
    if( gameType=='Y'){
        for(int i=0; i<4; i++){                  //beállítja a pédányosításhoz a színt
            for(int j=1; j<13; j++){                //1-tol R-ig innen kapja a számot a lap
                Card c;                             //példányost egy kértyalapot
                c.setNumber(numbers[j]);            //értéket ada számának
                c.setColor(color[i]);               //értéket ada színének
                c.setColor2(color[i]);              //joker lapoknál a választott szín, itt megegyezik a lap eredeti szinével
                int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
                while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
                    k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
                }                                   //
                deck[k] = c;                        //ha nincs egyezés bekerül a map-be
            }
        }
    }
    else{
        for(int i=0; i<4; i++){                  //beállítja a pédányosításhoz a színt
            for(int j=10; j<13; j++){               //1-tol R-ig innen kapja a számot a lap
                Card c;                             //példányost egy kértyalapot
                c.setNumber(numbers[j]);            //értéket ada számának
                c.setColor(color[i]);               //értéket ada színének
                c.setColor2(color[i]);              //joker lapoknál a választott szín, itt megegyezik a lap eredeti szinével
                int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
                while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
                    k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
                }                                   //
                deck[k] = c;                        //ha nincs egyezés bekerül a map-be
            }
        }
    }

    for(std::map<int, Card>::iterator i=deck.begin(); i!=deck.end(); i++){  //végigmegy a map-en
        drawDeck.push_back(i->second);      //az összekevert lapok a húzó pakliba kerülnek
    }
    PrintDrawDeck();
    int distributedCard;
    if( gameType=='Y'){
        distributedCard=DIRSTRIBUTED_CARD_NORMAL_GAME
    }else{
        distributedCard=DIRSTRIBUTED_CARD_TEST_GAME
    }
    Deal(distributedCard, cnt_players);

}

void Table::PrintDrawDeck()
{
    std::cout<<"Beleptem a PrintDrawDeck() fugvenybe"<<std::endl;
    for(unsigned i=0; i<drawDeck.size(); i++){
        drawDeck[i].Print();
        std::cout<<" ";
    }
    std::cout<<drawDeck.size();
    std::cout<<std::endl;
}


void Table::ShuffleDrawDeck()
{
    std::map<int, Card> deck;               //ebbe kerülnek véletlenszerűen a lapok
    srand(time(NULL));                      //elindul a rendomizálás
    for(unsigned i = 0; i<playDeck.size(); i++){ //végigmegy a dobó paklin
        int j = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
        while(deck.find(j)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            j = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[j] = playDeck[i];              //ha noincs egyezés bekerül a map-be
    }

    playDeck.clear();                       //kiüríti a dobó paklit

    for(std::map<int, Card>::iterator i=deck.begin(); i!=deck.end(); i++){  //végigmegy a map-en
        drawDeck.push_back(i->second);      //az összekevert lapok a húzó pakliba kerülnek
    }
}

void Table::Draw(int player_id)
{

    Hands[player_id].push_back(drawDeck[(drawDeck.size())-1]);     //a játékos kezébe kerül az osztó pakli utolsó eleme
    drawDeck.pop_back();                                       // az osztó pakli utolsó elemét törli
}

void Table::DrawEnough(int player_id)
{
    for(unsigned i=0; i<numberOfDrawCards; i++){        //annyiszor fut le, ahány lapot kell húznia a soron következő játékosnak
        Draw(player_id);
    }
    numberOfDrawCards=1;                                //visszaállítja a húzando lapok számát 1-re
    action = false;                                     //vissazállítja az akciólap változót hamisra
    PrintTable();                                       //kilistázza az asztal tertelmát
}

void Table::Play(int player_id, QChar c, QChar n, QChar c2)
{
    std::list<Card>::iterator j = Hands[player_id].end();           //létrehoz egy iterátort ami a keze első elemér mutat
    std::list<Card>::iterator i = Hands[player_id].begin();         //létrehoz egy iterátort ami a keze utolsó elemér mutat
    while(i != Hands[player_id].end()){                             //végigmegy a kézen
        if(i->getColor()==c && i->getNumber()==n){      //ha megtalálta a lapot
            j=i;                                        //a j-t átállítja ugy, hogy erre a lapra mutasson
            std::cout<<"Megtalaltam a lapot"<<std::endl;
        }
        i++;                                            //növeli i-t
    }
    if(j->getColor()=='W'){
        j->setColor2(c2);
    }
    playDeck.push_back(playedCard);                     //a hívott lapot a kijátszott lapok közé teszi
    playedCard=*j;                                      //a dobott lapt a hívott lapba teszi
    Hands[player_id].erase(j);                                      //j-t törli a kézből

    if(n=='D'){                                         //ha húzz kettőt, akkor
        action = true;                                  //akor beállítja az akciót igaznak
        if(numberOfDrawCards==1){                       //ha ez az első ilyen lap,
            numberOfDrawCards=2;                        //akkor a húzandó lapok számát kettőre állítja
        }else{                                          //ha már volt hívva ugyan ilyen lap
            numberOfDrawCards=numberOfDrawCards+2;      //kettővel növeli a húzandó lapkat
        }
    }else{
        if(n=='F'){                                     //ha joker húzz négyet
            action = true;                              //akor beállítja az akciót igaznak
            if(numberOfDrawCards==1){                   //ha ez az első ilyen lap,
                numberOfDrawCards=4;                    //akkor a húzandó lapok számát négyre állítja
            }else{                                      //ha már volt hívva ugyan ilyen lap
                numberOfDrawCards=numberOfDrawCards+4;  //néggyel növeli a húzandó lapkat
            }
        }else{
            if(n=='S'){                                 //ha ugorj
                action = true;                          //akor beállítja az akciót igaznak
                numberOfDrawCards=0;                    //a húzandó lapok számát nullára állítj
            }else{
                if(n=='R'){                             //ha fordulj
                    action = false;                     //akkor beállítja az akciót hamisnak
                    numberOfDrawCards=1;                //a húzandó lapok számát 1-re állítja
                    std::cout<<"megforditottad a kort!"<<std::endl;
                    // TODO megfordítani a kört
                }else{                                  //ha nem akció lap
                    action = false;                     //akkor beállítja az akciót hamisnak
                    numberOfDrawCards=1;                //a húzandó lapok számát 1-re állítja
                }
            }
        }
    }
    PrintTable();
    std::cout<<"jartam a Play() fuggvenyben"<<std::endl;      //
}

void Table::Deal(int cnt_cards, int cnt_players)
{
    for(int j=0; j<cnt_players;j++){
    Hand hand;
    Hands.push_back(hand);
        for(int i=0; i<cnt_cards; i++){
            Draw(j);
        }
    }

    playedCard=drawDeck[(drawDeck.size())-1];
    drawDeck.pop_back();
    PrintTable();
}

/*void Table::SayUno(){
    if(Hand.size()!=1){
        std::cout<<"Nem mondhatod be, hogy UNO!"<<std::endl;    //üzenetet ad a bemondás sikerteklenségéről
    }
    else{
        std::cout<<"Bemondtad, hogy UNO!"<<std::endl;           //üzenetet ad a bemondás sikeréről
        //TODO: küldjön üzenetet a servernek a bemonmdásról
    }
}
*/
void Table::PrintTable(){
    for(unsigned i =0; i<Hands.size(); i++){
        std::cout<<"A "<<i+1<<". jatekos lapjai: ";
        //std::list<Card>::iterator j = Hands[i].begin();
        for(std::list<Card>::iterator j = Hands[i].begin(); j != Hands[i].end(); j++){
            Card c = *j;
            c.Print();
            std::cout<<" ";
        }
    }

    std::cout<<std::endl;
    std::cout<<"A hivott lap: ";
    QChar col=playedCard.getColor();
    if(col=='W'){
        playedCard.Print();
        QChar col2=playedCard.getColor2();
        qDebug() <<" A valasztott szin: "<<col2;
    }else{
        playedCard.Print();
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}


QString Table::Send(int player_id){
    QString data;
    data.clear();
    data.append(playedCard.getNumber());
    data.append(playedCard.getColor());
    data.append(playedCard.getColor2());
    if (action) {
        data.append("1");
    } else {
        data.append("0");
    }
    qDebug() << data;
    //std::list<Card>::iterator i = Hand.begin();
    for(std::list<Card>::iterator i = Hands[player_id].begin(); i != Hands[player_id].end(); i++){
        Card c = *i;
        data.append(c.getNumber());
        data.append(c.getColor());
        data.append(c.getColor2());
    }
    return data;
}

