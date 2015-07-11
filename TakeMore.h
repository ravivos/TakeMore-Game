/*---------------------------------------------- H FILE
			
				"TAKE MORE"
			AUTHOR - Raviv Rachmiel && Roei 
	Is a game where two players take a card or two from the list
	That is made randomally with rnd.
	The goal is to get the biggest sum of numbers at the end of the game
	---1 player---
	chooses to start or be second, each turn gets the list of all cards and chooses if to take one or two
	--2 players---
	chooses which one starts, one or two, checks to start

	ends when there are no more cards

-----------------------------------------------*/

//TODO:
/*
class player - has a name, sum in hand (int), id
class game - has the players (array), size of cards, vector of cards, player now
MAX_PLAYERS - const (10)
1)InitGame() {
	gets how many players, their names - first one written starts
	inits the Random array of numbers
	returns Game
}
2)PrintCards(Game);
3)GetMove(Game) - prints the player now name with sumNow and total sum left asks for 1 or 2, gets the move - 1 or 2
4)printStatus of players now; - PrintStats(Game);
5) void Game - inits game(), while game->numLeft>1:
					PrintStatus (set,playerNow stats,otherplayer stats, sum left)
					GetMove()
					UpdateMove(Game) - removes from list, change players turn
	after while:
		left o or 1, if o, check the player with highest sum (getWinner()) and returns it as winner
		PrintWinner(player);
		else (1) - adds the remaining to playerNow and returns getWinner()
		if(AnotherGame()) {
			freeGame()
		}
		else() {
			DestroyGame
		}
6) DestroyGame - frees the game and the players
7) FreeGame - frees the game  
*/

//Includes:
#include <vector>
//#include <list>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <type_traits>

//Using
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

//DEFINES:
#define MAX_PLAYERS 10
#define MAX_CARD_VALUE 100
#define MIN_CARD_VALUE 0
#define MAX_LEVEL 2

//class Card, now will hold int but can be inherited to special cards
//this is a regular card, of int
class Card {
int card;
public:
	Card();
	virtual int getCard();//always returns int, maybe does something too like scrumble all cards, also if we want double so we will have funciton overloading for double getCar
	virtual int toPrint();//gets what to print whule the GET gets what to sum
};	

//class player - has a name, sum in ;hand (int), id
//has a virtual function, getMove which gets the move
class Game;

class Player {
    string name;
    int sumNow;
    int id;
    const Game& currGame;
public:
    Player(string name, const Game& game); //updates id to ++, inits sunNow to zero
	virtual int getMove() = 0; //returns one or two
	void printStats() const; // name, sum in hand
	int getSum() const;
	int getId() const;
	string getName() const;
	const Game& getCurrGame();
	void setSum(int sum);
	//default ocnstructor is fine for now
};

class ManualPlayer : public Player {
public:
	ManualPlayer(string name, const Game& game) : Player(name, game) {}
    int getMove();
};


//=======================================================
//=======================================================
//=======================================================

//Bots - dont forget to implement in cpp and case

class Bot1 : public Player {
public:
	Bot1(string name, const Game& game) : Player(name, game) {}
    int getMove();
};

class Bot2 : public Player {
public:
	Bot2(string name, const Game& game) : Player(name, game) {}
    int getMove();
};

class BotOPT : public Player {
public:
	BotOPT(string name, const Game& game) : Player(name, game) {}
    int getMove();
};


//=======================================================
//=======================================================
//=======================================================

//class game - has the players (vector), size of cards, array of cards, playerNow, iterator-onNow,numPlayers, int cardNow
//has functions - PrintCards, PrintStatus, constructos, distruc**tor
class Game {
vector<Player*> players;
vector<Card> cards;
int numOfCards;
int numPlayers;
int playerNow;
int cardNow;
public:
	Game(int numPlayers,int numCards); //inits array of n --Cards-- to random,onNow to 0, Array to Players, players now to 0
	~Game();
	//Getters and Setters
	vector<Player*> getPlayers();
	vector<Card> getCards();
	Player& getPlayerNow();
	int getCardNow();
	int getNumOfCards();
	int getNumPlayers();
	//TOOD: add more when needed
	//Others:
	void addPlayer(string name,int level); //gets the id and name and adds 
	void changeTurn(); //onNow= (onNow + 1) % numPlayers
	void updateMove(int move); //one or Two or Zero, if zero than doWin
	//void PrintCards();
	void printStats(); //whos turn, others, list, sum of list
	void doWin(); 
	
};	


//Get Messages from user with input functions:
//input name
string getNameFromUser(); 
//input num of players
int getNumPlayersFromUser();
//input num of cards
int getNumCardsFromUser();
//which kind of player
int getLevelPlayersFromUser(string name);
//input type of turn
int getTypeOfTurnFromUser();

//More Printers:
//TODO: add more when needed
 //prints - hello, enter how many players and then all of your names, by playing order
void printStartScreen();
//GoodBye, hope you had fun
void printExitMess();
void printAnotherGameMess();
void printNextTurnMess();
void printWinner(int id,string name);
void printDoneWinners();
//No more printers


/*
prints hello screen
gets how many players, their names - first one written starts, gets form the Gets
inits the game with it ands add players in a for(n) loop
returns Game
*/
Game* initGame();




/*
void Game - inits game(), while game->numLeft>1:
					PrintStatus (set,playerNow stats,otherplayer stats, sum left)
					GetMove()
					UpdateMove(Game) - removes from list, change players turn
	after while:
		left o or 1, if o, check the player with highest sum (getWinner()) and returns it as winner
		PrintWinner(player);
		else (1) - adds the remaining to playerNow and returns getWinner()
		if(AnotherGame()) {
			freeGame()
		}
		else() {
			DestroyGame
		}
*/
void gameLoop(Game* game);

//frees the game and the players, with the goodBye Letter
void destroyGame();	

//frees the game itself only and starts another Game
void freeGame(Game);
 