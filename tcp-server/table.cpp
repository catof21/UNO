#include "table.h"
#include "QString"

#define RANDOM_INTREVAL 4500;
#define DIRSTRIBUTED_CARD 7;

Table::Table()
{
    std::cout<<"Beleptem a Table konstruktotraba"<<std::endl;
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

    for(int i=0; i<4; i++){                 //négyzser lefut a joker lapok létrehozásához
        Card c;                             //példányost egy kértyalapot
        c.setNumber('I');                   //a szám értéke különböziok az eddigiektől
        c.setColor('W');                    //a szín értéke a joker lesz
        c.setColor2('R');                   //ezt at értéket kell átállítani a játékos választására a lap meghívásakor
        int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
        while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[k] = c;                        //ha nincs egyezés bekerül a map-be

        c.setNumber('F');                   //a szám értéke F, mert 4 lapot kell húzni a lap kijátszásakor
        c.setColor('W');                    //a szín értéke a joker lesz
        c.setColor2('R');                   //ezt at értéket kell átállítani a játékos választására a lap meghívásakor
        k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
        while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[k] = c;                        //ha nincs egyezés bekerül a map-be
    }

    for(std::map<int, Card>::iterator i=deck.begin(); i!=deck.end(); i++){  //végigmegy a map-en
        drawDeck.push_back(i->second);      //az összekevert lapok a húzó pakliba kerülnek
    }

    numberOfDrawCards=1;
    action = false;



//    delete numbers;
//    delete color;
    std::cout << " kileptt a tabla";
}

Table::~Table()
{

}

void Table::PrintDrawDeck()
{
    std::cout<<"Beleptem a PrintDrawDeck() fugvenybe"<<std::endl;
    for(int i=0; i<drawDeck.size(); i++){
        drawDeck[i].Print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}


void Table::ShuffleDrawDeck()
{
    std::map<int, Card> deck;               //ebbe kerülnek véletlenszerűen a lapok
    srand(time(NULL));                      //elindul a rendomizálás
    for(int i = 0; i<playDeck.size(); i++){ //végigmegy a dobó paklin
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

void Table::Draw()
{
    for(unsigned i=0; i<numberOfDrawCards; i++){        //annyiszor fut le, ahány lapot kell húznia a soron következő játékosnak
//        qDebug() <<"Beleptem a Draw() fuggvenybe"
       /* Card d;
        int i = drawDeck.size();
        std::cout<<i<<std::endl;
        d = drawDeck[(drawDeck.size())-1];
        d.Print();*/
        Hand.push_back(drawDeck[(drawDeck.size())-1]);  //a játékos kezébe kerül az osztó pakli utolsó eleme
        drawDeck.pop_back();                            // az osztó pakli utolsó elemét törli
    }
    numberOfDrawCards=1;                                //visszaállítja a húzando lapok számát 1-re
    action = false;                                     //vissazállítja az akciólap változót hamisra
//    PrintTable();                                       //kilistázza az asztal tertelmát
}

void Table::PlayClient()
{
    if(Hand.size()!=0){
        char c, n;                                      //létrehozza a lap színét és számát tartalmazó változókat
        std::cout<<"A dobando lap szine:"<<std::endl;   //bekéri a dobandó lap színét
        std::cin>>c;                                    //elmenti a lap színét
        std::cout<<"A dobando lap szama:"<<std::endl;   //bekéri a lap számát
        std::cin>>n;                                    //elmenti a lap számát
        std::list<Card>::iterator j = Hand.end();       //létrehoz egy iterátort ami a keze első elemér mutat
        std::list<Card>::iterator i = Hand.begin();     //létrehoz egy iterátort ami a keze utolsó elemér mutat
        while(i != Hand.end()){                         //végigmegy a kézen
            if(i->getColor()==c && i->getNumber()==n){  //ha megtalálta a lapot
                j=i;                                    //a j-t átállítja ugy, hogy erre a lapra mutasson
                std::cout<<"Megtalaltam a lapot"<<std::endl;
            }
            i++;                                        //növeli i-t
        }
        if(j==Hand.end()){                              //ha j a kéz végére mutat, akkor nem találta meg, azaz nincs a kezében
            std::cout<<"Ninc silyen lap a kezedben. Kerlek adj meg masikat!"<<std::endl;
            PlayClient();                               //újra meghívja ezt a függvényt, hogy új lapot választhasson a játék
        }else{
            if(action==true){                           //ha a kázbe van a alap, és az előző lap action lap volt
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
                            std::cout<<"válassz színt!"<<std::endl; //bekéri, a válsztott színt
                            char c2;
                            std::cin>>c2;                           //és menti
                            Play(c, n, c2);                         //meghívja a server Play() függvényét
                        }else{                                      //ha vana  kezünkben a választott színből, akkor nem tehetjük ki ezt a lapot
                            std::cout<<"Nem hivhatod ki ezt a lapot, mert van a hivo szinu lapod!"<<std::endl;
                        }
                    }else{                                          //ha nem F, akkor további feltétel nélkül kijátszhatja a lapo
                        Play(c, n, c);                              //meghívja a server Play() függvényét
                    }
                }else{                                              //ha nem megfelelő a szín, nem játszahtja kia  lapot
                    std::cout<<"A hivott akciolapra csak ugyan olyan akciolapot tehetsz. Ha nincs nalad ilyen lap, valaszd a huzas/passz menut!"<<std::endl;
                }
            }else{                                                  //ha nem kell a korábbi lap utasításait betartanunk (vagy nem akciólap, vagy az előz játékosra vonatkozott
                if(c=='W'){                                         //ha a lap joker
                    if(n=='I'){                                     //és joker jap
                        std::cout<<"válassz színt!"<<std::endl;     //bekéri a választott színt
                        char c2;
                        std::cin>>c2;                               //ezt menti
                        Play(c, n, c2);                             //meghívja a server Play() függvényét
                    }else{                                          //ha joker húzz négyet
                        int j=0;
                        std::list<Card>::iterator i = Hand.begin(); //akkor megnézzi, hogy  a választott színből van-e a kézben
                        for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
                            if(playedCard.getColor2()==i->getColor()){
                                j++;
                            }
                          //  Card c = *i;
                          //  c.Print();
                          //  std::cout<<" ";
                        }
                        if(j==0){
                            std::cout<<"válassz színt!"<<std::endl;
                            char c2;
                            std::cin>>c2;
                            Play(c, n, c2);
                        }else{
                            std::cout<<"Nem hivhatod ki ezt a lapot, mert van a hivo szinu lapod!"<<std::endl;
                        }
                    }
                }else{                                              //ha nem joker lap
                    if(playedCard.getColor2()==c || playedCard.getNumber()==n){ //megnézi, hogy a színe, vagy a száma megegyezik-e a hívott lapéval
                        Play(c, n, c);                                          //akkor megnézzi, hogy  a választott színből van-e a kézben
                    }else{                                                      //ha sem a szín, sem a száma nem egyezik meg, a lap nem játszható ki
                        std::cout<<"Nem hivhatod ki ezt a lapot, mert sem a szine sem a szama nem egyezik meg a hívo lapeval!"<<std::endl;
                    }
                }
            }
        }
    }
    std::cout<<"jartam a PlayClient() fuggvenyben"<<std::endl;      //
}

