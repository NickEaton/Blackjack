#include "Card.h"

Deck::Deck() {
	int counter = 0;
	for (auto i = 1; i < 5; ++i) {
		for (auto j = 2; j < 15; ++j) {
			deck[counter] = Card(i, j);
			++counter;
		}
	}
}