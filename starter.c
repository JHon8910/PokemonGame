#include <stdio.h>
#include <stdbool.h>

// define your constants here
#define STARTER_NUM 3
#define OPPONENT_NUM 3
#define INDEX_HP 0
#define INDEX_ATT 1
#define INDEX_DEF 2
#define INDEX_TYPE 3

#define TYPE_FIRE 'f'
#define TYPE_WATER 'w'
#define TYPE_GRASS 'g'
#define FIRE_VALUE 1
#define WATER_VALUE 2
#define GRASS_VALUE 3

#define CMD_ATK 'a'
#define CMD_SWITCH 's'
#define CMD_HEAL 'h'
#define CMD_STATS 'c'
#define CMD_OPP 'o'
#define CMD_CMDS '?'

int main(void) {
    // Begin game
    printf("Welcome to Pokemon!!!\n\n");

    // Ask user for details on their starter pokemon 
    // starters[first][second]
    // first index represents which pokemon
    // second index represents respective stats of the pokemon: 
        /*
            0: HP
            1: ATT
            2: DEF
            3: TYPING (1: fire, 2: water, 3: grass)
        */
    int starters[STARTER_NUM][4];

    int i = 0;
    while (i < STARTER_NUM) {
        int stats = 20; 
        bool valid = false; 

        // Scan hp of starter pokemon
        int hp;
        while (!valid) { // valid == false
            printf("You have %d stat points remaining.\n", stats);
            printf("Please enter the HEALTH of your starter pokemon: ");
            scanf("%d", &hp);
            if (hp > stats) {
                printf("You cannot use more than your given stat points\n\n");
            } else {
                stats -= hp;
                valid = true;
            }
        }

        // scan att of starter pokemon
        valid = false;
        int att;
        while (!valid) { // valid == false
            printf("You have %d stat points remaining.\n", stats);
            printf("Please enter the ATTACK of your starter pokemon: ");
            scanf("%d", &att);
            if (att > stats) {
                printf("You cannot use more than your given stat points\n\n");
            } else {
                stats -= att;
                valid = true;
            }
        }

        // scan def of starter pokemon
        valid = false;
        int def;
        while (!valid) { // valid == false
            printf("You have %d stat points remaining.\n", stats);
            printf("Please enter the DEFENCE of your starter pokemon: ");
            scanf("%d", &def);
            if (def > stats) {
                printf("You cannot use more than your given stat points\n\n");
            } else {
                stats -= def;
                valid = true;
            }
        }

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

        // Assign stats to pokemon
        starters[i][INDEX_HP] = hp;
        starters[i][INDEX_ATT] = att;
        starters[i][INDEX_DEF] = def;
        if (type == TYPE_FIRE) {
            starters[i][INDEX_TYPE] = FIRE_VALUE;
        } else if (type == TYPE_WATER) {
            starters[i][INDEX_TYPE] = WATER_VALUE;
        } else {
            starters[i][INDEX_TYPE] = GRASS_VALUE;
        }
        i++;
    }

    // Ask user for number of potions to start with
    int potions;
    printf("How many potions do you have: ");
    scanf("%d", &potions);

    // Create opponent pokemon
    int opponents[OPPONENT_NUM][4];
    int j = 0;
    while (j < OPPONENT_NUM) {
        opponents[j][0] = 10;    // hp
        opponents[j][1] = 5;     // att
        opponents[j][2] = 5;     // def
        opponents[j][3] = j + 1; // typing will be fire, water, grass
        j++;
    }

    // Print current pokemon details
    int curr_pokemon = 0;
    printf("Your current pokemon: \n");
    printf("Pokemon %d:\n", curr_pokemon + 1);
    printf("HP:  %d\n", starters[curr_pokemon][INDEX_HP]);
    printf("ATT: %d\n", starters[curr_pokemon][INDEX_ATT]);
    printf("DEF: %d\n", starters[curr_pokemon][INDEX_DEF]);
    printf("TYPE: ");
    if (starters[curr_pokemon][INDEX_TYPE] == FIRE_VALUE) {
        printf("FIRE\n");
    } else if (starters[curr_pokemon][INDEX_TYPE] == WATER_VALUE) {
        printf("WATER\n");
    } else {
        printf("GRASS\n");
    }
    printf("\n");

    // Print current opponent's statas
    int curr_opponent = 0;
    printf("Current opposing pokemon: \n");
    printf("Pokemon %d:\n", curr_opponent + 1);
    printf("HP:  %d\n", starters[curr_opponent][INDEX_HP]);
    printf("ATT: %d\n", starters[curr_opponent][INDEX_ATT]);
    printf("DEF: %d\n", starters[curr_opponent][INDEX_DEF]);
    printf("TYPE: ");
    if (starters[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
        printf("FIRE\n");
    } else if (starters[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
        printf("WATER\n");
    } else {
        printf("GRASS\n");
    }
    printf("\n");

    // Calculate advantageous types
    // dmg_dealt = adv * (own_att - opp_def) 
    // dmg_taken = 1 / adv * (opp_att - own_def)
    double adv = 1.0;
    if (starters[curr_pokemon][INDEX_TYPE] == FIRE_VALUE) {
        if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
            adv = 2.0;
        } else if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
            adv = 0.5;
        }
    } else if (starters[curr_pokemon][INDEX_TYPE] == WATER_VALUE) {
        if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
            adv = 2.0;
        } else if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
            adv = 0.5;
        }
    } else {
        if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
            adv = 2.0;
        } else if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
            adv = 0.5;
        }
    } 

    int dmg_dealt = adv * (starters[curr_pokemon][INDEX_ATT] / opponents[curr_opponent][INDEX_DEF]) + 1;
    int dmg_taken = 1 / adv * (opponents[curr_opponent][INDEX_ATT] / starters[curr_pokemon][INDEX_DEF]) + 1;

    printf("dealt: %d\n" , dmg_dealt);
    printf("taken: %d\n" , dmg_taken);

    // Scan commands
    printf("Valid commands:\n");
    printf("[%c]: ATTACK the opponent!\n", CMD_ATK);
    printf("[%c]: HEAL your pokemon by using a potion!\n", CMD_HEAL);
    printf("[%c]: SWITCH out your pokemon!\n", CMD_SWITCH);
    printf("[%c]: CHECK your party's stats!\n", CMD_STATS);
    printf("[%c]: CHECK your opponent's stats!\n", CMD_OPP);
    printf("[%c]: VIEW valid commands!\n", CMD_CMDS);
    printf("Please enter a command: ");
    char cmd;
    bool lost = false;
    while (scanf(" %c", &cmd) != EOF && !lost) {
        // Attack the opponent
        if (cmd == CMD_ATK) {
            opponents[curr_opponent][INDEX_HP] -= dmg_dealt;
            printf("You attack the opponent! Opposing pokemon now has %d HP!\n", opponents[curr_opponent][INDEX_HP]);
            if (opponents[curr_opponent][INDEX_HP] <= 0) {
                printf("Opponent has fainted!\n");
                curr_opponent++;

                // If there are no more opponents
                if (curr_opponent == OPPONENT_NUM) {
                    printf("CONGRATULATIONS!! YOU HAVE DEFEATED ALL OF YOUR OPPONENTS!!\n");
                    printf("YOU ARE NOW THE NEW POKEMON CHAMPION!!\n");
                    return 0;
                }
                
                // Print new opponent
                printf("Current opposing pokemon: \n");
                printf("Pokemon %d:\n", curr_opponent + 1);
                printf("HP:  %d\n", starters[curr_opponent][INDEX_HP]);
                printf("ATT: %d\n", starters[curr_opponent][INDEX_ATT]);
                printf("DEF: %d\n", starters[curr_opponent][INDEX_DEF]);
                printf("TYPE: ");
                if (starters[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                    printf("FIRE\n");
                } else if (starters[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                    printf("WATER\n");
                } else {
                    printf("GRASS\n");
                }
                printf("\n");

                // Recalcualte advantageous types
                adv = 1.0;
                if (starters[curr_pokemon][INDEX_TYPE] == FIRE_VALUE) {
                    if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                        adv = 2.0;
                    } else if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                        adv = 0.5;
                    }
                } else if (starters[curr_pokemon][INDEX_TYPE] == WATER_VALUE) {
                    if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                        adv = 2.0;
                    } else if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                        adv = 0.5;
                    }
                } else {
                    if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                        adv = 2.0;
                    } else if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                        adv = 0.5;
                    }
                } 

                dmg_dealt = adv * (starters[curr_pokemon][INDEX_ATT] / opponents[curr_opponent][INDEX_DEF]) + 1;
                dmg_taken = 1 / adv * (opponents[curr_opponent][INDEX_ATT] / starters[curr_pokemon][INDEX_DEF]) + 1;
            }
            // Switch the user's pokemon
        } else if (cmd == CMD_SWITCH) {
            // Switch to another pokemon
            printf("Please switch to another pokemon!\n");
            bool valid_switch = false;
            while (!valid_switch) {
                int i = 0; 
                while (i < STARTER_NUM) { 
                    if (i == curr_pokemon) {
                        printf("ON FIELD\n");
                    }
                    printf("========================================\n");
                    printf("Pokemon %d:\n", i + 1);
                    printf("HP:  %d\n", starters[i][INDEX_HP]);
                    printf("ATT: %d\n", starters[i][INDEX_ATT]);
                    printf("DEF: %d\n", starters[i][INDEX_DEF]);
                    printf("TYPE: ");
                    if (starters[i][INDEX_TYPE] == FIRE_VALUE) {
                        printf("FIRE\n");
                    } else if (starters[i][INDEX_TYPE] == WATER_VALUE) {
                        printf("WATER\n");
                    } else {
                        printf("GRASS\n");
                    }
                    printf("========================================\n");
                    printf("\n");
                    i++;
                } 
                printf("Choose which pokemon to switch to: ");
                int switch_pokemon;
                scanf("%d", &switch_pokemon);
                switch_pokemon--;
                if (starters[switch_pokemon][INDEX_HP] <= 0) {
                    printf("Chosen pokemon has fainted, choose another!\n");
                } else {
                    valid_switch = true; 
                    curr_pokemon = switch_pokemon;

                    // Recalculate advantageous types
                    adv = 1.0;
                    if (starters[curr_pokemon][INDEX_TYPE] == FIRE_VALUE) {
                        if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                            adv = 2.0;
                        } else if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                            adv = 0.5;
                        }
                    } else if (starters[curr_pokemon][INDEX_TYPE] == WATER_VALUE) {
                        if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                            adv = 2.0;
                        } else if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                            adv = 0.5;
                        }
                    } else {
                        if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                            adv = 2.0;
                        } else if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                            adv = 0.5;
                        }
                    } 
                }
            }

            // Heal one of the user's pokemon
        } else if (cmd == CMD_HEAL) {
            if (potions > 0) {
                // Use potion
                potions--; // potions = potions - 1;
                starters[curr_pokemon][INDEX_HP] += 5; // starters[curr_pokemon][INDEX_HP] = starters[curr_pokemon][INDEX_HP] + 5;
                printf("Potion used! You currently have %d potions left!\n", potions);
                printf("Your current pokemon has %d hp!\n", starters[curr_pokemon][INDEX_HP]);

            } else {
                printf("You have no more potions left!\n");
            }

            // Check party stats
        } else if (cmd == CMD_STATS) {
            int i = 0; 
            while (i < STARTER_NUM) { 
                if (i == curr_pokemon) {
                    printf("ON FIELD\n");
                }
                printf("========================================\n");
                printf("Pokemon %d:\n", i + 1);
                printf("HP:  %d\n", starters[i][INDEX_HP]);
                printf("ATT: %d\n", starters[i][INDEX_ATT]);
                printf("DEF: %d\n", starters[i][INDEX_DEF]);
                printf("TYPE: ");
                if (starters[i][INDEX_TYPE] == FIRE_VALUE) {
                    printf("FIRE\n");
                } else if (starters[i][INDEX_TYPE] == WATER_VALUE) {
                    printf("WATER\n");
                } else {
                    printf("GRASS\n");
                }
                printf("========================================\n");
                printf("\n");
                i++;
            }

            // Check opponent's stats
        } else if (cmd == CMD_OPP) {
            int curr_opponent = 0;
            printf("Current opposing pokemon: ");
            printf("Pokemon %d:\n", curr_opponent + 1);
            printf("HP:  %d\n", starters[curr_opponent][INDEX_HP]);
            printf("ATT: %d\n", starters[curr_opponent][INDEX_ATT]);
            printf("DEF: %d\n", starters[curr_opponent][INDEX_DEF]);
            printf("TYPE: ");
            if (starters[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                printf("FIRE\n");
            } else if (starters[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                printf("WATER\n");
            } else {
                printf("GRASS\n");
            }
            printf("\n");
        
            
            // Invalid Command 
        } else if (cmd == CMD_CMDS) {
            printf("Valid commands:\n");
            printf("[%c]: ATTACK the opponent!\n", CMD_ATK);
            printf("[%c]: HEAL your pokemon by using a potion!\n", CMD_HEAL);
            printf("[%c]: SWITCH out your pokemon!\n", CMD_SWITCH);
            printf("[%c]: CHECK your party's stats!\n", CMD_STATS);
            printf("[%c]: VIEW valid commands!\n", CMD_CMDS);
        
            
            // Invalid Command 
        } else {
            printf("Unknown command: %c\n", cmd);
        }

        // Opponent attacks!
        if (cmd == CMD_ATK || cmd == CMD_SWITCH || cmd == CMD_HEAL) {
            starters[curr_pokemon][INDEX_HP] -= dmg_taken;
            printf("Opponent attacked! Your current pokemon has %d hp\n\n", starters[curr_pokemon][INDEX_HP]);
            if (starters[curr_pokemon][INDEX_HP] <= 0) {
                printf("Current pokemon has fainted!\n");
                
                // Check that there are other available pokemon left
                bool available = false;
                int l = 0; 
                while (l < STARTER_NUM) {
                    if (starters[l][INDEX_HP] > 0) {
                        available = true; 
                    }
                    l++;
                }

                if (available) {
                    // Switch to another pokemon
                    printf("Please switch to another pokemon!\n");
                    bool valid_switch = false;
                    while (!valid_switch) {
                        int i = 0; 
                        while (i < STARTER_NUM) { 
                            if (i == curr_pokemon) {
                                printf("ON FIELD\n");
                            }
                            printf("========================================\n");
                            printf("Pokemon %d:\n", i + 1);
                            printf("HP:  %d\n", starters[i][INDEX_HP]);
                            printf("ATT: %d\n", starters[i][INDEX_ATT]);
                            printf("DEF: %d\n", starters[i][INDEX_DEF]);
                            printf("TYPE: ");
                            if (starters[i][INDEX_TYPE] == FIRE_VALUE) {
                                printf("FIRE\n");
                            } else if (starters[i][INDEX_TYPE] == WATER_VALUE) {
                                printf("WATER\n");
                            } else {
                                printf("GRASS\n");
                            }
                            printf("========================================\n");
                            printf("\n");
                            i++;
                        } 

                        printf("Choose which pokemon to switch to: ");
                        int switch_pokemon;
                        scanf("%d", &switch_pokemon);
                        switch_pokemon--;
                        if (starters[switch_pokemon][INDEX_HP] <= 0) {
                            printf("Chosen pokemon has fainted, choose another!\n");
                        } else {
                            valid_switch = true; 
                            curr_pokemon = switch_pokemon;

                            // Recalculate advantageous types
                            adv = 1.0;
                            if (starters[curr_pokemon][INDEX_TYPE] == FIRE_VALUE) {
                                if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                                    adv = 2.0;
                                } else if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                                    adv = 0.5;
                                }
                            } else if (starters[curr_pokemon][INDEX_TYPE] == WATER_VALUE) {
                                if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                                    adv = 2.0;
                                } else if (opponents[curr_opponent][INDEX_TYPE] == GRASS_VALUE) {
                                    adv = 0.5;
                                }
                            } else {
                                if (opponents[curr_opponent][INDEX_TYPE] == WATER_VALUE) {
                                    adv = 2.0;
                                } else if (opponents[curr_opponent][INDEX_TYPE] == FIRE_VALUE) {
                                    adv = 0.5;
                                }
                            } 
                        }
                    }
                } else {
                    lost = true;
                }
            }
        }

        // Ask again for command
        printf("Please enter a command: ");
    }

    if (lost) {
        printf("Your entire party has fainted!\n");
        printf("Game Over!\n");
    }
    return 0;
}