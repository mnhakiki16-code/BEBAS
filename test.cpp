#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define MENU_MAIN 0
#define MENU_MISSION_LIST 1
#define MENU_MISSION_VIEW 2
#define MENU_MISSION_PROBLEM 3
#define MENU_SHOP 4


//tes tes tes

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
    PlayerState (std::string name="", int money=0, int reputation=0): name(name), money(money), reputation(reputation)
    {

    }
};

#define KIND_MISSION 0
#define EVIL_MISSION 1

class MissionProblem
{
public:
    std::string statement;
    int answer;

    MissionProblem(
        std::string statement="", std::vector<std::string> answers=std::vector<>()
    ) 
    : statement(statement), answer(answer)
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

    Mission(
        int mission_type=-1, MissionProblem problem = MissionProblem(), std::string description = "", int prize = 0
    )
    : mission_type(mission_type), problem(problem), prize(prize), description(description)
    {

    }
};

class GameState
{
public:
    PlayerState player;
    std::vector<Mission> mission;
    int menu;
    GameState(PlayerState player) : player(player)
    {
        this->menu = 0;
    }
};

void complete_mission (GameState &gs, Mission &mission)
{
    std::cout << "\n================================\n";
    std::cout << "       MISSION COMPLETE!\n";
    std::cout << "\n================================\n";

    //dapat duit
    gs.player.money += mission.prize;

    std::cout << "Reward: +" << mission.prize << "money\n";

    if (mission.mission_type == KIND_MISSION)
    {
        gs.player.reputation += 10;

        std::cout << "Reputation: +10\n";
        std::cout << "You helped someone, We are proud of you\n";
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
        gs.player.reputation -= 5;

        std::cout << "Reputation: -5";
        std::cout << "You have completed the operation.\n"; 
    }

    std::cout << "\n";
    std::cout << "Current money: "
              << gs.player.money << "\n";
    std::cout << "Current reputation: " 
              << gs.player.reputation << "\n";
}

void do_mission (GameState &gs, Mission &mission)
{
    std::cout << "\n================================\n";
    if (mission.mission_type == KIND_MISSION)
    {
        std::cout << "HELP PEOPLE\n";
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
        std::cout << "HACKER OPERATION\n";
    }

    std::cout << "\n================================\n";

    std::cout << mission.description << "\n\n";

    std::cout << "PROBLEM: \n";
    std::cout << mission.problem.statement << "\n";

    int answer; 

    std::cout << "Your Answer: ";
    std::cin >> answer;

    if (answer == mission.problem.answer)
    {
        complete_mission(gs, mission);
    }
    else 
    {
        std::cout << "\n MISSION FAILED!! \n";
        std::cout << "Wrong Answer.\n";
    }
}

void mission_list(GameState &gs)
{
    while (true)
    {
        std::cout << "\n================================\n";
        std::cout << "       MISSION LIST: \n";
        std::cout << "\n================================\n";

        for (int i = 0; i < gs.mission.size(); ++i)
        {
            Mission &mission = gs.mission[i];
            
            std::cout << "\n[" << i + 1 << "\n]";

            if (mission.mission_type == KIND_MISSION)
            {
                std::cout << "[HELP] ";
            }
            else if (mission.mission_type == EVIL_MISSION)
            {
                std::cout << "[EVIL] ";
            }

            std::cout << mission.description << "\n";
            std::cout << "Reward: " << mission.prize << "\n";
        }

        std::cout << "\n[0] Back\n";

        int option;

        std::cout << "\nChoose mission: ";
        std::cin >> option;

        if (option == 0)
        {
            return;
        }

        if (option < 1 || option > gs.mission.size())
        {
            std::cout << "Invalid mission.\n";
            continue;
        }
        Mission &selected_mission = gs.mission[option - 1]; 

        do_mission (gs, selected_mission);
    }
}

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
            std::cout << "NAME: " << gs.player.name << "\n"
                      << "MONEY: " << gs.player.money << "\n"
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
            mission_list(gs);

            gs.menu = MENU_MAIN;
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