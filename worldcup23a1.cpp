#include "worldcup23a1.h"

world_cup_t::world_cup_t() : m_numPlayers(0) {}

world_cup_t::~world_cup_t() { }

StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId<=0 || points<0){
        return StatusType::INVALID_INPUT;
    }

    if(m_teams.find(teamId)){
        return StatusType::FAILURE;
    }
    try{
        shared_ptr<Team> newTeam = std::make_shared<Team>(teamId, points);
        m_teams.insert(newTeam);
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    if((!m_teams.find(teamId)) || !(m_teams.find(teamId)->m_data)->isEmptyTeam()){
        std::cout << "coulnd remove team "<< teamId << std::endl;
        return StatusType::FAILURE;
    }
    try{
        m_teams.remove(teamId);
        if((m_validTeams.find(teamId)) && (m_validTeams.find(teamId)->m_data)->isEmptyTeam()){
            m_validTeams.remove(teamId);
        }
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    // TODO: Your code goes here
    if(playerId<=0 || teamId<=0 || gamesPlayed<0 || goals<0 ||cards<0 || (gamesPlayed==0 && (goals>0 || cards>0))){
        return StatusType::INVALID_INPUT;
    }

    if(m_teams.find(teamId) == nullptr || m_playersById.find(playerId) != nullptr){
        return StatusType::FAILURE;
    }
    try{
        shared_ptr<Team> currentTeam = m_teams.find(teamId)->m_data;
        shared_ptr<Player> newPlayer = std::make_shared<Player>(playerId, teamId, gamesPlayed-currentTeam->getPlayedTogether(),
                                                          goals, cards, goalKeeper);
        newPlayer->setTeamPtr(currentTeam.get());
        m_playersById.insert(newPlayer);
        m_playersByScore.insert(newPlayer);
        m_numPlayers++;

        currentTeam->insertPlayer(newPlayer);
        addIfValidTeam(currentTeam);
        insertPlayerToList(m_playersByScore.find(newPlayer));
        std::cout << "players by id: " <<std::endl;
        m_playersById.printD(m_playersById.getRoot(), 10);
        std::cout << "players by id: " <<std::endl;
        m_playersByScore.printD(m_playersByScore.getRoot(), 10);
        m_playersListByScore.printList();
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    // TODO: Your code goes here
    if(playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(m_playersById.find(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    try{
        shared_ptr<Player> playerToRemove = m_playersById.find(playerId)->m_data;
        Team *playerTeam = playerToRemove->getTeamPtr();
        m_playersListByScore.removeNode(playerToRemove->getDequePtr());
        m_playersById.remove(playerId);
        m_playersByScore.remove(playerToRemove);
        playerTeam->removePLayer(playerToRemove);
        if (!isValidTeam(playerTeam) && m_validTeams.find(playerTeam->getTeamId()) != nullptr){
            m_validTeams.remove(playerTeam->getTeamId());
        }
        m_playersByScore.printD(m_playersByScore.getRoot(), 10);
        m_playersListByScore.printList();
        m_numPlayers--;
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    if(playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0){
        return StatusType::INVALID_INPUT;
    }
    if(m_playersById.find(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    try{
        shared_ptr<Player> currentPlayer = m_playersById.find(playerId)->m_data;
        Team* currentTeam = currentPlayer->getTeamPtr();
        m_playersByScore.remove(currentPlayer);
        m_playersListByScore.removeNode(currentPlayer->getDequePtr());
        currentTeam->removePLayer(currentPlayer);

        currentPlayer->updateGamesPlayed(gamesPlayed);
        currentPlayer->updateGoals(scoredGoals);
        currentPlayer->updateCards(cardsReceived);

        m_playersByScore.insert(currentPlayer);
        currentTeam->insertPlayer(currentPlayer);
        insertPlayerToList(m_playersByScore.find(currentPlayer));
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}


StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> team1  = m_teams.find(teamId1)->m_data;
    shared_ptr<Team> team2 = m_teams.find(teamId2)->m_data;

    if(team1==nullptr || team2==nullptr){
        return StatusType::FAILURE;
    }
    try{
        if(team1->getScore() > team2->getScore()){
            team1->updatePoints(WIN);
        }
        else if(team1->getScore() < team2->getScore()){
            team2->updatePoints(WIN);
        }
        else{
            team1->updatePoints(DRAW);
            team2->updatePoints(DRAW);
        }
        team1->increasePlayedTogether();
        team2->increasePlayedTogether();
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if(playerId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Player> player = m_playersById.find(playerId)->m_data;
    if(player==nullptr){
        return StatusType::FAILURE;
    }

    int played=0;
    try
    {
        played+= player->getGamesPlayed();
        int playedWithTeam=0;
        playedWithTeam= player->getTeamPtr()->getPlayedTogether();
        played+=playedWithTeam;
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return played;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    
    shared_ptr<Team> team = m_teams.find(teamId)->m_data;
    if(team == nullptr){
        return StatusType::FAILURE;
    }
    int points=0;
    try
    {
        points=team->getPoints();
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
    return points;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(newTeamId<=0 || teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team1 = m_teams.find(teamId1)->m_data;
    shared_ptr<Team> team2 = m_teams.find(teamId2)->m_data;
    if(m_teams.find(newTeamId)!=nullptr){
        shared_ptr<Team> newTeam = m_teams.find(newTeamId)->m_data;
    }
    else{
        shared_ptr<Team> newTeam = nullptr;
    }
    if(team1==nullptr || team2==nullptr || ((m_teams.find(newTeamId)!=nullptr && newTeamId!=teamId1) && (
            m_teams.find(newTeamId)!=nullptr && newTeamId!=teamId2))){
        return StatusType::FAILURE;
    }

    try{
        if(teamId1==newTeamId){
            team1->merge(team2);
            remove_team(teamId2);
            addIfValidTeam(team1);

            // m_validTeams.remove(team2);
        }
        else if(teamId2==newTeamId){
            team2->merge(team1);
            remove_team(teamId1);
            addIfValidTeam(team2);
            // m_teams.remove(team1);
            // m_validTeams.remove(team1);
        }
        else{
            add_team(newTeamId, 0);
            shared_ptr<Team> newTeam = m_teams.find(newTeamId)->m_data;
            newTeam->merge(team1);
            newTeam->merge(team2);
            remove_team(teamId1);
            remove_team(teamId2);
            //m_teams.insert(newTeam);
            addIfValidTeam(newTeam);
            // m_teams.remove(team1);
            // m_validTeams.remove(team1);
            // m_teams.remove(team2);
            // m_validTeams.remove(team2);
        }
    
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    m_teams.printD(m_teams.getRoot(), 10);
    m_validTeams.printD(m_teams.getRoot(), 10);

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId==0){
        return StatusType::INVALID_INPUT;
    }
    if(teamId<0){
        int id=0;
        try{
            if(m_numPlayers<=0){
                return StatusType::FAILURE;
            }

            shared_ptr<Player> top_scorer = m_playersByScore.getMaxValueInTree();        
            id = top_scorer->getPlayerId();

        }
        catch(std::bad_alloc&){
            return StatusType::ALLOCATION_ERROR;
        }
        return id;
    }
    try
    {
        if(m_teams.find(teamId)!=nullptr){
            shared_ptr<Team> team = m_teams.find(teamId)->m_data;
            if(team->getTotalPlayers()<=0){
                return StatusType::FAILURE;
            }
            return team->getTopScorerId(); 
        }
        else{
            shared_ptr<Team> newTeam = nullptr;
            return StatusType::FAILURE;
        }
    }
    catch(const std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
    return StatusType::FAILURE;

}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId==0){
        return StatusType::INVALID_INPUT;
    }
    if(teamId<0){
        return m_numPlayers;
    }

    if(m_teams.find(teamId)!=nullptr){
        shared_ptr<Team> team = m_teams.find(teamId)->m_data;
        return team->getTotalPlayers(); 
    }
    else{
        shared_ptr<Team> newTeam = nullptr;
        return StatusType::FAILURE;
    }

    return StatusType::FAILURE;

}


StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId==0 || output == nullptr){
        return StatusType::INVALID_INPUT;
    }

    if(teamId<0){
        if(m_numPlayers<=0){
            return StatusType::FAILURE;
        }
        try{
            shared_ptr<Player>* playersArray = m_playersByScore.inOrderArray();
            for(int i=0;i<m_numPlayers;i++){
                output[i]=playersArray[i]->getPlayerId();
            }
            delete[] playersArray;
            return StatusType::SUCCESS;
        }
        catch(std::bad_alloc&){
            return StatusType::ALLOCATION_ERROR;
        }
    }

    try{
        if(m_teams.find(teamId)!=nullptr){
            shared_ptr<Team> team = m_teams.find(teamId)->m_data;
            if(team->getTotalPlayers()<=0){
                return StatusType::FAILURE;
            }
            team->getTeamPlayers(output);
            return StatusType::SUCCESS;
        }
        else{
            return StatusType::FAILURE;
        }
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId<=0 || teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(m_numPlayers==1){
        return StatusType::FAILURE;
    }
    try{
        if(m_teams.find(teamId)!=nullptr){
            shared_ptr<Team> team = m_teams.find(teamId)->m_data;
            if(team->findPlayer(playerId)!= nullptr){
                shared_ptr<Player> player = team->findPlayer(playerId);
                shared_ptr<Player> prevPlayer = nullptr;
                shared_ptr<Player> nextPlayer = nullptr;

                if(player->getDequePtr()->m_prev!=nullptr){
                    prevPlayer = player->getDequePtr()->m_prev->m_nodeData;
                }
                if(player->getDequePtr()->m_next!=nullptr){
                    nextPlayer = player->getDequePtr()->m_next->m_nodeData;
                }

                if(prevPlayer==nullptr && nextPlayer!=nullptr){
                    return nextPlayer->getPlayerId();
                }
                else if(prevPlayer!=nullptr && nextPlayer==nullptr){
                    return prevPlayer->getPlayerId();
                }

                return closest(player, prevPlayer, nextPlayer);

            }
            return StatusType::FAILURE;
        }
        return StatusType::FAILURE;
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::FAILURE;

}

int world_cup_t::closest(shared_ptr<Player> player, shared_ptr<Player> prevPlayer, shared_ptr<Player> nextPlayer)
{
    if(player->getGoals()-prevPlayer->getGoals() < player->getGoals()-nextPlayer->getGoals()){
        return prevPlayer->getPlayerId();
    }
    else if(player->getGoals()-prevPlayer->getGoals() > player->getGoals()-nextPlayer->getGoals()){
        return nextPlayer->getPlayerId();
    }

    if(player->getCards()-prevPlayer->getCards() < player->getCards()-nextPlayer->getCards()){
            return prevPlayer->getPlayerId();
    }
    else if(player->getCards()-prevPlayer->getCards() > player->getCards()-nextPlayer->getCards()){
        return nextPlayer->getPlayerId();
    }

        
    if(player->getPlayerId()-prevPlayer->getPlayerId() < player->getPlayerId()-nextPlayer->getPlayerId()){
        return prevPlayer->getPlayerId();
    }
    else if(player->getPlayerId()-prevPlayer->getPlayerId() > player->getPlayerId()-nextPlayer->getPlayerId()){
        return nextPlayer->getPlayerId();
    }

    if(prevPlayer->getPlayerId()>nextPlayer->getPlayerId()){
        return prevPlayer->getPlayerId();
    }
    return nextPlayer->getPlayerId();
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId<0 || maxTeamId<0 || maxTeamId<minTeamId){
        return StatusType::INVALID_INPUT;
    }
    
    if(m_validTeams.getSize()<=0){
        return StatusType::FAILURE;
    }

    Pair* pairs = fill(minTeamId, maxTeamId);

    int realSize = 0;
    while(pairs[realSize].m_teamId>0){
        realSize++;
    }

    if(realSize == 0){
        delete[] pairs;
        return StatusType::FAILURE;
    }
    
    while(realSize>1){
        int pos =0;
        for(int i=0;i<realSize;i+=2){
            if(i+1<realSize){
                if(pairs[i].m_score<pairs[i+1].m_score){
                    pairs[pos] = pairs[i+1];
                    pairs[pos].m_score += (pairs[i].m_score+WIN);
                }
                else if(pairs[i].m_score>pairs[i+1].m_score){
                    pairs[pos] = pairs[i];
                    pairs[pos].m_score += (pairs[i+1].m_score+WIN);
                }
                else{
                    if(pairs[i].m_teamId<pairs[i+1].m_teamId){
                        pairs[pos] = pairs[i+1];
                        pairs[pos].m_score += (pairs[i].m_score+WIN);
                    }
                    else{
                        pairs[pos] = pairs[i];
                        pairs[pos].m_score += (pairs[i+1].m_score+WIN);
                    }
                }
                pos++;
            }
            else{
                pairs[pos]=pairs[i];
            }
        }
        if(realSize%2==0){          //upper bound;
            realSize = realSize/2;
        }
        else{
            realSize = realSize/2+1;
        }
        
    }

    int winnerId = pairs[0].m_teamId;
    delete[] pairs;
    return winnerId;
}

// auxiliary functions

world_cup_t::Pair* world_cup_t::fill(int min, int max)
{
    int size = max-min; 
    Pair* pairs = new Pair[size];
    for(int i=0;i<size;i++){
        struct Pair pair;
        pair.m_score = -1;
        pair.m_teamId = -1;
        pairs[i] = pair;;
    }

    fill_aux(pairs, 0, min, max, m_validTeams.getRoot());
    return pairs;
}

void world_cup_t::fill_aux(Pair* pairs, int pos, int min, int max, AVLTree<shared_ptr<Team>, SortTeamById>::BinNode* root)
{
    if (root == nullptr)
        return;
    
    if (root->m_data->getTeamId() > min){
        fill_aux(pairs,pos, min, max, root->m_left);
    }
    
    if (root->m_data->getTeamId()>=min && root->m_data->getTeamId()<=max){
        int score = root->m_data->getScore();
        struct Pair pair;
        pair.m_score = score;
        pair.m_teamId = root->m_data->getTeamId();
        pairs[pos] = pair;
    }
     
    /* recursively call the right subtree */
   fill_aux(pairs, ++pos, min, max, root->m_right);
}

//can be shared pyr or weak ptr
template <class S>
bool world_cup_t::isValidTeam(S team) {
    return (team->getTotalPlayers()>=PLAYERS_NUM_IN_VALID_TEAM && team->getGoalkeepers()>0);
}

void world_cup_t::addIfValidTeam(shared_ptr<Team> team) {
    // if the team keeps the valid teams condition and is not in the tree
    if (isValidTeam(team) && m_validTeams.find(team->getTeamId()) == nullptr){
        m_validTeams.insert(team);
    }
}

void world_cup_t::removeIfNodValidTeam(shared_ptr<Team> team) {
// if the team doesn't keep the valid teams condition and is in the tree
    if (!isValidTeam(team) && m_validTeams.find(team->getTeamId()) != nullptr){
        m_validTeams.remove(team);
    }
}

void world_cup_t::insertPlayerToList(AVLTree<shared_ptr<Player>, SortByScore>::BinNode* newNode) {
    TwoWayList<shared_ptr<Player>>::ListNode *newListNode = m_playersListByScore.initNode(newNode->m_data);
    (newNode->m_data)->setDequePtr(newListNode);
    // in case it is the first element in the list
    if (m_numPlayers == SINGLE_PLAYER){
        m_playersListByScore.setHead(newListNode);
        return;
    }
    if(newNode->m_father != nullptr){
        if(SortByScore::lessThan(newNode->m_father->m_data, newNode->m_data)){
            m_playersListByScore.insertAfter(newListNode, (newNode->m_father->m_data)->getDequePtr());
        }
        else{
            m_playersListByScore.insertBefore(newListNode, (newNode->m_father->m_data)->getDequePtr());
        }
    }
    else if(newNode->m_right){
        m_playersListByScore.insertBefore(newListNode, (newNode->m_right->m_data)->getDequePtr());
    }
    else{
        m_playersListByScore.insertAfter(newListNode, (newNode->m_right->m_data)->getDequePtr());
    }
}