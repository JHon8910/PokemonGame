#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// define your constants here
#define STATS 3
#define OPP_STATS 3
#define INDEX_HP 0
#define INDEX_ATT 1
#define INDEX_DEF 2
#define INDEX_TYPE 3
#define INDEX_STATUS 4

#define CMD_ATK 'a'
#define CMD_HEAL 'h'
#define CMD_STATS 'c'
#define CMD_OPP 'o'
#define CMD_CMDS '?'

int main(void) {
    // Begin game
    printf("Welcome to Pokemon!!!\n\n");

    // Ask user for details on their starter pokemon 
    // Index represents respective stats of the pokemon: 
    /*
        0: HP
        1: ATT
        2: DEF
        3: TYPING (1: fire, 2: water, 3: grass)
    */
    int own[STATS];
    int stats = 20; 
    bool valid = false; 

    printf("Let's create a pokemon!\n");
    printf("You have 20 points dedicated to spread across your pokemon's HP, ATT and DEF\n");

    // Scan hp of starter pokemon
    while (!valid) { // valid == false
        printf("You have %d stat points remaining.\n", stats);
        printf("Please enter the HEALTH of your starter pokemon: ");
        scanf("%d", &own[INDEX_HP]);
        if (own[INDEX_HP] > stats) {
            printf("You cannot use more than your given stat points\n\n");
        } else if (own[INDEX_HP] <= 0) {
            printf("Invalid number!");
        } else {
            stats -= own[INDEX_HP];
            valid = true;
        }
    }

    // scan att of starter pokemon
    valid = false;
    while (!valid) { // valid == false
        printf("You have %d stat points remaining.\n", stats);
        printf("Please enter the ATTACK of your starter pokemon: ");
        scanf("%d", &own[INDEX_ATT]);
        if (own[INDEX_ATT] > stats) {
            printf("You cannot use more than your given stat points\n\n");
        } else if (own[INDEX_ATT] <= 0) {
            printf("Invalid number!");
        } else {
            stats -= own[INDEX_ATT];
            valid = true;
        }
    }

    // Assign def of starter pokemon
    printf("The remaining stats will be assigned to your pokemon's defence!\n");
    own[INDEX_DEF] = stats;
    
    // Ask user for number of potions to start with
    valid = false; 
    int potions;
    while (!valid) {
        printf("\nHow many potions do you have? (max 5): ");
        scanf("%d", &potions);
        if (potions > 5) {
            printf("You cannot have more than 5 potions!\n");
        } else if (potions < 0) {
            printf("You cannot have a negative number of potions!\n");
        } else {
            valid = true; 
        }
    }

    // Create opponent pokemon
    int opp[OPP_STATS];
    int frozen = 0; 
    int poisoned = 0; 
    int sleeping = 0; 
    stats = 20; 
    valid = false; 

    srand(time(0));
    opp[INDEX_HP] = rand() % stats;
    stats -= opp[INDEX_HP];
    opp[INDEX_ATT] = rand() % stats;
    stats -= opp[INDEX_ATT];
    opp[INDEX_DEF] = stats;

    // Print current pokemon details
    printf("\n========================================\n");
    printf("Your pokemon: \n");
    printf("HP:  %d\n", own[INDEX_HP]);
    printf("ATT: %d\n", own[INDEX_ATT]);
    printf("DEF: %d\n", own[INDEX_DEF]);
    printf("========================================\n");

    // Print opponent's stats
    printf("\n========================================\n");
    printf("Opposing pokemon: \n");
    printf("HP:  %d\n", opp[INDEX_HP]);
    printf("ATT: %d\n", opp[INDEX_ATT]);
    printf("DEF: %d\n", opp[INDEX_DEF]);
    printf("========================================\n\n");

    // Calculate advantageous types
    // dmg_dealt = adv * (own_att / opp_def) + 1;
    // dmg_taken = 1 / adv * (opp_att / own_def) + 1;
    int dmg_dealt = (own[INDEX_ATT] / opp[INDEX_DEF]) + 1;
    int dmg_taken = (opp[INDEX_ATT] / own[INDEX_DEF]) + 1;

    // Scan commands
    printf("Valid commands:\n");
    printf("[%c]: ATTACK the opponent!\n", CMD_ATK);
    printf("[%c]: HEAL your pokemon by using a potion!\n", CMD_HEAL);
    printf("[%c]: CHECK your pokemon's stats!\n", CMD_STATS);
    printf("[%c]: CHECK your opponent's stats!\n", CMD_OPP);
    printf("[%c]: VIEW commands!\n\n", CMD_CMDS);
    printf("Please enter a command: ");

    char cmd;
    bool lost = false;
    while (scanf(" %c", &cmd) != EOF && !lost) {
        // Attack the opponent
        if (cmd == CMD_ATK) {
            opp[INDEX_HP] -= dmg_dealt;
            printf("You attack the opponent! Opposing pokemon now has %d HP!\n\n", opp[INDEX_HP]);
            if (opp[INDEX_HP] <= 0) {
                printf("Opponent has fainted!\n");
                printf("CONGRATULATIONS!! YOU HAVE DEFEATED ALL OF YOUR OPPONENTS!!\n");
                printf("YOU ARE NOW THE NEW POKEMON CHAMPION!!\n");
                return 0;
            }

            // Heal the user's pokemon
        } else if (cmd == CMD_HEAL) {
            if (potions > 0) {
                // Use potion
                potions--; // potions = potions - 1;
                own[INDEX_HP] += 5; // own[INDEX_HP] = own[INDEX_HP] + 5;
                printf("Potion used! You currently have %d potions left!\n", potions);
                printf("Your pokemon currently has %d hp!\n\n", own[INDEX_HP]);

            } else {
                printf("You have no more potions left!\n\n");
            }

            // Check pokemon stats
        } else if (cmd == CMD_STATS) {
            printf("\n========================================\n");
            printf("Your Pokemon:\n");
            printf("HP:  %d\n", own[INDEX_HP]);
            printf("ATT: %d\n", own[INDEX_ATT]);
            printf("DEF: %d\n", own[INDEX_DEF]);
            printf("========================================\n");
            printf("\n");

            // Check opponent's stats
        } else if (cmd == CMD_OPP) {
            printf("\n========================================\n");
            printf("Opposing pokemon: \n");
            printf("HP:  %d\n", opp[INDEX_HP]);
            printf("ATT: %d\n", opp[INDEX_ATT]);
            printf("DEF: %d\n", opp[INDEX_DEF]);
            printf("========================================\n");
            printf("\n");
        
            // Check Commands
        } else if (cmd == CMD_CMDS) {
            printf("\nValid commands:\n");
            printf("[%c]: ATTACK the opponent!\n", CMD_ATK);
            printf("[%c]: HEAL your pokemon by using a potion!\n", CMD_HEAL);
            printf("[%c]: CHECK your party's stats!\n", CMD_STATS);
            printf("[%c]: CHECK your opponent's stats!\n", CMD_OPP);
            printf("[%c]: VIEW commands!\n\n", CMD_CMDS);
        
            // Invalid Command 
        } else {
            printf("Unknown command: %c\n", cmd);
        }

        // Opponent's turn!
        if (cmd == CMD_ATK || cmd == CMD_HEAL) {
            // Opponent attacks!
            own[INDEX_HP] -= dmg_taken;
            printf("Opponent attacked! Your current pokemon has %d HP!\n\n", own[INDEX_HP]);

            if (own[INDEX_HP] <= 0) {
                printf("Current pokemon has fainted!\n");
                lost = true;
            }
        }

        // Ask again for command
        if (!lost) printf("Please enter a command: ");
    }

    if (lost) {
        printf("Your pokemom fainted!\n");
        printf("Game Over! You'll get become champion next time!\n");
    }
    return 0;
}