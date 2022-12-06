#ifndef EX1_Team_H
#define EX1_Team_H

#include "AVLTree.h"
#include "SortById.h"
#include "SortByScore.h"

using std::shared_ptr;

class Player;

class Team{
public:
    /**
     * Constructor of Team
     * @param teamId
     * @param points
     */
    Team(int teamId, int points);
    /**
     * Destructor of team, destroy the team's players trees
     */
    ~Team() = default;

    /**
     * @return teh is of the team
     */
    int getTeamId() const;

    /**
     * @return the points of the team
     */
    int getPoints() const;

    /**
     * @return the nu,ber of games that the players of the team has played together
     */
    int getPlayedTogether() const;

    /**
     * @return the number of players in the team
     */
    int getTotalPlayers() const;

    /**
     * @return the sum of the goals of all teh players in this team
     */
    int getTotalGoals() const;

    /**
     * @return the sum of cards that all the players in this team received
     */
    int getTotalCards() const;

    /**
     * @return the team's score, computed by:
     * the points plus the difference between the total goals to the total cards
     */
    int getScore() const;

    /**
     * @return the number of goalkeepers in the team
     */
    int getGoalkeepers() const;

    /**
     * @return a tree of all the players in the team sorted by their score
     */
    AVLTree<shared_ptr<Player>, SortByScore> getScoreTree() const;

    /**
     * @return a tree of all the players in the team sorted by their ID
     */
    AVLTree<shared_ptr<Player>, SortById> getIdTree() const;

    /**
     * increase the number of games that the players played together by one
     */
    void increasePlayedTogether();

    /**
     * insert a new player to the cards and updates the params of the fields
     * @param player a new player
     */
    void insertPlayer(const shared_ptr<Player>& player);

    /**
     * remove a new player to the cards and updates the params of the fields
     * @param player
     */
    void removePLayer(shared_ptr<Player> player);

    /**
     * @return if there aren't any players in the team
     */
    bool isEmptyTeam() const;

    /**
     * Adds the given points to the total points of the team
     * @param points
     */
    void updatePoints(int points);

    /**
     * gets all players from one team and puts in the current
     * @param toMerge
     */
    void merge(shared_ptr<Team> toMerge);


    /**
     * gets all player from 2 teams and puts it in the current
     * @param team1
     * @param team2
     */
    void unite(shared_ptr<Team> team1, shared_ptr<Team> team2);

    template <class T>
    static shared_ptr<Player> * mergeSortedArrays(shared_ptr<Player>* targetArray, shared_ptr<Player>* mergedArray,
                                                  shared_ptr<Player>* newArray, int sizeTarget, int sizeMerged);

    /**
     * helper function for unite that relocates the players from two teams to the current
     * @tparam T comparison type
     * @param newTeamTree the tree of the team that all the players will be added to
     * @param team1Tree
     * @param team2Tree
     * @param toAddPlayers true if it is the first time this function called and we want the team counter and status
     * to change accordingly
     */
    template<class T>
    void uniteFillTree(AVLTree<shared_ptr<Player>, T>& newTeamTree,
                             AVLTree<shared_ptr<Player>, T>& team1Tree, AVLTree<shared_ptr<Player>, T>& team2Tree, bool toAddPlayers);
    /**
     * Helper function of merge that relocates the players from one team to the current
     * @tparam T
     * @param merged
     * @param targetTree
     * @param mergedTree
     */
    template<class T>
    void fillNewTree(shared_ptr<Team> merged, AVLTree<shared_ptr<Player> , T>& targetTree,  AVLTree<shared_ptr<Player> ,
            T>& mergedTree, bool toAddPlayers);

    template<class T>
    static shared_ptr<Player> * mergeSortedArraysByTrees(AVLTree<shared_ptr<Player> , T>& targetTree, AVLTree<shared_ptr<Player> , T>& mergedTree,
                                      int sizeTarget, int sizeMerged);

    /**
     * @return the id of the player with the best score
     */
    int getTopScorerId();

    /**
     * @param output an empty array that the function fills with IDs
     */
    void getTeamPlayers(int *const output);

    /**
     * @param playerId
     * @return a pointer to the player with the given ID
     */
    shared_ptr<Player> findPlayer(int playerId);

    /**
     * print operator for the team fields
     * @param os
     * @param team
     * @return
     */
    friend ostream& operator<<(ostream& os, const Team& team);

private:
    int m_teamId;
    int m_points;
    int m_playedTogether;
    int m_totalPlayers;
    int m_totalGoals;
    int m_totalCards;
    int m_goalkeepers;
    AVLTree<shared_ptr<Player>, SortById> m_teamPlayersByID;
    AVLTree<shared_ptr<Player>, SortByScore> m_teamPlayersByScore;
};

#endif //EX1_Team_H