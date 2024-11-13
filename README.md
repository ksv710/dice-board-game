# Dice Board Game

A two-player, tile-based board game where players roll dice, earn money and points, and strategically place tiles on a 7x7 grid. Each turn brings new opportunities and challenges, and the player with the highest score at the end wins!

## Table of Contents

- [About the Game](#about-the-game)
<!-- - [Game Rules](#game-rules) -->
- [Technologies Used](#technologies-used)
- [Installation](#installation)

---

## About the Game

In this game, players roll dice, land on cells, collect money and points, and place tiles on the board to mark their progress. Each cell on the board provides different rewards, and players compete to accumulate the most points while strategically placing their tiles.

---

<!-- ## Game Rules

1. **Objective:** The player with the most points by the end of the game wins.
2. **Turn Flow:**
   - Players roll two dice each turn to determine their position on the board.
   - Depending on where they land, they earn money, points, or other rewards.
   - Players then place a tile on an available cell to mark their move.
3. **Special Cells:** Cells provide either money (e.g., `$1`) or points (e.g., `*1`).
4. **Winning Conditions:** The game ends when the board is filled or a predetermined goal is reached. -->

---

## Technologies Used

- **C++**: Core game logic and structure

---

## Installation

Follow these steps to set up the project locally:

1. **Clone the Repository:**
   git clone https://github.com/your-username/dice-board-game.git
2. **Navigate to the Project Directory:**
   cd dice-board-game
3. **Compile the Game:**
   g++ Main.cpp Board.cpp Dice.cpp Player.cpp Tile.cpp CellId.cpp BoardSize.cpp -o main
4. **Run the Game:**
   ./main
