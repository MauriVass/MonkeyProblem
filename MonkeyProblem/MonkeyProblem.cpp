#include "pch.h"
#include "Chromosome.h"
#include "Population.h"
#include <iostream>
using namespace std;

void Print(Population* p, int popSize) {
	vector<Chromosome> chroms = p->GetChromosomes();
	for (int i = 0; i < popSize; i++)
	{
		chroms[i].Print();
	}
}

int main()
{
	//The population size should be large: the larger the faster the algorithm can find a good solution, but it would take a lot of power.
	//A good number for the population size is >100
	int popSize = 1000;
	Population* p = new Population(popSize);

	int generation = 0;
	int maxNumGeneration = 50000;
	for (int i = 0; i < maxNumGeneration; i++)
	{
		p->CreateNewPopulation();

		//DEBUG (it shows all the chromosomes in the current population)
		//cout << "i : " << i << "\n";
		//Print(p, popSize);

		generation++;
		if (p->GetStop())
			i = maxNumGeneration;
	}

	cout << "Generations: " << generation << "\n";
	p->PrintBest();
}
