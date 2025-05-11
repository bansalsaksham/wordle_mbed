#include "keyboard.h"
#include "dictionary.h"
#include "speech.h"
#include <string>
#include <stdlib.h>

#define DICTIONARY_SIZE (sizeof(dictionary) / sizeof(dictionary[0])) // Dynamically calculate dictionary size

DLinkedList *keyboard;
LLNode *curr;
char *goal_word;
char *guess; // Dynamic allocation for word length
int idx_2 = 0;
int row = 0;
int word_length = 0; // Length of the goal word
char *hint1;
char *hint2;

/*
 * Function to compare chars in the doubly linked list.
 */
int compareChar(void *input1, void *input2)
{
    return (*(char *)input1 == *(char *)input2) ? 1 : 0;
}

/*
 * Function to update the keyboard display, showing the current letter
 * and its neighbors with the center letter highlighted.
 */
void update_keyboard_display()
{
    char prev = curr->prev ? *(char *)curr->prev->data : *(char *)keyboard->tail->data; // Wrap to tail
    char next = curr->next ? *(char *)curr->next->data : *(char *)keyboard->head->data; // Wrap to head

    uLCD.locate(7, 15);
    uLCD.color(0xFFFFFF); // White for neighbors
    uLCD.putc(prev);      // Display previous letter

    uLCD.locate(8, 15);
    uLCD.color(0x00FF00); // Green for the current letter
    uLCD.putc(*(char *)curr->data); // Display current letter

    uLCD.locate(9, 15);
    uLCD.color(0xFFFFFF); // White for neighbors
    uLCD.putc(next);      // Display next letter
}

/*
 * Initializes the keyboard and selects a random goal word.
 */
void init_keyboard()
{
    // Select random word from dictionary
    // Change random_selection to Word1 to match the type in hard_dictionary

    int random_word_ind;

    if (selected_game_mode == 2) {
        Word1 random_selection; // Now matches the type in hard_dictionary
        random_word_ind = rand() % 10; // Select a random word index from hard_dictionary
        random_selection = hard_dictionary[random_word_ind]; // Assign directly from hard_dictionary
        goal_word = random_selection.letters;
        hint1 = random_selection.hint1;
        hint2 = random_selection.hint2;
        } 
    else {
        Word random_selection; // Now matches the type in hard_dictionary
        random_word_ind = rand() % DICTIONARY_SIZE; // Select from the regular dictionary
        random_selection = dictionary[random_word_ind]; // Assign from dictionary
        goal_word = random_selection.letters;
        hint1 = random_selection.hint1;
        hint2 = random_selection.hint2;
    }


    word_length = strlen(goal_word); // Get the length of the selected word
    guess = (char *)malloc((word_length + 1) * sizeof(char)); // Allocate memory for the guess array
    printf("Goal word is %s\n\r", goal_word);

    // Populate the keyboard with letters 'a' to 'z'
    keyboard = create_dlinkedlist();
    for (char c = 'a'; c <= 'z'; ++c)
    {
        char *letter = (char *)malloc(sizeof(char));
        *letter = c;
        insertTail(keyboard, (void *)letter);
    }

    curr = keyboard->head; // Set current letter to 'a'
    update_keyboard_display(); // Show initial keyboard display
}
/*
 * Moves the keyboard selection to the left.
 */
void moveleft() {
    curr = curr->prev ? curr->prev : keyboard->tail; // Wrap around to tail
    update_keyboard_display();
    wait_us(200000); // Debounce delay
}

/*
 * Moves the keyboard selection to the right.
 */
void moveright() {
    curr = curr->next ? curr->next : keyboard->head; // Wrap around to head
    update_keyboard_display();
    wait_us(200000); // Debounce delay
}

/*
 * Selects the current letter and adds it to the guess.
 */
void select_letter() {
    if (idx_2 < word_length) {
        guess[idx_2] = *(char*)curr->data;
        uLCD.locate(idx_2, 2 + row);
        uLCD.putc(guess[idx_2]); // Display the letter
        idx_2++;
    }

    if (idx_2 == word_length) {
        guess[idx_2] = '\0'; // Null-terminate the guessed word
        check_word(); // Validate the guess
        idx_2 = 0;
        row++; // Move to the next row for the next guess
    }
    wait_us(200000); // Debounce delay
}

/*
 * Removes the last letter from the guess.
 */
void remove_letter() {
    if (idx_2 > 0) {
        idx_2--; // Decrement index
        uLCD.locate(idx_2, 2 + row);
        uLCD.putc(' '); // Clear the letter on screen
        guess[idx_2] = '\0'; // Null-terminate
    }
}

/*
 * Removes an incorrect letter from the keyboard.
 */
