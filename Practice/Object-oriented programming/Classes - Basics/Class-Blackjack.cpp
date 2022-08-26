// LearnCpp - Summary and quiz

#include <iostream>
#include <cassert>
#include <array>
#include <random>
#include <algorithm>
#include <ctime>

/*
 ******************************
 * CARD part
 ******************************
 */
enum class CardSuit
{
    suit_club,
    suit_diamond,
    suit_heart,
    suit_spade,

    max_suits
};

enum class CardRank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks
};

class Card
{
private:
  CardRank m_cRank{};
  CardSuit m_cSuit{};

public:
  Card() = default;

  Card(CardRank cRank, CardSuit cSuit) : m_cRank{ cRank }, m_cSuit{ cSuit }
  {
  }

  void print() const
  {
    switch(m_cRank)
    {
      case CardRank::rank_2:
          std::cout << '2';
          break;
      case CardRank::rank_3:
          std::cout << '3';
          break;
      case CardRank::rank_4:
          std::cout << '4';
          break;
      case CardRank::rank_5:
          std::cout << '5';
          break;
      case CardRank::rank_6:
          std::cout << '6';
          break;
      case CardRank::rank_7:
          std::cout << '7';
          break;
      case CardRank::rank_8:
          std::cout << '8';
          break;
      case CardRank::rank_9:
          std::cout << '9';
          break;
      case CardRank::rank_10:
          std::cout << 'T';
          break;
      case CardRank::rank_jack:
          std::cout << 'J';
          break;
      case CardRank::rank_queen:
          std::cout << 'Q';
          break;
      case CardRank::rank_king:
          std::cout << 'K';
          break;
      case CardRank::rank_ace:
          std::cout << 'A';
          break;
      default:
          std::cout << '?';
          break;
    }

    switch(m_cSuit)
    {
      case CardSuit::suit_club:
          std::cout << 'C';
          break;
      case CardSuit::suit_diamond:
          std::cout << 'D';
          break;
      case CardSuit::suit_heart:
          std::cout << 'H';
          break;
      case CardSuit::suit_spade:
          std::cout << 'S';
          break;
      default:
          std::cout << '?';
          break;
    }
  }

  int getValue() const
  {
    if (m_cRank <= CardRank::rank_10)
    {
      // RANK_2 is 0 (value 2)
      // RANK_3 is 1 (value 3)
      // etc.
      return (static_cast<int>(m_cRank) + 2);
    }

    switch (m_cRank)
    {
    case CardRank::rank_jack:
    case CardRank::rank_queen:
    case CardRank::rank_king:
      return 10;
    case CardRank::rank_ace:
      return 11;
    default:
      assert(false && "should never happen");
      return 0;
    }
  }
};


/*
 ******************************
 * DECK part
 ******************************
 */
class Deck
{
public:
  using deck_type = std::array<Card, 52>;
  using deck_index_type = deck_type::size_type;

  deck_type m_deck{};

public:
  Deck()
  {
    deck_index_type deckIndex{ 0 };

    int maxSuit{ static_cast<int>(CardSuit::max_suits) };
    int maxRank{ static_cast<int>(CardRank::max_ranks) };

    for(int currentSuit = 0; currentSuit < maxSuit; ++currentSuit)
    {
      for(int currentRank = 0; currentRank < maxRank; ++currentRank)
      {
        m_deck[deckIndex] = { static_cast<CardRank>(currentRank), static_cast<CardSuit>(currentSuit) };
        ++deckIndex;
      }
    }
  }

  void print()
  {
    int column{};
    for(const auto& card : m_deck)
    {
      card.print();
      std::cout << " ";
      if(++column > 4)
        {
            std::cout << '\n';
            column = 0;
        }
    }
    std::cout << '\n' << '\n';
  }

  void shuffle()
  {
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(m_deck.begin(), m_deck.end(), mt);
  }

};


/*
 ******************************
 * GAME part
 ******************************
 */
bool playBlackjack(Deck& deck)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution<> deckRange{ 1, 52 };

    Card dealerCard;
    int dealerScore{};
    Card playerCard;
    int playerScore{};

    Deck::deck_index_type deck_index;

    std::cout << "\n********** DEALER STARTS THE GAME **********\n";
    std::cout << "Dealer gets one card!\n";
    deck_index = static_cast<Deck::deck_index_type>(deckRange(mt));
    dealerCard = deck.m_deck[deck_index];
    dealerScore = dealerCard.getValue();
    std::cout << "Dealer current score is: " << dealerScore << '\n';

    std::cout << "\n********** PLAYER STARTS THE GAME **********\n";
    std::cout << "Player gets two cards!\n";
    for(int iii = 0; iii < 2; ++iii)
    {
        deck_index = static_cast<Deck::deck_index_type>(deckRange(mt));
        playerCard = deck.m_deck[deck_index];
        playerScore += playerCard.getValue();
        std::cout << "Player current score is: " << playerScore << '\n';
    }

    char action{};

    std::cout << "\n********** INFO - If you want one more card type h (as hit), or s (as stand) **********\n";

    std::cout << "\n********** PLAYER PLAYING! **********\n";
    do
    {
        std::cout << "Do you want one more card?\n";

        std::cin >> action;
        if(action == 'h')
        {
            std::cout << "Player wants one more card!\n";
            deck_index = static_cast<Deck::deck_index_type>(deckRange(mt));
            playerCard = deck.m_deck[deck_index];
            playerScore += playerCard.getValue();
            std::cout << "Player current score is: " << playerScore << '\n';
        }
        else if(action == 's')
        {
            std::cout << "Player doesn't want more cards!\n";
            break;
        }
        else
        {
            std::cout << "You entered wrong action! You should choose either 'h' or 's'. Please, try again.\n";
            continue;
        }

        if(playerScore > 21)
        {
            std::cout << "Player score went over 21!\n";
            return false;
        }
    } while(action != 's');

    std::cout << "\n********** DEALER PLAYING! **********\n";
    do
    {
        std::cout << "Do you want one more card?\n";

        std::cin >> action;
        if(action == 'h')
        {
            std::cout << "Dealer wants one more card!\n";
            deck_index = static_cast<Deck::deck_index_type>(deckRange(mt));
            dealerCard = deck.m_deck[deck_index];
            dealerScore += dealerCard.getValue();
            std::cout << "Dealer current score is: " << dealerScore << '\n';
        }
        else if(action == 's')
        {
            std::cout << "Dealer doesn't want more cards!\n";
            break;
        }
        else
        {
            std::cout << "You entered wrong action! You should choose either 'h' or 's'. Please, try again.\n";
            continue;
        }

        if((dealerScore >= 17) && (dealerScore <= 21))
        {
            std::cout << "Dealer has score between 17 and 21. No more cards for him!\n";
            break;
        }

        if(dealerScore > 21)
        {
            std::cout << "Dealer score went over 21!\n";
            return true;
        }
    } while(action != 's');

    std::cout << "\n-------------------------------\n";

    std::cout << "PLAYER final score = " << playerScore << '\n';
    std::cout << "DEALER final score = " << dealerScore << '\n';

    return (playerScore > dealerScore);
}


/*
 * Following main() won't compile because m_deck, used in playBlackjack(), is private.
 * This would work if we create getDeck() function or add playBlackjack() as a friend
 * function to Deck class.
 */
int main()
{
  Deck deck;

  deck.print(); // Print cards from deck sequentially
  deck.shuffle();
  deck.print(); // Print shuffled deck

  bool player{ playBlackjack(deck) };

  std::cout << "\nPLAYER " << (player ? "won" : "lost") << '\n';

  return 0;
}
