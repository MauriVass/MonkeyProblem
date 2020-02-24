#include "pch.h"
#include "Chromosome.h"
#include <iostream>
#include <stdlib.h>
#include<ctime>
using namespace std;

//The Chromosome class is a solution (good or bad). A chromosome has a set of genes of type char.
//A chromosome can be mutated(one genes if changed) or inverted(the genes are divided in parts and these parts are reversed)
//Two chromosomes can crossover to create two new children(offspring) with genes similar to their parents.

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

//Returns a copy of the current genes
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
	//Select one random gene
	int index = rand() % nofGenes;

	//Change it with a different one
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

	//Decide how many cuts will be according with the sentence length
	int nofCuts = 1;
	if (nofGenes > 10)
		nofCuts = 2;

	int cutMin, cutMax = 0;
	if (nofCuts == 2)
	{
		cutMin = 1 + rand() % (nofGenes / 2 - 1);
		cutMax = cutMin + 1 + rand() % (nofGenes / 2 - 2);
	}
	else {
		cutMin = 1 + rand() % (nofGenes - 1);
	}

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

	int cutMin, cutMax = 0;
	if (nofCuts == 2)
	{
		cutMin = 1 + rand() % (nofGenes / 2 - 1);
		cutMax = cutMin + 1 + rand() % (nofGenes / 2 - 2);
	}
	else {
		cutMin = 1 + rand() % (nofGenes - 1);
	}

	//Copy old genes
	char* chars = new char[nofGenes];
	for (int i = 0; i < nofGenes; i++)
		chars[i] = genes[i];


	if (nofCuts == 1)
	{
		for (int i = 0; i < nofGenes - (cutMin + cutMax); i++)
			genes[i] = chars[i + cutMin + cutMax];
		for (int i = nofGenes - (cutMin + cutMax); i < nofGenes; i++)
			genes[i] = chars[i - (nofGenes - (cutMin + cutMax))];
	}
	else if (nofCuts == 2) {
		//Character after cutMax are placed at the beginning of new genes
		for (int i = cutMax; i < nofGenes; i++)
			genes[i - cutMax] = chars[i];
		//Character between cutMin and cutMax are not moved
		for (int i = cutMin; i < cutMax; i++)
			genes[i + nofGenes - cutMax - 2] = chars[i];
		//Character before cutMin are placed at the end of new genes
		for (int i = 0; i < cutMin; i++)
			genes[i + nofGenes - cutMin] = chars[i];
	}

	delete[] chars;
}

//The fitness is calculated as an integer between 0 and nofGenes
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
