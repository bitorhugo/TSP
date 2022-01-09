//
// Created by Vitor Hugo on 28/12/2021.
//

#include "generation.h"
#include <stdio.h>

/*
 * Private prototypes
 */
void parent_selection(POPULATION *population, int num_elitism);

void calculate_cumulative_probability(POPULATION *population, float *cumulative_prob_arr);

float sum_population_fitness(POPULATION *population);

CHROMOSOME fitness_selection(POPULATION population, const float *cumulative_prob);

float float_in_range(float min, float max);

void breed(POPULATION *population, int num_elitism);

CHROMOSOME copy_chromosome(CHROMOSOME chromosome);

CHROMOSOME cross_over(CHROMOSOME *parent_one, CHROMOSOME *parent_two);

POPULATION mutation(POPULATION population, float mutation_prob);

int int_in_range(int min, int max);

void swap_gene(GENE *a, GENE *b);

/*
 * Public implementations
 */
POPULATION insert_first_population(const COUNTRY *booked_trip, int size_population) {
    // create population
    POPULATION new_population = {0};

    // set size of population
    new_population.num_chromosomes = size_population;

    // insert chromosomes that build the population
    insert_chromosomes(&new_population, booked_trip);

    // sort chromosomes by fitness value
    sort_chromosomes_by_fitness(&new_population);

    return new_population;
}

POPULATION insert_child_population(GENERATION *generation, int num_elitism, float mutation_prob) {
    // create population
    POPULATION new_population = deep_copy_population(&generation->parent_population);

    // choose parent chromosomes for breeding
    parent_selection(&new_population, num_elitism);

    // breed population using cross-over method
    breed(&new_population, num_elitism); // TODO: FIND NUM_GENES BUG

    // mutate population
    new_population = mutation(new_population, mutation_prob);

    // sort chromosomes by fitness value
    sort_chromosomes_by_fitness(&new_population);

    return new_population;
}

POPULATION deep_copy_population(POPULATION *population) {
    // create population
    POPULATION new_population = {0};

    // set size of population
    new_population.num_chromosomes = population->num_chromosomes;

    // allocate memory for chromosomes
    new_population.chromosomes = allocate_memory_chromosome(new_population.num_chromosomes);

    // insert chromosomes that build the population
    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        // set pointers for each chromosome for each population
        CHROMOSOME *temp_chromo_old = population->chromosomes + i;
        CHROMOSOME *temp_chromo_new = new_population.chromosomes + i;

        // set number of genes
        temp_chromo_new->num_genes = population->chromosomes->num_genes;

        // allocate memory for genes
        temp_chromo_new->genes = allocate_memory_gene(temp_chromo_new->num_genes);

        for (size_t j = 0; j < population->chromosomes->num_genes; ++j) {
            // set coordinates and id for each gene
            GENE *temp_gene_old = temp_chromo_old->genes + j;
            GENE *temp_gene_new = temp_chromo_new->genes + j;

            // set gene values
            temp_gene_new->id = temp_gene_old->id;
            temp_gene_new->x = temp_gene_old->x;
            temp_gene_new->y = temp_gene_old->y;
        }

        // calculate fitness value of chromosome
        temp_chromo_new->fitness_value = calculate_fitness(temp_chromo_new);
    }

    return new_population;
}

/*
 * Private implementations
 */
void parent_selection(POPULATION *population, int num_elitism) {

    /*
     * Selection can be performed via:
     * fitness selection (Roulette Wheel)
     * Elitism (most fit chromosomes pass onto next generation automatically)
     */

    // holds the sum of each chromosome probability to be selected
    float cumulative_prob[population->num_chromosomes]; // create local array to not allocate memory for it
    calculate_cumulative_probability(population, cumulative_prob);

    /*
     * if any chromosome is to be passed via elitism
     * we start to iterate from next chromosome to it
    */

    // copy population to select chromosomes from
    POPULATION temp_population = deep_copy_population(population);

    // choose chromosomes
    CHROMOSOME *temp_chromo;
    for (size_t i = num_elitism; i < population->num_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;
        *temp_chromo = fitness_selection(temp_population, cumulative_prob);
    }

}

void calculate_cumulative_probability(POPULATION *population, float *cumulative_prob_arr) {
    /*
     * Probability is calculated via the formula
     * Pi = Ai / ∑Aj
     * Pi = probability of each chromosome
     * Ai = fitness of each chromosome
     * ∑Aj = sum of all chromosomes fitness
     */

    // ∑Aj
    float sum_chromosome_fitness = sum_population_fitness(population);

    /*
     * We can think about the sum_prob as a roulette
     * Each section of the roulette represent the chance (percentage)
     * of being chosen
     */
    float roulette[population->num_chromosomes];

    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population->chromosomes + i;
        // calculate prob of each chromosome
        roulette[i] = temp_chromo->fitness_value / sum_chromosome_fitness;
        // calculate cumulative probability of each chromosomes
        if (i < 1) {
            cumulative_prob_arr[i] = roulette[i];
        } else {
            cumulative_prob_arr[i] = roulette[i] + cumulative_prob_arr[i - 1];
        }
    }
}

