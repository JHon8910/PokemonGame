#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// define your constants here
#define STATS 4
#define OPP_STATS 5
#define INDEX_HP 0
#define INDEX_ATT 1
#define INDEX_DEF 2
#define INDEX_TYPE 3
#define INDEX_STATUS 4

#define TYPE_FIRE 'f'
#define TYPE_WATER 'w'
#define TYPE_GRASS 'g'
#define FIRE_VALUE 1
#define WATER_VALUE 2
#define GRASS_VALUE 3

#define MOVE_ATT 1
#define MOVE_ICE 2
#define MOVE_POI 3
#define MOVE_SIN 4

#define STATUS_NOR 0
#define STATUS_FRO 1
#define STATUS_POI 2
#define STATUS_SLE 3

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

    // Scan for type of pokemon
    printf("\nValid types: \n");
    printf("[%c]: FIRE type\n", TYPE_FIRE);
    printf("[%c]: WATER type\n", TYPE_WATER);
    printf("[%c]: GRASS type\n", TYPE_GRASS);

    valid = false;
    char type;
    while (!valid) {
        printf("Please enter the TYPE of your starter pokemon: ");
        scanf(" %c", &type);
        if (type == TYPE_FIRE || type == TYPE_GRASS || type == TYPE_WATER) {
            valid = true;
        } else {
            printf("Invalid type entered!\n\n");
        }
    }

    if (type == TYPE_FIRE) {
        own[INDEX_TYPE] = FIRE_VALUE;
    } else if (type == TYPE_WATER) {
        own[INDEX_TYPE] = WATER_VALUE;
    } else {
        own[INDEX_TYPE] = GRASS_VALUE;
    }
    
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
    opp[INDEX_TYPE] = rand() % 3 + 1;
    opp[INDEX_STATUS] = STATUS_NOR;

    // Print current pokemon details
    printf("\n========================================\n");
    printf("Your pokemon: \n");
    printf("HP:  %d\n", own[INDEX_HP]);
    printf("ATT: %d\n", own[INDEX_ATT]);
    printf("DEF: %d\n", own[INDEX_DEF]);
    printf("TYPE: ");
    if (own[INDEX_TYPE] == FIRE_VALUE) {
        printf("FIRE\n");
    } else if (own[INDEX_TYPE] == WATER_VALUE) {
        printf("WATER\n");
    } else {
        printf("GRASS\n");
    }
    printf("========================================\n");

    // Print opponent's stats
    printf("\n========================================\n");
    printf("Opposing pokemon: \n");
    printf("HP:  %d\n", opp[INDEX_HP]);
    printf("ATT: %d\n", opp[INDEX_ATT]);
    printf("DEF: %d\n", opp[INDEX_DEF]);
    printf("TYPE: ");
    if (opp[INDEX_TYPE] == FIRE_VALUE) {
        printf("FIRE\n");
    } else if (opp[INDEX_TYPE] == WATER_VALUE) {
        printf("WATER\n");
    } else {
        printf("GRASS\n");
    }
    printf("========================================\n\n");

    // Calculate advantageous types
    // dmg_dealt = adv * (own_att / opp_def) + 1;
    // dmg_taken = 1 / adv * (opp_att / own_def) + 1;
    double adv = 1.0;
    if (own[INDEX_TYPE] == FIRE_VALUE) {
        if (opp[INDEX_TYPE] == GRASS_VALUE) {
            adv = 2.0;
        } else if (opp[INDEX_TYPE] == WATER_VALUE) {
            adv = 0.5;
        }
    } else if (own[INDEX_TYPE] == WATER_VALUE) {
        if (opp[INDEX_TYPE] == FIRE_VALUE) {
            adv = 2.0;
        } else if (opp[INDEX_TYPE] == GRASS_VALUE) {
            adv = 0.5;
        }
    } else {
        if (opp[INDEX_TYPE] == WATER_VALUE) {
            adv = 2.0;
        } else if (opp[INDEX_TYPE] == FIRE_VALUE) {
            adv = 0.5;
        }
    } 

    int dmg_dealt = adv * (own[INDEX_ATT] / opp[INDEX_DEF]) + 1;
    int dmg_taken = 1 / adv * (opp[INDEX_ATT] / own[INDEX_DEF]) + 1;

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
            int move;             
            bool valid_move = false; 
            while (!valid_move) {
                // List valid moves 
                printf("\nWhich move do you use?\n");
                printf("[%d]: ", MOVE_ATT);
                if (own[INDEX_TYPE] == FIRE_VALUE) {
                    printf("Flamethrower - The foe is scorched with intense flames\n");
                } else if (own[INDEX_TYPE] == WATER_VALUE) {
                    printf("Bubble Beam - A spray of bubbles is forcefully ejected at the foe\n");
                } else {
                    printf("Vine Whip - Strikes the target with slender, whiplike vines\n");
                }

                printf("[%d]: Ice Beam - Chance to FREEZE opponent\n", MOVE_ICE);
                printf("[%d]: Poison Gas - Envelops the target in a toxic gas that may poison\n", MOVE_POI);
                printf("[%d]: Sing - A soothing song lulls the foe into a deep slumber\n", MOVE_SIN);

                // Scan for move 
                printf("Enter a number (1-4): ");
                scanf("%d", &move);
                if (move == MOVE_ATT) {
                    valid_move = true; 
                    opp[INDEX_HP] -= dmg_dealt;
                    printf("You attack the opponent! Opposing pokemon now has %d HP!\n\n", opp[INDEX_HP]);
                    if (opp[INDEX_HP] <= 0) {
                        printf("Opponent has fainted!\n");
                        printf("CONGRATULATIONS!! YOU HAVE DEFEATED ALL OF YOUR OPPONENTS!!\n");
                        printf("YOU ARE NOW THE NEW POKEMON CHAMPION!!\n");
                        return 0;
                    }
                } else if (move == MOVE_ICE) {
                    printf("Your pokemon used Ice Beam!\n");
                    valid_move = true; 
                    printf("HIT! The opposing pokemon is now frozen!\n\n");
                    frozen = 3; 
                    opp[INDEX_STATUS] = STATUS_FRO;
                } else if (move == MOVE_POI) {
                    printf("Your pokemon used Poison Gas!\n");
                    valid_move = true; 
                    printf("HIT! The opposing pokemon is now poisoned!\n\n");
                    poisoned = 4; 
                    opp[INDEX_STATUS] = STATUS_POI;
                } else if (move == MOVE_SIN) {
                    printf("Your pokemon used Sing!\n");
                    valid_move = true; 
                    printf("HIT! The opposing pokemon is now asleep!\n\n");
                    sleeping = 5; 
                    opp[INDEX_STATUS] = STATUS_SLE;
                } else {
                    printf("Invalid input!\n");
                }
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
            printf("TYPE: ");
            if (own[INDEX_TYPE] == FIRE_VALUE) {
                printf("FIRE\n");
            } else if (own[INDEX_TYPE] == WATER_VALUE) {
                printf("WATER\n");
            } else {
                printf("GRASS\n");
            }
            printf("========================================\n");
            printf("\n");

            // Check opponent's stats
        } else if (cmd == CMD_OPP) {
            printf("\n========================================\n");
            printf("Opposing pokemon: \n");
            printf("HP:  %d\n", opp[INDEX_HP]);
            printf("ATT: %d\n", opp[INDEX_ATT]);
            printf("DEF: %d\n", opp[INDEX_DEF]);
            printf("TYPE: ");
            if (opp[INDEX_TYPE] == FIRE_VALUE) {
                printf("FIRE\n");
            } else if (opp[INDEX_TYPE] == WATER_VALUE) {
                printf("WATER\n");
            } else {
                printf("GRASS\n");
            }
            printf("STATUS: ");
            if (opp[INDEX_STATUS] == STATUS_FRO) {
                printf("FROZEN\n");
            } else if (opp[INDEX_STATUS] == STATUS_POI) {
                printf("POISONED\n");
            } else if (opp[INDEX_STATUS] == STATUS_SLE) {
                printf("SLEEPING\n");
            } else {
                printf("NORMAL\n");
            }
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
            if (opp[INDEX_STATUS] == STATUS_FRO) {
                // if opponent is frozen, misses a turn
                if (frozen > 0) {
                    frozen--;
                    printf("Opponent is frozen!\n");
                } else {
                    printf("Opponent is no longer frozen!\n");
                    opp[INDEX_STATUS] = STATUS_NOR;
                }
            } else if (opp[INDEX_STATUS] == STATUS_SLE) {
                // if opponent is sleeping, misses a turn
                if (sleeping > 0) {
                    sleeping--;
                    printf("Opponent is sleeping!\n");
                } else {
                    printf("Opponent is no longer sleeping!\n");
                    opp[INDEX_STATUS] = STATUS_NOR;
                }
            } 
            if (opp[INDEX_STATUS] == STATUS_NOR || opp[INDEX_STATUS] == STATUS_POI) {
                if (opp[INDEX_STATUS] == STATUS_POI) {
                    // if opponent is poisoned, will take 2 damage
                    if (poisoned > 0) {
                        printf("Opponent is poisoned! Took 2 damage!\n");
                        opp[INDEX_HP] -= 2; 
                        poisoned--; 
                        printf("Opposing pokemon now has %d HP!\n\n", opp[INDEX_HP]);
                        if (opp[INDEX_HP] <= 0) {
                            printf("Opponent has fainted!\n");
                            printf("CONGRATULATIONS!! YOU HAVE DEFEATED ALL OF YOUR OPPONENTS!!\n");
                            printf("YOU ARE NOW THE NEW POKEMON CHAMPION!!\n");
                            return 0;
                        }
                    } else {
                        printf("Opponent is no longer poisoned!\n");
                        opp[INDEX_STATUS] = STATUS_NOR;
                    }
                }

                // Opponent attacks!
                own[INDEX_HP] -= dmg_taken;
                printf("Opponent attacked! Your current pokemon has %d HP!\n\n", own[INDEX_HP]);

                if (own[INDEX_HP] <= 0) {
                    printf("Current pokemon has fainted!\n");
                    lost = true;
                }
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