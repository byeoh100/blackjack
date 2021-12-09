#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unistd.h>

std::vector<int> deck = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
std::vector<int> globalCards;

class Player{
private:
    int total = 0;
    std::vector<int> cards;
public:
    void clearCards()
    {
        cards.clear();
        total = 0;
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
    int choice;
    bool gameLose = false;
    
    gameStart(player, dealer);
    player.hitStand();
    std::cin >> choice;
    while(choice == 1)
    {
            player.getCards();
            usleep(300000);
            std::cout << player.hit();
            usleep(300000);
            std::cout << std::endl;
            if(player.getTotal() > 21)
            {
                std::cout << "BUST!" << std::endl;
                gameLose = true;
                break;
            }
            player.hitStand();
            std::cin >> choice;
    }
    if(gameLose == false)
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
            std::cout << "DEALER BUST!" << std::endl;
            std::cout << "Payout" << std::endl;
        }
        else
        {
            std::cout << "Dealer stands with: " << dealer.getTotal() << std::endl;
            dealer.getCards();
            std::cout << std::endl;
            if(player.getTotal() > dealer.getTotal())
            {
                std::cout << "Player win!" << std::endl;
                std::cout << "Payout" << std::endl;
            }
            else if(player.getTotal() < dealer.getTotal())
            {
                std::cout << "Player lose!" << std::endl;
                gameLose = true;
            }
        }
    }
    std::cout << "Play again?" << std::endl;
}

//work on stand choice
//make dealer
//win or no?
//betting