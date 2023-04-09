#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

struct Card {
    std::string face;
    std::string value;
    bool isJoker;
};


//spored Fisher-Yates
void shuffleCards(Card *cards, int numCards) {
    std::srand(std::time(0));
    
    Card* end = cards + numCards - 1;
    for (Card* i = end; i > cards; i--) {
        int j = std::rand() % (i - cards + 1);
        std::swap(*i, *(cards + j));
    }
}

int main() {
    const std::string faces[] = {"Srce", "Detelina", "Lokum", "List"};
    const std::string nums[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const int numFaces = sizeof(faces) / sizeof(faces[0]);
    const int numValues = sizeof(nums) / sizeof(nums[0]);

    // Niza so obicni karti
    Card cards[54];
    Card *pc = &cards[0];
    for (int v = 0; v < numValues; v++) {
        for (int f = 0; f < numFaces; f++) {
            pc->face = faces[f];
            pc->value = nums[v];
            pc->isJoker = false;
            pc++;
        }
    }

    // Dodavame jokeri vo nizata (posledni dva indeksi)
    pc->face = "Joker";
    pc->value = "J1";
    pc->isJoker = true;
    pc++;
    
    pc->face = "Joker";
    pc->value = "J2";
    pc->isJoker = true;
    pc++;


    // Pecatime karti 
    pc = &cards[0];
    int b = 4;
    for (int i = 0; i < 54; i++) {
        std::cout << pc->face << " " << pc->value << std::endl;
        
        //se koristi za dodavanje na nova linija pomegu 4 karti za podobra preglednost
        b--;
        if(b == 0){
            std::puts("");
            b = 4;
        }
        pc++;
    }


    shuffleCards(cards, 54);
    
    //Izmesani
    std::cout << "\nIzmesani Karti:\n";
    int numOfCards = 0;
    for (Card* i = cards; i < cards + 54; i++) {
        std::cout << i->face << " " << i->value << std::endl;
    }


    // Distribucija na kartite
    Card playerCards[4][14]; // do 14 karti za sekoj igrac 14+14+13+13
    int cardCounts[4] = {0, 0, 0, 0}; // Sledi broj na karti
    int playerIndex = 0;
    for (Card* i = cards; i < cards + 54; i++) {
        playerCards[playerIndex][cardCounts[playerIndex]] = *i;
        cardCounts[playerIndex]++;
        playerIndex = (playerIndex + 1) % 4;
    }
    
    for (int i = 0; i < 4; i++) {
        std::cout << "\nIgrac " << i + 1 << " karti:\n";
        for (int j = 0; j < cardCounts[i]; j++) {
            std::cout << playerCards[i][j].face << " " << playerCards[i][j].value << std::endl;
        }
    }

    std:puts("");
    std::cout<<"Debug:"<<std::endl;
    std::cout<<cardCounts[0]<<std::endl;
    std::cout<<cardCounts[1]<<std::endl;
    std::cout<<cardCounts[2]<<std::endl;
    std::cout<<cardCounts[3]<<std::endl;
    
    return 0;
}
