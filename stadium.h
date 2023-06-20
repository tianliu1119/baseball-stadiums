#ifndef STADIUM_H
#define STADIUM_H
#include <string>
#include <vector>
#include "souvenir.h"

/****************************************************************
 * Stadium struct
 *   Represents a baseball stadium and contains program-related
 *   info regarding the stadium. Manages 13 attributes: name,
 *   team, location, box office phone number, capacity, opening date,
 *   surface type, league, x-position on map, y-position on map,
 *   file path of stadium picture, stadium label that is
 *   displayed on the map, and list of souvenirs being offered.
 ****************************************************************/
struct Stadium
{
    std::string name;      // stadium name
    std::string team;      // stadium team
    std::string location;  // stadium location (address)
    std::string phone;     // stadium box office number
    std::string capacity;  // stadium capacity
    std::string opened;    // stadium date opened
    std::string surface;   // stadium surface type (grass/artificial)
    std::string league;    // stadium league (American/National)
    int x;                 // stadium pip's x position on the map
    int y;                 // stadium pip's y position on the map
    std::string picPath;   // stadium picture's file path
    std::string lblTxt;    // stadium's label name on the map
    std::vector<Souvenir> souvenirs;  // list of souvenirs from the stadium

    // Default constructor
    Stadium()
    {
        souvenirs.push_back(Souvenir("Baseball cap", 25.99, 0));
        souvenirs.push_back(Souvenir("Baseball bat", 35.35, 0));
        souvenirs.push_back(Souvenir("Team Pennant", 12.99, 0));
        souvenirs.push_back(Souvenir("Autographed baseball", 19.99, 0));
    }

    // Parameterized constructor
    Stadium(std::string theName,
            std::string theTeam,
            std::string theLocation,
            std::string thePhone,
            std::string theCapacity,
            std::string theDate,
            std::string theSurface,
            std::string theLeague,
            int xPos = 0,
            int yPos = 0,
            std::string thePicPath = "",
            std::string theLblTxt = "")
        : name(theName), team(theTeam), location(theLocation), phone(thePhone),
          capacity(theCapacity), opened(theDate), surface(theSurface), league(theLeague),
          x(xPos), y(yPos), picPath(thePicPath), lblTxt(theLblTxt)
    {
        if (lblTxt == "")
            lblTxt = name;
        souvenirs.push_back(Souvenir("Baseball cap", 25.99, 0));
        souvenirs.push_back(Souvenir("Baseball bat", 35.35, 0));
        souvenirs.push_back(Souvenir("Team Pennant", 12.99, 0));
        souvenirs.push_back(Souvenir("Autographed baseball", 19.99, 0));
    }
};

#endif // STADIUM_H
