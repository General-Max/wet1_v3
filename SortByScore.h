#ifndef DATA_STRUCTS1_V2_SORTBYSCORE_H
#define DATA_STRUCTS1_V2_SORTBYSCORE_H

#include "Player.h"

class SortByScore{
public:
    SortByScore() = default;
    ~SortByScore() = default;

    static bool equalTo(Player* player1, Player* player2);

    static bool lessThan(Player* player1, Player* player2);

    static bool equalTo(Player* player1, int otherGoals);

    static bool lessThan(Player* player1, int otherGoals);
};

#endif //DATA_STRUCTS1_V2_SORTBYSCORE_H
