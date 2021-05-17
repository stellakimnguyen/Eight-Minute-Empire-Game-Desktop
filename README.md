# Eight-Minute Empire Game

### Compilation and Usage

- A render of the Eight-Minute Empire boardgame on desktop, via the console.
- Experiments with several [design patterns](#design-patterns)
- Familiarize wtih C++

## How it works
### Gameplay
- The driver asks for the number of players
- The Player objects are then initialized with the number obtained
- The 42 cards are initialized
- 6 cards are drawn from the deck and displayed
- The bidding facility asks for their bids
- It compares the bids and determines the starting player
- It substracts the card's chosen price from the first player's coin supply
- The game starts with the players deciding where they want to place the supplementary armies
- It continues with the players playing the default actions Move (Army), Add (Army), Build (City), Destroy (City), Ship (Armies oversea)
- The game loops through a definite amount of turns determined by the number of players
- The game ends by computing the players' score and determines the winner

#### Design Patterns
###### Player Strategy Pattern
- Determines the player's strategy within 3 types (interactive, greedy and moderate)
- Takes the currently available cards from the general hand
- Returns the one it will keep according to the strategy chosen
###### Phase Observer Pattern
- Has a view and an observer
- Observer notifies the view at every change
- Updates the view
###### Statistics Observer
- Has a view and an observer
- Observer notifies the view at every change
- Returns statistics
###### Singleton
- Allows only one instance of a map
- Responsible for keeping track of its sole instance

### Files
##### Maps
- Maps implement a connected graph with subgraphs for continents, the latter is also connected
- Adjacent regions are created to allow continents and lands to travel

#### MapLoader
- Loads the map

#### Player
- Calls the different actions according to the card it owns
- Computes its score at the end

#### BiddingFacility
- Takes players' bids to determine the first player

#### Cards
- Initializes the deck
- Allows exchanges to happen


#### Game
- Loops the game in order to have multiples rounds
- Compares players' scores and determines the winner

##### Example UML for Strategy Pattern
![](https://i.ibb.co/RT4fRYj/Untitled-Diagram.png)
