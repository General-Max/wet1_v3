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

void Team::mergeTeams(shared_ptr<Team> toMerge, int size)
{
    int sizeTree = this->getTotalPlayers();
    AVLTree<shared_ptr<Player>, SortById>::BinNode* temp1 = mergeTrees<SortById>(this->m_teamPlayersByID, sizeTree, toMerge->m_teamPlayersByID, size);
    this->m_teamPlayersByID.setRoot(temp1);
    AVLTree<shared_ptr<Player>, SortByScore>::BinNode* temp2 = mergeTrees<SortByScore>(this->m_teamPlayersByScore, sizeTree, toMerge->m_teamPlayersByScore, size);
    this->m_teamPlayersByScore.setRoot( temp2);

    shared_ptr<Player>* allPlayers = new shared_ptr<Player>[sizeTree+size];
    int i=0;
    storeInOrder<SortById>(this->m_teamPlayersByID.getRoot(), allPlayers, &i, sizeTree+size);
    for(int j=0;j<sizeTree+size; j++){
        if(allPlayers[j]->getGoalKeeper()){
            this->m_goalkeepers++;
        }
        m_totalCards+=allPlayers[j]->getCards();
        m_totalGoals+=allPlayers[j]->getGoals();
        m_totalPlayers++;
    }
    delete[] allPlayers;
    delete temp1;
    delete temp2;
}

template<class T>
typename AVLTree<shared_ptr<Player>, T>::BinNode* Team::mergeTrees( AVLTree<shared_ptr<Player>, T> root1, int size1,
                                                                    AVLTree<shared_ptr<Player>, T> root2, int size2)
{
    shared_ptr<Player>* first = root1.inOrderArray();

    shared_ptr<Player>* second = root2.inOrderArray();

    shared_ptr<Player>* merged = mergeSortedArrays<T>(first, second, size1, size2);

    delete[] first;
    delete[] second;

    return sortedArrayToAVL<T>(merged, 0, size1+size2-1);

}

template<class T>
typename AVLTree<shared_ptr<Player>,T>::BinNode* Team::sortedArrayToAVL(shared_ptr<Player>* array, int start, int end)
{
    if(start > end){
        return nullptr;
    }

    int mid = (start+end)/2;
    typename AVLTree<shared_ptr<Player>,T>::BinNode* root= AVLTree<shared_ptr<Player>,T>::initNode(array[mid]);

    root->m_left=sortedArrayToAVL<T>(array, start, mid-1);

    root->m_right=sortedArrayToAVL<T>(array, mid+1, end);

    int height = 0;
    if(root->m_left!= nullptr && root->m_right!= nullptr){
        if(root->m_left->m_height > root->m_right->m_height){
            height = root->m_left->m_height + 1;
        }
        else{
            height = root->m_right->m_height + 1;
        }
    }
    else{
        if(root->m_left== nullptr && root->m_right!= nullptr){
            height = root->m_right->m_height + 1;
        }
        else if(root->m_left!= nullptr && root->m_right== nullptr){
            height = root->m_left->m_height + 1;
        }
        else{
            height = 0;
        }
    }
    root->m_height =height;
    return root;
}

template<class T>
shared_ptr<Player>* Team::mergeSortedArrays(shared_ptr<Player>* first, shared_ptr<Player>* second, int size1, int size2)
{
    shared_ptr<Player>* merged = new shared_ptr<Player>[size1+size2];
    int i=0, j=0, k=0;

    while(i<size1 && j<size2){
        if(T::lessThan(first[i],second[j])){
            merged[k]=first[i];
            i++;
        }
        else{
            merged[k]=second[j];
            j++;
        }
        k++;
    }

    while (i < size1){
        merged[k] = first[i];
        i++; k++;
    }

    while (j < size2){
        merged[k] = second[j];
        j++; k++;
    }

    return merged;

}

