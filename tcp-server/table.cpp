#include "table.h"

#define RANDOM_INTREVAL 4500;
#define DIRSTRIBUTED_CARD 7;

Table::Table()
{
    std::cout<<"Beleptem a Table konstruktotraba"<<std::endl;
    std::map<int, Card> deck;               //ebbe kerülnek véletlenszerűen a lapok
    srand(time(NULL));                      //elindul a rendomizálás
    char numbers[13]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'S', 'D', 'R'};
                                            //feltöltjük a lapok lehetséges értékeivel, hogy innen adhassunk értéket a lakop attributumának a példányosítás során
    char color[4]={'R', 'G', 'B', 'Y'};     //feltöltjük a lapok lehetséges színeivel, hogy innen adhassunk értékel a lakop attributumának a példányosítás során
    for(int i=0; i<4; i++){                  //beállítja a pédányosításhoz a színt
            for(int j=0; j<13; j++){            //0-tol R-ig innen kapja a számot a lap
            Card c;                             //példányost egy kértyalapot
            c.setColor(color[i]);               //értéket ada színének
            c.setNumber(numbers[j]);            //értéket ada számának
            int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
            while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
                k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
            }                                   //
            deck[k] = c;                        //ha nincs egyezés bekerül a map-be
        }

        for(int j=1; j<13; j++){                //1-tol R-ig innen kapja a számot a lap
            Card c;                             //példányost egy kértyalapot
            c.setColor(color[i]);               //értéket ada színének
            c.setNumber(numbers[j]);            //értéket ada számának
            int k = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
            while(deck.find(k)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
                k = rand() % RANDOM_INTREVAL;   //új kulcsot kér
            }                                   //
            deck[k] = c;                        //ha nincs egyezés bekerül a map-be
        }
    }

    for(std::map<int, Card>::iterator i=deck.begin(); i!=deck.end(); i++){  //végigmegy a map-en
        drawDeck.push_back(i->second);      //az összekevert lapok a húzó pakliba kerülnek
    }
}

Table::~Table()
{

}

/*void Table::PrintDrawDeck()
{
    std::cout<<"Beleptem a PrintDrawDeck() fugvenybe"<<std::endl;
    for(int i=0; i<drawDeck.size(); i++){
        drawDeck[i].Print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}
*/

void Table::ShuffleDrawDeck()
{
    std::map<int, Card> deck;               //ebbe kerülnek véletlenszerűen a lapok
    srand(time(NULL));                      //elindul a rendomizálás
    for(int i = 0; i<playDeck.size(); i++){ //végigmegy a dobó paklin
        int j = rand() % RANDOM_INTREVAL;   //random kulcsot ad a kártyalap mellé
        while(deck.find(j)!=deck.end()){    //ha már kiosztotta a kulcsot elveszne a kártyalap
            j = rand() % RANDOM_INTREVAL;   //új kulcsot kér
        }                                   //
        deck[j] = playDeck[i];              //ha noinc segyezés bekerül a map-be
    }

    playDeck.clear();                       //kiüríti a dobó paklit

    for(std::map<int, Card>::iterator i=deck.begin(); i!=deck.end(); i++){  //végigmegy a map-en
        drawDeck.push_back(i->second);      //az összekevert lapok a húzó pakliba kerülnek
    }
}

void Table::Draw()
{
    std::cout<<"Beleptem a Draw() fuggvenybe"<<std::endl;
   /* Card d;
    int i = drawDeck.size();
    std::cout<<i<<std::endl;
    d = drawDeck[(drawDeck.size())-1];
    d.Print();*/
    Hand.push_back(drawDeck[(drawDeck.size())-1]);
    drawDeck.pop_back();
    for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
        Card c = *i;
        c.Print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}

void Table::Play(char c, char n)
{
//    if(Hand.size()!=0){
//        char c, n;
//        std::cout<<"A dobando lap szine:"<<std::endl;
//        std::cin>>c;
//        std::cout<<"A dobando lap szama:"<<std::endl;
//        std::cin>>n;
        std::list<Card>::iterator j = Hand.end();
        std::list<Card>::iterator i = Hand.begin();
        while(i != Hand.end()){
            if(i->getColor()==c && i->getNumber()==n){
                j=i;
                std::cout<<"Megtalaltam a lapot"<<std::endl;
            }
            i++;
        }
//        if(j==Hand.end()){
//            std::cout<<"Ninc silyen lapot a kezedben. Kerlek adj meg masikat!"<<std::endl;
//            Play();
//        }else{
            drawDeck.push_back(playedCard);
            playedCard=*j;
            Hand.erase(j);
            for(std::list<Card>::iterator i = Hand.begin(); i != Hand.end(); i++){
                Card c = *i;
                c.Print();
                std::cout<<" ";
            }
            std::cout<<std::endl;
            playedCard.Print();
            std::cout<<std::endl;
//        }
//    }
//    std::cout<<"jartam a Play() fuggvenyben"<<std::endl;
}

void Table::Deal()
{
    for(int i=0; i<7; i++){
        Draw();
    }
    playedCard=drawDeck[(drawDeck.size())-1];
    drawDeck.pop_back();
}


