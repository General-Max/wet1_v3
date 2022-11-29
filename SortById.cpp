#include "SortById.h"

bool SortById::equalTo(Player* player1, Player* player2){
    return player1->getPlayerId()==player2->getPlayerId();
}

bool SortById::lessThan(Player* player1, Player* player2){
    return player1->getPlayerId() < player2->getPlayerId();
}

bool SortById::equalTo(Player *player1, int otherId) {
    return player1->getPlayerId()==otherId;
}

bool SortById::lessThan(Player* player1, int otherId){
    return player1->getPlayerId() < otherId;
}