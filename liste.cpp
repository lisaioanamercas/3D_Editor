#include "Liste.h"

void listaVida(Lista& lsi)
{
	lsi.prim = lsi.ultim = nullptr;
	lsi.nrElem = 0;
}

bool esteVida(Lista& lsi)
{
	if (lsi.prim == nullptr && lsi.ultim == nullptr)
		return true;
	else return false;
}

void insereazaLista(Lista& lsi, int pos, int element)
{
	try
	{
		if (pos < 0 || (pos != 0 && lsi.prim == nullptr) || pos > lsi.nrElem)
			throw  404;
	}
	catch (int eroare)
	{
		cout << "POZITIE INVALIDA";
		return;
	}

	nod* temp = new nod;
	temp->info = element;

	if (pos == 0 || lsi.prim == nullptr)
	{
		temp->next = lsi.prim;
		lsi.prim = temp;

		if (lsi.ultim == nullptr)
			lsi.ultim = temp;
	}
	else
	{
		nod* parcurs = lsi.prim;
		int index = 0;

		while (index < pos - 1)
		{
			parcurs = parcurs->next;
			index++;
		}

		temp->next = parcurs->next;
		parcurs->next = temp;

		if (parcurs == lsi.ultim)
			lsi.ultim = temp;
	}

	lsi.nrElem++;
}

void eliminaLista(Lista& lsi, int pos)
{
	try
	{
		if (pos < 0 || (pos != 0 && lsi.prim == nullptr) || pos > lsi.nrElem)
			throw  404;
	}
	catch (int eroare)
	{
		cout << "POZITIE INVALIDA";
		return;
	}

	nod* temp = lsi.prim;
	int index = 0;

	if (lsi.prim == lsi.ultim)
	{
		delete(lsi.prim);
		lsi.prim = lsi.ultim = nullptr;

		lsi.nrElem = 0;
	}
	else
	{
		while (index < pos - 1)
		{
			temp = temp->next;
			index++;
		}

		if (pos == 0)
		{
			lsi.prim = lsi.prim->next;
			delete(temp);
		}
		else if (pos == lsi.nrElem - 1)
		{
			delete(lsi.ultim);
			lsi.ultim = temp;
			lsi.ultim->next = nullptr;
		}
		else
		{
			nod* del = temp->next;
			temp->next = temp->next->next;

			delete(del);
		}

		lsi.nrElem--;
	}
}

void golesteLista(Lista& lsi)
{
	while (!esteVida(lsi))
		eliminaLista(lsi, 0);
}

void eliminaElemLista(Lista& lsi, int element)
{
	while (!esteVida(lsi) && lsi.prim->info == element)
		eliminaLista(lsi, 0);

	if (esteVida(lsi))
		return;

	int index = 0;
	nod* temp = lsi.prim;

	while (temp->next != nullptr)
	{
		if (temp->next->info == element)
			eliminaLista(lsi, index + 1);
		else
		{
			index++;
			temp = temp->next;
		}
	}
}

void afisareLista(Lista lsi)
{
	nod* temp = lsi.prim;
	while (temp != nullptr)
	{
		cout << temp->info << ' ';
		temp = temp->next;
	}
}
