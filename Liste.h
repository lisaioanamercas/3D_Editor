#pragma once

#include <iostream>

using namespace std;

struct nod
{
	int info;
	nod* next;
};

struct Lista
{
	nod* prim;
	nod* ultim;

	int nrElem;
};

void listaVida(Lista& lsi);

bool esteVida(Lista& lsi);

void insereazaLista(Lista& lsi, int pos, int element);

void eliminaLista(Lista& lsi, int pos);

void golesteLista(Lista& lsi);

void eliminaElemLista(Lista& lsi, int element);

void afisareLista(Lista lsi);
