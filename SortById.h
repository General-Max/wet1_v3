//
// Created by User on 27/11/2022.
//

#ifndef DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H
#define DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H

#include "Player.h"

class SortById{
public:
    SortById() = default;
    ~SortById() = default;
    static bool equalTo(shared_ptr<Player> player1, shared_ptr<Player> player2);

    static bool lessThan(shared_ptr<Player> player1, shared_ptr<Player> player2);

    static bool equalTo(shared_ptr<Player> player1, int otherId);

    static bool lessThan(shared_ptr<Player> player1, int otherId);
};

#endif //DATA_STRUCTS1_V2_SORTINGTREEMETHODS_H
