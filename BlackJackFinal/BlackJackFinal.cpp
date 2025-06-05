#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


vector<int> createShuffledDeck() 
{
    vector<int> deck;

    for (int i = 1; i <= 13; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            deck.push_back(i);
        }
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));

    return deck;
}

int cardValue(int card) 
{
    if (card > 10) return 10; 
    if (card == 1) return 11;  
    return card;
}

int calculateTotal(const vector<int>& hand) 
{
    int total = 0;
    int aceCount = 0;

    for (int card : hand) 
    {
        int value = cardValue(card);
        total += value;

        if (card == 1) aceCount++;
    }
    while (total > 21 && aceCount > 0) 
    {
        total -= 10;
        aceCount--;
    }

    return total;
}

void showHand(const vector<int>& hand, const string& owner);




vector<int> createShuffledDeck() 
{
    
}

int cardValue(int card) 
{
   
}

int calculateTotal(const vector<int>& hand) 
{
   
}

void showHand(const vector<int>& hand, const string& owner) 
{
  
}

int main()
{
    vector<int> deck = createShuffledDeck();

    vector<int> playerHand, dealerHand;

    return 0;
}