#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Deck
{
private:
    struct node
    {
        string name;
        node* next;
        node* prev;
    };

    node* first;
    node* last;
    int size;

public:
    Deck()
    {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    ~Deck()
    {
        last = nullptr;
        while (size != 0)
        {
            node* n = first;
            first = first->next;
            delete n;
            size--;
        }
    }

    void add(const string card)
    {
        node* n = new node;
        n->name = card;

        if (size == 0)
        {
            n->next = nullptr;
            n->prev = nullptr;

            first = n;
            last = n;
        }

        else if (size != 0)
        {
            n->prev = last;
            n->next = nullptr;

            last->next = n;
            last = n;
        }

        size++;
    }

    void add(const string card, int n)
    {
        for (int i = 0; i < n; i++)
        {
            add(card);
        }
    }

    node* get_node(int n)
    {
        if (n >= size)
        {
            cout << "Cannot get the " << n << "th element from a " << size << " sized deck!\n";
            return nullptr;
        }

        node* card = first;
        for (int i = 0; i < n; i++)
        {
            card = card->next;
        }

        return card;
    }

    // first element is 0, second is 1 etc.
    void remove_node(node* card)
    {
        if (size == 0)
        {
            cout << "Cannot remove from an empty deck!\n";
            return;
        }

        if (card == nullptr)
        {
            cout << "Cannot remove a nullptr from the deck!\n";
            return;
        }


        if (card->prev == nullptr)
        {
            first = card->next;
        }
        else if (card->prev != nullptr)
        {
            card->prev->next = card->next;
        }

        if (card->next == nullptr)
        {
            last = card->prev;
        }
        else if (card->next != nullptr)
        {
            card->next->prev = card->prev;
        }

        size--;
        delete card;
    }

    void draw_cards(int n) 
    {
        srand(time(nullptr));

        if (n > size)
        {
            cout << "Cannot draw more cards than the number of cards in the deck!\n";
            return;
        }

        for (int i = 0; i < n; i++)
        {
            int random = rand() % (size - i);
            node* card = get_node(random);
            cout << "Card " << (i + 1) << ": " << card->name << endl;

            remove_node(card);
        }
    }
};
int main() 
{
    Deck best;
    best.add("Runaway Steamkin", 4);
    best.add("Risk Factor", 4);
    best.add("Experimental Frenzy", 2);
    best.add("Ghitu Lavarunner", 4);
    best.add("Shock", 4);
    best.add("Lightning Strike", 4);
    best.add("Guttersnipe", 4);
    best.add("Electrostatic Field", 2);
    best.add("Viashino Pyromancer", 4);
    best.add("Rekindling Phoenix", 2);
    best.add("Lava Coil", 2);
    best.add("Shivan Fire", 2);
    best.add("Mountain", 22);

    best.draw_cards(7);
}