/*---------------------------------------------- H FILE
			
				"TAKE MORE"
			AUTHOR - Raviv Rachmiel && Roei Rosezwieg
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

//The CPP - implementation
#include "TakeMore.h"

int getUniqueId() {
    static int id=0;
    return id++;
}


//Card:
Card::Card() { 
    card = (rand()%(MAX_CARD_VALUE-MIN_CARD_VALUE) + MIN_CARD_VALUE);
    
} 		

//always returns int, maybe does something too like scrumble all cards, also if we want double so we will have funciton overloading for double getCar
int Card::getCard() { 
    return card;
}

//gets what to print whule the GET gets what to sum
int Card::toPrint() { 
    return card;
    
} 
//Player:
Player::Player(string name,const Game& currGame) : name(name), currGame(currGame), sumNow(0) {
    id = getUniqueId(); 
}

void Player::printStats() const {
	cout << "player" << getName() << "(id " << getId() <<"), sum: " << getSum() << endl;
}

string Player::getName() const {
    return name;
}

int Player::getId() const {
    return id;
}

int Player::getSum() const {
    return sumNow;
}

const Game& Player::getCurrGame() {
	return currGame;
}

void Player::setSum(int sum) {
    sumNow = sum;
}

//Manual Player:
int ManualPlayer::getMove() {
    int num;
    while((num = getTypeOfTurnFromUser()) && (num < 1 || num > 2));
    return num;
}

//=========================================
//=========================================
//=========================================
//BOTS - dont forget to change in h and case too

//Bot1
int Bot1::getMove() {
    return rand() % 2 + 1;
}

//Bot2
int global_for_bot_2_only=0;
int Bot2::getMove() {
	if(global_for_bot_2_only==0) {
		 rand() % 2;
	}
	global_for_bot_2_only++;
    return (global_for_bot_2_only)%2+1;
}

//BotOPT
/*
This will be the best bot and it will be programmed by Dynamic programming
*/

int max4(int a,int b,int c,int d) {
	int max = a;
	if(max < b) {
		max = b;
	}
	if(max < c) {
		max = c;
	}
	if(max < d) {
		max = d;
	}
	return max;
}

int recCheck(vector<Card> cards,int cardNow,int size,int numPlayers) {
	if(size-cardNow==1) {
		return cards[cardNow].getCard();
	}
	if(size-cardNow==0) {
		return 0;
	}
	if(numPlayers==1) {
		int a = cards[cardNow].getCard() + cards[cardNow+1].getCard() - recCheck(cards,cardNow+2,size,numPlayers);
    	int b = cards[cardNow].getCard()-recCheck(cards,cardNow+1,size,numPlayers);
    	return a>b? a : b;
	}
	//else, we want to check for all of the touples of 1*x and 2*x where x is <=(numPlayers-1)
	int a2 = cards[cardNow].getCard() + cards[cardNow+1].getCard() - recCheck(cards,cardNow+2,size,numPlayers);
    int b2 = cards[cardNow].getCard()-recCheck(cards,cardNow+1,size,numPlayers);
    int c2 = cards[cardNow].getCard() + cards[cardNow+1].getCard() - recCheck(cards,cardNow+2,size,numPlayers-1);
    int e2 = cards[cardNow].getCard()-recCheck(cards,cardNow+1,size,numPlayers-1);
    return max4(a2,b2,c2,e2);
}

int BotOPT::getMove() {
	/*Player* p = (this);
	Game g = std::remove_reference(p->getCurrGame())::value;
    vector<Card> cards = g.getCards();
    int cardNow = g.getCardNow();
    int np = g.getNumPlayers(); 
    int size = cards.size();
    int a = cards[cardNow].getCard() + cards[cardNow+1].getCard() - recCheck(cards,cardNow+2,size,np-1);
    int b = cards[cardNow].getCard()+recCheck(cards,cardNow+1,size,np-1);
*/
    int a =1;
    int b =2;
    return a>b? 2 : 1;
}


//=========================================
//=========================================
//=========================================

//Game
//inits array of n --Cards-- to random,onNow to 0, Array to Players, players now to 0
Game::Game(int numPlayers,int numCards) : numPlayers(numPlayers) , numOfCards(numCards), cardNow(0), playerNow(0),
    cards(numCards), players(){
} 
//Getters and Setters
vector<Player*> Game::getPlayers() {
    return players;
}
vector<Card> Game::getCards() {
    return cards;
}
Player& Game::getPlayerNow() {
	return *players[playerNow];
}
int Game::getCardNow() {
	return cardNow;
}
int Game::getNumOfCards() {
	return numOfCards;
}
int Game::getNumPlayers() {
	return numPlayers;
}

//==================================
//==================================
//TO CHANGE THE CASE FOR BOTS
//==================================
//==================================

//gets the id and name and adds  
void Game::addPlayer(string name,int level) {
    Player * p = NULL;
	switch(level) { //Every time we add a bot level, we need to add a case for it ---------in the addPlayer
		case 0:
			p = new ManualPlayer(name,*this);
			break;
		case 1:
			p = new Bot1(name,*this);
			break;
		case 2:
			p = new Bot2(name,*this);
			break;
		case 3:
			p = new BotOPT(name,*this);
			break;
	}
	players.push_back(p);
}  
void Game::changeTurn() {
    playerNow = (playerNow+1) % numPlayers;
}
void Game::updateMove(int move) {
    for( ; cardNow < cards.size() && move-- ; cardNow++) {
        Player& p =getPlayerNow();
        p.setSum(p.getSum() + cards[cardNow].getCard());
    }
    if(cardNow == cards.size()) doWin();
}
void Game::printStats() {
    cout << "Current cards: ";
    for (int i=cardNow;i<numOfCards;i++) {
    	Card v=cards[i];
        cout << v.toPrint() << " ";
    }
    cout << endl;
    cout << "\tName\t\tScore" << endl;
    for (auto v : players) {
        
        if(v->getId() == getPlayerNow().getId()) {
            cout << ">";
        } else {
            cout << " ";
        }
        cout << "\t" << v->getName() << "\t\t" << v->getSum() << endl;
    }
    cout << "--------------------------------------------" << endl;
    
}

