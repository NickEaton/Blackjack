#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>

class Card {
	int r; //2-10, JQK=10, A=11
	int n; //2-14
	char s;
public:
	Card(int rank, char suite, int num);
	Card();
	int getRank();
	int getSuite();
	int getNum();
	std::string getFileName();
};

class Deck {
	int it;
	Card deck[52];
public:
	Deck();
	Card draw();
};

class Hand {
public:
	int index;
	Card hand[5];
	Hand(Card c1, Card c2);
	Hand();
	void addCard(Card card);
	int getValue();
};

#endif