template<class T>
void Team::storeInOrder(typename AVLTree<shared_ptr<Player>, T>::BinNode* root, shared_ptr<Player>* arr, int *index, int length)
{
    if(root == nullptr){
        return;
    }
    if((*index)>length){
        return;
    }
    storeInOrder<T>(root->m_left, arr, index, length);
    std::cout<<"here"<<std::endl;
    std::cout<< (*index) <<std::endl;
    arr[*index] = root->m_data;
    std::cout<<"but not here"<<std::endl;
    (*index)++;

    storeInOrder<T>(root->m_right, arr, index, length);
}


/*
void Team::storeInorder(AVLTree<shared_ptr<Team>, SortById>::BinNode* root, shared_ptr<Player>* inOrder, int *index)
{
    if(root== nullptr){
        return;
    }
    storeInorder(root->m_left, inOrder, index);

    inOrder[*index] = root->m_data;
    (*index)++;
    storeInorder(root->m_right, inOrder, index);

}
*/
//void Team::unite(shared_ptr<Team> team1, shared_ptr<Team> team2)
//{
//
//    uniteFillTree(this->m_teamPlayersByID, team1->m_teamPlayersByID, team2->m_teamPlayersByID, true);
//    uniteFillTree(this->m_teamPlayersByScore, team1->m_teamPlayersByScore, team2->m_teamPlayersByScore, false);
//    // set it to an empty team, its trees has been deleted in the fill function
//    team1->m_totalPlayers = 0;
//    team2->m_totalPlayers = 0;
//    this->updatePoints(team1->getPoints() + team2->getPoints());
//}

//
//template <class T>
//void Team::uniteFillTree(AVLTree<shared_ptr<Player>, T>& newTeamTree,
//                         AVLTree<shared_ptr<Player>, T>& team1Tree, AVLTree<shared_ptr<Player>, T>& team2Tree, bool toAddPlayers){
//    int sizeTeam1 = team1Tree.getSize();
//    int sizeTeam2 = team2Tree.getSize();
//    int size = sizeTeam1 + sizeTeam2;
//
//    shared_ptr<Player>* tempArray = mergeSortedArraysByTrees<T>(newTeamTree, team1Tree, newTeamTree.getSize(), sizeTeam1);
//    shared_ptr<Player>* newArray = new shared_ptr<Player>[size];
//    newArray = mergeSortedArrays<T>( tempArray, team2Tree.inOrderArray(), newArray, sizeTeam1, sizeTeam2);
//
//    team1Tree.emptyTree();
//    team2Tree.emptyTree();
//
//    sortedArrayToAVL<T>(newArray, 0, size);
//
//    for(int i=0;i<size;i++){
//        if(toAddPlayers){
//            if(newArray[i]->getGoalKeeper()){
//                this->m_goalkeepers++;
//            }
//            m_totalCards+=newArray[i]->getCards();
//            m_totalGoals+=newArray[i]->getGoals();
//            m_totalPlayers++;
//        }
//    }
//    delete[] newArray;
//}


//template<class T>
//void Team::fillNewTree(shared_ptr<Team> toMerge, AVLTree<shared_ptr<Player>, T>& targetTree, AVLTree<shared_ptr<Player>,
//        T>& mergedTree, bool toAddPlayers) {
//    int sizeTarget = targetTree.getSize();
//    int sizeMerged = mergedTree.getSize();
//    int size = sizeTarget+sizeMerged;
//
//    shared_ptr<Player>* newArray = mergeSortedArraysByTrees(targetTree, mergedTree, sizeTarget, sizeMerged);
//
//    targetTree.emptyTree();
//    mergedTree.emptyTree();
//
//    sortedArrayToAVL<T>(newArray, 0, size);
//
//    for(int i=0;i<size;i++){
//        if(toAddPlayers){
//            if(newArray[i]->getGoalKeeper()){
//                this->m_goalkeepers++;
//            }
//            m_totalCards+=newArray[i]->getCards();
//            m_totalGoals+=newArray[i]->getGoals();
//            m_totalPlayers++;
//        }
//    }
//    delete[] newArray;
//}


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
