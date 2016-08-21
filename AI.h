#ifndef AI_H
#define AI_H

#include "Card.h"

class AI {
public:
	Hand h;
	AI(Card c1, Card c2);
	AI();
	virtual bool hit();
	bool bust();
	void addCard(Card card);
};

class Player : public AI {
public:
	Hand h;
	Player();
	Player(Card c1, Card c2);
	void hit(Card card);
};

#endif