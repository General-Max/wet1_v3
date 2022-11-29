// sort team by its id
#include "SortTeamById.h"

bool SortTeamById::equalTo(shared_ptr<Team> team1, shared_ptr<Team> team2){
    return team1->getTeamId()==team2->getTeamId();
}

bool SortTeamById::equalTo(shared_ptr<Team>team1, int otherId) {
    return team1->getTeamId()==otherId;
}

bool SortTeamById::lessThan(shared_ptr<Team> team1, shared_ptr<Team> team2){
    return team1->getTeamId() < team2->getTeamId();
}

bool SortTeamById::lessThan(shared_ptr<Team> team1, int otherId){
    return team1->getTeamId() < otherId;
}
