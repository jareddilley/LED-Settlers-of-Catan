# SMART-Catan-Game-Board
![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/catan-dice-roll-demo.gif)

Fully 3D printed 2-4 person Catan board with corresponding LED tiles, electronic rolling with place pointers, recourse summary display, and all in a battery-powered sealed package. This project is powered by a rechargeable 9V battery and an Arduino nano to minimize its footprint. Above is a demo of the rolling animation that is done at the touch of a button. When clicked a random number generator is used to roll the dice with the same probability of rolling numbers that two regular dice do. Once rolled the number will be displayed on the seven-segment display and the corresponding locations will be singled out and lit up. This fixes one of the common issues of Catan where you roll the dice and try to figure out who gets what.

Built with the Open Source mindset allowing other people to build it at home with a 3D printer (I used an Ender 3 Pro) with a choice of soldier or using a breadboard. 

Attached is the Fusion 360 so the models can be edited directly and used to better understand how it is broken down. A YouTube link for visual learners: https://www.youtube.com/watch?v=NJuYirOUeOg&t=12s&ab_channel=JaredDilley
![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/3D-Breakdown.JPG)

# Board Generation
![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/catan-board-gen-demo.gif)

When the board is powered on the tiles are randomly set up in an instant. I know some people like to play an evenly distributed board, but it can be added as a feature in the second version. The instant setup of the board was the main issue I wanted to fix with this project. Whenever you want to play a game of Catan it always takes time to set up the board. Here it can be set up instantly with the flick of a switch.

# Info Display
![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/catan-info-display-demo.gif)

With the Arduino micro powering the board I figured I would add additional info that can be tracked on displays. In the middle of the board lies the power center that doubles as the desert tile. Here you can find a seven-segment display that serves as a remembrance for what was previously rolled to the next player. In V2 this could also serve as a time for those who take too long on their turn. In addition, there sits an OLED display that stores the number of rolls that each resource has been rolled. This can help judge the board for what resources might be in short supply and makes for cool stats to look at, at the end of the game. 

![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/displays.png)

# Bonus
![image](https://github.com/jareddilley/SMART-Catan-game-board/blob/main/Media/night.png)

The light-up hexagons make a game night in the dark that much cooler.
