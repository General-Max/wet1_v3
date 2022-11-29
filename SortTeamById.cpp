// sort team by its id
#include "SortTeamById.h"

bool SortTeamById::equalTo(Team* team1, Team* team2){
    return team1->getTeamId()==team2->getTeamId();
}

bool SortTeamById::equalTo(Team *team1, int otherId) {
    return team1->getTeamId()==otherId;
}

bool SortTeamById::lessThan(Team* team1, Team* team2){
    return team1->getTeamId() < team2->getTeamId();
}

bool SortTeamById::lessThan(Team* team1, int otherId){
    return team1->getTeamId() < otherId;
}
