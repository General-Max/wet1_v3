#ifndef DATA_STRUCTRS_WET1_SORTTEAMBYID_H
#define DATA_STRUCTRS_WET1_SORTTEAMBYID_H

#include "Team.h"

using std::shared_ptr;

class SortTeamById{
public:
    SortTeamById() = default;
    ~SortTeamById() = default;

    static bool equalTo(shared_ptr<Team> team1, shared_ptr<Team> team2);

    static bool equalTo(shared_ptr<Team> team1, int otherId);

    static bool lessThan(shared_ptr<Team> team1, shared_ptr<Team> team2);

    static bool lessThan(shared_ptr<Team> team1, int otherId);
};

#endif //DATA_STRUCTRS_WET1_SORTTEAMBYID_H
