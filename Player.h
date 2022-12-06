#ifndef EX1_Player_H
#define EX1_Player_H

#include <ostream>
#include <memory>
class Team;
#include "TwoWayList.h"
#include "SortByScore.h"

using std::ostream;
using std::shared_ptr;

class Player{
public:
    /**
     * Constructor of Player, created a new player with the given values:
     * @param playerId
     * @param teamId
     * @param gamesPlayed
     * @param goals
     * @param cards
     * @param goalkeeper true if the player can be a goal keeper, otherwise, false
     */
     Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalkeeper); // check for consts

     /**
      * destructor of player
      */
     ~Player() = default;


     /**
      * @return the id of the player
      */
    int getPlayerId() const;

    /**
     * @return the id of the team that the player belongs to
     */
    int getTeamId() const;

    /**
     * @return the number of games the player has played
     */
    int getGamesPlayed() const;

    /**
     * @return the number of goals of the player
     */
    int getGoals() const;

    /**
     * @return the number of cards that the player received
     */
    int getCards() const;

    /**
     * @return true if the player can be a goal keeper, else false
     */
    bool getGoalKeeper() const;

    /**
     * @return a pointer to the team that the player belongs to
     */
    Team*  getTeamPtr();


    /**
     * @return a pointer to the node that contains this player data in the deque
     */
    TwoWayList<shared_ptr<Player>>::ListNode* getDequePtr();

    /**
     * set a pointer to the node that contains this player data in the deque
     * @param newDequePtr
     */
    void setDequePtr(TwoWayList<shared_ptr<Player>>::ListNode* newDequePtr);

    /**
     * prints this player details
     * @param os
     * @param player
     * @return
     */
    friend ostream& operator<<(ostream& os, const Player& player);

    /**
     * add the new games number to the current one
     * @param newGamedNumber
     */
    void updateGamesPlayed(int newGamedNumber);

    /*
     * add the new games number to the current one
     * @param newGoalsNumber
     */
    void updateGoals(int newGoalsNumber);

    /**
     * add the new games number to the current one
     * @param newCardsNumber
     */
    void updateCards (int newCardsNumber);

    /**
     * determine if the player can be a goal keeper or not
     * @param isGoalKeeper
     */
    void setGoalKeeper(bool isGoalKeeper);

    /**
     * Sets the pointer to the team that the player belongs to
     * @param teamPtr
     */
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