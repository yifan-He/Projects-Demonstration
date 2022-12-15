Source code: A3_Team24 folder

This is a imitation of the card game: Eight-Emperor card game.

<h3> Project discription</h3>
The projects can be mainly devide to 5 parts.<br/>
1.Map (we have L Shape map, Rectangular map shap, and Invalid Map)<br/>
2.Map Loader(Loading maps)<br/>
3.Card deck(There are more then 56 cards in this game)<br/>
4.Player(the Status of Players)<br/>
5.Bidding and counting(Bidding happens at the starting phase of the game, players bidding for high scores go first. Counting will count the points after one of the end conditions has been met. The player with higher scores win.)<br/><br/>

The eight-minute empire: Legends game consists of a connected graph map representing a world’s continent with one or more countries/regions connected by land and water, where each node is a country/region and each edge represents adjacency between regions. <br/>Two or more players start with some coins, and armies on the board on two separate regions, and bid to select the starting player. <br/>Each turn, the player buys a card from the 6-card display. Each card gives a good and an action. The player takes the action immediately. <br/><br/>

<h3>How to win</h3>
Actions allow players to build their empires and take control of the board.The game ends when each player owns a certain number of cards depending on the number of players.<br/>Players count up victory points and the player who has the most victory points from regions, continents, and cards’ abilities has the most powerful empire and is the winner! <br/>If players are tied,the player with the most coins wins. If still tied, the player with the most armies on the board wins.If still tied, the player with the most controlled regions wins.

<h3>My role in this project</h3>
I was responsible for implementing the bidding mechanism between players, using the observer design pattern to show each phase after a player's action, and using the strategy design pattern to control the actions of the computer player if the user chooses to play against the computer or watch the computer play against themselves.
I have also finished the integration of these five sections above.

<h3>The process of the game play</h3>

Phase 1: <br/>
1.We need to choose our map for the game. <br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/part1.png"/><br/><br/>

2.The Map Loader will Load the shape that chosen by players and display it.
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/part2.png"/><br/>

3.choose the mode: human vs human, human vs computer, computer vs computer
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/part3.png"/><br/>

4.Enter the name, starting region, coins for bidding and the colour you would like your country to be. If user choose to vs computer player, it also need to choose what kinds of computer player you want to against(each computer player will have different strategy which was controled by the strategy pattern).<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/part4.png"/><br/>

Phase 2: <br/>
1.After shuffle the card deck, draw 6 cards from the deck and display the function of each card. Ask player to choose one of these 6 cards and performs the effects of the card.<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/Phase2_1.png"/><br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/phase2_2.png"/><br/>

2.Demonstrate the player and map status by using the Observer design pattern<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/phase2_3.png"/><br/>

3.repeat the Phase 2 until the end of the game.<br/>

Phase 3:<br/>
1.Count the score and show the winner.<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%201/img/phase3.png"/><br/>
