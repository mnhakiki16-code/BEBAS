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
    int price;
    Computer(std::string name="", double multiplier=0, int price = 0)
    : name(name), multiplier(multiplier), price(price)

    {

    }
};

std::vector<Computer> computer_list = {
    Computer("Shitty Starter Computer", 1.0, 0),
    Computer("ACER NITRO 5", 2.5, 16000),
    Computer("Lenovo", 1.5, 7000),
    Computer("Asus", 2.0, 8000),
    Computer("Quantum Phantom", 33.0, 100000),
};

class PlayerState
{
public:
    std::string name;
    int money, reputation;
    int computer;
    PlayerState (std::string name="", int money=0, int reputation=0,int computer = 0): name(name), money(money), reputation(reputation), computer(computer)
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

class DefenseProblem 
{
    public:
        std::string statement;
        std::vector<std::string> answer;

        DefenseProblem(
            std::string statement = "",
            std::vector<std::string> answer = {}
        )
            : statement(statement), answer(answer)
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
    double multiplier = computer_list[gs.player.computer].multiplier;

    int reward = mission.prize * multiplier;

    gs.player.money += reward;

    std::cout << "Base Reward: " << mission.prize << " $\n";
    std::cout << "Computer Multiplier: " << multiplier << "\n";
    std::cout << "Final Reward: +$ " << reward << "\n";