void remove_from_keyboard(char letter) {
    LLNode* temp = keyboard->head;
    while (temp) {
        if (*(char*)temp->data == letter) {
            if (temp->prev) temp->prev->next = temp->next;
            else keyboard->head = temp->next; // Update head

            if (temp->next) temp->next->prev = temp->prev;
            else keyboard->tail = temp->prev; // Update tail

            free(temp->data);
            free(temp);
            break;
        }
        temp = temp->next;
    }
}

/*
 * Draw a single frame of fireworks at a specific height.
 */
void draw_fireworks(int height, bool final_burst) {
    uLCD.cls(); // Clear the screen
    uLCD.color(0xFFFFFF); // White color for fireworks

    // Firework trail (rising effect)
    uLCD.line(60, 120, 60, height, 0x888888); // Grey trail

    // Burst or ongoing fireworks
    if (!final_burst) {
        // Rising fireworks with small burst
        uLCD.line(40, height, 60, height - 20, 0xFF0000); // Red line
        uLCD.line(60, height - 20, 80, height, 0x00FF00); // Green line
        uLCD.circle(60, height - 10, 5, 0xFFFF00);       // Yellow center
    } else {
        // Final burst: Exploding fireworks
        uLCD.line(40, height, 80, height - 40, 0xFF0000); // Red diagonal
        uLCD.line(80, height, 40, height - 40, 0x00FF00); // Green diagonal
        uLCD.line(60, height + 10, 60, height - 50, 0x0000FF); // Vertical
        uLCD.line(30, height - 20, 90, height - 20, 0xFFFF00); // Horizontal
        uLCD.circle(60, height - 20, 10, 0xFFFFFF);       // Outer circle
        uLCD.circle(60, height - 20, 20, 0xFFFFFF);       // Larger circle
    }
}
bool hint_shown = false; // Track if the hint has been displayed

/*
 * Checks the player's guess against the goal word
 * and removes incorrect letters from the keyboard.
 */
void check_word() {
    bool is_correct = true;

    for (int i = 0; i < word_length; i++) {
        if (guess[i] == goal_word[i]) {
            uLCD.locate(i, 2 + row);
            uLCD.color(0x00FF00); // Green for correct position
            uLCD.putc(guess[i]);
        } else if (strchr(goal_word, guess[i])) {
            is_correct = false;
            uLCD.color(0xFFFF00); // Yellow for misplaced
            uLCD.putc(guess[i]);
        } else {
            is_correct = false;
            uLCD.color(0xFF0000); // Red for incorrect
            uLCD.putc(guess[i]);
            remove_from_keyboard(guess[i]); // Remove incorrect letter
        }
    }

    if (is_correct) {
        // Fireworks Animation
        for (int height = 120; height > 40; height -= 10) {
            draw_fireworks(height, false); // Rising fireworks
            wait_us(200000);              // Delay for animation effect
        }
        draw_fireworks(40, true); // Final burst at the top
        wait_us(500000);          // Hold final burst
        uLCD.cls();
        uLCD.locate(4, 4);
        uLCD.color(0x00FF00);
        uLCD.printf("You Win!");
        return;
    }

    if (hint_shown) {
        // If hint was already shown, this is the final allowed guess
        uLCD.cls();
        uLCD.locate(4, 4);
        uLCD.color(0xFF0000);
        uLCD.printf("You Lose :(");
        return;
    }

    if (row == 4) { // After 5 incorrect guesses
        uLCD.locate(0, 10);
        uLCD.color(0xFFFFFF);
        uLCD.printf("Hint: %s", hint1);
        uLCD.locate(0, 12);
        uLCD.printf("Hint: %s", hint2);
        hint_shown = true; // Mark that the hint has been displayed
    } else if (row == 6) { // After 6 guesses
        uLCD.cls();
        uLCD.locate(4, 4);
        uLCD.color(0xFF0000);
        uLCD.printf("You Lose :(");
    }
}

/*
 * Resets the game state by selecting a new goal word, reinitializing the keyboard, 
 * and resetting the player's guess progress.
 */
void reroll() {
    // Free existing resources
    free(guess);
    LLNode* temp = keyboard->head;
    while (temp) {
        LLNode* next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }
    free(keyboard);

    // Reinitialize variables
    idx_2 = 0;
    row = 0;
    hint_shown = false;

    // Reinitialize keyboard and word
    init_keyboard();

    // Clear the screen and redraw the initial state
    uLCD.cls();
    draw_lower_status();
    draw_sprite();   // Add this line to regenerate the sprite (goal word or interactive sprite)
    draw_sprite1();
    printf("New goal word is %s\n\r", goal_word);
}
