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

void Team::setTotalPlayers(int totalPlayers)
{
    this->m_totalPlayers = totalPlayers;
}

void Team::setTotalGoals(int totalGoals)
{
    this->m_totalGoals = totalGoals;
}

void Team::setTotalCards(int totalCards)
{
    this->m_totalCards = totalCards;
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

/*
void Team::merge(shared_ptr<Team> toMerge)
{

    shared_ptr<Player>* originalPlayersById = m_teamPlayersByID.inOrderArray();
    shared_ptr<Player>* originalPlayersByScore = m_teamPlayersByScore.inOrderArray();
    shared_ptr<Player>* playersToMergeById = toMerge->m_teamPlayersByID.inOrderArray();
    shared_ptr<Player>* playersToMergeByScore = toMerge->m_teamPlayersByID.inOrderArray();

    int originalSize = m_teamPlayersByID.getSize();
    int toMergeSize = toMerge->m_teamPlayersByID.getSize();

    shared_ptr<Player>* newPlayersById = mergeSortedArrays(originalPlayersById, originalSize,playersToMergeById, toMergeSize);
    shared_ptr<Player>* newPlayersByScore = mergeSortedArrays(originalPlayersByScore, originalSize,playersToMergeByScore, toMergeSize);

}

template<class T>
shared_ptr<Player>* Team::mergeSortedArrays(shared_ptr<Player>* arr1, int size1,shared_ptr<Player>* arr2, int size2)
{
    int size = size1+size2;
    
    shared_ptr<Player>* newArr = (shared_ptr<Player>*) malloc(sizeof(shared_ptr<Player>)*(size));
    int index1=0;
    int index2=0;
    int i=0;
    while(index1<size1 && index2<size2){
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
}
*/


void Team::merge(shared_ptr<Team> toMerge)
{
    fillNewTree(toMerge, this->m_teamPlayersByID, toMerge->m_teamPlayersByID);
    fillNewTree(toMerge, this->m_teamPlayersByScore, toMerge->m_teamPlayersByScore);
    this->updatePoints(toMerge->getPoints());
}

void Team::unite(shared_ptr<Team> team1, shared_ptr<Team> team2, int newTeamId) {
    Team* newTeam = new Team(newTeamId, team1->getPoints()+team2->getPoints());

    newTeam->merge(team1);
    newTeam->merge(team2);
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
