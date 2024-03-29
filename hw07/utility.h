#ifndef UTILITY_H
#define UTILITY_H

// *** Do not modify this file ***

#define MAX_SIZE 20

typedef struct 
{
  char cards[MAX_SIZE];
  int size; 
} CardDeck;

void print_deck(CardDeck deck);

void print_decks(CardDeck upper_deck, CardDeck lower_deck);

#endif 
