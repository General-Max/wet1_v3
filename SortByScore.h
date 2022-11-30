#ifndef DATA_STRUCTS1_V2_SORTBYSCORE_H
#define DATA_STRUCTS1_V2_SORTBYSCORE_H

#include "Player.h"
using std::shared_ptr;
class Player;

class SortByScore{
public:
    SortByScore() = default;
    ~SortByScore() = default;

    static bool equalTo(shared_ptr<Player> player1, shared_ptr<Player> player2);

    static bool lessThan(shared_ptr<Player> player1, shared_ptr<Player> player2);

    static bool equalTo(shared_ptr<Player> player1, int otherGoals);

    static bool lessThan(shared_ptr<Player> player1, int otherGoals);
};

#endif //DATA_STRUCTS1_V2_SORTBYSCORE_H
