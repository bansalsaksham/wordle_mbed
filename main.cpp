//=================================================================
// The main program file.
//
// Copyright 2024 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"
#include "speech.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
int selected_game_mode = 0; // Default to EASY (index 0 in menu_options)


void set_random_seed(Timer);
void show_start_menu();

enum GameMode {
    EASY,
    MEDIUM,
    HARD
};

GameMode currentMode = EASY; // Default mode is EASY

/*
 * This function handles the main logic of the game. You should
 * initialize the hardware in this function, make calls to
 * functions that update the keyboard and your guess of
 * the word.
 */
int main()
{
    GameInputs inputs;

    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    printf("Program Starting\n");
    myled1 = 1;

    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time

    // Show advanced start menu
    show_start_menu();

    // Initialize game state
    set_random_seed(t);

    while (1)
    {
        t.start();
        myled2 = !myled2; // Blink LED2 to show game progress

        // CORE GAME LOOP
        draw_lower_status(); // Draws a line to separate the keyboard from guesses

        // Read user inputs and store in 'inputs' variable
        inputs = read_inputs();

        // Update game based on user inputs
        if (inputs.left)
        {
            moveleft(); // Move cursor left in the keyboard
        }
        else if (inputs.right)
        {
            moveright(); // Move cursor right in the keyboard
        }
        else if (inputs.center)
        {
            select_letter(); // Select the current letter for the guess
        }
        else if (inputs.b2)
        {
            remove_letter(); // Remove the last selected letter
        }
        else if (inputs.b3)
        {
            reroll(); // Reset the game
        }

        // Compute update time
        t.stop();
        dt = t.read_ms();
        if (dt < 100)
            wait_us((100 - dt) * 1000);
    }
    return 0;
}

// Set timer, display start screen
void set_random_seed(Timer t)
{
    t.start();
    uLCD.cls();
    uLCD.locate(4, 4);
    uLCD.printf("Push any button to start.");
    while (1)
    {
        GameInputs inputs = read_inputs();
        if (inputs.b1 || inputs.b2 || inputs.b3)
            break;
    }
    wait_us(200000);
    uLCD.cls();
    draw_sprite();
    draw_sprite1();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
    init_keyboard();
    }
/*
 * Advanced start menu implementation.
 * Allows the user to select a difficulty level or view instructions.
 */
void show_start_menu()
{
    int selected_option = 0;
    const char *menu_options[] = {"Easy", "Medium", "Hard", "Instructions"};
    const int num_options = 4;
    bool menu_active = true; // Track if the menu is active

    // Initial Menu Display
    uLCD.cls();
    uLCD.locate(4, 1);
    uLCD.color(0xFFFFFF);
    uLCD.printf("Start Menu");

    // Render menu options
    for (int i = 0; i < num_options; i++)
    {
        uLCD.locate(2, 3 + i);
        if (i == selected_option)
        {
            uLCD.color(0x00FF00); // Highlight selected option
            uLCD.printf("-> %s", menu_options[i]);
        }
        else
        {
            uLCD.color(0xFFFFFF); // Default color for other options
            uLCD.printf("   %s", menu_options[i]);
        }
    }

    while (menu_active)
    {
        // Process inputs
        GameInputs inputs = read_inputs();

        if (inputs.left && selected_option > 0)
        {
            selected_option--;
            wait_us(200000); // Debounce delay
        }
        else if (inputs.right && selected_option < num_options - 1)
        {
            selected_option++;
            wait_us(200000); // Debounce delay
        }
        else if (inputs.center)
        {
            selected_game_mode = selected_option;
            if (selected_option == 3) // Instructions selected
            {
                // Display instructions
                uLCD.cls();
                uLCD.locate(0, 1);
                uLCD.printf("Instructions:");
                uLCD.locate(0, 3);
                uLCD.printf("1. Use left/right");
                uLCD.locate(0, 4);
                uLCD.printf("   to select.");
                uLCD.locate(0, 5);
                uLCD.printf("2. Center to");
                uLCD.locate(0, 6);
                uLCD.printf("   confirm choice.");
                uLCD.locate(0, 7);
                uLCD.printf("3. Guess the word!");
                uLCD.locate(0, 9);
                uLCD.printf("Press any button");
                uLCD.locate(0, 10);
                uLCD.printf(" to return.");

                while (1)
                {
                    GameInputs back_input = read_inputs();
                    if (back_input.b1 || back_input.b2 || back_input.b3)
                        break;
                }

                // Return to menu
                uLCD.cls();
                uLCD.locate(4, 1);
                uLCD.printf("Start Menu");

                // Re-render menu options
                for (int i = 0; i < num_options; i++)
                {
                    uLCD.locate(2, 3 + i);
                    if (i == selected_option)
                    {
                        uLCD.color(0x00FF00);
                        uLCD.printf("-> %s", menu_options[i]);
                    }
                    else
                    {
                        uLCD.color(0xFFFFFF);
                        uLCD.printf("   %s", menu_options[i]);
                    }
                }
            }
            else
            {
                // Clear the screen and transition to game
                uLCD.cls(); // Clear any leftover menu/instruction text
                uLCD.locate(4, 5);
                uLCD.color(0xFFFFFF);
                uLCD.printf("Starting");
                uLCD.locate(4, 6);
                uLCD.color(0xFFFFFF);
                uLCD.printf("%s mode...", menu_options[selected_option]);
                wait_us(2000000); // Display message briefly

                menu_active = false; // Exit the menu loop
            }
        }

        // Update menu display without clearing the screen
        for (int i = 0; i < num_options; i++)
        {
            uLCD.locate(2, 3 + i);
            if (i == selected_option)
            {
                uLCD.color(0x00FF00); // Highlight selected option
                uLCD.printf("-> %s", menu_options[i]);
            }
            else
            {
                uLCD.color(0xFFFFFF); // Default color for other options
                uLCD.printf("   %s", menu_options[i]);
            }
        }
    }
}
