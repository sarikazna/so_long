# So_Long

## Description

So_Long is a simple 2D game project implemented in C as part of the School 42 curriculum. The objective of the game is to navigate a character through a maze while collecting items and avoiding obstacles. It's a fun and challenging project that demonstrates skills in programming, game development, and graphics rendering.

<img src="https://github.com/sarikazna/42lisboa/assets/121969818/5329be80-3fb2-467f-8fe3-e5fc5a44e23a" width="700">

## Features

- Maze navigation with a player character.
- Collectible items to score points.
- Obstacles to avoid, adding challenge to the gameplay.
- Simple graphics rendering using the minilibx library.

## Installation

To play So_Long, follow these steps:

1. You may need to install the following dependencies:
   
   ```bash
   sudo apt-get install gcc make xorg libxext-dev libbsd-dev

2. Clone this repository to your local machine, compile it, and run it by copy pasting this code into your bash terminal.
   
   ```bash
   git clone https://github.com/sarikazna/42lisboa sararudman_rep && cd sararudman_rep/so_long && make && make bonus && ./so_long_bonus maps/valid_bonus_maps/map_square.ber
3. To run the game again:
   
   ```bash
   make re && ./so_long maps/valid_maps/map_a.ber
4. To run the bonus game that contain an enemy (the needle) run:
   
   ```bash
   make re && ./so_long_bonus maps/valid_bonus_maps/map_square.ber
Feel free to create your own maze of the game as well. See section Maps below for more details.

## Controls

Use WASD or arrow keys to move.
|KEY|OBJECT|
|---|------|
| W | Move up |
| A | Move left |
| S | Move down |
| D | Move right |
| Esc | Close the game |



## Maps/Maze
The game is able to parse any kind of map, as long as it respects the below rules:
The map must be a .ber file.

And can only contain these characters:

CHAR	OBJECT
|CHAR|OBJECT|
|---|------|
|1	|Wall|
|C	|Bone|
|E	|Exit|
|P	|Player|
|0	|Floor|

For bonus there's an extra character - which makes you lose once touch it.

|CHAR|OBJECT|
|---|------|
|X |Needly|

<img width="160" alt="Posnetek zaslona 2024-03-28 232603" src="https://github.com/sarikazna/42lisboa/assets/121969818/02894461-64b7-4a5e-a2ad-26cb367f8fa2">

The map must be rectangular and surrounded by walls '1'.

The map must contain one exit, at least one collectible, and one starting position.

## Resources used to code this project

1. Project instructions by 42: https://cdn.intra.42.fr/pdf/pdf/105321/en.subject.pdf
2. What is MiniLibx? https://harm-smits.github.io/42docs/libs/minilibx/introduction.html
3. 42 vidoes e-learning on MiniLibx (in French): https://elearning.intra.42.fr/notions/minilibx/subnotions
4. Guide on so_long project: https://reactive.so/post/42-a-comprehensive-guide-to-so_long
5. Video on the project (in Russian): https://www.youtube.com/watch?v=D1DeE-Qit3M&t=569s
