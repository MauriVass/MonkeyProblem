# Monkey Problem
How long would it take to an infinity number of monkeys randomly typing on a keyboard to write a sentence like: "MonkeyProblem" or "To be or not to be"?.. Long time, maybe an infinite amount of time.  

Instead, this problem can be easily solved with genetic algorithms.

# Main Aspects:
- **Gene**: encoding of the problem (a gene is a single character in this case).
- **Chromosome**: a set of genes.
  - **Fitness**: how much a chromosome is near to the solution.
  - **Mutation**: Chromosomes can mutate, one of their genes is changed.
  - **Inversion**: Chromosomes can be inverted (the genes are divided into groups and these groups are reversed)
  - **CrossOver**: Two chromosomes can crossover to create two new children (offspring) with genes similar to their parents.
- **Population**: a set of chromosomes.

In the beginning, the population is a set of randomly generated chromosomes, among these the most fitted have more probability to be chosen to mutate, inverted or crossed over with some other chromosome; meanwhile, the lowest fitted ones are replaced by the new ones.
In this way, at each iteration, the population approaches the solution until it reaches it. 
