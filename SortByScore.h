#ifndef DATA_STRUCTS1_V2_SORTBYSCORE_H
#define DATA_STRUCTS1_V2_SORTBYSCORE_H

#include "Player.h"
using std::shared_ptr;
class Player;

class SortByScore{
public:
    // Default Destructor and Constructor
    SortByScore() = default;
    ~SortByScore() = default;

    /**
     * gets 2 players and compare them by their score (goals -> cards -> IDs)
     * @param player1
     * @param player2
     * @return true if the players has the same score, else false
     */
    static bool equalTo(shared_ptr<Player> player1, shared_ptr<Player> player2);

    /**
     * gets 2 players and compare them by their score (goals -> cards -> IDs)
     * @param player1
     * @param player2
     * @return true if player 1 has smaller score than the one of player 2,
     * else false
     */
    static bool lessThan(shared_ptr<Player> player1, shared_ptr<Player> player2);

    /**
     * gets a player and a score and compare them by their score (goals -> cards -> IDs)
     * @param player1
     * @param otherGoals
     * @return true if the player has the given score
     */
    static bool equalTo(shared_ptr<Player> player1, int otherGoals);

    /**
     *  gets a player and a score and compare them by their score (goals -> cards -> IDs)
     * @param player1
     * @param otherGoals
     * @return true if the player has smaller score than the given score
     */
    static bool lessThan(shared_ptr<Player> player1, int otherGoals);
};

#endif //DATA_STRUCTS1_V2_SORTBYSCORE_H
