#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points) : m_teamId(teamId),m_points(points), m_playedTogether(0),
                                     m_totalPlayers(0), m_totalGoals(0), m_totalCards(0), m_goalkeepers(0) {}

int Team::getTeamId() const
{
    return this->m_teamId;
}
int Team::getPoints() const
{
    return this->m_points;
}
int Team::getPlayedTogether() const
{
    return this->m_playedTogether;
}

int Team::getTotalPlayers() const
{
    return this->m_totalPlayers;
}

int Team::getTotalGoals() const
{
    return this->m_totalGoals;
}

int Team::getTotalCards() const
{
    return this->m_totalCards;
}

void Team::increasePlayedTogether()
{
    this->m_playedTogether++;
}

bool Team::isEmptyTeam() const {
    return m_totalPlayers == 0;
}

void Team::insertPlayer(const shared_ptr<Player>& player)
{
    if(player->getGoalKeeper()){
        this->m_goalkeepers++;
    }
    m_teamPlayersByID.insert(player);
    m_teamPlayersByScore.insert(player);
    m_totalCards+=player->getCards();
    m_totalGoals+=player->getGoals();
    m_totalPlayers++;
    //needs to be finishid !!!!
}

void Team::updatePoints(int points) {
    this->m_points += points;
}

int Team::getScore() const
{
    return this->m_points+ (this->m_totalGoals - this->m_totalCards);
}

void Team::removePLayer(shared_ptr<Player> player) {
    if(player->getGoalKeeper()){
        this->m_goalkeepers--;
    }
    m_teamPlayersByID.remove(player);
    m_teamPlayersByScore.remove(player);
    m_totalCards-=player->getCards();
    m_totalGoals-=player->getGoals();
    m_totalPlayers--;
}

int Team::getGoalkeepers() const {
    return m_goalkeepers;
}

AVLTree<shared_ptr<Player>, SortByScore> Team::getScoreTree() const
{
    return this->m_teamPlayersByScore;
}

AVLTree<shared_ptr<Player>, SortById> Team::getIdTree() const
{
    return this->m_teamPlayersByID;
}


template<class T>
shared_ptr<Player> * Team::mergeSortedArrays(AVLTree<shared_ptr<Player>, T> &targetTree, AVLTree<shared_ptr<Player>, T> &mergedTree,
                        int sizeTarget, int sizeMerged){
    shared_ptr<Player>* targetArray = targetTree.inOrderArray();
    shared_ptr<Player>* mergedArray = mergedTree.inOrderArray();

    int size = sizeTarget+sizeMerged;

    shared_ptr<Player>* newTeam = new shared_ptr<Player>[size];
    int index1=0;
    int index2=0;
    int i=0;
    while(index1<sizeTarget && index2<sizeMerged){
        if(T::lessThan(targetArray[index1], mergedArray[index2])){
            newTeam[i] = targetArray[index1];
            index1++;
        }
        else{
            newTeam[i] = mergedArray[index2];
            index2++;
        }
        i++;
    }

    for(int j = index1; j<sizeTarget;j++)
    {
        newTeam[i]=targetArray[index1];
        index1++;
        i++;
    }

    for(int j = index2; j<sizeMerged;j++)
    {
        newTeam[i]=mergedArray[index2];
        index2++;
        i++;
    }

    for(int i = 0; i<sizeTarget; i++){
        *(targetArray+i)= nullptr;
    }

    for(int i = 0; i<sizeMerged; i++){
        *(mergedArray+i)= nullptr;
    }

    delete[] targetArray;
    delete[] mergedArray;
    return newTeam;
}

void Team::merge(shared_ptr<Team> toMerge)
{
    fillNewTree(toMerge, this->m_teamPlayersByID, toMerge->m_teamPlayersByID);
    fillNewTree(toMerge, this->m_teamPlayersByScore, toMerge->m_teamPlayersByScore);
    this->updatePoints(toMerge->getPoints());
}

template<class T>
void Team::fillNewTree(shared_ptr<Team> toMerge, AVLTree<shared_ptr<Player>, T>& targetTree, AVLTree<shared_ptr<Player>, T>& mergedTree) {
    int sizeTarget = targetTree.getSize();
    int sizeMerged = mergedTree.getSize();
    int size = sizeTarget+sizeMerged;

    shared_ptr<Player>* newArray = mergeSortedArrays(targetTree, mergedTree, sizeTarget, sizeMerged);

    targetTree.emptyTree();
    mergedTree.emptyTree();

    for(int i=0;i<size;i++){
        if(newArray[i]->getGoalKeeper()){
            this->m_goalkeepers++;
        }
        m_totalCards+=newArray[i]->getCards();
        m_totalGoals+=newArray[i]->getGoals();
        m_totalPlayers++;

        targetTree.insert(newArray[i]);
    }
    delete[] newArray;
}


Team::~Team() {
    std::cout << "delete team " << this->m_teamId << std::endl;
}

int Team::getTopScorerId()
{
    return m_teamPlayersByScore.getMaxValueInTree()->getPlayerId();
}

void Team::getTeamPlayers(int *const output)
{
    shared_ptr<Player>* playersArray = m_teamPlayersByScore.inOrderArray();
    for(int i=0;i<m_totalPlayers;i++){
        output[i]=playersArray[i]->getPlayerId();
    }
    delete[] playersArray;
}

shared_ptr<Player> Team::findPlayer(int playerId)
{
    if(m_teamPlayersByID.find(playerId)!=nullptr){
        shared_ptr<Player> player = m_teamPlayersByID.find(playerId)->m_data;
        return player;
    }
    return nullptr;
}


ostream& operator<<(ostream& os, const Team& team)
{
    os << "team id: " <<  team.getTeamId() << ", members: " << team.getTotalPlayers();
    return os;
}
