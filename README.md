# wwfCheat
I got sick of losing to my grandma in words with friends 2 so I developed this to calculate the best possible words to play on my turn. Currently runs using a greedy algorithm and does not use complicated AI and therefore takes a long time to run. I've unfotunately been short on time so I have not had time to implement a heuristic algorithm that can better find words and run significantly faster. I also would like some form of prediction model so the algorithm plays the best word that can lead to more future points. 

# Usage
1. Compile main.cpp
2. Run compiled program
3. Follow built in instructions

# Plans
- Multithreading, I have implemented this into a few Java programs but never in C++. After doing a quick internet search it looks like C++ is a little more difficult to implement multithreading into so I may convert this project to Java to do that. I believe multithreading will greatly improve the runtime issues.
- Prediction Model. I need to implement a form of prediction model into the algorithm so that the algorithm considers what tiles the opponent may have and what tiles remain that the user can still draw when picking a word. For example playing a 52 point word and a 12 point word is worse than if it holds onto some letter and plays a 40 point word and 30 point word using one of the previous letters. Additionally Scrabble ends when the first player goes out. If the user can go out and win with a low scoring word it should do so and not draw out the game cause that could cost the win.
- Blank Tiles. Currently the algorithm does not support the blank tile that you can draw and forces the user to play the turn if this is drawn. I'd like to add in support for this tile in the future.
- Heuristic Algorithm. An algorithm that decides on a word with certain properties and not necessarily just being the highest possible word. The algorithm should also eliminate words with certain properties instead of still checking them. For example if we find a word worth 50 points any words with 3 letters and a sum less than 17 should be eliminated.
