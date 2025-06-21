#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <windows.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;


enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

const char* formStr[] = { u8"♥", u8"♦", u8"♣", u8"♠" };


struct Card
{
    int value;
    Suit suit;
};

string suitToString(Suit suit)
{
    switch (suit)
    {
    case Suit::Hearts:
        return u8"♥";
    case Suit::Diamonds:
        return u8"♦";
    case Suit::Clubs:
        return u8"♣";
    case Suit::Spades:
        return u8"♠";
    default:
        return "?";
    }
}

string valueToString(int value)
{
    switch (value)
    {
    case 1:  return "A"; // AS
    case 11: return "J"; // Joker
    case 12: return "Q"; // Queen
    case 13: return "K"; // KING
    default: return to_string(value);
    }
}


vector<Card> createShuffledDeck()
{
    vector<Card> deck;

    for (int i = 1; i <= 13; ++i)
    {
        deck.push_back({ i, Suit::Hearts });
        deck.push_back({ i, Suit::Diamonds });
        deck.push_back({ i, Suit::Clubs });
        deck.push_back({ i, Suit::Spades });
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));

    return deck;
}

int cardValue(const Card& card)
{
    if (card.value > 10) return 10;
    if (card.value == 1) return 11;
    return card.value;
}

int calculateTotal(const vector<Card>& hand)
{
    int total = 0;
    int aceCount = 0;

    for (const Card& card : hand)
    {
        int value = cardValue(card);
        total += value;
        if (card.value == 1) aceCount++;
    }

    while (total > 21 && aceCount > 0)
    {
        total -= 10;
        aceCount--;
    }

    return total;
}

void showHand(const vector<Card>& hand, const string& owner)
{
    cout << owner << " hand: ";
    for (const Card& card : hand)
    {
        if (card.suit == Suit::Hearts || card.suit == Suit::Diamonds)
        {
            cout << RED;
        }

        cout << "[" << valueToString(card.value) << suitToString(card.suit) << "]";

        if (card.suit == Suit::Hearts || card.suit == Suit::Diamonds)
        {
            cout << RESET;
        }

        cout << " ";
    }
    cout << "=> Total: " << calculateTotal(hand) << endl;
}

void playGame()
{
    vector<Card> deck = createShuffledDeck();
    vector<Card> playerHand, dealerHand;

    playerHand.push_back(deck.back()); deck.pop_back();
    playerHand.push_back(deck.back()); deck.pop_back();
    dealerHand.push_back(deck.back()); deck.pop_back();
    dealerHand.push_back(deck.back()); deck.pop_back();

    while (true)
    {
        showHand(playerHand, "Player");

        int total = calculateTotal(playerHand);
        if (total > 21)
        {
            cout << "You busted! Dealer wins.\n";
            return;
        }

        cout << "Hit or stand? (h/s): ";
        char choice;
        cin >> choice;

        while (choice != 'h' && choice != 's')
        {
            cout << "Invalid choice. Please enter 'h' or 's': ";
            cin >> choice;
        }

        if (choice == 'h')
        {
            playerHand.push_back(deck.back()); deck.pop_back();
        }
        else
        {
            break;
        }
    }

    while (calculateTotal(dealerHand) < 17)
    {
        dealerHand.push_back(deck.back()); deck.pop_back();
    }

    showHand(playerHand, "Player");
    showHand(dealerHand, "Dealer");

    int playerTotal = calculateTotal(playerHand);
    int dealerTotal = calculateTotal(dealerHand);

    if (dealerTotal > 21 || playerTotal > dealerTotal)
    {
        cout << "You win!\n";
    }
    else if (dealerTotal == playerTotal)
    {
        cout << "It's a tie!\n";
    }
    else
    {
        cout << "Dealer wins!\n";
    }
}



int main()
{
    vector<Card> deck = createShuffledDeck();
    vector<Card> playerHand, dealerHand;

    playerHand.push_back(deck.back()); deck.pop_back();
    playerHand.push_back(deck.back()); deck.pop_back();
    dealerHand.push_back(deck.back()); deck.pop_back();
    dealerHand.push_back(deck.back()); deck.pop_back();

    SetConsoleOutputCP(CP_UTF8);

    while (true)
    {
        showHand(playerHand, "Player");

        int total = calculateTotal(playerHand);
        if (total > 21)
        {
            cout << "You busted! Dealer wins.\n";
            return 0;
        }

        cout << "Hit or stand? (h/s): ";
        char choice;
        cin >> choice;

        while (choice != 'h' && choice != 's')
        {
            cout << "Invalid choice. Please enter 'h' or 's': ";
            cin >> choice;
        }

        if (choice == 'h')
        {
            playerHand.push_back(deck.back()); deck.pop_back();
        }
        else
        {
            break;
        }
    }

    while (calculateTotal(dealerHand) < 17)
    {
        dealerHand.push_back(deck.back()); deck.pop_back();
    }

    showHand(playerHand, "Player");
    showHand(dealerHand, "Dealer");

    int playerTotal = calculateTotal(playerHand);
    int dealerTotal = calculateTotal(dealerHand);

    if (dealerTotal > 21 || playerTotal > dealerTotal)
    {
        cout << "You win!\n";
    }
    else if (dealerTotal == playerTotal)
    {
        cout << "It's a tie!\n";
    }
    else
    {
        cout << "Dealer wins!\n";
    }

    char again;
    do
    {
        playGame();

        cout << "\nDo you want to play more ? (y/n): ";
        cin >> again;

        while (again != 'y' && again != 'n')
        {
            cout << "Invalid choice, write 'y' for yes or 'n' for no: ";
            cin >> again;
        }

    } while (again == 'y');

    cout << "Thank's for playing!\n";
    return 0;
}
