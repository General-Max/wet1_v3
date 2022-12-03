//
// Created by User on 27/11/2022.
//

#ifndef DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H
#define DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H

#include "Player.h"

class SortById{
public:
    // Default Destructor and Constructor

    SortById() = default;
    ~SortById() = default;

    /**
     * gets 2 players and compare them by their ID
     * @param player1
     * @param player2
     * @return true if the players has the same id, else false
     */
    static bool equalTo(shared_ptr<Player> player1, shared_ptr<Player> player2);

    /**
     * gets 2 players and compare them by their ID
     * @param player1
     * @param player2
     * @return true if the id of player 1 is smaller from the one of player 2
     */
    static bool lessThan(shared_ptr<Player> player1, shared_ptr<Player> player2);

    /**
     * gets a player and an ID and compare them by their ID
     * @param player1
     * @param otherId
     * @return true if the id of player 1 is equal to the given id, else false
     */
    static bool equalTo(shared_ptr<Player> player1, int otherId);

    /**
     *  gets a player and an ID and compare them by their ID
     * @param player1
     * @param otherId
     * @return true if the id of player 1 is smaller than the one of the given
     * id, else false
     */
    static bool lessThan(shared_ptr<Player> player1, int otherId);
};

#endif //DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H
