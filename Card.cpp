#include "Card.h"
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

Card::Card(int rank, char suite, int num) {
	r = rank; s = suite; n = num;
}

Card::Card() {
	r = 0; s = 0; n = 0;
}

int Card::getRank() {
	return Card::r;
}

int Card::getSuite() {
	return Card::s;
}

int Card::getNum() {
	return Card::n;
}

std::string Card::getFileName() {
	std::string file{};
	if (n <= 10) {
		file.append(std::to_string(n));
		if (s == 0) {
			file.append("_of_spades.png");
		}
		else if (s == 1) {
			file.append("_of_clubs.png");
		}
		else if (s == 2) {
			file.append("_of_hearts.png");
		}
		else if (s == 3) {
			file.append("_of_diamonds.png");
		}
		return file;
	}

	if (n == 11) {
		file.append("jack");
	}
	else if (n == 12) {
		file.append("queen");
	}
	else if (n == 13) {
		file.append("king");
	}
	else if (n == 14) {
		file.append("ace");
	}

	if (s == 0) {
		file.append("_of_spades2.png");
	}
	else if (s == 1 && n != 14) {
		file.append("_of_clubs2.png");
	}
	else if (s == 1 && n == 14) {
		file.append("_of_clubs.png");
	}
	else if (s == 2 && n != 14) {
		file.append("_of_hearts2.png");
	}
	else if (s == 2 && n == 14) {
		file.append("_of_hearts.png");
	}
	else if (s == 3 && n != 14) {
		file.append("_of_diamonds2.png");
	}
	else if (s == 3 && n == 14) {
		file.append("_of_diamonds.png");
	}
	return file;
}

Deck::Deck() {
	it = -1;
	srand(time(NULL));
	int counter = 0;
	for (auto i = 0; i < 4; ++i) {
		for (auto j = 2; j < 15; ++j) {
			if (j >= 10 && j<=13) {
				deck[counter] = Card(10, i, j);
				++counter;
				continue;
			}
			if (j == 14) {
				deck[counter] = Card(11, i, j);
				++counter;
				continue;
			}
			deck[counter] = Card(j, i, j);
			++counter;
		}
	}

	for (auto i = 0; i < 5; ++i) {
		for (auto j = 0; i < 52; ++i) {
			int r = rand() % 52;
			Card temp = deck[r];
			deck[r] = deck[j];
			deck[j] = temp;
		}
	}
}

Card Deck::draw() {
	++it;
	return deck[it];
}

Hand::Hand(Card c1, Card c2) {
	hand[0] = c1; hand[1] = c2; index = 2;
}

Hand::Hand() {

}

void Hand::addCard(Card card) {
	hand[index] = card;
	++index;
}

int Hand::getValue() {
	int sum{};
	for (auto i : hand) {
		sum += i.getRank();
	}
	return sum;
}