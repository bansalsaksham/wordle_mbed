# 2035le – A Wordle-Inspired Embedded Game

Welcome to **2035le**, a custom embedded implementation of the popular game Wordle, developed on the Mbed platform. This game offers an interactive, hardware-based take on the familiar word-guessing experience.

---

## 🎮 Game Overview

- **Objective:** Guess a 5-letter hidden word in ≤6 tries.
- **Feedback:** Letters in your guess are marked as:
  - ✅ Correct and in the correct position
  - 🔄 Correct but in the wrong position
  - ❌ Not in the word
- **Interface:** Game is played on an LCD using a nav-switch and pushbuttons.

---

## 🧰 Hardware Requirements

- Mbed-compatible board (e.g., LPC1768 or Nucleo-F401RE)
- uLCD display
- 5-way navigation switch
- Pushbuttons
- Speaker or buzzer (for sound features)

---

## 📁 Project Structure

```plaintext
wordle_mbed/
├── main.cpp                  # Game loop & main logic
├── dictionary.h             # Stores Word structs with hints
├── graphics.{cpp,h}         # LCD display & sprite rendering
├── keyboard.{cpp,h}         # Linked list-based keyboard
├── speech.{cpp,h}           # Audio output via PWM
├── hardware.{cpp,h}         # Peripheral initialization
├── doubly_linked_list.{cpp,h} # Used for keyboard structure
├── globals.h                # Global definitions
├── sprite.bmp               # Custom game sprite
└── CMakeLists.txt           # Mbed build configuration
```

---

## ✅ Basic Features Implemented

- [x] 2035-related 5-letter dictionary
- [x] Nav-switch to scroll through keyboard letters
- [x] Select and delete letters with nav/pushbuttons
- [x] Word submission and guess row management
- [x] Correct/misplaced letter visualization
- [x] Removal of unused letters from the keyboard
- [x] Hint display after 5 incorrect guesses
- [x] Win and Game Over screens
- [x] Custom sprite added for in-game visuals

---

## 🚀 Advanced Features

- [x] 🌀 Animations (e.g., win screen effects)
- [x] ⌨️ 2D Keyboard layout
- [x] 🔁 Reroll for a new word
- [x] ⏱️ Timer display
- [x] 📊 History of attempts or high score
- [x] 🧠 Wordle-like UI with color-coded rows
- [x] 📏 Support for longer word lengths
- [x] 🎮 Multiple game modes (e.g., Easy/Hard)
- [x] 🎨 10+ Custom sprites


---

## 🕹️ How to Play

1. Power up the board.
2. Use the nav-switch to scroll/select letters.
3. Press the center button to confirm a letter.
4. Use the pushbutton to delete a letter.
5. Submit the word after all 5 letters are filled.
6. Receive feedback and continue guessing.
7. Guess correctly to win, or receive a hint after 5 attempts.

---

## 💡 Customization

- Add more words: Edit `dictionary.h` with 2035-relevant terms.
- Design new sprites: Use [Piskel](https://www.piskelapp.com/) and save as `.bmp`.
- Modify gameplay: Adjust guess limit, word length, or add new game modes.

---

## 👨‍💻 Author

Saksham Bansal  
Undergraduate – Electrical Engineering
Georgia Institute of Technology
