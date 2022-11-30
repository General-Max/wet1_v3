#include "worldcup23a1.h"
#include "Team.h"
#include "Player.h"
#include <memory>

world_cup_t::world_cup_t() : m_numPlayers(0) {}

world_cup_t::~world_cup_t()
{
    // TODO: check if needed: delete m_topScorer
    // TODO:: check if all the rest deleted automatically because destroying this call each one destructor
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    // TODO: Your code goes here
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
      //  shared_ptr<Team> playerTeam = std::shared_ptr<Team>(playerToRemove->getTeamPtr());
        Team *playerTeam = playerToRemove->getTeamPtr();
        m_playersListByScore.removeNode(playerToRemove->getDequePtr());
        m_playersById.remove(playerId);
        m_playersByScore.remove(playerToRemove);
        playerTeam->removePLayer(playerToRemove);
        if(m_validTeams.find(playerToRemove->getTeamId()) != nullptr){
            removeIfNodValidTeam(m_validTeams.find(playerToRemove->getTeamId())->m_data);
        }
        std::cout << "AFTER REMOVE players by score: " <<std::endl;
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
    // TODO: Your code goes here
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

        //    m_playersListByScore.printList();
        m_playersByScore.insert(currentPlayer);
        currentTeam->insertPlayer(currentPlayer);
        insertPlayerToList(m_playersByScore.find(currentPlayer));
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    m_playersByScore.printD(m_playersByScore.getRoot(), 10);
    m_playersListByScore.printList();
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

bool world_cup_t::isValidTeam(shared_ptr<Team> team) {
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
    shared_ptr<Team> newTeam = m_teams.find(newTeamId)->m_data;

    if(team1==nullptr || team2==nullptr || ((newTeam!= nullptr && newTeamId!=teamId1) && (newTeam!= nullptr && newTeamId!=teamId2))){
        return StatusType::FAILURE;
    }

    try{
        if(teamId1==newTeamId){
            team1->merge(team2);
        }
        else if(teamId2==newTeamId){
           team2->merge(team1);
        }
        else{
            shared_ptr<Team> newTeam = std::make_shared<Team>(newTeamId,0);
            newTeam->merge(team1);
            newTeam->merge(team2);
        }
    
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

