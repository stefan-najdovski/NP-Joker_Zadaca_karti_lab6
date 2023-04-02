#include <cstdio>
#include <raylib.h>
#include <cstring>
#include <random>

#define CARDS 54
#define FACES 15

struct card {
    const char *face;
    const char *suit;
};

typedef struct card Card;

void fillDeck( Card * wDeck, const char * wFace[],
               const char * wSuit[] );
void shuffle( Card * wDeck );
void deal(const Card* const wDeck[], Card* player1[], Card* player2[], Card* player3[], Card* player4[]);
bool hasDuplicates(const Card * const wDeck[], size_t size);
int countCards(size_t size);
int getCardValue(const Card *card, const char *wFace[], const char *wSuit[]);
void sortDeck(Card *wDeck, const char *wFace[], const char *wSuit[]);
int getCardIndex(const char *face, const char *suit, const char *wFace[], const char *wSuit[]);
void printCards(const Card * const player[], size_t numCards);


int main() {
    Card deck[CARDS];

    const char *face[] = {"Ace", "Deuce", "Three", "Four", "Five",
                          "Six", "Seven", "Eight", "Nine", "Ten",
                          "Jack", "Queen", "King", "Joker1", "Joker2"};

    const char *suit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};


    fillDeck(deck, face, suit);
    shuffle(deck);
    int totalCards = countCards(CARDS);
    printf("Total number of cards: %d\n", totalCards);


    Card *player1[CARDS / 4], *player2[CARDS / 4], *player3[CARDS / 4], *player4[CARDS / 4];
    for (int i = 0; i < CARDS / 4; i++) {
        player1[i] = &deck[i * 4];
        player2[i] = &deck[i * 4 + 1];
        player3[i] = &deck[i * 4 + 2];
        player4[i] = &deck[i * 4 + 3];
    }

    printf("\n Играч 1:\n");
    printCards(player1, CARDS / 4);
    printf("\n Играч 2:\n");
    printCards(player2, CARDS / 4);
    printf("\n Играч 3:\n");
    printCards(player3, CARDS / 4);
    printf("\n Играч 4:\n");
    printCards(player4, CARDS / 4);


    if (hasDuplicates(player1, CARDS / 4)) {
        printf("Player 1 has duplicate cards!\n");
    }

    if (hasDuplicates(player2, CARDS / 4)) {
        printf("Player 2 has duplicate cards!\n");
    }

    if (hasDuplicates(player3, CARDS / 4)) {
        printf("Player 3 has duplicate cards!\n");
    }

    if (hasDuplicates(player4, CARDS / 4)) {
        printf("Player 4 has duplicate cards!\n");
    }

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Card Game");

    Texture2D cardTextures[CARDS];
    Texture2D cardBackTexture = LoadTexture("cards/back.png");
    for (int i = 0; i < 52; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "cards/%d_of_%s.png", i % 13 + 1,
                 (i / 13 == 0 ? "clubs" : i / 13 == 1 ? "diamonds" : i / 13 == 2 ? "hearts" : "spades"));

        cardTextures[i] = LoadTexture(filename);
    }
    cardTextures[52] = LoadTexture("cards/black_joker.png");
    cardTextures[53] = LoadTexture("cards/red_joker.png");


    while (!WindowShouldClose()) {


        if (IsKeyPressed(KEY_S)) {
            shuffle(deck);

        } else if(IsKeyPressed(KEY_R)){
            sortDeck(deck, face, suit);
        }


        BeginDrawing();


        ClearBackground(BLACK);

        auto screenWidth = (float) GetScreenWidth();
        auto screenHeight = (float) GetScreenHeight();


        const float CARD_SCALE = screenWidth / 4000.0f;
        const float CARD_SPACING_X = screenWidth / 80.0f;


        const float ROW_SPACING_Y = screenHeight / 6.0f;

        int numRows = CARDS / 13;
        Rectangle srcRect = {0.0f, 0.0f, (float) cardTextures[0].width,
                             (float) cardTextures[0].height};
        for (int col = 0; col < CARDS / 4; col++) {
            for (int row = 0; row < numRows; row++) {
                float x = screenWidth / 20 + (float) col * ((float) cardTextures[0].width * CARD_SCALE + CARD_SPACING_X);
                float y = ROW_SPACING_Y * (float) (row + 1) - (float) cardTextures[0].height * CARD_SCALE / 2;

                Card *currentPlayer;
                switch (row) {
                    case 0:
                        currentPlayer = player1[col];
                        break;
                    case 1:
                        currentPlayer = player2[col];
                        break;
                    case 2:
                        currentPlayer = player3[col];
                        break;
                    default:
                        currentPlayer = player4[col];
                        break;
                }

                int cardIndex = getCardIndex(currentPlayer->face, currentPlayer->suit, face, suit);
                Rectangle destRect = {x, y, CARD_SCALE * (float) cardTextures[cardIndex].width,
                                      CARD_SCALE * (float) cardTextures[cardIndex].height};

                Rectangle cardBackDestRect = {x , y , CARD_SCALE * (float) cardBackTexture.width,
                                              CARD_SCALE * (float) cardBackTexture.height};
                DrawTexturePro(cardBackTexture, cardBackDestRect, cardBackDestRect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(cardTextures[cardIndex], srcRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
            }
        }
        DrawText("Stefan Najdovski \t INKI \t 6 4 8 \t Joker Zadaca", 10, (int) screenHeight - 95, 20, WHITE);
        DrawText("S - Izmesaj gi kartite so pomos na Fisher–Yates shuffle algoritam.", 10, (int) screenHeight - 45, 18, WHITE);
        DrawText("R - Za kartite da se podredat vertikalno (od levo kon desno)", 10, (int) screenHeight - 65, 18, WHITE);
        DrawText("ESC - EXIT", 10, (int) screenHeight - 25, 18, WHITE);

        EndDrawing();
    }


    for (const auto &cardTexture : cardTextures) {
        UnloadTexture(cardTexture);
    }
    CloseWindow();
    return 0;
}


void fillDeck( Card * const wDeck, const char * wFace[],
               const char * wSuit[] )
{
    size_t i;


    for ( i = 0; i < CARDS; ++i ) {
        wDeck[ i ].face = wFace[ i % FACES ];
        wDeck[ i ].suit = wSuit[ i / FACES ];
    }
}

void shuffle(Card *const wDeck) {
    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = CARDS - 1; i > 0; --i) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(g);
        Card temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal(Card * const wDeck[], Card* player1[], Card* player2[], Card* player3[], Card* player4[]) {
    for (size_t i = 0; i < CARDS / 4; ++i) {
        player1[i] = wDeck[i * 4];
        player2[i] = wDeck[i * 4 + 1];
        player3[i] = wDeck[i * 4 + 2];
        player4[i] = wDeck[i * 4 + 3];
    }
}



bool hasDuplicates(const Card * const wDeck[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (wDeck[i] == wDeck[j]) {
                return true;
            }
        }
    }
    return false;
}

