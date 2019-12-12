// MonkeyProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	int popSize = 10;
	Population* p = new Population(popSize);

	int generation = 0;
	for (int i = 0; i < 5000; i++)
	{
		p->CreateNewPopulation();
		//cout << "i : " << i << "\n";
		//Print(p, popSize);
		generation++;
		if (p->GetStop())
			i = 9999999999;
	}

	cout << "Generations: " << generation << "\n";
	p->PrintBest();

}
