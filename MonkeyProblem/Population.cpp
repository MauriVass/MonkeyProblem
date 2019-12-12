#include "pch.h"
#include "Population.h"
#include <iostream>
#include <algorithm>
using namespace std;

Population::Population(int popSize)
{
	populationSize = popSize;
	//Keep top 20% Chromosomes
	topChromosomes = populationSize * 0.2f;

	bestFitness = -1;
	stop = false;

	const int n = 51;
	word = new char[n + 1]{ "Monkey Problem solved with Genetic Algorithm->(GA)." };
	nCharacter = n;

	for (int i = 0; i < populationSize; i++)
	{
		Chromosome* c = new Chromosome(nCharacter,word);
		c->Mutation();
		chromosomes.push_back(*c);
	}
}


vector<Chromosome> Population::GetChromosomes()
{
	return chromosomes;
}

void Population::SortPopulation()
{
	std::sort(chromosomes.begin(), chromosomes.end(), [](Chromosome & one, Chromosome & two) {return one.CalculateFitness() > two.CalculateFitness(); });
	if (chromosomes[0].CalculateFitness()>bestFitness)
	{
		bestFitness = chromosomes[0].CalculateFitness();
		bestChromosome = chromosomes[0].GetGenes();
		cout << "Better found\t";
		for (int i = 0; i < nCharacter; i++)
		{
			cout << bestChromosome[i];
		}
		cout << "\n";
	}
	if (bestFitness==nCharacter)
	{
		stop = true;
	}
}

void Population::CreateNewPopulation()
{
	SortPopulation();
	Chromosome* c1 = new Chromosome(nCharacter,word, false);
	Chromosome* c2 = new Chromosome(nCharacter,word, false);
	vector<Chromosome> offsping;

	int n1, n2, counter = 0;

	/*Given a population size of 20: (kind of)
	- 1/5 are the top Chromosomes, these will not be changed,
	- 1/5 are generated with Crossover between top Chromosomes
	- 1/5 are generated with Crossover between any Chromosomes
	- 1/5 are generated with Inversion of top Chromosomes
	- 1/5 are generated as new Chromosomes
	*/	

	//Crossover between top Chromosomes
	for (int j = 0; j < topChromosomes/2*3; j++)
	{
		n1 = rand() % (topChromosomes);
		n2 = rand() % (topChromosomes);
		offsping = chromosomes[n1].CrossOver(chromosomes[n2]);
		c1 = &(offsping.at(0));
		c2 = &(offsping.at(1));
		if (chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness())
			chromosomes.at(topChromosomes + counter) = *c1;
		counter++;

		if (chromosomes.at(topChromosomes + counter).CalculateFitness() <= c2->CalculateFitness())
			chromosomes.at(topChromosomes + counter) = *c2;
		counter++;
	}

	//Crossover between any Chromosomes
	for (int j = 0; j < topChromosomes/2; j++)
	{
		n1 = rand() % (populationSize);
		n2 = rand() % (populationSize);
		offsping = chromosomes[n1].CrossOver(chromosomes[n2]);
		c1 = &(offsping.at(0));
		c2 = &(offsping.at(1));

		if (chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness()) 
			chromosomes.at(topChromosomes + counter) = *c1;
		counter++;

		if (chromosomes.at(topChromosomes + counter).CalculateFitness() <= c2->CalculateFitness())
			chromosomes.at(topChromosomes + counter) = *c2;
		counter++;
	}

	/*for (int j = 0; j < topChromosomes / 2; j++)
	{
		n1 = rand() % (topChromosomes);

		c1 = &chromosomes.at(n1);
		c1->Inversion();

		if (chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness())
			chromosomes.at(topChromosomes + counter) = *c1;
		counter++;
	}*/

	/*for (int j = 0; j < topChromosomes/2; j++)
	{
		Chromosome* c = new Chromosome(nCharacter,word);
		c->Inversion();
		chromosomes.at(topChromosomes + counter++) = *c;
	}*/
}

void Population::PrintBest()
{
	if (stop)
		cout << "PROBLEM SOLVED \n";
	cout << "Best solution found: fitness: " << bestFitness << "\n";
	for (int i = 0; i < nCharacter; i++)
	{
		cout << bestChromosome[i];
	}
}

bool Population::GetStop()
{
	return stop;
}

Population::~Population()
{
}