void Table::Play(char c, char n, char c2)
{
    std::list<Card>::iterator j = Hand.end();           //létrehoz egy iterátort ami a keze első elemér mutat
    std::list<Card>::iterator i = Hand.begin();         //létrehoz egy iterátort ami a keze utolsó elemér mutat
    while(i != Hand.end()){                             //végigmegy a kézen
        if(i->getColor()==c && i->getNumber()==n){      //ha megtalálta a lapot
            j=i;                                        //a j-t átállítja ugy, hogy erre a lapra mutasson
            std::cout<<"Megtalaltam a lapot"<<std::endl;
        }
        i++;                                            //növeli i-t
    }

    playDeck.push_back(playedCard);                     //a hívott lapot a kijátszott lapok közé teszi
    playedCard=*j;                                      //a dobott lapt a hívott lapba teszi
    Hand.erase(j);                                      //j-t törli a kézből

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

void Table::Deal()
{
    for(int i=0; i<7; i++){
        Draw();
    }
    playedCard=drawDeck[(drawDeck.size())-1];
    drawDeck.pop_back();
    PrintTable();
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

void Table::PrintTable(){
    std::cout<<"A lapjaid: ";
    std::list<Card>::iterator i = Hand.begin();
    for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
        Card c = *i;
        c.Print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"A hivott lap: ";
    char col=playedCard.getColor();
    if(col=='W'){
        playedCard.Print();
        char col2=playedCard.getColor2();
        std::cout<<" A valasztott szin: "<<col2;
    }else{
        playedCard.Print();
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}


QString Table::Send(){
    QString data;
    data.clear();
    data.append(playedCard.getNumber());
    data.append(playedCard.getColor());
    data.append(playedCard.getColor2());
    std::list<Card>::iterator i = Hand.begin();
    for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
        Card c = *i;
        data.append(c.getNumber());
        data.append(c.getColor());
        data.append(c.getColor2());
    }
    return data;
}
