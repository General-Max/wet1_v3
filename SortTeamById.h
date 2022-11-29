#ifndef DATA_STRUCTRS_WET1_SORTTEAMBYID_H
#define DATA_STRUCTRS_WET1_SORTTEAMBYID_H
#include "Team.h"

class SortTeamById{
public:
    SortTeamById() = default;
    ~SortTeamById() = default;

    static bool equalTo(Team* team1, Team* team2);

    static bool equalTo(Team* team1, int otherId);

    static bool lessThan(Team* team1, Team* team2);

    static bool lessThan(Team* team1, int otherId);
};

#endif //DATA_STRUCTRS_WET1_SORTTEAMBYID_H
