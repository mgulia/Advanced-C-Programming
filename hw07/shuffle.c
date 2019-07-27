#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) 
{
	//Initializes variables
	int count;
	int num = orig_deck.size;

	//Seperates the card deck into upper and lower deck
	for (int j = 0; j<num - 1; j++)
	{
		int upperNum = j + 1;
		int lowerNum = num - upperNum;

		for (int a = 0; a<upperNum; a++)
		{
			upper_deck[j].cards[a] = orig_deck.cards[a];
			count = a + 1;
		}
		
		upper_deck[j].size = upperNum;

		for (int b = 0; b<lowerNum; b++)
		{
			lower_deck[j].cards[b] = orig_deck.cards[count];
			 count++;
		}

		lower_deck[j].size = lowerNum;
	}

}


void helper(CardDeck upper_deck, CardDeck lower_deck, CardDeck cb, int indexLower, int indexUpper)
{
	//Prints the output if the index for upper deck and lower deck are equal to  their respective sizes
	if(upper_deck.size == indexUpper && lower_deck.size == indexLower)
	{
		print_deck(cb);
		printf("\n");
		return;	
	}

	//adds lower cards to combined deck if helper is done with upper deck
	else if(upper_deck.size == indexUpper)
	{
		cb.cards[indexUpper + indexLower] = lower_deck.cards[indexLower];
		helper(upper_deck, lower_deck, cb, indexLower + 1, indexUpper);	
	}
	
	//adds upper cards to combined deck if helper is done with lower deck
	else if(lower_deck.size == indexLower)
	{
		cb.cards[indexUpper + indexLower] = upper_deck.cards[indexUpper];
		helper(upper_deck, lower_deck, cb, indexLower, indexUpper + 1);
	}

	//uses helper to complete recursive calls for upper and lower
	else
	{	
		cb.cards[indexUpper + indexLower] = lower_deck.cards[indexLower];
		helper(upper_deck, lower_deck, cb, indexLower + 1, indexUpper);
		
		cb.cards[indexUpper + indexLower] = upper_deck.cards[indexUpper];
		helper(upper_deck, lower_deck, cb, indexLower, indexUpper + 1);
	}

}



void interleave(CardDeck upper_deck, CardDeck lower_deck) 
{

	//Creates struct for combined deck	
	CardDeck cb = {
		.size = upper_deck.size + lower_deck.size,
		.cards = {'0'}
	};
	
	//Initializes indexes for upper and lower deck
	int indexLower = 0;
	int indexUpper = 0;

	//calls helper function to get the possible outcomes
	helper(upper_deck, lower_deck, cb, indexLower, indexUpper);

}


void shuffle(CardDeck orig_deck) {
	int numpairs = -1;
	int i = 0;

	numpairs = orig_deck.size - 1;

	//creates memory for upper and lower deck
	CardDeck * upper_deck = malloc((orig_deck.size - 1) * sizeof(*upper_deck));
	CardDeck * lower_deck = malloc((orig_deck.size - 1) * sizeof(*lower_deck));

	//if either of the decks are empty then it returns
	if (upper_deck == NULL) 
	{
		return;	
	}
	
	if (lower_deck == NULL) 
	{
		return;
	}

	// calls divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);


	while ( i < numpairs) 
	{
		//calls interleave for each pair
		interleave(upper_deck[i], lower_deck[i]);
		i++;
	}

	//frees allocated memory
	free(upper_deck);
	free(lower_deck);
} 
