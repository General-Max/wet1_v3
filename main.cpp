#include <iostream>
#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "SortById.h"
#include "SortByScore.h"
#include "SortTeamById.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //AVLTree<Player*, SortById> playersT;
    AVLTree<Player*, SortByScore> playersST;

//    Player* p1 = new Player(21, 1, 0, 1, 20, true);
//    Player* p2 = new Player(25, 1, 1, 1, 20, false);
//    Player* p3 = new Player(3, 1, 1, 1, 5, false);
//
//    std::cout << "---------------------" << std::endl;
//
//    playersST.insert(p1);
//    playersST.printD(playersST.getRoot(), 10);
//    std::cout << "---------------------\n";
//    playersST.insert(p2);
//    playersST.printD(playersST.getRoot(), 10);
//    std::cout << "---------------------";
//
//    playersST.insert(p3);
//
//    playersST.printD(playersST.getRoot(), 10);

    return 0;
}