void Game::doWin() {
	if(numOfCards - cardNow != 0) {
		return;
	}
	//else - we have a winner, now lets find it
	cout << endl;
	printStats();
	cout << endl;
	vector<Player*>::iterator winner = players.begin();
	for(vector<Player*>::iterator it = players.begin();it!=players.end();it++) {
		if((*it)->getSum()>(*winner)->getSum()) {
			winner = it;
		}
	}
	for(vector<Player*>::iterator it = players.begin();it!=players.end();it++) {
		if((*it)->getSum()==(*winner)->getSum()) {
			printWinner((*it)->getId(),(*it)->getName());
		}
	}
	printDoneWinners();
} 


//Init Game:
Game* initGame() {
	srand(time(NULL)); 
	printStartScreen(); 
	int cardsNum = getNumCardsFromUser();
	int playersNum = getNumPlayersFromUser();
	Game* game = new Game(playersNum,cardsNum);
	for(int i=0;i<playersNum;i++) {
		string name = getNameFromUser();
		int level = getLevelPlayersFromUser(name);
		game->addPlayer(name,level);
	}
	return game;
}
 

//Game Loop:
void gameLoop(Game* game) {
	while(game->getNumOfCards() - game->getCardNow() >1) {
		game->printStats();
		int oneOrTwo = game->getPlayerNow().getMove();
		game->updateMove(oneOrTwo);
		game->changeTurn();
	}
	if(game->getNumOfCards() - game->getCardNow() == 1) {
		game->updateMove(1);
	}
	game->doWin();
}





//Other

//Getters from user:
//input name
string getNameFromUser() {
	cout << "Hello Player, Enter Your Name: " << endl; 
	string s;
	cin >> s;
	return s;
}

//TODO: make it nicer, macro for invalid and throw insert

//input num of players
int getNumPlayersFromUser() {
	cout << "Please enter the number of players that want to play: " << endl;
	int num;
	cin >> num;
	if(num>MAX_PLAYERS || num<2) {
		while(num>MAX_PLAYERS || num <2) {
			cout << "invalid number input, please try again";
			cin >> num;
		}
	}
	return num;
}
//input num of cards
int getNumCardsFromUser() {
	cout << "Please enter the number of cards that you want in the game: " << endl;
	int num;
	cin >> num;
/*	if(num>MAX_CARD_VALUE || num<0) {
		while(num>MAX_LEVEL || num <0) {
			cout << "invalid number input, please try again";
			cin >> num;
		}
	}*/
	return num;
}
//which kind of player
int getLevelPlayersFromUser(string name) {
	cout << "Hey " << name << ", please choose the level of computer, 0-" << MAX_LEVEL <<",when 0 is user and "<< MAX_LEVEL << " is the highest:"<< endl;
	int level;
	cin >> level;
	if(level>MAX_LEVEL || level <0) {
		while(level>MAX_LEVEL || level <0) {
			cout << "invalid level input, please try again";
			cin >> level;
		}
	}
	return level;
}
//input type o f turn
int getTypeOfTurnFromUser() {
    int num;
    cout << "Please enter the type of turn (1 | 2) that you wish to play: " << endl;
    do {
        cin >> num;
        if(num <= 2 && num >= 1) break;
        cout << "invalid turn type. Try again" << endl;
    } while(1);
    return num;
}

//Printers:
std::string getFileContents (std::ifstream&); 
 //prints - hello, enter how many players and then all of your names, by playing order
void printStartScreen() {
	std::ifstream Reader("Welcome.txt");             //Open file

    std::string Art = getFileContents(Reader);       //Get file
    
    std::cout << Art << std::endl;               //Print it to the screen

    Reader.close ();                           //Close file
    cout << endl;
    //end of title of ascii art from google
}
//GoodBye, hope you had fun
void printExitMess() {
	cout << endl;
	cout << endl;
	std::ifstream Reader("Bye.txt");             //Open file

    std::string Art = getFileContents(Reader);       //Get file
    
    std::cout << Art << std::endl;               //Print it to the screen

    Reader.close ();                           //Close file
    cout << endl;
    //end of title of ascii art from google
}
void printAnotherGameMess() {
	cout << endl;
	cout << endl;
	cout << "New Game Starting" << endl;
	cout << endl;
}
//void PrintNextTurnMess() {}
void printWinner(int id,string name) {
	cout << "Winner is player " << id+1 << " - " << name << endl;
}

void printDoneWinners() {
	cout << "And all the rest are just plain losers" << endl;
}
//No more printers




std::string getFileContents (std::ifstream& File)
{
    std::string Lines = "";        //All lines
    
    if (File)                      //Check if everything is good
    {
	while (File.good ())
	{
	    std::string TempLine;                  //Temp line
	    std::getline (File , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline chara cter
	    
	    Lines += TempLine;                     //Add newline
	}
	return Lines;
    }
    else                           //Return error
    {
	return "ERROR File does not exist.";
    }
    } 
