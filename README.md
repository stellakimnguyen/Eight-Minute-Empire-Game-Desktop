# COMP 345: Eight-Minute Empire Game
## Assignment 1
### Team members:
  - Maryam Benadada (40053165)
  - Stella Nguyen (40065803)

### Compilation and Usage

As there is only one main driver for all files, we have a created a driver test class for each component, either the maps (map and map loader), the players, cards and bidding facility. The driver test classes are then called into the main driver, either EightMinuteEmpire.cpp to be tested. In order to review one component in question at a time, functions belonging to the test drivers from the other components must be commented.
The test will then be run on the console, prompting actions from the user.

### How it works
##### Gameplay
- The driver asks for the number of players
- The Player objects are then initialized with the number obtained
- The 42 cards are initialized
- 6 cards are drawn from the deck and displayed
- The bidding facility asks for their bids
- It compares the bids and determines the starting player
 
##### Maps
- Maps implement a connected graph with subgraphs for continents, the latter is also connected
- Adjacent regions are created to allow continents and lands to travel