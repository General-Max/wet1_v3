#ifndef EX1_Player_H
#define EX1_Player_H

#include <ostream>
class Team;
//#include "ListNode.h"
using std::ostream;


class Player{
public:
     Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalkeeper); // check for consts
    ~Player() =default;

    int getPlayerId() const;

    int getTeamId() const;

    int getGamesPlayed() const;

    int getGoals() const;

    int getCards() const;

    bool getGoalKeeper() const;

  //  Team* getTeamPtr();

    //ListNode<Player*>* getDequePtr();

  //  void setDequePtr(ListNode<Player*>* newDequePtr);

    friend ostream& operator<<(ostream& os, const Player& player);

    void updateGamesPlayed(int newGamedNumber);

    void updateGoals(int newGoalsNumber);

    void updateCards (int newCardsNumber);

    //TODO: CHECK IF NEED
    void setGoalKeeper(bool isGoalKeeper);

    //void setTeamPtr(Team* teamPtr);
private:
    int m_playerId;
    int m_teamId;
    int m_gamesPlayed;
    int m_goals;
    int m_cards;
    bool m_goalKeeper;
    shared_ptr<Team> m_team_ptr;
    //ListNode<Player*>* m_dequePtr;
};

#endif // EX1_Player_H