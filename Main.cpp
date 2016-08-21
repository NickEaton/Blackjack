#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Card.h"
#include "AI.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	Player player;
	AI nick;
	AI salem;
	AI noah;

	sf::RenderWindow title(sf::VideoMode(200, 100), "Blackjack");
	while (title.isOpen()) {
		sf::RectangleShape titleCard(sf::Vector2f(190, 40));
		titleCard.setPosition(5, 5);
		titleCard.setFillColor(sf::Color::Color(224, 224, 224));
		titleCard.setOutlineColor(sf::Color::Black);
		titleCard.setOutlineThickness(1);

		sf::RectangleShape yesButton(sf::Vector2f(90, 40));
		yesButton.setPosition(5, 55);
		yesButton.setFillColor(sf::Color::Color(224, 224, 224));
		yesButton.setOutlineColor(sf::Color::Black);
		yesButton.setOutlineThickness(1);

		sf::RectangleShape noButton(sf::Vector2f(90, 40));
		noButton.setPosition(105, 55);
		noButton.setFillColor(sf::Color::Color(224, 224, 224));
		noButton.setOutlineColor(sf::Color::Black);
		noButton.setOutlineThickness(1);

		sf::Font font;
		font.loadFromFile("arial.ttf");
		
		sf::Text card;
		card.setFont(font);
		card.setString("Will You Play or Spectate?");
		card.setCharacterSize(15);
		card.setFillColor(sf::Color::Black);
		card.setPosition(10, 15);

		sf::Text play;
		play.setFont(font);
		play.setString("Play");
		play.setCharacterSize(15);
		play.setFillColor(sf::Color::Black);
		play.setPosition(33, 65);

		sf::Text spectate;
		spectate.setFont(font);
		spectate.setString("Spectate");
		spectate.setCharacterSize(15);
		spectate.setFillColor(sf::Color::Black);
		spectate.setPosition(118, 65);

		title.clear(sf::Color::Color(192, 192, 192));
		title.draw(titleCard);
		title.draw(yesButton);
		title.draw(noButton);
		title.draw(card);
		title.draw(play);
		title.draw(spectate);
		title.display();

		sf::Event event;
		
		while (title.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return 0;
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && ((event.mouseButton.x >= 5 && event.mouseButton.x <= 95) && (event.mouseButton.y >= 55 && event.mouseButton.y <= 95))) {
				cout << "[INFO]User is playing" << endl;
				title.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && ((event.mouseButton.x >= 105 && event.mouseButton.x <= 195) && (event.mouseButton.y >= 55 && event.mouseButton.y <= 95))) {
				cout << "[INFO]User is spectating" << endl;
				title.close();
			}
		}
	}
	
	while (true) {
		sf::RenderWindow window(sf::VideoMode(770, 400), "Blackjack");

		Deck deck = Deck();

		player = Player(deck.draw(), deck.draw());
		noah = AI(deck.draw(), deck.draw());
		salem = AI(deck.draw(), deck.draw());

		sf::Texture c1;
		c1.loadFromFile(player.h.hand[0].getFileName());
		sf::Sprite card1;
		card1.setTexture(c1);
		card1.setPosition(sf::Vector2f(15, 50));
		card1.scale(.275, .275);

		sf::Texture c2;
		c2.loadFromFile(player.h.hand[1].getFileName());
		sf::Sprite card2;
		card2.setTexture(c2);
		card2.setPosition(sf::Vector2f(165, 50));
		card2.scale(.275, .275);

		sf::RectangleShape hitButton(sf::Vector2f(135, 50));
		hitButton.setFillColor(sf::Color::Color(255, 51, 51));
		hitButton.setOutlineThickness(1);
		hitButton.setOutlineColor(sf::Color::Black);
		hitButton.setPosition(sf::Vector2f(15, 265));

		sf::Font font;
		font.loadFromFile("AdobeGothicStd-Bold.otf");

		sf::Text hit;
		hit.setFont(font);
		hit.setString("Hit");
		hit.setCharacterSize(24);
		hit.setFillColor(sf::Color::Black);
		hit.setPosition(sf::Vector2f(62, 275));

		sf::Text stay;
		stay.setFont(font);
		stay.setString("Stay");
		stay.setCharacterSize(24);
		stay.setFillColor(sf::Color::Black);
		stay.setPosition(sf::Vector2f(55, 335));

		sf::RectangleShape stayButton(sf::Vector2f(135, 50));
		stayButton.setFillColor(sf::Color::Color(51, 51, 255));
		stayButton.setOutlineThickness(1);
		stayButton.setOutlineColor(sf::Color::Black);
		stayButton.setPosition(sf::Vector2f(15, 325));

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

		sf::RectangleShape specBox(sf::Vector2f(280, 110));
		specBox.setFillColor(sf::Color::Color(51, 255, 51));
		specBox.setOutlineColor(sf::Color::Black);
		specBox.setOutlineThickness(1);
		specBox.setPosition(sf::Vector2f(165, 265));

		bool blj = false;
		sf::Text blackjack;
		blackjack.setFont(font);
		blackjack.setString("Blackjack");
		blackjack.setFillColor(sf::Color::Black);
		blackjack.setCharacterSize(24);
		blackjack.setPosition(sf::Vector2f(250, 310));

		bool bst = false;
		sf::Text bust;
		bust.setFont(font);
		bust.setString("Bust");
		bust.setFillColor(sf::Color::Black);
		bust.setCharacterSize(24);
		bust.setPosition(sf::Vector2f(275, 310));

		sf::Sprite card3;
		sf::Sprite card4;
		sf::Sprite card5;

		sf::Texture car3;
		card3.setPosition(sf::Vector2f(315, 50));
		card3.scale(.275, .275);

		sf::Texture car4;
		card4.setPosition(sf::Vector2f(465, 50));
		card4.scale(.275, .275);

		sf::Texture car5;
		card5.setPosition(615, 50);
		card5.scale(.275, .275);

		int plindex = 1;
		while (window.isOpen()) {
			sf::Event event;

			if (player.h.getValue() == 21) {
				cout << "[INFO]Player Blackjacked" << endl;
				blj = true;
			}

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					return 0;
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 15 && event.mouseButton.x <= 150 && event.mouseButton.y >= 265 && event.mouseButton.y <= 315) {
					cout << "[INFO]Hit Button Clicked" << endl;
					player.hit(deck.draw());
					if (plindex == 1) {
						cout << "[INFO]Loaded Card 3" << endl;
						car3.loadFromFile(player.h.hand[2].getFileName());
						card3.setTexture(car3);
					}
					else if (plindex == 2) {
						cout << "[INFO]Loaded Card 4" << endl;
						car4.loadFromFile(player.h.hand[3].getFileName());
						card4.setTexture(car4);
					}
					else if (plindex == 3) {
						cout << "[INFO]Loaded Card 5" << endl;
						car5.loadFromFile(player.h.hand[4].getFileName());
						card5.setTexture(car5);
					}
					if (player.h.getValue() == 21) {
						cout << "[INFO]Player Blackjacked" << endl;
						blj = true;
					}
					if (player.h.getValue() > 21) {
						cout << "[INFO]Player Busted" << endl;
						bst = true;
					}
					++plindex;
				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.x >= 15 && event.mouseButton.x <= 150 && event.mouseButton.y >= 325 && event.mouseButton.y <= 375) {
					cout << "[INFO]Stay Button Clicked" << endl;
					while (noah.hit() && !noah.bust()) {
						noah.addCard(deck.draw());
					}
					while (salem.hit() && !salem.bust()) {
						salem.addCard(deck.draw());
					}
					int pv = player.h.getValue();
					int nv = noah.h.getValue();
					int sv = salem.h.getValue();
					if (pv > nv && pv > sv) {
						//player wins
					}
					else if (nv > pv && nv > sv) {
						//noah wins
					}
					else if (sv > pv && sv > nv) {
						//salem wins
					}
				}
			}

			window.clear(sf::Color::Color(192, 192, 192));
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
			if (blj || bst) 
				window.draw(specBox);
			if (blj)
				window.draw(blackjack);
			if (bst) 
				window.draw(bust);
			/* if (plindex <= 1)
				window.draw(ca3);
			if (plindex <= 2)
				window.draw(ca4);
			if (plindex <= 3)
				window.draw(ca5); */
			window.display();
		}
	}

return 0;
}