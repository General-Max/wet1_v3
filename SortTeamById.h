#ifndef DATA_STRUCTRS_WET1_SORTTEAMBYID_H
#define DATA_STRUCTRS_WET1_SORTTEAMBYID_H

#include "Team.h"

using std::shared_ptr;

class SortTeamById{
public:
    // Default Destructor and Constructor
    SortTeamById() = default;
    ~SortTeamById() = default;

    /**
     * gets two teams and compare them by theirs ID
     * @param team1
     * @param team2
     * @return true if the teams has the same ID, else false
     */
    static bool equalTo(shared_ptr<Team> team1, shared_ptr<Team> team2);

    /**
     * gets a team and an ID and compare them by theirs ID
     * @param team1
     * @param team2
     * @return true if the team has the given ID
     */
    static bool equalTo(shared_ptr<Team> team1, int otherId);

    /**
     * gets 2 teams and compare them by theirs ID
     * @param team1
     * @param team2
     * @return true if the ID of team1 is smaller than the one of team2, else false
     */
    static bool lessThan(shared_ptr<Team> team1, shared_ptr<Team> team2);

    /**
     * gets a team and an ID adn compare them by theirs ID
     * @param team1
     * @param team2
     * @return true if the ID of team1 is smaller than the given ID,else false
     */
    static bool lessThan(shared_ptr<Team> team1, int otherId);
};

#endif //DATA_STRUCTRS_WET1_SORTTEAMBYID_H
