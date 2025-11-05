# Battleship Analysis Engine

Calculate the best moves with this tool. Made for GamePigeon 8x8 battleship.

## Use

Mark on the map which tiles have been hit and which tiles are confirmed to be a miss.

## Hit chance

The middle heatmap shows the probability of hitting a ship on that tile. For reasons that I get into on my website, peba1207.github.io, It may not necessary be the best move.

## Information Gain

The heatmap on the right tells you the expected information gain from guessing a given tile. Guessing high information gain tiles allows the next turns to have more high probability tiles. 