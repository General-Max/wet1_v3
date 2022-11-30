#include "SortById.h"

bool SortById::equalTo(shared_ptr<Player> player1, shared_ptr<Player> player2){
    return player1->getPlayerId()==player2->getPlayerId();
}

bool SortById::lessThan(shared_ptr<Player> player1, shared_ptr<Player> player2){
    return player1->getPlayerId() < player2->getPlayerId();
}

bool SortById::equalTo(shared_ptr<Player> player1, int otherId) {
    return player1->getPlayerId()==otherId;
}

bool SortById::lessThan(shared_ptr<Player> player1, int otherId){
    return player1->getPlayerId() < otherId;
}