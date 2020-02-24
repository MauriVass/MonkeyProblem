#include "pch.h"
#include "Population.h"
#include <iostream>
#include <algorithm>
using namespace std;

//This Population class contains all information about the chromosomes and the best solution found.
//It also contains methods to generate a new population from the current one.

Population::Population(int popSize)
{
	populationSize = popSize;
	//Keep top 20% Chromosomes
	topChromosomes = populationSize * 0.2f;
	acceptWorseSolution = false;

	bestFitness = -1;
	stop = false;

	//Case 1
	const int n = 51;
	word = new char[n + 1]{ "Monkey Problem solved with Genetic Algorithm->(GA)." };
	
	//Case 2
	/*const int n = 15;
	word = new char[n + 1]{ "Monkey Problem." };
	*/
	nCharacter = n;

	//Initialize population generating the first chromosomes
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

//Sort the population according to the increasing chromosomes' fitness
void Population::SortPopulation()
{
	std::sort(chromosomes.begin(), chromosomes.end(), [](Chromosome & one, Chromosome & two) {return one.CalculateFitness() > two.CalculateFitness(); });
	float fitness = chromosomes[0].CalculateFitness();
	if (fitness > bestFitness)
	{
		bestFitness = fitness;
		bestChromosome = chromosomes[0].GetGenes();
		cout << "Better found\t";
		for (int i = 0; i < nCharacter; i++)
		{
			cout << bestChromosome[i];
		}
		cout << "\tfitness: " << bestFitness <<  "\n";
	}
	//Stopping condition
	if (bestFitness==nCharacter)
	{
		stop = true;
	}
}

//Create a new population using the current population
void Population::CreateNewPopulation()
{
	//Sort the population in order to have easy access to the best chromosomes
	SortPopulation();

	//Initialize some variables
	Chromosome* c1 = new Chromosome(nCharacter,word, false);
	Chromosome* c2 = new Chromosome(nCharacter,word, false);
	vector<Chromosome> offsping;

	int n1, n2, counter = 0;

	//There are different ways to generate a new population:
	//At the beginning you should use crossover a lot,
	//then reaching the end you should use more mutation

	//In this case I use only crossover, it works fine but when the sentence is almost complete(one or two characters are different)
	//it slows down and it takes lot of generations to find the first complete solution.

	/*Given a population: (kind of)
	- 1/5 are the top Chromosomes, these will not be changed,
	- 1/5 are generated with Crossover between top Chromosomes
	- 1/5 are generated with Crossover between any Chromosomes
	- 1/5 are generated with Inversion of top Chromosomes
	- 1/5 are generated as new Chromosomes
	*/	

	/*Actually: (Better performance among the tried values)
	-20% top Chromosomes are unchanged
	-60%(topChromosomes / 2 * 3) are crossed over between top Chromosomes
	-20% are crossed over between any Chromosomes
	*/

	//Crossover between top Chromosomes
	for (int j = 0; j < topChromosomes / 2 * 3; j++)
	{
		//Choose two random numbers in range [0,topChromosomes)
		n1 = rand() % (topChromosomes);
		n2 = rand() % (topChromosomes);
		//Generate new offspring
		offsping = chromosomes[n1].CrossOver(chromosomes[n2]);
		c1 = &(offsping.at(0));
		c2 = &(offsping.at(1));
		//Add the new children in the population if they are better then the chromosome the will be replaced
		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness()) {
			chromosomes.at(topChromosomes + counter) = *c1;
		}
		counter++;

		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c2->CalculateFitness()){
			chromosomes.at(topChromosomes + counter) = *c2;
		}

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

		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness()) {
			chromosomes.at(topChromosomes + counter) = *c1;
		}
		counter++;

		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c2->CalculateFitness()){
			chromosomes.at(topChromosomes + counter) = *c2;
		}
		counter++;
	}

	//Inversion on a random top Chromosome
	/*for (int j = 0; j < topChromosomes / 2; j++)
	{
		n1 = rand() % (topChromosomes);

		c1 = &chromosomes.at(n1);
		c1->Inversion();

		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness()) {
			chromosomes.at(topChromosomes + counter) = *c1;
		}
		counter++;
	}*/

	//Create new Chromosome and apply inversion
	/*for (int j = 0; j < topChromosomes/2; j++)
	{
		Chromosome* c = new Chromosome(nCharacter,word);
		c->Inversion();
		if (acceptWorseSolution || chromosomes.at(topChromosomes + counter).CalculateFitness() <= c1->CalculateFitness()) {
			chromosomes.at(topChromosomes + counter) = *c;
		}
		counter++;
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
