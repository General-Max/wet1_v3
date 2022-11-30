#include <iostream>
#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "SortById.h"
#include "SortByScore.h"
#include "SortTeamById.h"
#include <memory>
#include "worldcup23a1.h"
using std::shared_ptr;
using std::cout;
using std::endl;

int main() {
    cout << "Hello, World!" << endl;
    world_cup_t world;
    world.add_team(1, 0);
    world.add_team(2, 0);
    world.add_team(3, 0);
    world.add_team(4, 0);
    world.remove_team(3);
    world.add_player(21, 1, 2, 1, 20, true);
    world.add_player(25, 1, 1, 1, 20, false);
    world.add_player(3, 1, 1, 1, 5, false);
    world.add_player(4, 1, 1, 1, 1, false);
    world.add_player(5, 1, 1, 2, 5, false);
    world.add_player(6, 2, 2, 2, 4, true);
    world.add_player(24, 1, 1, 2, 3, true);
    world.update_player_stats(25, 1, 2, 1);
    world.get_num_played_games(25);
    world.play_match(1, 2);
    world.get_num_played_games(25);
    world.add_player(7, 1, 1, 2, 2, true);
    world.add_player(8, 1, 1, 2, 1, true);
    world.add_player(9, 1, 1, 5, 30, true);
    world.add_player(10, 1, 1, 5, 29, true);
    world.add_player(11, 1, 1, 5, 28, true);
    world.add_player(12, 1, 1, 5, 27, true);
    world.add_player(51, 1, 1, 6, 40, true);
    world.add_player(52, 1, 1, 6, 40, true);
    world.add_player(53, 1, 1, 6, 40, true);
    world.add_player(54, 1, 1, 6, 10, true);
    world.add_player(60, 1, 1, 6, 5, true);
    world.add_player(70, 1, 1, 6, 4, true);
    world.add_player(100, 1, 1, 8, 6, true);
    world.add_player(80, 1, 1, 10, 7, true);
    world.add_player(90, 1, 1, 10, 7, true);
    world.remove_team(2);
    world.remove_player(21);
    world.unite_teams(1, 2, 1);
    std::shared_ptr<std::shared_ptr<int>> table;

    //reset the table to fit an array of 10 nodes
    table.reset(new std::shared_ptr<int>[10],[](std::shared_ptr<int> * p) {delete [] p;});

    cout << "the points of team 1:" << world.get_team_points(1).ans() << endl;
    cout << "--------------------------\n";
    cout << "try to unite:\n";
    world.unite_teams(1,2,2);
    cout << "united:\n";
    return 0;
}
