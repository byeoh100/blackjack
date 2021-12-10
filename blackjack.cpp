#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unistd.h>
#include <climits>

std::vector<int> deck = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
std::vector<int> globalCards;

class Player{
private:
    int total = 0;
    int money;
    int bet;
    std::vector<int> cards;
public:
    void clearCards()
    {
        cards.clear();
        total = 0;
    }
    void moneyReset()
    {
        money = 1000;
    }
    int getMoney()
    {
        return money;
    }
    void playerBet()
    {
        do
        {
            std::cout << "Place wager(increments of 5): " << std::endl;
            std::cin >> bet;
            while(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');    
                std::cout << "Invalid entry, try again" << std::endl;
                std::cin >> bet;
            }
            if(bet % 5 == 0)
            {
                std::cout << "You wager: " << bet << std::endl;
                money -= bet;
                break;
            }
            else if(bet % 5 != 0)
                std::cout << "Invalid entry, try again" << std::endl;
        }while(1);       
    }
    int getBet()
    {
        return bet;
    }
    int winPayout()
    {
        money += (bet * 2);
        return bet;
    }
    int BJwinPayout()
    {
        money += (bet * 2.5);
        return bet * 1.5;
    }
    void losePayout()
    {
        bet = 0;
    }
    void tiePayout()
    {
        money += bet
    }
    int hit()
    {
        bool tooMany = true;
        int num;
        do
        {
            int eq = 0;
            num =  rand() % 13;
            for(int i = 0; i < globalCards.size(); i++)
            {
                if(globalCards[i] == num)
                    eq++;
            }
            if(eq <= 4)
                tooMany = false;
                eq = 0;
        } while(tooMany == true);
        int rCard = deck[num];
        globalCards.push_back(rCard);
        cards.push_back(rCard);
        return rCard;
    }
    int getTotal()
    {
        total = accumulate(cards.begin(), cards.end(), 0);
        return total;
    }
    void getCards()
    {
        for(int i = 0; i < cards.size(); i++)
            std::cout << cards[i] << " ";
    }
    void hitStand()
    {
        std::cout << "You are at: " << getTotal() << std::endl;
        std::cout << "1 - Hit" << std::endl;
        std::cout << "2 - Stand" << std::endl;
    }
    bool playerBjack()
    {
        if(cards[0] == 1 && cards[1] == 10 || cards[0] == 10 && cards[1] == 1)
            return true;
        return false;
    }
    bool dealerBjack()
    {
        if(cards[0] == 10 && cards[1] == 1)
            return true;
        return false;
    }
    int hard1()
    {
        if(cards[0] == 1)
        {
            int choice;
            std::cout << "Would you like to have your ace worth 1 or 11" << std::endl;
            std::cin >> choice;
            if(choice == 11)
                cards[0] += 10;
            return 0;
        }
        if(cards[1] == 1)
        {
            int choice;
            std::cout << "Would you like to have your ace worth 1 or 11" << std::endl;
            std::cin >> choice;
            if(choice == 11)
                cards[1] += 10;
            return 0;
        }
        return 0;
    }
};
void gameStart(Player &player, Player &dealer)
{
    srand(time(NULL));
    std::cout << "Dealing dealer cards";
    usleep(300000);
    std::cout << ".";
    usleep(300000);
    std::cout << ".";
    usleep(300000);
    std::cout << "." << std::endl;
    usleep(300000);
    std::cout << dealer.hit() << " ";
    usleep(300000);
    dealer.hit();
    std::cout << 'X' << std::endl;
    sleep(1);
    std::cout << "Dealing player cards";
    usleep(300000);
    std::cout << ".";
    usleep(300000);
    std::cout << ".";
    usleep(300000);
    std::cout << "." << std::endl;
    usleep(300000);
    std::cout << player.hit() << " ";
    usleep(300000);
    std::cout << player.hit() << " ";
    std::cout << std::endl;
    usleep(300000);
}

