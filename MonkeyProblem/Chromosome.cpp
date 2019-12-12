#include "pch.h"
#include "Chromosome.h"
#include <iostream>
#include <stdlib.h>
#include<ctime>
using namespace std;

Chromosome::Chromosome(int nofGene, char* word, bool initialize)
{
	nofGenes = nofGene;
	genes = new char[nofGenes];

	Chromosome::word = word;

	if (initialize)
	{
		//Use ascii table from 32->' ' to 126->'~'
		srand(rand() * time(0));
		for (int i = 0; i < nofGenes; i++) {
			genes[i] = GenerateChar();
		}
	}
}

char Chromosome::GenerateChar()
{
	int index = 32 + rand() % (126 - 32 + 1);
	return char(index);
}

void Chromosome::Print() {
	cout << "Word:\t";
	for (int i = 0; i < nofGenes; i++) {
		cout << char(genes[i]);
	}
	cout << "\t fitness: " << CalculateFitness();
	cout << "\n";
}

char * Chromosome::GetGenes()
{
	char* g = new char[nofGenes];
	for (int i = 0; i < nofGenes; i++)
	{
		g[i] = genes[i];
	}
	return g;
}

void Chromosome::SetGenes(char * genes)
{
	Chromosome::genes = genes;
}

void Chromosome::Mutation()
{
	int index = rand() % nofGenes;

	char oldC = genes[index];
	char newC = GenerateChar();
	if(oldC==newC)
		newC = GenerateChar();
	genes[index] = newC;
}

vector<Chromosome> Chromosome::CrossOver(Chromosome parent2)
{
	vector<Chromosome> children;
	Chromosome* c1 = new Chromosome(nofGenes,word, false);
	Chromosome* c2 = new Chromosome(nofGenes,word, false);

	int nofCuts = 1;
	if (nofGenes > 10)
		nofCuts = 2;

	int cutMin = nofCuts == 2 ? 1 + rand() % (nofGenes / 2 - 1) : 1 + rand() % (nofGenes - 1);
	int cutMax = nofCuts == 2 ? cutMin + 1 + rand() % (nofGenes / 2 - 2) : 0;

	char* newGenes = new char[nofGenes];

	//Child 1
	newGenes = GetGenes();
	for (int i = cutMin; i < nofGenes - cutMax; i++) {
		newGenes[i] = parent2.GetGenes()[i];
	}

	c1->SetGenes(newGenes);
	c1->Mutation();
	children.push_back(*c1);

	//Child 2
	newGenes = parent2.GetGenes();
	for (int i = cutMin; i < nofGenes - cutMax; i++)
		newGenes[i] = genes[i];
	c2->SetGenes(newGenes);
	c2->Mutation();
	children.push_back(*c2);

	return children;
}

void Chromosome::Inversion()
{
	int nofCuts = 1;
	if (nofGenes > 10)
		nofCuts = 2;

	int cutMin = nofCuts == 2 ? 1 + rand() % (nofGenes / 2 - 1) : 1 + rand() % (nofGenes - 2);
	int cutMax = nofCuts == 2 ? cutMin + 1 + rand() % (nofGenes / 2 - 2) : 0;

	char* chars = new char[nofGenes];
	for (int i = 0; i < nofGenes; i++)
		chars[i] = genes[i];


	if (cutMax == 0)
	{
		for (int i = 0; i < nofGenes - (cutMin + cutMax); i++)
			genes[i] = chars[i + cutMin + cutMax];
		for (int i = nofGenes - (cutMin + cutMax); i < nofGenes; i++)
			genes[i] = chars[i - (nofGenes - (cutMin + cutMax))];
	}
	else {
		//Character after cutMax are placed at the beginning of genes
		for (int i = cutMax; i < nofGenes; i++)
			genes[i - cutMax] = chars[i];
		//Character between cutMin and cutMax are not moved
		for (int i = cutMin; i < cutMax; i++)
			genes[i + nofGenes - cutMax - 2] = chars[i];
		//Character before cutMin are placed at the end of genes
		for (int i = 0; i < cutMin; i++)
			genes[i + nofGenes - cutMin] = chars[i];
	}

	delete[] chars;
}

float Chromosome::CalculateFitness()
{
	fitness = 0;
	for (int i = 0; i < nofGenes; i++)
	{
		if (word[i] == genes[i])
		{
			fitness++;
		}
	}
	return fitness;
}

Chromosome::~Chromosome()
{
}
