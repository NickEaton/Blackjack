#include "Card.h"
#include "AI.h"

AI::AI(Card c1, Card c2) {
	h = Hand(c1, c2);
}

AI::AI() {
	h = Hand(Card(), Card());
}

bool AI::hit() {
	return h.getValue() <= 17 && h.index < 5 ? true : false;
}

bool AI::bust() {
	return h.getValue() > 21 ? true : false;
}

void AI::addCard(Card card) {
	h.addCard(card);
}

Player::Player(Card c1, Card c2) {
	h = Hand(c1, c2);
}

Player::Player() {
	h = Hand(Card(), Card());
}

void Player::hit(Card card) {
	h.addCard(card);
}