int main()
{   
    Player player;
    Player dealer;
    player.moneyReset();
    int choice;
    char startComm;
    bool gameLose = false;
    bool game = false;
    bool blackjack = false;
    
    std::cout << "+ to deal" << std::endl;
    std::cin >> startComm;
    do
    {
        if(startComm == '+')
        {
            bool game = true;
            std::cout << "Balance: " << player.getMoney() << std::endl;
            player.playerBet();
            break;
        }
        else
            std::cout << "Invalid Entry, try again" << std::endl;
            std::cin >> startComm;
    }while(game == false);
    do
    {
        gameStart(player, dealer);
        if(player.playerBjack() == true && dealer.dealerBjack() == false)
        {
            std::cout << "Blackjack!" << std::endl;
            std::cout << "+ " << player.BJwinPayout() << std::endl;
            blackjack = true;
        }
        else if(player.playerBjack() == true && dealer.dealerBjack() == true)
        {
            std::cout << "Blackjack!" << std::endl;
            std::cout << "Tie" << std::endl;
            player.tiePayout();
            blackjack = true;
        }
        else if(player.playerBjack() == false && dealer.dealerBjack() == true)
        {
            std::cout << "Dealer blackjack!" << std::endl;
            std::cout << "Player lose" << std::endl;
            player.losePayout();
            blackjack = true;
        }
        else
        {
            player.hard1();
            player.hitStand();
            std::cin >> choice;
            while(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');    
                std::cout << "Invalid entry, try again" << std::endl;
                std::cin >> choice;
            }
        }
        while(choice == 1)
        {
                player.getCards();
                usleep(300000);
                std::cout << player.hit();
                usleep(300000);
                std::cout << std::endl;
                if(player.getTotal() > 21)
                {
                    usleep(300000);
                    std::cout << "Bust!" << std::endl;
                    player.losePayout();
                    gameLose = true;
                    break;
                }
                player.hitStand();
                std::cin >> choice;
        }
        if(gameLose == false && blackjack == false)
        {
            std::cout << "Dealer reveals: " << std::endl;
            usleep(300000);
            dealer.getCards();
            std::cout << std::endl;
            while(dealer.getTotal() < 17)
            {
                usleep(300000);
                std::cout << "Dealer hits: " << std::endl;
                dealer.getCards();
                usleep(300000);
                std::cout << dealer.hit();
                usleep(300000);
                std::cout << std::endl;
            }
            if(dealer.getTotal() > 21)
            {
                usleep(300000);
                std::cout << "Dealer bust!" << std::endl;
                std::cout << "+ " << player.winPayout() << std::endl;
            }
            else
            {
                usleep(300000);
                std::cout << "Dealer stands with: " << dealer.getTotal() << std::endl;
                dealer.getCards();
                std::cout << std::endl;
                if(player.getTotal() > dealer.getTotal())
                {
                    usleep(500000);
                    std::cout << "Player win with: " << player.getTotal() << std::endl;
                    std::cout << "+ " << player.winPayout() << std::endl;
                }
                else if(player.getTotal() < dealer.getTotal())
                {
                    usleep(500000);
                    std::cout << "Player win loses with: " << player.getTotal() << std::endl;
                    player.losePayout();
                    gameLose = true;
                }
                else if(player.getTotal() == dealer.getTotal())
                {
                    usleep(500000);
                    std::cout << "Tie" << std::endl;
                    player.tiePayout();
                }
            }
        }
        usleep(300000);
        std::cout << "+ to play again" << std::endl;
        std::cout << "Any other key to exit" << std::endl;
        std::cin >> startComm;
        while(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');    
            std::cout << "Invalid entry, try again" << std::endl;
            std::cin >> startComm;
        }
        if(startComm == '+')
        {
            if(player.getMoney() != 0)
            {
                game = true;
                player.clearCards();
                dealer.clearCards();
                gameLose = false;
                blackjack = false;
                std::cout << "Balance: " << player.getMoney() << std::endl;
                player.playerBet();
            }
            else if(player.getMoney() == 0)
            {
                std::cout << "Balance: " << player.getMoney() << std::endl;
                std::cout << "You're out of money, you lose!" << std::endl;
                startComm == '-';
                break;
            }
        }
        else
            break;
    } while(game == true);
    std::cout << "You finish with: " << player.getMoney() << std::endl;
}

//splits
