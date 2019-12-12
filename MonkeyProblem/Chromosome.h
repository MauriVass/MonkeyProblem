#pragma once
#include <vector>
class Chromosome
{
public:
	Chromosome(int nofGene,	char* word, bool initialize = true);
	~Chromosome();

	void Print();

	char* GetGenes();
	void SetGenes(char* genes);
	
	void Mutation();
	std::vector<Chromosome> CrossOver(Chromosome parent2);
	void Inversion();

	float CalculateFitness();

private:
	int nofGenes;
	char* genes;
	float fitness;

	char* word;
	char GenerateChar();
};

