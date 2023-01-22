- [1. BATTLESHIP GAME](#1-battleship-game)
  - [1.1. Rules](#11-rules)
  - [1.2. For developers](#12-for-developers)
  - [1.3. Future features](#13-future-features)
  - [1.4. References](#14-references)

# 1. BATTLESHIP GAME

![Battleship_logo.png](https://github.com/PabloCuestaMorer/battleship-game/assets/images/battleship_logo.png)

![AirCarrier_ship.png](https://github.com/PabloCuestaMorer/battleship-game/assets/images/ship.png)

The objective of the academic project for the subject of Object Oriented Programming at San Jorge University in Zaragoza, Spain, is to develop a **C++** game called "Battleship" in which two players take turns strategically placing their own fleet and trying to sink the opposing player's fleet through guessing the location of the opponent's ships on a 10x10 grid. The game includes features such as the option to save and load the current state of the game.

## 1.1. Rules

The game is played between two players.
Each player has two grids: one to place their own ships and another to record the results of their shots.
The columns are numbered (0-9) and the rows are labeled with capital letters (A-J).
At the beginning of the game, each player must place their ships on their own grid. Each player has five ships:

    - An aircraft carrier that occupies 5 spaces
    - An battleship that occupies 4 spaces
    - An submarine that occupies 3 spaces
    - An patrol boat that occupies 2 spaces
    - An ship that occupies 1 space

- The ships must be placed horizontally or vertically and there must be a clear space around the ships. The ships cannot touch each other.
- Once the ships are placed, each player takes turns shooting at the opponent's grid by indicating the coordinates of the chosen space (e.g. "B3").
- If the shot misses, the system will indicate "**water**." If the shot hits a ship, the system will indicate "**hit**" and the player gets another turn.
- If all spaces of a ship are hit, the ship is considered "**sunk**". If all of the opponent's ships are sunk, the game is over (**hit, sunk and fleet destroyed**).
- The game also includes the option to save and ~~load~~ (**_Unfinished_**) the current state of the game.

*Developed by Pablo Cuesta. Zaragoza, Spain. San Jorge University*

## 1.2. For developers

To activate the automatic placement of ships (instead of by hand).
In the Main.cpp class:

    .placeShipsRandomly();

## 1.3. Future features

1. Load game
2. A single-player mode with an AI opponent
3. Different levels of difficulty for the AI opponent
4. A graphical user interface (GUI)
5. An option to play on different board sizes
6. An option to play with more players

## 1.4. References

- [1] Wikipedia, "Battleship (game)," [Online]. Available: https://en.wikipedia.org/wiki/Battleship_(game).