    if (mission.mission_type == KIND_MISSION)
    {
        std::cout << "You helped someone, We are proud of you\n";
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
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

int mission_choice(GameState &gs, Mission &mission)
{
    int choice;

    std::cout << "\n================================\n";
    std::cout << "        WHAT WILL YOU DO?\n";
    std::cout << "\n================================\n";

    if (mission.mission_type == KIND_MISSION)
    {
        std::cout << "1. Help them\n";
        std::cout << "2. Ignore them\n";
        std::cout << "3. Take advantage of the situation\n";
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
        std::cout << "1. Continue operation\n";
        std::cout << "2. Abort operation\n";
        std::cout << "3. Take everything\n";
    }

    std::cout << "Your choice: ";
    std::cin >> choice; 

    return choice;
}

bool hack_attack (GameState &gs) //HAMUINUI THGUIHAUIHGUIAHEQIGUJAIGHUIJISGHUISJOIERHFAIHTFIOAUOIHUIOSAHJIOUSAHIOUAIOHISHIOAUIOGHSOIU
{
    if (gs.player.reputation >= -5)
    {
        return true;
    }

    std::cout << "\n================================\n";
    std::cout << "             WARNING!!";
    std::cout << "\n================================\n";    

    std::cout << "YOU ARE HACKED BY THE GODFATHER\n";
    std::cout << "GET THE KEY TO COUNTERATTACK BY SOLVING THIS PROBLEM\n";

    int index = rand() % defense_problem.size();

    DefenseProblem &problem = defense_problem[index];

    std::cout << "DEFENSE CHALLANGE\n";
    std::cout << problem.statement << "\n";

    std::string answer;
    std::cout << "Your answer: ";
    std::cin >> answer;

    for (auto &ans : problem.answer)
    {
        if (answer == ans)
        {
            std::cout << "DEFENSE SUCCESFUL\n";
            return true;
        }
    }
    std::cout << "DEFENSE FAILED!\n";
    
    int lose_money = gs.player.money * 50 / 100;
    gs.player.money -= lose_money;

    std::cout << "THE GODFATHER TAKE 50% OF YOUR MONEY\n";
    std::cout << "Money lost: $" << lose_money << "\n";
    std::cout << "Remaining money: $" << gs.player.money << "\n";
    
    return false;
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

    int choice = mission_choice(gs, mission);

    if (mission.mission_type == KIND_MISSION)
    {
        if (choice == 1)
        {
            std::cout << "You decide to help them\n YEAY YOU ARE KIND :D\n";
            gs.player.reputation += 10;
        }
        else if (choice == 2)
        {
            std::cout << "You decide to ignore them\n sooooooo saddddd :(\n";
            gs.player.reputation -= 2;
        }
        else if (choice == 3)
        {
            std::cout << "You decide to take advantage of the situation >:( \n";
            gs.player.reputation -=10; 
        }
        else 
        {
            std::cout << "\nInvalid choice. >:/\n";
            return; 
        }
    }
    else if (mission.mission_type == EVIL_MISSION)
    {
        if (choice == 1)
        {
            std::cout << "You decided to continue the operation\n Good luck\n";
            gs.player.reputation -= 2;
        }
        else if (choice == 2)
        {
            std::cout << "You decide to abort the operation\n Great choice, Son\n";
            gs.player.reputation += 2;
        }
        else if (choice == 3)
        {
            std::cout << "You decided to take everything\n Devil look up to you, Son\n";
            gs.player.reputation -= 15;
        }
        else 
        {
            std::cout << "\nInvalid choice. >:/\n";
            return; 
        }
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

void computer_shop(GameState &gs)
{
    while (1)
    {
        std::cout << "\n================================\n";
        std::cout << "       WELCOME TO THE SHOP, SON\n";
        std::cout << "\n================================\n";

        std::cout << "Your money is: " << gs.player.money << " $\n";
        std::cout << "Your current computer: "
                  << computer_list[gs.player.computer].name << "\n";
        std::cout << "Multiplier: "
                  << computer_list[gs.player.computer].multiplier << "\n\n";
        
        for (int i = 0; i < computer_list.size(); ++i)
        {
            Computer &computer = computer_list[i];

            std::cout << "[" << i + 1 << "] " << computer.name << "\n";
            std::cout << "     Multiplier: " << computer.multiplier << " x\n";
            std::cout << "     Price: " << computer.price << " $\n"; 
        }

        std::cout << "[0] Back\n";

        int option;

        std::cout << "\nChose computer: ";
        std::cin >> option;

        if (option == 0)
        {
            return;
        }

        if (option < 1 || option > computer_list.size())
        {
            std::cout << "Invalid option\n";
            continue;
        }

        int index = option - 1;

        if (index == gs.player.computer)
        {
            std::cout << "You already own this computer. \n";
            continue;
        }

        Computer &computer = computer_list[index];

        if (gs.player.money < computer.price)
        {
            std::cout << "You don't have enough money\n";
            continue;
        }

        gs.player.money -= computer.price;
        gs.player.computer = index;

        std::cout << "\nComputer Upgraded, Son!\n";
        std::cout << "You now have: " << computer.name << "\n";
    }
}

std::vector<DefenseProblem> defense_problem = 
    {
        DefenseProblem(
            
        )
    };

signed main()
{
    std::string name;

    SetConsoleOutputCP(CP_UTF8);

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

            "Ilung ma have 10 million dollar",
            10000000
        )

    );

    while (1)
    {
        if (gs.menu == MENU_MAIN)
        {
            std::cout << "NAME: " << gs.player.name << "\n"
                      << "MONEY: " << gs.player.money << "\n"
                      << "REPUTATION: " << gs.player.reputation << "\n" 
                      << "COMPUTER: " << computer_list[gs.player.computer].name << "\n"
                      << "Multiplier: " << computer_list[gs.player.computer].multiplier << " x\n";

                      std::cout << std::endl; 

            std::cout << "1. MISSION LIST" << "\n"
                      << "2. COMPUTER SHOP" << "\n"
                      << "3. EXIT" << "\n";
            

            int option;

            std::cout << "Enter option: ";
            std::cin >> option;
            if (option == 1) 
            {
                gs.menu = MENU_MISSION_LIST;
            }
            else if (option == 2)
            {
                gs.menu = MENU_SHOP;    
            }
            else if (option == 3)
            {
                break;
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
        else if (gs.menu == MENU_SHOP)
        {
            computer_shop(gs);
            gs.menu = MENU_MAIN;
        }
    }
    return 0;
}