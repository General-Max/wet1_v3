#ifndef EX1_Team_H
#define EX1_Team_H

#include "AVLTree.h"
#include "SortById.h"
#include "SortByScore.h"
#include <memory>

using std::shared_ptr;

class Player;

class Team{
public:
    Team(int teamId, int points);
    ~Team() = default;

    int getTeamId() const;
    int getPoints() const;
    int getPlayedTogether() const;
    int getTotalPlayers() const;
    int getTotalGoals() const;
    int getTotalCards() const;
    int getScore() const;
    int getGoalkeepers() const;
    AVLTree<shared_ptr<Player>, SortByScore> getScoreTree() const;
    AVLTree<shared_ptr<Player>, SortById> getIdTree() const;

    void increasePlayedTogether();
    void setTotalPlayers(int totalPlayers);
    void setTotalGoals(int totalGoals);
    void setTotalCards(int totalCards);

    void insertPlayer(shared_ptr<Player> player);
    void removePLayer(shared_ptr<Player> player);
    bool isEmptyTeam() const;
    void updatePoints(int points);

    void merge(shared_ptr<Team> merged);

    static void unite(shared_ptr<Team> team1, shared_ptr<Team> team2, int newTeamId);

    template<class T>
    void fillNewTree(shared_ptr<Team> merged, AVLTree<shared_ptr<Player> , T>& targetTree,  AVLTree<shared_ptr<Player> , T>& mergedTree, bool doInsert);

    template<class T>
    static shared_ptr<shared_ptr<Player>> mergeSortedArrays(AVLTree<shared_ptr<Player> , T>& targetTree, AVLTree<shared_ptr<Player> , T>& mergedTree,
                                      int sizeTarget, int sizeMerged);


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