int countCards(size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        ++count;
    }
    return count;
}


int getCardValue(const Card *card, const char *wFace[], const char *wSuit[]) {
    int faceValue = 0;
    int suitValue = 0;

    for (int i = 0; i < FACES; ++i) {
        if (strcmp(card->face, wFace[i]) == 0) {
            faceValue = i;
            break;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (strcmp(card->suit, wSuit[i]) == 0) {
            suitValue = i;
            break;
        }
    }

    return suitValue * FACES + faceValue;
}

void sortDeck(Card *wDeck, const char *wFace[], const char *wSuit[]) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < CARDS - 1; ++i) {
            int card1Value = getCardValue(&wDeck[i], wFace, wSuit);
            int card2Value = getCardValue(&wDeck[i + 1], wFace, wSuit);

            if (card1Value > card2Value) {
                Card temp = wDeck[i];
                wDeck[i] = wDeck[i + 1];
                wDeck[i + 1] = temp;
                sorted = false;
            }
        }
    }
}


int getCardIndex(const char *face, const char *suit, const char *wFace[], const char *wSuit[]) {
    int faceIndex = 0;
    int suitIndex = 0;

    for (int i = 0; i < FACES; ++i) {
        if (strcmp(face, wFace[i]) == 0) {
            faceIndex = i;
            break;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (strcmp(suit, wSuit[i]) == 0) {
            suitIndex = i;
            break;
        }
    }

    return faceIndex + suitIndex * FACES;
}

void printCards(const Card * const player[], size_t numCards) {
    for (size_t i = 0; i < numCards; ++i) {
        printf("%5s of %-8s%s", player[i]->face, player[i]->suit, (i + 1) % 4 ? " " : "\n");
    }
}

