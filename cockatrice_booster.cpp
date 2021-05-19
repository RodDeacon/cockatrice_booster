/*
    this program will create a deck with x booster packs in it.
    assumes that the files are in .dec format with each line starting with a number then the name of the card.
    draft booster : 10 commons, 3 uncommons, 1 rare/mythic, 1 basic lance, 1 token/ad card
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

// file names
const std::string COMMONS_FILE      = "stx-commons.dec";
const std::string UNCOMMONS_FILE    = "stx-uncommons.dec";
const std::string RARES_FILE        = "stx-rare-mythics.dec";
const std::string DECK_OUT          = "output.dec";

// amount of cards
const int cNum = 10;    // commons
const int uNum = 3;     // uncommons
const int rNum = 1;     // rares

// amount of boosters
const int BOOSTER_AMOUNT = 1;


// function prototypes
void create_map(std::map<std::string, std::set<std::string>> &);
void create_map(std::map<std::string , std::set<std::string>> &, std::string, std::string);
void print_map(std::map<std::string, std::set<std::string>>);
void print_map(std::map<std::string, std::set<std::string>>, std::string);
// void create_deck(std::map<std::string, std::string>, std::map<std::string, int> &);



int main()
{

    std::map<std::string, std::set<std::string>> cardList; // make a map of commons, uncommons, rares

    create_map(cardList);
    print_map(cardList);

    std::map<std::string, int> deck;  

   // create_deck(cardList, deck);


    system("pause");
    return 0;

}



void create_map(std::map<std::string, std::set<std::string>> &map)
{

    create_map(map, COMMONS_FILE,    "commons");
    create_map(map, UNCOMMONS_FILE,  "uncommons");
    create_map(map, RARES_FILE,      "rares");

}


// create a useable map with parameters of the map, file name, and the rarity
void create_map(std::map<std::string, std::set<std::string>> &map, std::string fName, std::string rarity)
{

    std::ifstream file(fName); // open file

    std::string y;      // name of the card

    std::set<std::string> set;

    while (std::getline(file, y)) // while the file still has lines
    {

        // parse each line
        std::string temp = y.substr(2,y.length());
    
        std::cout << "the card to be added to the set" << temp << std::endl;


        // add to set
        set.insert(temp);

    }

    map.insert(std::pair<std::string, std::set<std::string>>(rarity, set)); // insert rarity and the set into the map.
    
}



void print_map(std::map<std::string, std::set<std::string>> map)
{

    print_map(map, "commons");
    print_map(map, "uncommons");
    print_map(map, "rares");

}



void print_map(std::map<std::string, std::set<std::string>> map, std::string rarity)
{

    std::set<std::string> tempSet = map[rarity];

    std::cout << rarity << ":" << std::endl;

    for (auto it= tempSet.begin(); it != tempSet.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

}


// Create a deck file consisting of the correct amount of cards
// void create_deck(std::map<std::string, std::string> card_set, std::map<std::string, int> &outputDeck)
// {

//     std::ofstream out_file(deck); // output file

    

//     out_file.close();

// }
