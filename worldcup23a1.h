//
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_

#include "wet1util.h"
#include "Player.h"
#include "Team.h"
#include "AVLTree.h"
#include "TwoWayList.h"
#include "SortById.h"
#include "SortTeamById.h"

const int DRAW = 1;
const int WIN = 3;
const int PLAYERS_NUM_IN_VALID_TEAM = 11;
const int SINGLE_PLAYER = 1;
class world_cup_t {
private:

    // struct for the knockout_player function
    struct Pair {
        int m_teamId;
        int m_score;
    };

    int m_numPlayers;
    AVLTree<shared_ptr<Player>, SortByScore> m_playersByScore;
    AVLTree<shared_ptr<Player>, SortById> m_playersById;
    AVLTree<shared_ptr<Team>, SortTeamById> m_teams;
    AVLTree<shared_ptr<Team>, SortTeamById> m_validTeams;
    TwoWayList<shared_ptr<Player>> m_playersListByScore;

    /**
     * insert a new node to the players deque
     * @param newNode to be inserted to the list
     */
    void insertPlayerToList(AVLTree<shared_ptr<Player>, SortByScore>::BinNode* newNode);

    /**
     * return true if team has at least 11 players and at least one goalkeeper
     * @tparam S can be weak pointer or shared ptr pointer
     * @param team
     * @return
     */
    template<class S>
    bool isValidTeam(S team);

    /**
     * Adds the team to the valid teams tree in case it keeps valid team's condition
     * @param team
     */
    void addIfValidTeam(shared_ptr<Team> team);

    /**
     * remove a node from the valid tree teams in case the team is no longer a valid node
     * @param team
     */
    void removeIfNodValidTeam(shared_ptr<Team> team);

    /**
     * the id of the closest player to the current one
     * @param player
     * @param prevPlayer the player with closest score from beneath
     * @param nextPlayer the player with closest score from above
     * @return
     */
    int closest(shared_ptr<Player> player, shared_ptr<Player> prevPlayer, shared_ptr<Player> nextPlayer);

    /**
     * @param min
     * @param max
     * @return an array of pairs that contains the valid teams that their IDs are in
     * the bounds
     */
    Pair* fill(int min, int max);

    /**
     * recursively does the fill function task
     * @param pairs an array to fill
     * @param pos current position in the array
     * @param min
     * @param max
     * @param root
     */
    void fill_aux(Pair* pairs, int pos, int min, int max, AVLTree<shared_ptr<Team>, SortTeamById>::BinNode* root);


public:
    // <DO-NOT-MODIFY> {

    world_cup_t();
    virtual ~world_cup_t();

    StatusType add_team(int teamId, int points);

    StatusType remove_team(int teamId);

    StatusType add_player(int playerId, int teamId, int gamesPlayed,
                          int goals, int cards, bool goalKeeper);

    StatusType remove_player(int playerId);

    StatusType update_player_stats(int playerId, int gamesPlayed,
                                   int scoredGoals, int cardsReceived);

    StatusType play_match(int teamId1, int teamId2);

    output_t<int> get_num_played_games(int playerId);

    output_t<int> get_team_points(int teamId);

    StatusType unite_teams(int teamId1, int teamId2, int newTeamId);

    output_t<int> get_top_scorer(int teamId);

    output_t<int> get_all_players_count(int teamId);

    StatusType get_all_players(int teamId, int *const output);

    output_t<int> get_closest_player(int playerId, int teamId);

   output_t<int> knockout_winner(int minTeamId, int maxTeamId);

    // } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_
