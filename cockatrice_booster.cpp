/*
    this program will create a deck with x booster packs in it.
    assumes that the files are in .dec format with each line starting with a number then the name of the card.
    draft booster : 10 commons, 3 uncommons, 1 rare/mythic, 1 basic lance, 1 token/ad card
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

// file names
const std::string commons   = "stx-commons.dec";
const std::string uncommons = "stx-uncommons.dec";
const std::string rares     = "stx-rare-mythics.dec";

// amount of cards
const int cNum = 10;    // commons
const int uNum = 3;     // uncommons
const int rNum = 1;     // rares


// function prototypes
void create_map(std::map<std::string, std::string> &);
void create_map(std::map<std::string , std::string> &, std::string, std::string);
void print_map(std::map<std::string, std::string>);


int main()
{

    std::map<std::string, std::string> cardList; // make a map of commons, uncommons, rares

    create_map(cardList);

    

    system("pause");
    return 0;

}



void create_map(std::map<std::string, std::string> &map)
{

    create_map(map, commons,    "commons");
    create_map(map, uncommons,  "uncommons");
    create_map(map, rares,      "rares");

}



void create_map(std::map<std::string, std::string> &map, std::string fName, std::string rarity)
{
    std::cout << "running second create map" << std::endl;

    std::ifstream file(fName);

    int x;              // numbers of cards in deck
    std::string y;      // name of the card


    while (std::getline(file, y))
    {
    
    
        std::cout << "adding " << x << " cards named " << y << "\n" << "rarity: " << rarity << "\n" << std::endl; // debug
        map.emplace(rarity, y);
    
    }
    
    // for each element, print out the map 




}

void print_map(std::map<std::string, std::string> map)
{
    for (auto itr = map.begin(); itr != map.end(); itr++)
    {
        std::cout << *itr;
    }
}