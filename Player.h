#ifndef EX1_Player_H
#define EX1_Player_H

#include <ostream>
#include <memory>
class Team;
#include "TwoWayList.h"
using std::ostream;
using std::shared_ptr;

class Player{
public:
     Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalkeeper); // check for consts
    ~Player();

    int getPlayerId() const;

    int getTeamId() const;

    int getGamesPlayed() const;

    int getGoals() const;

    int getCards() const;

    bool getGoalKeeper() const;

    Team*  getTeamPtr();

    TwoWayList<shared_ptr<Player>>::ListNode* getDequePtr();

    void setDequePtr(TwoWayList<shared_ptr<Player>>::ListNode* newDequePtr);

    friend ostream& operator<<(ostream& os, const Player& player);

    void updateGamesPlayed(int newGamedNumber);

    void updateGoals(int newGoalsNumber);

    void updateCards (int newCardsNumber);

    //TODO: CHECK IF NEED
    void setGoalKeeper(bool isGoalKeeper);

    void setTeamPtr(Team*  teamPtr);
private:
    int m_playerId;
    int m_teamId;
    int m_gamesPlayed;
    int m_goals;
    int m_cards;
    bool m_goalKeeper;
    Team* m_team_ptr;
    TwoWayList<shared_ptr<Player>>::ListNode* m_dequePtr;

};

#endif // EX1_Player_H