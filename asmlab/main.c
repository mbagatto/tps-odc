#include <stdio.h>
#include "lib.h"

char *suits[] = {"espada", "oro", "copa", "basto", "comodin"};

void test01Array()
{
    array_t *deck = arrayNew(TypeCard, 5);
    for(int32_t i = 0; i < 5; i++)
    {
        int32_t number = i + 1;
        card_t *c = cardNew(suits[i], &number);
        arrayAddLast(deck, c);
        cardDelete(c);
    }

    arrayPrint(deck, stdout);
    printf("\n");

    card_t *firstCard = arrayGet(deck, 1);
    card_t *stackedCard = arrayGet(deck, 2);

    cardAddStacked(firstCard, stackedCard);
    arrayPrint(deck, stdout);
    printf("\n");
    arrayDelete(deck);
}


void test02List()
{
    list_t *deck = listNew(TypeCard);

    for(int32_t i = 0; i < 5; i++)
    {
        int32_t number = i + 1;
        card_t *c = cardNew(suits[i], &number);
        listAddLast(deck, c);
        cardDelete(c);
    }

    listPrint(deck, stdout);
    printf("\n");

    card_t *firstCard = listGet(deck, 3);
    card_t *stackedCard = listGet(deck, 4);

    cardAddStacked(firstCard, stackedCard);
    listPrint(deck, stdout);
    printf("\n");
    listDelete(deck);
}

int main(void) {
    test01Array();
    test02List();
    return 0;
}
