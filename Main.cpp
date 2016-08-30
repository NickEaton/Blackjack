/*Blackjack Simulator
Author ~ Nick
Date ~ 8/27/16
Description ~ A program to simulate a virtual game of blackjack.
The user can choose to either play the game themselves, or to
spectate 2 AI's playing each other
*/

//SFML for all visual aspects
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//Vector for storage
#include <vector>
//Includes the Card, Deck and Hand classes
#include "Card.h"
//Includes the AI and Player classes
#include "AI.h"
//Log info to the console through cout
#include <iostream>
//std::string
#include <string>
//sleep
#include <conio.h>
//milliseconds for sleep functions
#include <chrono>
//accesses thread sleep functions
#include <thread>

using namespace std;

//one method to rule them all
int main() {

	//Home goto identifier
	HOME:

	//AI declarations
	Player player;
	AI nick;
	AI salem;
	AI noah;

	//Score declarations
	int playerScore = 0;
	int noahScore = 0;
	int salemScore = 0;

	//Title window, choose play or spectate
	sf::RenderWindow title(sf::VideoMode(200, 100), "Blackjack");

	//Main title loop
	while (title.isOpen()) {

		//Title box rectange
		sf::RectangleShape titleCard(sf::Vector2f(190, 40));
		titleCard.setPosition(5, 5);
		titleCard.setFillColor(sf::Color::Color(224, 224, 224));
		titleCard.setOutlineColor(sf::Color::Black);
		titleCard.setOutlineThickness(1);

		//Yes button
		sf::RectangleShape yesButton(sf::Vector2f(90, 40));
		yesButton.setPosition(5, 55);
		yesButton.setFillColor(sf::Color::Color(224, 224, 224));
		yesButton.setOutlineColor(sf::Color::Black);
		yesButton.setOutlineThickness(1);

		//No button
		sf::RectangleShape noButton(sf::Vector2f(90, 40));
		noButton.setPosition(105, 55);
		noButton.setFillColor(sf::Color::Color(224, 224, 224));
		noButton.setOutlineColor(sf::Color::Black);
		noButton.setOutlineThickness(1);

		//Loading font from local file
		sf::Font font;
		font.loadFromFile("arial.ttf");
		
		//Title text
		sf::Text card;
		card.setFont(font);
		card.setString("Will You Play or Spectate?");
		card.setCharacterSize(15);
		card.setFillColor(sf::Color::Black);
		card.setPosition(10, 15);

		//Play button text
		sf::Text play;
		play.setFont(font);
		play.setString("Play");
		play.setCharacterSize(15);
		play.setFillColor(sf::Color::Black);
		play.setPosition(33, 65);

		//Spectate button text
		sf::Text spectate;
		spectate.setFont(font);
		spectate.setString("Spectate");
		spectate.setCharacterSize(15);
		spectate.setFillColor(sf::Color::Black);
		spectate.setPosition(118, 65);

		//Clear the gui and draw the objects to the window
		title.clear(sf::Color::Color(192, 192, 192));
		title.draw(titleCard);
		title.draw(yesButton);
		title.draw(noButton);
		title.draw(card);
		title.draw(play);
		title.draw(spectate);
		title.display();

		//Event list
		sf::Event event;
		
		//Event manager
		while (title.pollEvent(event)) {

			//Window closed
			if (event.type == sf::Event::Closed)
				return 0;

			//Play button clicked
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && ((event.mouseButton.x >= 5 && event.mouseButton.x <= 95) && (event.mouseButton.y >= 55 && event.mouseButton.y <= 95))) {
				cout << "[INFO]User is playing" << endl;
				title.close();
				goto PLAY;
			}

			//Spectate button clicked
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && ((event.mouseButton.x >= 105 && event.mouseButton.x <= 195) && (event.mouseButton.y >= 55 && event.mouseButton.y <= 95))) {
				cout << "[INFO]User is spectating" << endl;
				title.close();
				goto SPECTATE;
			}
		}
	}
	
	//Play Loop

	PLAY:

	while (true) {

		//Generate the window
		sf::RenderWindow window(sf::VideoMode(770, 400), "Blackjack");

	//Main play loop goto identifier
	LOOP:

		//Local win tracker vars
		bool playWin = false;
		bool noahWin = false;
		bool salemWin = false;
		bool houseWin = false;

		//The card deck
		Deck deck = Deck();

		//Initialization of the AI and player
		player = Player(deck.draw(), deck.draw());
		noah = AI(deck.draw(), deck.draw());
		salem = AI(deck.draw(), deck.draw());

		//Load the background
		sf::Texture bg;
		bg.loadFromFile("Background.jpg");
		sf::Sprite background;
		background.setTexture(bg);
		background.setPosition(sf::Vector2f(0, 0));

		//Load the player's 1st card file as a sprite
		sf::Texture c1;
		c1.loadFromFile(player.h.hand[0].getFileName());
		sf::Sprite card1;
		card1.setTexture(c1);
		card1.setPosition(sf::Vector2f(15, 50));
		card1.scale(.275, .275);

		//Load the player's 2nd card file as a sprite
		sf::Texture c2;
		c2.loadFromFile(player.h.hand[1].getFileName());
		sf::Sprite card2;
		card2.setTexture(c2);
		card2.setPosition(sf::Vector2f(165, 50));
		card2.scale(.275, .275);

		//Hit button
		sf::RectangleShape hitButton(sf::Vector2f(135, 50));
		hitButton.setFillColor(sf::Color::Color(255, 51, 51));
		hitButton.setOutlineThickness(1);
		hitButton.setOutlineColor(sf::Color::Black);
		hitButton.setPosition(sf::Vector2f(15, 265));

		//Load font
		sf::Font font;
		font.loadFromFile("AdobeGothicStd-Bold.otf");
		
		//Hit text 
		sf::Text hit;
		hit.setFont(font);
		hit.setString("Hit");
		hit.setCharacterSize(24);
		hit.setFillColor(sf::Color::Black);
		hit.setPosition(sf::Vector2f(62, 275));

		//Stay text
		sf::Text stay;
		stay.setFont(font);
		stay.setString("Stay");
		stay.setCharacterSize(24);
		stay.setFillColor(sf::Color::Black);
		stay.setPosition(sf::Vector2f(55, 335));

		//Player win message
		sf::Text plWin;
		plWin.setFont(font);
		plWin.setString("Player wins, new game...");
		plWin.setCharacterSize(18);
		plWin.setFillColor(sf::Color::Black);
		plWin.setPosition(sf::Vector2f(500, 310));

		//Noah win message
		sf::Text nwWin;
		nwWin.setFont(font);
		nwWin.setString("Noah wins, new game...");
		nwWin.setCharacterSize(18);
		nwWin.setFillColor(sf::Color::Black);
		nwWin.setPosition(sf::Vector2f(500, 310));

		//Salem win message
		sf::Text svWin;
		svWin.setFont(font);
		svWin.setString("Salem wins, new game...");
		svWin.setCharacterSize(18);
		svWin.setFillColor(sf::Color::Black);
		svWin.setPosition(sf::Vector2f(500, 310));

		//House win message (on a tie between 2 players)
		sf::Text hsWin;
		hsWin.setFont(font);
		hsWin.setString("House wins, new game...");
		hsWin.setCharacterSize(18);
		hsWin.setFillColor(sf::Color::Black);
		hsWin.setPosition(sf::Vector2f(500, 310));

		//Load a new font for displaying text directly to the background
		font.loadFromFile("impact.ttf");

		//Player's score string, updates on game wins
		std::string plString{ "Player's Score: " };
		plString.append(std::to_string(playerScore));
		sf::Text plScore;
		plScore.setFont(font);
		plScore.setCharacterSize(18);
		plScore.setString(plString);
		plScore.setFillColor(sf::Color::Color(128, 128, 128));
		plScore.setPosition(sf::Vector2f(15, 15));

		//Noah's score string, updates on game wins
		std::string nwString{ "Noah's Score: " };
		nwString.append(std::to_string(noahScore));
		sf::Text nwScore;
		nwScore.setFont(font);
		nwScore.setCharacterSize(18);
		nwScore.setString(nwString);
		nwScore.setFillColor(sf::Color::Color(128, 128, 128));
		nwScore.setPosition(sf::Vector2f(165, 15));

		//Salem's score string, updates on game wins
		std::string svString{ "Salem's Score: " };
		svString.append(std::to_string(salemScore));
		sf::Text svScore;
		svScore.setFont(font);
		svScore.setCharacterSize(18);
		svScore.setString(svString);
		svScore.setFillColor(sf::Color::Color(128, 128, 128));
		svScore.setPosition(sf::Vector2f(315, 15));

		//Home button
		sf::RectangleShape homeButton(sf::Vector2f(135, 30));
		homeButton.setFillColor(sf::Color::Color(255, 51, 51));
		homeButton.setOutlineColor(sf::Color::Black);
		homeButton.setOutlineThickness(1);
		homeButton.setPosition(sf::Vector2f(615, 15));

		//Set font back to the original
		font.loadFromFile("AdobeGothicStd-Bold.otf");

		//Home button text
		sf::Text home;
		home.setFont(font);
		home.setFillColor(sf::Color::Black);
		home.setString("Home");
		home.setCharacterSize(16);
		home.setPosition(sf::Vector2f(657, 20));

		//Stay Button
		sf::RectangleShape stayButton(sf::Vector2f(135, 50));
		stayButton.setFillColor(sf::Color::Color(51, 51, 255));
		stayButton.setOutlineThickness(1);
		stayButton.setOutlineColor(sf::Color::Black);
		stayButton.setPosition(sf::Vector2f(15, 325));

		//Redacted
		/* sf::RectangleShape ca3(sf::Vector2f(135, 200));
		ca3.setFillColor(sf::Color::Transparent);
		ca3.setOutlineColor(sf::Color::Black);
		ca3.setOutlineThickness(1);
		ca3.setPosition(sf::Vector2f(315, 50)); 

		sf::RectangleShape ca4(sf::Vector2f(135, 200));
		ca4.setFillColor(sf::Color::Transparent);
		ca4.setOutlineColor(sf::Color::Black);
		ca4.setOutlineThickness(1);
		ca4.setPosition(sf::Vector2f(465, 50));

		sf::RectangleShape ca5(sf::Vector2f(135, 200));
		ca5.setFillColor(sf::Color::Transparent);
		ca5.setOutlineColor(sf::Color::Black);
		ca5.setOutlineThickness(1);
		ca5.setPosition(sf::Vector2f(615, 50)); */

		//Special box to announce a bust or blackjack by the player
		sf::RectangleShape specBox(sf::Vector2f(280, 110));
		specBox.setFillColor(sf::Color::Color(51, 255, 51));
		specBox.setOutlineColor(sf::Color::Black);
		specBox.setOutlineThickness(1);
		specBox.setPosition(sf::Vector2f(165, 265));

		//game end var
		bool gameEnd = false;

		//Special box to announce the game winner & reset
		sf::RectangleShape specBox2(sf::Vector2f(280, 110));
		specBox2.setFillColor(sf::Color::Color(255, 128, 0));
		specBox2.setOutlineColor(sf::Color::Black);
		specBox2.setOutlineThickness(1);
		specBox2.setPosition(sf::Vector2f(465, 265));

		//player blackjack boolean
		bool blj = false;

		//Blackjack text
		sf::Text blackjack;
		blackjack.setFont(font);
		blackjack.setString("Blackjack");
		blackjack.setFillColor(sf::Color::Black);
		blackjack.setCharacterSize(24);
		blackjack.setPosition(sf::Vector2f(250, 310));

		//player bust bool
		bool bst = false;

		//Bust text
		sf::Text bust;
		bust.setFont(font);
		bust.setString("Bust");
		bust.setFillColor(sf::Color::Black);
		bust.setCharacterSize(24);
		bust.setPosition(sf::Vector2f(275, 310));

		//Sprites for potential cards in the player hand
		sf::Sprite card3;
		sf::Sprite card4;
		sf::Sprite card5;

		//Init textures for the cards and set location
		sf::Texture car3;
		card3.setPosition(sf::Vector2f(315, 50));
		card3.scale(.275, .275);

		sf::Texture car4;
		card4.setPosition(sf::Vector2f(465, 50));
		card4.scale(.275, .275);

		sf::Texture car5;
		card5.setPosition(615, 50);
		card5.scale(.275, .275);

		//counter vars
		int plindex = 1;
		int blackj = 0;

		while (window.isOpen()) {

			//Local event list
			sf::Event event;

			//Exit if the player gets a natural blackjack
			if (player.h.getValue() == 21 && blackj == 0) {
				cout << "[INFO]Player Blackjacked" << endl;
				blj = true;
				blackj++;
			}

			//Event handler
			while (window.pollEvent(event)) {

				//Window closed
				if (event.type == sf::Event::Closed)
					return 0;

				//Home button clicked, return to Title window
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 615 && event.mouseButton.x <= 750 && event.mouseButton.y >= 15 && event.mouseButton.y <= 45) {
					cout << "[INFO]Home Button Clicked";
					goto HOME;
				}

				//Hit button clicked, add a card to the player and check if bust or blackjack
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 15 && event.mouseButton.x <= 150 && event.mouseButton.y >= 265 && event.mouseButton.y <= 315) {
					cout << "[INFO]Hit Button Clicked" << endl;
					player.hit(deck.draw());

					//Load player card 3
					if (plindex == 1) {
						cout << "[INFO]Loaded Card 3" << endl;
						car3.loadFromFile(player.h.hand[2].getFileName());
						card3.setTexture(car3);
					}

					//Load player card 4
					else if (plindex == 2) {
						cout << "[INFO]Loaded Card 4" << endl;
						car4.loadFromFile(player.h.hand[3].getFileName());
						card4.setTexture(car4);
					}

					//Load player card 5
					else if (plindex == 3) {
						cout << "[INFO]Loaded Card 5" << endl;
						car5.loadFromFile(player.h.hand[4].getFileName());
						card5.setTexture(car5);
					}

					//Check for a blackjack
					if (player.h.getValue() == 21) {
						cout << "[INFO]Player Blackjacked" << endl;
						blj = true;
					}

					//Check for a bust
					if (player.h.getValue() > 21) {
						cout << "[INFO]Player Busted" << endl;
						bst = true;
					}

					//Incr. player counter
					++plindex;
				}

				//Stay button event, end the game and calculate the winner
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 15 && event.mouseButton.x <= 150 && event.mouseButton.y >= 325 && event.mouseButton.y <= 375) {
					cout << "[INFO]Stay Button Clicked" << endl;

					//Game ended goto identifier
					GAME_END:

					gameEnd = true;

					//Calculate noah's moves
					while (noah.hit() && !noah.bust()) {
						noah.addCard(deck.draw());
					}

					//Calculate salem's moves
					while (salem.hit() && !salem.bust()) {
						salem.addCard(deck.draw());
					}

					//Local final values to compare
					int pv = player.h.getValue();
					int nv = noah.h.getValue();
					int sv = salem.h.getValue();

					//Player busted, value gets thrown out
					if (pv > 21)
						pv = 0;

					//Noah busted, value gets thrown out
					if (nv > 21)
						nv = 0;

					//Salem busted, value gets thrown out
					if (sv > 21)
						sv = 0;
					cout << "[INFO]PV=" << pv << " NV=" << nv << " SV=" << sv << endl;
					if (pv > nv && pv > sv && player.h.getValue() <= 21) {
						cout << "[INFO]Player wins" << endl;
						playWin = true;
						playerScore++;
						goto LN;
					}
					if (nv > pv && nv > sv && noah.h.getValue() <= 21) {
						cout << "[INFO]Noah wins" << endl;
						noahWin = true;
						noahScore++;
						goto LN;
					}
					if (sv > pv && sv > nv && salem.h.getValue() <= 21) {
						cout << "[INFO]Salem wins" << endl;
						salemWin = true;
						salemScore++;
						goto LN;
					}
					cout << "[INFO]House wins" << endl;
					houseWin = true;
				}
			}

			//Redraw identifier
			LN:

			//Clear the window and draw all the elements
			window.clear(sf::Color::Color(192, 192, 192));
			window.draw(background);
			window.draw(card1);
			window.draw(card2);
			//if (plindex > 1)
				window.draw(card3);
			//if (plindex > 2)
				window.draw(card4);
			//if (plindex > 3)
				window.draw(card5); 
			window.draw(hitButton);
			window.draw(stayButton);
			window.draw(hit);
			window.draw(stay);
			window.draw(plScore);
			window.draw(nwScore);
			window.draw(svScore);
			window.draw(homeButton);
			window.draw(home);

			//If blackjack or bust, drawthe spec box
			if (blj || bst) 
				window.draw(specBox);

			//Draw the blackjack text if blj
			if (blj) {
				window.draw(blackjack);
			}

			//Draw the bust text if bst
			if (bst) {
				window.draw(bust);
			}

			//If the game is over, draw the winner box
			if (gameEnd) {
				window.draw(specBox2);
			}

			//Draw the winner's text
			if (playWin)
				window.draw(plWin);
			if (noahWin)
				window.draw(nwWin);
			if (salemWin)
				window.draw(svWin);
			if (houseWin)
				window.draw(hsWin);
			
			/* if (plindex <= 1)
				window.draw(ca3);
			if (plindex <= 2)
				window.draw(ca4);
			if (plindex <= 3)
				window.draw(ca5); */
			window.display();

			//Go to the main loop if the current game is over
			if (gameEnd) {
				std::this_thread::sleep_for(std::chrono::milliseconds(2500));
				goto LOOP;
			}

			//Go to the GAME_END identifier if the player has busted or blackjacked
			if (bst || blj) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				goto GAME_END;
			}
		}
	}

	//Spectate Loop

	SPECTATE:

	while (true) {

		//Drawing window
		sf::RenderWindow window(sf::VideoMode(770, 400), "Blackjack");

	//Spectate loop goto var
	SLOOP:

		//Log info
		cout << "[INFO]Entering Spectate Loop" << endl;

		//Card counters
		int scounter = 3; 
		int ncounter = 3;

		//Game status
		bool gameEnd = false;

		//Local deck
		Deck deck = Deck();

		//Constructing the AI objects
		noah = AI(deck.draw(), deck.draw());
		salem = AI(deck.draw(), deck.draw());

		//Noah's 1st card (preloaded)
		sf::Texture nc1;
		nc1.loadFromFile(noah.h.hand[0].getFileName());
		sf::Sprite noahCard1;
		noahCard1.setTexture(nc1);
		noahCard1.scale(.2, .2);
		noahCard1.setPosition(sf::Vector2f(15, 35));

		//Noah's 2nd card (preloaded)
		sf::Texture nc2;
		nc2.loadFromFile(noah.h.hand[1].getFileName());
		sf::Sprite noahCard2;
		noahCard2.setTexture(nc2);
		noahCard2.scale(.2, .2);
		noahCard2.setPosition(sf::Vector2f(125, 35));

		//Unloaded sprites
		sf::Sprite noahCard3;
		sf::Sprite noahCard4;
		sf::Sprite noahCard5;


		//Noah's unloaded card sprites & textures
		sf::Texture nc3;
		noahCard3.scale(.2, .2);
		noahCard3.setPosition(sf::Vector2f(235, 35));

		sf::Texture nc4;
		noahCard4.scale(.2, .2);
		noahCard4.setPosition(sf::Vector2f(345, 35));

		sf::Texture nc5;
		noahCard5.scale(.2, .2);
		noahCard5.setPosition(sf::Vector2f(455, 35));

		//Salem's 1st card (preloaded)
		sf::Texture sc1;
		sc1.loadFromFile(salem.h.hand[0].getFileName());
		sf::Sprite salemCard1;
		salemCard1.setTexture(sc1);
		salemCard1.scale(.2, .2);
		salemCard1.setPosition(sf::Vector2f(15, 225));

		//Salem's 2nd card (preloaded)
		sf::Texture sc2;
		sc2.loadFromFile(salem.h.hand[1].getFileName());
		sf::Sprite salemCard2;
		salemCard2.setTexture(sc2);
		salemCard2.scale(.2, .2);
		salemCard2.setPosition(sf::Vector2f(125, 225));


		//Salem's unloaded card sprites
		sf::Sprite salemCard3;
		sf::Sprite salemCard4;
		sf::Sprite salemCard5;

		//Unloaded card textures & sprites
		sf::Texture sc3;
		salemCard3.scale(.2, .2);
		salemCard3.setPosition(sf::Vector2f(235, 225));

		sf::Texture sc4;
		salemCard4.scale(.2, .2);
		salemCard4.setPosition(sf::Vector2f(345, 225));

		sf::Texture sc5;
		salemCard5.scale(.2, .2);
		salemCard5.setPosition(sf::Vector2f(455, 225));


		//Main game loop
		while (window.isOpen()) {

			//Win vars
			bool noahWin = false;
			bool salemWin = false;
			bool houseWin = false;

			//Only let AI hit once per iteration
			bool nhitthisit = false;
			bool shitthisit = false;

			//Font
			sf::Font font;
			font.loadFromFile("AdobeGothicStd-Bold.otf");

			//Home button text
			sf::Text home;
			home.setFont(font);
			home.setString("Home");
			home.setCharacterSize(18);
			home.setFillColor(sf::Color::Black);
			home.setPosition(sf::Vector2f(660, 20));

			//Home box
			sf::RectangleShape homeBox(sf::Vector2f(135, 35));
			homeBox.setFillColor(sf::Color::Color(255, 51, 51));
			homeBox.setOutlineColor(sf::Color::Black);
			homeBox.setOutlineThickness(1);
			homeBox.setPosition(sf::Vector2f(620, 15));

			//Switching font for readability
			font.loadFromFile("impact.ttf");

			//Noah score text
			sf::Text noaht;
			std::string nsc{ "Noah's Score: " };
			nsc.append(std::to_string(noahScore));
			noaht.setFont(font);
			noaht.setFillColor(sf::Color::Color(128, 128, 128));
			noaht.setString(nsc);
			noaht.setCharacterSize(18);
			noaht.setPosition(sf::Vector2f(15, 5));

			//Salem score text
			sf::Text salemt;
			std::string ssc{ "Salem's Score: " };
			ssc.append(std::to_string(salemScore));
			salemt.setFont(font);
			salemt.setFillColor(sf::Color::Color(128, 128, 128));
			salemt.setString(ssc);
			salemt.setCharacterSize(18);
			salemt.setPosition(sf::Vector2f(15, 190));
			
			//Win box
			sf::RectangleShape winBox(sf::Vector2f(175, 135));
			winBox.setFillColor(sf::Color::Color(255, 128, 0));
			winBox.setOutlineColor(sf::Color::Black);
			winBox.setOutlineThickness(1);
			winBox.setPosition(sf::Vector2f(580, 250));

			//Salem win text
			sf::Text sWin;
			sWin.setFont(font);
			sWin.setString("Salem wins...\nNew Game");
			sWin.setFillColor(sf::Color::Black);
			sWin.setCharacterSize(18);
			sWin.setPosition(sf::Vector2f(620, 290));

			//Noah win text
			sf::Text nWin;
			nWin.setFont(font);
			nWin.setString("Noah wins...\nNew Game");
			nWin.setFillColor(sf::Color::Black);
			nWin.setCharacterSize(18);
			nWin.setPosition(sf::Vector2f(620, 290));

			//House win text
			sf::Text hWin;
			hWin.setFont(font);
			hWin.setString("House wins...\nNew Game");
			hWin.setFillColor(sf::Color::Black);
			hWin.setCharacterSize(18);
			hWin.setPosition(sf::Vector2f(620, 290));

			//Background sprite
			sf::Texture bg;
			bg.loadFromFile("Background.jpg");
			sf::Sprite background;
			background.setTexture(bg);

			//Local event list
			sf::Event event;

			//Iterate through and check for events
			while (window.pollEvent(event)) {

				//Window closed event
				if (event.type == sf::Event::Closed)
					return 0;

				//Home button pressed event
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 620 && event.mouseButton.x <= 755 && event.mouseButton.y >= 15 && event.mouseButton.y <= 50) {
					cout << "[INFO]Home button pressed" << endl;
					goto HOME;
				}
			}

		//Goto identifier when the AI hits and sprites need to be re-loaded
		SN:

			//Noah's current hand value text
			sf::Text noahHand;
			std::string nhv{ "Noah's Hand Value: " };
			nhv.append(std::to_string(noah.h.getValue()));
			noahHand.setFont(font);
			noahHand.setFillColor(sf::Color::Color(128, 128, 128));
			noahHand.setString(nhv);
			noahHand.setCharacterSize(18);
			noahHand.setPosition(sf::Vector2f(235, 5));

			//Salem's current hand value text
			sf::Text salemHand;
			std::string shv{ "Salem's Hand Value: " };
			shv.append(std::to_string(salem.h.getValue()));
			salemHand.setFont(font);
			salemHand.setFillColor(sf::Color::Color(128, 128, 128));
			salemHand.setString(shv);
			salemHand.setCharacterSize(18);
			salemHand.setPosition(sf::Vector2f(235, 190));

			//Clear all entities
			window.clear(sf::Color::Color(192, 192, 192));

			//Draw all entities
			window.draw(background);
			window.draw(noahCard1);
			window.draw(noahCard2);
			window.draw(noahCard3);
			window.draw(noahCard4);
			window.draw(noahCard5);
			window.draw(salemCard1);
			window.draw(salemCard2);
			window.draw(salemCard3);
			window.draw(salemCard4);
			window.draw(salemCard5);
			window.draw(homeBox);
			window.draw(home);
			window.draw(noaht);
			window.draw(salemt);
			window.draw(noahHand);
			window.draw(salemHand);
			window.draw(winBox);
			
			//Special win cases
			if (salemWin) {
				salemWin = false;
				window.draw(sWin);
				cout << "[INFO]Salem Wins" << endl;
			}
			if (noahWin) {
				noahWin = false;
				window.draw(nWin);
				cout << "[INFO]Noah Wins" << endl;
			}
			if (houseWin) {
				houseWin = false;
				window.draw(hWin);
				cout << "[INFO]Salem Wins" << endl;
			}

			//Display all to the local window
			window.display();

			//If the game is over, wait 2.5 seconds and return to the top 
			if (gameEnd) {
				std::this_thread::sleep_for(std::chrono::milliseconds(2500));
				goto SLOOP;
			}

			//Noah's AI determination to hit or not
			if (noah.hit() && !noah.bust() && !nhitthisit) {

				//Noah has hit this iteration
				nhitthisit = true;

				cout << "[INFO]Noah hits" << endl;
				cout << "[INFO]Ncounter = " << ncounter << endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(2500));

				noah.addCard(deck.draw());

				//Load noah card 3
				if (ncounter == 3) {
					nc3.loadFromFile(noah.h.hand[2].getFileName());

					//Log noah card 3
					cout << noah.h.hand[2].getFileName() << endl;
					noahCard3.setTexture(nc3);
				}

				//Load noah card 4
				if (ncounter == 4) {
					nc4.loadFromFile(noah.h.hand[3].getFileName());

					//Log noah card 4
					cout << noah.h.hand[3].getFileName() << endl;
					noahCard4.setTexture(nc4);
				}

				//Load noah card 5
				if (ncounter == 5) {
					nc5.loadFromFile(noah.h.hand[4].getFileName());

					//Log noah card 5
					cout << noah.h.hand[4].getFileName() << endl;
					noahCard5.setTexture(nc5);
				}
				
				//Incr. noah counter
				ncounter++;
				goto SN;
			}

			//Salem's AI determination to hit or not
			if (salem.hit() && !salem.bust() && !shitthisit) {

				//Salem has hit this iteration
				shitthisit = true;

				cout << "[INFO]Salem hits" << endl;
				cout << "[INFO]SCounter = " << scounter << endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(2500));

				//Load salem card 3
				salem.addCard(deck.draw());
				if (scounter == 3) {
					sc3.loadFromFile(salem.h.hand[2].getFileName());

					//Log salem card 3
					cout << salem.h.hand[2].getFileName() << endl;
					salemCard3.setTexture(sc3);
				}

				//Load salem card 4
				if (scounter == 4) {
					sc4.loadFromFile(salem.h.hand[3].getFileName());

					//Log salem card 4
					cout << salem.h.hand[3].getFileName() << endl;
					salemCard4.setTexture(sc4);
				}

				//Load salem card 5
				if (scounter == 5) {
					sc5.loadFromFile(salem.h.hand[4].getFileName());

					//Log salem card 5
					cout << salem.h.hand[4].getFileName() << endl;
					salemCard5.setTexture(sc5);
				}

				//Incr. salem counter
				scounter++;
				goto SN;
			}

			//If neither AI wants to hit, enter the game end statements to calc winner
			if (!salem.hit() && !noah.hit()) {
				gameEnd = true;

				//If noah busts and salem does not, salem wins
				if (!salem.bust() && noah.bust()) {
					salemWin = true;
					salemScore++;
					goto SN;
				}

				//If salem busts and noah does not, noah wins
				if (!noah.bust() && salem.bust()) {
					noahWin = true;
					noahScore++;
					goto SN;
				}

				//If both salem and noah bust, calc the higher value
				if (!salem.bust() && !noah.bust()) {

					//salem > noah, salem wins
					if (salem.h.getValue() > noah.h.getValue()) {
						salemWin = true;
						salemScore++;
						goto SN;
					}

					//noah > salem, noah wins
					if (noah.h.getValue() > salem.h.getValue()) {
						noahWin = true;
						noahScore++;
						goto SN;
					}

					//salem = noah, house wins
					if (noah.h.getValue() == salem.h.getValue()) {
						houseWin = true;
						goto SN;
					}
				}

				//by default the house wins (if both players bust)
				houseWin = true;
				goto SN;
			}

			//Log info
			cout << "[INFO]Iteration Complete" << endl;
		}
	}

//End it all
return 0;
}