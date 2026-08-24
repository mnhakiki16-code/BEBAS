#include <iostream>

#define MENU_MAIN 0
#define MENU_MISSION_LIST 1
#define MENU_MISSION_VIEW 2
#define MENU_MISSION_PROBLEM 3
#define MENU_SHOP 4

class Computer
{
public:
    double multiplier;
    std::string name;
    Computer(std::string name="", double multiplier=0): name(name), multiplier(multiplier)
    {

    }
};

std::vector<Computer> computer_list = {
    Computer("Shitty Starter Computer", 1),
};

class PlayerState
{
public:
    std::string name;
    int money, reputation;
    GameState(std::string name="", int money=0, int reputation=0): name(name), money(money), reputation(reputation)
    {

    }
};

class GameState
{
public:
    PlayerState player;
    std::vector<Mission> missions;
    int menu;
    GameState(PlayerState player) : player(player)
    {
        this->player = player;
        this->menu = 0;
    }
};

#define KIND_MISSION 0
#define EVIL_MISSION 1

class MissionProblem
{
public:
    MissionProblem(std::string statement="", std::vector<std::string> answers=std::vector<>())
    {

    }
};

class Mission
{
public:
    int mission_type;
    MissionProblem problem;
    std::string description;
    int prize;
    Mission(int mission_type=-1, MissionProblem problem, std::string description, int prize): mission_type(mission_type), problem(problem), prize(prize), description(description)
    {

    }
};

int yn_prompt(std::string prompt_string)
{

}

signed main()
{
    std::string name;

    std::cout << "Enter your name: ";
    std::cin >> name;

    PlayerState ps(name);
    GameState gs(ps);

    gs.problems.push_back(
        Misison(
            KIND_MISSION,
            MissionProblem(

            )
        )
    );

    while (1)
    {
        if (gs.menu == MENU_MAIN)
        {
            std::cout << "NAME: " << gs.player.name << "\n";
                      << "MONEY: " << gs.player.money << "\n";
                      << "REPUTATION: " << gs.player.reputation << "\n" << std::endl;

            std::cout << "1. MISSION LIST" << "\n"
                      << "2. EXIT" << "\n";
            

            int option;

            std::cout << "Enter option: ";
            std::cin >> option;
            if (option == 1)
            {
                gs.menu = MENU_MISSION_LIST;
            }
        }
        else if (gs.menu == MENU_MISSION_LIST)
        {
            for (int i = 0; i < gs.missions.size(); ++i)
            {
                auto &curmission = gs.missions[i];
                std::cout << "MISSION NUMBER " << i+1 << ":\n";
                std::cout << "Description: " << curmission.description << "\n";
                std::cout << std::endl;
            }

            int mission_opt;
            std::cout << "Which mission do you want? ";
            std::cin >> mission_opt;
        }
        else if (gs.menu == MENU_MISSION_VIEW)
        {
             
        }
        else if (gs.menu == MENU_MISSION_PROBLEM)
        {

        }
    }
    return 0;
}