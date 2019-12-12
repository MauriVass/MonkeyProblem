#pragma once
#include "Chromosome.h"
#include <vector>

class Population
{
public:
	Population(int popSize);
	std::vector<Chromosome> GetChromosomes();
	void SortPopulation();
	void CreateNewPopulation();
	void PrintBest();
	bool GetStop();
	~Population();

private:
	int populationSize;
	int topChromosomes;

	int bestFitness;
	char* bestChromosome;
	bool stop;

	char* word;
	int nCharacter;
	std::vector<Chromosome> chromosomes;
	
};

