#include "lib.h"

funcCmp_t *getCompareFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcCmp_t *)&intCmp;
        break;
    case TypeString:
        return (funcCmp_t *)&strCmp;
        break;
    case TypeCard:
        return (funcCmp_t *)&cardCmp;
        break;
    default:
        break;
    }
    return 0;
}
funcClone_t *getCloneFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcClone_t *)&intClone;
        break;
    case TypeString:
        return (funcClone_t *)&strClone;
        break;
    case TypeCard:
        return (funcClone_t *)&cardClone;
        break;
    default:
        break;
    }
    return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcDelete_t *)&intDelete;
        break;
    case TypeString:
        return (funcDelete_t *)&strDelete;
        break;
    case TypeCard:
        return (funcDelete_t *)&cardDelete;
        break;
    default:
        break;
    }
    return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcPrint_t *)&intPrint;
        break;
    case TypeString:
        return (funcPrint_t *)&strPrint;
        break;
    case TypeCard:
        return (funcPrint_t *)&cardPrint;
        break;
    default:
        break;
    }
    return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
    if (*a < *b) {
          return 1;
    } else if (*a > *b) {
          return -1;
    }
    return 0;
}

void intDelete(int32_t *a)
{
  free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
  fprintf(pFile, "%i", *a);
}

int32_t *intClone(int32_t *a)
{
    int32_t* assignedMem = (int32_t*)malloc(sizeof(int32_t));
    *assignedMem = *a;
    return assignedMem;
}

/** Lista **/

list_t *listNew(type_t t)
{
    list_t* newList = (list_t*)malloc(sizeof(list_t));
    newList->type = t;
    newList->size = 0;
    newList->first = NULL;
    newList->last = NULL;
    return newList;
}

uint8_t listGetSize(list_t *l)
{
  return l->size;
}

void *listGet(list_t *l, uint8_t i)
{
  if (i >= l->size) {
    return 0;
  }

  listElem_t* elem = l->first;
  for (uint8_t j = 0; j < i && elem != 0; j++) {
    elem = elem->next;
  }
  return elem->data;
}

void listAddFirst(list_t *l, void *data)
{
  listElem_t* newElem = (listElem_t*)malloc(sizeof(listElem_t));
  newElem->data = getCloneFunction(l->type)(data);
  newElem->prev = NULL;
  newElem->next = l->first;

  if (l->first) {
     l->first->prev = newElem;
  }
  l->first = newElem;
  if (!l->last) {
    l->last = newElem;
  }
  l->size++;
}

void listAddLast(list_t *l, void *data)
{
  listElem_t* newElem = (listElem_t*)malloc(sizeof(listElem_t));
  newElem->data = getCloneFunction(l->type)(data);
  newElem->prev = l->last;
  newElem->next = NULL;

  if (l->last) {
    l->last->next = newElem;
  }
  l->last = newElem;
  if (!l->first) {
    l->first = newElem;
  }
  l->size++;
}

list_t *listClone(list_t *l)
{
  list_t* listClone = listNew(l->type);
  funcClone_t* funcClone = getCloneFunction(l->type);
  listClone->type = l->type;
  listClone->size = 0;
  listClone->first = NULL;
  listClone->last = NULL;

  for (uint8_t i = 0; i < l->size; i++) {
    listAddLast(listClone, listGet(l, i));
  }
  return listClone;
}

void *listRemove(list_t *l, uint8_t i)
{
  if (i >= l->size) {
    return 0;
  }

  listElem_t* elem = l->first;
  for (uint8_t j = 0; j < i; j++) {
    elem = elem->next;
  }
  void* data = elem->data;

  if (elem->prev != NULL) {
    elem->prev->next = elem->next;
  } else {
    l->first = elem->next;
  }
  if (elem->next != 0) {
    elem->next->prev = elem->prev;
  } else {
    l->last = elem->prev;
  }
  free(elem);
  l->size--;
  return data;
}

void listSwap(list_t *l, uint8_t i, uint8_t j)
{
  if (i >= l->size || j >= l->size || i == j) {
    return;
  }

  listElem_t* elem1 = l->first;
  for (uint8_t k = 0; k < i && elem1 != 0; k++) {
      elem1 = elem1->next;
  }
  listElem_t* elem2 = l->first;
  for (uint8_t k = 0; k < j && elem1 != 0; k++) {
      elem2 = elem2->next;
  }
  void* tmpData = elem1->data;
  elem1->data = elem2->data;
  elem2->data = tmpData;
}

void listDelete(list_t *l)
{
  uint8_t size = listGetSize(l);
  funcDelete_t* deleteFunc = getDeleteFunction(l->type);
  for (uint8_t i = 0; i < size; i++) {
    deleteFunc(listRemove(l, 0));
  }
  free(l);
}

void listPrint(list_t *l, FILE *pFile)
{
  fprintf(pFile, "[");
  listElem_t* elem = l->first;
  funcPrint_t* printFunc = getPrintFunction(l->type);
  for (uint8_t i = 0; i < l->size && elem != 0; i++) {
    printFunc(elem->data, pFile);
    elem = elem->next;
    if (elem) {
      fprintf(pFile, ",");
    }
  }
  fprintf(pFile, "]");
}

/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->cardDeck = cardDeck;
    game->funcGet = funcGet;
    game->funcRemove = funcRemove;
    game->funcSize = funcSize;
    game->funcPrint = funcPrint;
    game->funcDelete = funcDelete;
    return game;
}
int gamePlayStep(game_t *g)
{
    int applied = 0;
    uint8_t i = 0;
    while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
    {
        card_t *a = g->funcGet(g->cardDeck, i);
        card_t *b = g->funcGet(g->cardDeck, i + 1);
        card_t *c = g->funcGet(g->cardDeck, i + 2);
        if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
        {
            card_t *removed = g->funcRemove(g->cardDeck, i);
            cardAddStacked(b, removed);
            cardDelete(removed);
            applied = 1;
        }
        i++;
    }
    return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
    return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
    g->funcDelete(g->cardDeck);
    free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
    g->funcPrint(g->cardDeck, pFile);
}