float sum_population_fitness(POPULATION *population) {
    float sum = 0;
    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population->chromosomes + i;
        sum += temp_chromo->fitness_value;
    }
    return sum;
}

CHROMOSOME fitness_selection(POPULATION population, const float *cumulative_prob) {
    // range acts like the spinning mechanism of roulette
    float range = float_in_range(0.0f, 1.0f);

    // iterate over population to find chromosome selected
    for (size_t i = 1; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        if (range <= cumulative_prob[i] && range > cumulative_prob[i - 1]) {
            return *temp_chromo;
        }
    }

    return *population.chromosomes; // return first chromosome if failed
}

float float_in_range(float min, float max) {
    float scale = rand() / (float) RAND_MAX;
    return min + scale * (max - min);
}

void breed(POPULATION *population, int num_elitism) {
    /*
     * Cross-over is done by combining n parent chromosomes
     * i.e.
     * CHROMOSOME n0 * CHROMOSOME n1 = CHROMOSOME (n0 * n1)
     * CHROMOSOME n1 * CHROMOSOME n2 = CHROMOSOME (n1 * n2)
     * ...
     * CHROMOSOME nx * CHROMOSOME n0 = CHROMOSOME (nx * n0)
     */

    // save first chromo for successful cross-over
    CHROMOSOME saved_chromo = copy_chromosome(*population->chromosomes);

    CHROMOSOME *parent_one = NULL;
    CHROMOSOME *parent_two = NULL;
    CHROMOSOME *temp_chromo;
    // select parent one and parent two
    for (size_t i = num_elitism; i < population->num_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;

        parent_one = temp_chromo;
        if (i == population->num_chromosomes - 1) {
            // set parent_two address to saved_chromo address otherwise address of parent two == parent_one
            parent_two = &saved_chromo;
        } else {
            parent_two = temp_chromo + 1;
        }

        *temp_chromo = cross_over(parent_one, parent_two);
    }

}

CHROMOSOME copy_chromosome(CHROMOSOME chromosome) {
    // create chromosome
    CHROMOSOME new_chromosome;

    // set number of genes and fitness value
    new_chromosome.num_genes = chromosome.num_genes;
    new_chromosome.fitness_value = chromosome.fitness_value;

    // allocate memory for genes
    new_chromosome.genes = allocate_memory_gene(new_chromosome.num_genes);

    // set values for each gene
    for (size_t i = 0; i < new_chromosome.num_genes; ++i) {
        GENE *temp_gene_new = new_chromosome.genes + i;
        GENE *temp_gene_old = chromosome.genes + i;

        temp_gene_new->id = temp_gene_old->id;
        temp_gene_new->x = temp_gene_old->x;
        temp_gene_new->y = temp_gene_old->y;
    }

    return new_chromosome;
}

CHROMOSOME cross_over(CHROMOSOME *parent_one, CHROMOSOME *parent_two) {
    // Copy parent_one
    CHROMOSOME *child = parent_one;

    // Set initial fitness value
    child->fitness_value = 0;

    // Shuffle genes to choose random indices
    shuffle_genes(child);

    /*
     * Set number of genes to half
     * This equates to parent one genes that were selected
     * to stay in chromosome
     */
    child->num_genes = parent_one->num_genes / 2;

    // Fill the rest of chromosome with parent_two genes
    int flag = 0;
    for (size_t i = 0; i < parent_two->num_genes; ++i) {
        GENE *temp_parent = parent_two->genes + i;
        for (size_t j = 0; j < child->num_genes; ++j) {
            GENE *temp_child = child->genes + j;
            if (temp_parent->id == temp_child->id) {
                flag = 1;
                break;
            }
        }
        if (flag != 1) {
            GENE *temp_child = child->genes + child->num_genes;
            *temp_child = *temp_parent;
            child->num_genes += 1;
        }
        if (child->num_genes == parent_two->num_genes) {
            break;
        }
        flag = 0;
    }
    return *child;
}

POPULATION mutation(POPULATION population, float mutation_prob) {
    // create random index to be selected
    int random_gene_index = 0;

    /*
     * For each gene of each chromosome calculate a random value
     * to compare to the mutation probability value
     * If mutation prob is bigger than random value
     * mutate chromosome by swapping its genes
     */
    for (size_t i = 0; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        for (size_t j = 0; j < temp_chromo->num_genes; ++j) {
            GENE *temp_gene = temp_chromo->genes + j;
            float p_range = float_in_range(0.0f, 1.0f);
            if (p_range < mutation_prob) {
                do {
                    // random gene index must be different than current gene index
                    random_gene_index = int_in_range(0, temp_chromo->num_genes - 1);
                } while (random_gene_index == j);
                swap_gene(temp_gene, temp_chromo->genes + random_gene_index);
            }
        }

        // calculates fitness value of chromosome
        temp_chromo->fitness_value = calculate_fitness(temp_chromo);
    }
    return population;
}

int int_in_range(int min, int max) {
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

void swap_gene(GENE *a, GENE *b) {
    GENE temp = *a;
    *a = *b;
    *b = temp;
}