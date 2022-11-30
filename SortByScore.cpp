#include "SortByScore.h"

bool SortByScore::equalTo(shared_ptr<Player> player1, shared_ptr<Player>player2) {
    return player1->getPlayerId()==player2->getPlayerId();
}

bool SortByScore::lessThan(shared_ptr<Player>player1, shared_ptr<Player>player2) {
    if(player1->getGoals() < player2->getGoals()){
        return true;
    }
    else if(player1->getGoals() > player2->getGoals()){
        return false;
    }

    // in case both players have the same number of goals
    if(player1->getCards() > player2->getCards()){
        return true;
    }
    else if(player1->getCards() < player2->getCards()){
        return false;
    }

    // in case both players have the same number of cards
    if(player1->getPlayerId() < player2->getPlayerId()){
        return true;
    }
    return false;
}

bool SortByScore::equalTo(shared_ptr<Player>player1, int otherGoals) {
    return player1->getGoals() == otherGoals;
}

bool SortByScore::lessThan(shared_ptr<Player>player1, int otherGoals) {
    return player1->getGoals() < otherGoals;
}

