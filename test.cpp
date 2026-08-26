#include <iostream>
#include <vector>
#include <locale>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

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
    std::vector<std::string> answer;

    MissionProblem(
        std::string statement="", std::vector<std::string> answers=std::vector<std::string>()
    ) 
    : statement(statement), answer(answers)
    {

    }
};

class Mission
{
public:
    int mission_type;
    std::vector<MissionProblem> problem;
    std::string description;
    int prize;
    bool completed;

    Mission(
        int mission_type=-1, std::vector<MissionProblem> problem = {}, std::string description = "", int prize = 0
    )
    : mission_type(mission_type), problem(problem), prize(prize), description(description), completed(false)
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

    std::cout << "Reward: +" << mission.prize << " money\n";

    if (mission.mission_type == KIND_MISSION)
    {
        gs.player.reputation += 10;

        std::cout << "Reputation: +10\n";
        std::cout << "You helped someone, We are proud of you\n";
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
        gs.player.reputation -= 5;

        std::cout << "Reputation: -5 \n";
        std::cout << "You have completed the operation.\n"; 
    }

    std::cout << "\n";
    std::cout << "Current money: "
              << gs.player.money << "\n";
    std::cout << "Current reputation: " 
              << gs.player.reputation << "\n";
    
    std::string _;
    std::cout << "\nPress enter to continue . . . ";
    std::cin >> _;
}

void do_mission (GameState &gs, Mission &mission)
{
    if (mission.completed)
    {
        std::cout << "\nThis mission has already completed\n";

        std::string _;
        std::cout << "Press enter to continue. . .\n";
        std::cin >> _;

        return;
    }

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

    for (int i = 0; i < mission.problem.size(); ++i)
    {
        std::cout << "\n--------------------------------\n";
        std::cout << "Problem" << i + 1
                  << "/" << mission.problem.size() << "\n";
        std::cout << "\n--------------------------------\n";

        std::cout << mission.problem[i].statement << "\n";

        std::string answer;

        std::cout << "Your Answer: ";
        std::cin >> answer;

        int found = 0;
        for (auto &ans: mission.problem[i].answer)
        {
            if (ans == answer)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
        std::cout << "\n MISSION FAILED!! \n";
        std::cout << "Wrong Answer.\n";

        std::cout << "\nPress enter to continue . . . ";
        std::string _;
        std::cin >> _;

        return;
        }
        
        std::cout << "Correct!\n";  
    }
    mission.completed = true;
    complete_mission(gs, mission);
}

void mission_list(GameState &gs)
{
    while (true)
    {
        std::cout << "\n================================\n";
        std::cout << "       MISSION LIST: \n";
        std::cout << "\n================================\n";

        for (int i = 0; i < gs.missions.size(); ++i)
        {
            Mission &mission = gs.missions[i];
            
            std::cout << "\n[" << i + 1 << "]";
 
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
            gs.menu = MENU_MAIN;
            return;
        }

        if (option < 1 || option > gs.missions.size())
        {
            std::cout << "Invalid mission.\n";
            continue;
        }
        Mission &selected_mission = gs.missions[option - 1]; 

        do_mission(gs, selected_mission);
    }
}

int yn_prompt(std::string prompt_string)
{

}

signed main()
{
    std::string name;

    SetConsoleOutputCP(CP_UTF8);
    std::string biasa = "√";
    std::cout << biasa << "\n";

    std::cout << "Enter your name: ";
    std::cin >> name;


    PlayerState ps(name);
    GameState gs(ps);

    gs.missions.push_back(
        Mission(
            KIND_MISSION,
            {
                MissionProblem(
                    "There are 12 students in Class 12 in Melbourne.\n"
                    "There are many different ways to sit in a circle.\n",
                    std::vector<std::string>{"39916800"}
                ),
            },

            "HQQ butuh bantuan!",
            32070
        )
    );
    gs.missions.push_back(
        Mission(
            EVIL_MISSION,
            {
                MissionProblem(
                    "ISS wants to select 7 students from RUSHD High School.\n"
                    "There are 12 boys and 6 girls who will participate in the selection process.\n"
                    "How many ways are there to select at least 3 girls?\n",
                    std::vector<std::string>{"13608"}
                ),
            },

            "Ilung ma have 500 million dollar",
            500000000
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