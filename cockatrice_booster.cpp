/*
    this program will create a deck with x booster packs in it.
    assumes that the files are in .dec format with each line starting with a number then the name of the card.
    draft booster : 10 commons, 3 uncommons, 1 rare/mythic, 1 basic land, 1 token card

    To use the program add three .dec files into the same directory one for the commons, one for the uncommons, and one for the rares.
    rename the file names below to match the file names in the directory.

    you can also change the amount of booster packs by changing the BOOSTER_AMOUNT variable.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <thread>

// file names
const std::string COMMONS_FILE      = "stx-commons.dec";
const std::string UNCOMMONS_FILE    = "stx-uncommons.dec";
const std::string RARES_FILE        = "stx-rare-mythics.dec";
const std::string DECK_OUT          = "output.dec";

// amount of cards
const int cNum = 10;    // commons
const int uNum = 3;     // uncommons
const int rNum = 2;     // rares

// amount of boosters
const int BOOSTER_AMOUNT = 6;


// function prototypes
void create_map(std::map<std::string, std::set<std::string>> &);
void create_map(std::map<std::string , std::set<std::string>> &, std::string, std::string);

std::vector<std::string> create_vector(std::set<std::string>);

void print_map(std::map<std::string, std::set<std::string>>);
void print_map(std::map<std::string, std::set<std::string>>, std::string);

void print_vector(std::vector<std::string>, std::string);

void create_booster(std::map<std::string, std::set<std::string>>, std::map<std::string, int> &);
void create_booster(std::map<std::string, int> &, std::vector<std::string>, int);
void output_deck(std::map<std::string, int>);

int random_num(int, int);



int main()
{

    std::map<std::string, std::set<std::string>> cardList; // make a map of commons, uncommons, rares

    create_map(cardList);
    print_map(cardList);

    std::map<std::string, int> deck;  // this will be the output .dec file with the booster(s) included

    create_booster(cardList, deck);

    output_deck(deck);

    system("pause");
    return 0;

}


// creates a map of all the commons, uncommons, and rares to be used by the program.
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



//Create a deck file consisting of the correct amount of cards
void create_booster(std::map<std::string, std::set<std::string>> card_set, std::map<std::string, int> &outputDeck)
{

    std::vector<std::string> commons = create_vector(card_set["commons"]);
    std::vector<std::string> uncommons = create_vector(card_set["uncommons"]);
    std::vector<std::string> rares = create_vector(card_set["rares"]);

    print_vector(commons, "commons");
    print_vector(uncommons, "uncommons");
    print_vector(rares, "rares");
    for (int i = 0; i < BOOSTER_AMOUNT; i++)
    {     
        create_booster(outputDeck, commons, cNum);
        create_booster(outputDeck, uncommons, uNum);
        create_booster(outputDeck, rares, rNum);
   
    }
}

void create_booster(std::map<std::string, int> &outputDeck, std::vector<std::string> rarity, int rarityAmount)
{
    for (int i = 0; i < rarityAmount; i++)
    {
        

        std::chrono::milliseconds timespan(random_num(5,500)); 
        std::this_thread::sleep_for(timespan);

        int location = random_num(0, rarity.size()); // random location in the card_set
        
        std::string card = rarity.at(location); // card to be added
        std::cout << "the card to be added is " << card << std::endl;

        // check if the output deck already contains the specified card
        if (outputDeck.count(card) > 0) // if the outputDeck already contains this card then 
        {
            outputDeck.at(card)++;// increase the value at that key 
        } else 
        {
            outputDeck[card] = 1;
        }

    } 
}

std::vector<std::string> create_vector(std::set<std::string> set)
{
    std::vector<std::string> vector;
    for (auto it : set)
    {
        vector.push_back(it);
    }

    return vector;
}



// choose a random number 
int random_num(int min, int max)// create a random num
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    // unsigned seed = std::chrono::steady_clock::now();
    // std::chrono::system_clock::now().duration
    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> dist(0,max);

    return dist(e); // random num that was generated
}




// create a .dec file to output the results of the booster program. 
void output_deck(std::map<std::string, int> inputMap)
{

    std::ofstream output(DECK_OUT);

    for (std::pair<std::string, int> elem : inputMap)
    {
        // write the value to the file , then a space, then the key
        output << elem.second << " " << elem.first << std::endl;
    }

    output.close();
}



// print a vector out
void print_vector(std::vector<std::string> vector, std::string name)
{
    std::cout << "the vetor of " << name << " has " << vector.size() << " elements and is as follows :" << std::endl;

    for (auto elem : vector)
    {
        std::cout << elem << std::endl;
    }
}