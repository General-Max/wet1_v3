#ifndef EX1_Team_H
#define EX1_Team_H

#include "AVLTree.h"
#include "SortById.h"
#include "SortByScore.h"

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
    AVLTree<Player*, SortByScore> getScoreTree() const;
    AVLTree<Player*, SortById> getIdTree() const;

    void increasePlayedTogether();
    void setTotalPlayers(int totalPlayers);
    void setTotalGoals(int totalGoals);
    void setTotalCards(int totalCards);

    void insertPlayer(Player* player);
    void removePLayer(Player* player);
    bool isEmptyTeam() const;
    void updatePoints(int points);

    void merge(Team* merged);

    static void unite(Team* team1, Team* team2, int newTeamId);

    template<class T>
    void fillNewTree(Team* merged, AVLTree<Player* , T>& targetTree,  AVLTree<Player* , T>& mergedTree, bool doInsert);

    template<class T>
    static Player** mergeSortedArrays(AVLTree<Player* , T>& targetTree, AVLTree<Player* , T>& mergedTree,
                                      int sizeTarget, int sizeMerged);


private:
    int m_teamId;
    int m_points;
    int m_playedTogether;
    int m_totalPlayers;
    int m_totalGoals;
    int m_totalCards;
    int m_goalkeepers;
    AVLTree<Player*, SortById> m_teamPlayersByID;
    AVLTree<Player*, SortByScore> m_teamPlayersByScore;
};

#endif //EX1_Team_H