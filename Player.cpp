#include "Player.h"
//#include "Team.h"

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalkeeper) : m_playerId(playerId),
                                                                                                   m_teamId(teamId), m_gamesPlayed(gamesPlayed), m_goals(goals), m_cards(cards), m_goalKeeper(goalkeeper){}

//Player::~Player()
//{
//    //delete this->m_dequePtr;
//}

int Player::getPlayerId() const {
    return this->m_playerId;
}

int Player::getTeamId() const {
    return this->m_teamId;
}

int Player::getGamesPlayed() const {
    return this->m_gamesPlayed;
}

int Player::getGoals() const {
    return this->m_goals;
}

bool Player::getGoalKeeper() const {
    return this->m_goalKeeper;
}

int Player::getCards() const {
    return this->m_cards;
}

ostream& operator<<(ostream& os, const Player& player)
{
    os << "player id: " <<  player.getPlayerId() << ", goals: " << player.getGoals() << ", cards: "
       << player.getCards();
    return os;
}

void Player::updateGamesPlayed(int newGamedNumber) {
    this->m_gamesPlayed += newGamedNumber;
}

void Player::updateGoals(int newGoalsNumber) {
    this->m_goals += newGoalsNumber;
}

void Player::updateCards(int newCardsNumber) {
    this->m_cards += newCardsNumber;
}

void Player::setGoalKeeper(bool isGoalKeeper) {
    this->m_goalKeeper = isGoalKeeper;
}

//ListNode<Player *>* Player::getDequePtr() {
//    return m_dequePtr;
//}
//
//void Player::setDequePtr(ListNode<Player*>* newDequePtr) {
//    this->m_dequePtr = newDequePtr;
//}
//
//void Player::setTeamPtr(Team *teamPtr) {
//    m_team_ptr = teamPtr;
//}
//
//Team *Player::getTeamPtr() {
//    return m_team_ptr;
//}



