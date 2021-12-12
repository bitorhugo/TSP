//
// Created by Vitor Hugo on 28/11/2021.
//

#include "ag.h"

//------------------AG-------------------------//

void intialize_genetic_algorithm (COUNTRY *country, int num_iterations, int size_population, int num_elitism, float mutation_probability) {
    GENERATION *head = NULL;
    int AG_count = 1;

    while (AG_count <= num_iterations) {
        GENERATION *current_generation = insert_generation(&head, true);
        if (AG_count == 0) {
            current_generation->parent = create_initial_population(country, size_population);
            current_generation->child = create_next_population(current_generation->parent, num_elitism, mutation_probability);
        }
        else {
            
        }
        current_generation->id = AG_count;
        AG_count ++;
    }

}

//------------------GENERATION-------------------------//

GENERATION* insert_generation (GENERATION **head, bool at_head) {

    GENERATION *new_generation = allocate_memory_generation();

    if (is_generation_list_empty(head))
        at_head = true;


    if (at_head) {
        new_generation->next_generation = *head;
        *head = new_generation;
    }
    else {
        GENERATION *temp_generation = *head;
        while (temp_generation != NULL) {
            temp_generation = temp_generation->next_generation;
        }
        temp_generation->next_generation = new_generation;
    }

    return new_generation;

}

GENERATION * allocate_memory_generation() {
    GENERATION *new_generation = calloc(1, sizeof(GENERATION));
    return new_generation;
}

int is_generation_list_empty(GENERATION **head) {
    return head == NULL;
}

//------------------POPULATION-------------------------//

POPULATION *create_initial_population (COUNTRY *country_to_visit, int size_of_population) {

    POPULATION *new_population = allocate_memory_population();
    new_population->num_of_cromossomas = size_of_population;
    insert_cromossomas (new_population, country_to_visit);
    sort_cromo_by_fitness(new_population);
    return new_population;
}

POPULATION* create_next_population (POPULATION *old_population, int elitism_amount, float mutation_prob) {

    parent_selection(old_population, elitism_amount);

    int num_child = old_population->num_of_cromossomas - elitism_amount; // elitism chromosomes
    num_child /= 2; // fitness_proportional chromosomes

    CROMOSSOMA *temp_cromo;
    for (size_t i = 0; i < num_child; ++i) {
        temp_cromo = old_population->cromossomas + elitism_amount + num_child;

        CROMOSSOMA *parent_one = old_population->cromossomas + i;
        CROMOSSOMA *parent_two = parent_one + elitism_amount;

        temp_cromo = cross_over(parent_one, parent_two);
    }

    mutation(old_population, mutation_prob);

    return old_population;
}

//------------------CROMO-------------------------//

void insert_cromossomas (POPULATION *population, COUNTRY *country) {

    population->cromossomas = allocate_memory_cromossomas(population->num_of_cromossomas);
    CROMOSSOMA *temp_cromo;
    for (int i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        temp_cromo->num_of_genes = country->size_trip_cities;
        insert_gene (temp_cromo, country);
        shuffle_genes(temp_cromo, temp_cromo->num_of_genes);
        temp_cromo->fitness_value = fitness(temp_cromo);
    }

}

//------------------GENE-------------------------//

void insert_gene (CROMOSSOMA *cromo, COUNTRY *arr_of_countries) {
    cromo->genes = allocate_memory_genes(cromo->num_of_genes);
    GENE *temp_gene;
    CITY *temp_city;
    for (int i = 0; i < cromo->num_of_genes; i++) {
        temp_gene = cromo->genes + i;
        temp_city = arr_of_countries->cities + i;
        temp_gene->id = i;
        temp_gene->x = temp_city->coordinates->x;
        temp_gene->y = temp_city->coordinates->y;
    }
}

//------------------FITNESS-------------------------//

void sort_cromo_by_fitness (POPULATION *population) {
    // Selection Sort used due to low amount of values to compare
    CROMOSSOMA *a;
    CROMOSSOMA *b;
    for (int i = 0; i < population->num_of_cromossomas - 1; ++i) {
        for (int j = i + 1; j < population->num_of_cromossomas; ++j) {
            a = population->cromossomas + i;
            b = population->cromossomas + j;
            if (b->fitness_value > a->fitness_value) {
                swap_cromo(a, b);
            }

        }
    }

}

float fitness (CROMOSSOMA *cromo) {
    float sum = 0;
    GENE *temp_gene;
    for (size_t i = 0; i < cromo->num_of_genes; ++i) {
        temp_gene = cromo->genes + i;
        GENE *a = temp_gene;
        GENE *b = temp_gene + 1;
        if (i == cromo->num_of_genes - 1) // a = c0, b = c1, ..., a = c5, b = c0
            b = cromo->genes;
        sum += euclidean_dist(a, b);
    }
    return ((float)1 / sum);
}

float sum_population_fitness (POPULATION *population){
    float sum = 0;
    CROMOSSOMA *temp_cromo;
    for (size_t i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        sum += temp_cromo->fitness_value; // fitness_value of each individual
    }
    return sum;
}

//------------------CROSSOVER-------------------------//

CROMOSSOMA* cross_over (CROMOSSOMA *parent_one, CROMOSSOMA *parent_two) {

    // choose random non-repeating numbers from parent one
    int num_of_random_numbers = parent_one->num_of_genes / 2;
    CROMOSSOMA *child = parent_one; // copies parent_one
    child->fitness_value = 0; // makes sure that fitness value is 0
    shuffle_genes(child, child->num_of_genes); // shuffles genes
    child->num_of_genes = num_of_random_numbers;

    // fill the rest of child_cromo with parent_tow genes
    int flag = 0;
    for (size_t i = 0; i < parent_two->num_of_genes ; ++i) {
        GENE *temp_parent = parent_two->genes + i;
        for (size_t j = 0; j < child->num_of_genes; ++j) {
            GENE *temp_child = child->genes + j;
            if (temp_parent->id == temp_child->id) {
                flag = 1;
                break;
            }
        }
        if (flag != 1) {
            GENE *temp_child = child->genes + child->num_of_genes;
            *temp_child = *temp_parent;
            child->num_of_genes += 1;
        }
        if (child->num_of_genes == parent_two->num_of_genes) break;
        flag = 0;
    }
    return child;
}

void parent_selection (POPULATION *population, int elitism_amount) {
    CROMOSSOMA *temp_cromo;

    // via elitism n chromosomes with the best fitness stay to be crossed-over
    for (size_t i = elitism_amount; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        temp_cromo = fitness_proportional_selection(population);
    }

}

CROMOSSOMA* fitness_proportional_selection (POPULATION *population) {

    float roulette [population->num_of_cromossomas];
    float sum_Aj = sum_population_fitness(population);

    CROMOSSOMA *temp_cromo;
    for (size_t i = 0; i < population->num_of_cromossomas; ++i) { // roulette
        temp_cromo = population->cromossomas + i;
        roulette [i] = temp_cromo->fitness_value / sum_Aj;

        float p_range = float_rand(0.0f, 1.0f);
        if (p_range >= roulette[i]){
            return temp_cromo;
        }
    }

}

//------------------MUTATION-------------------------//

void mutation (POPULATION * population, float mutation_prob) {

    int random_gene_index = 0;

    CROMOSSOMA *temp_cromo;
    for (size_t i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        GENE *temp_gene;
        for (size_t j = 0; i < temp_cromo->num_of_genes; ++j) {
            temp_gene = temp_cromo->genes + j;
            float p_range = float_rand(0.0f, 1.0f);
            if (p_range < mutation_prob) {
                do {
                    random_gene_index = int_rand(0, temp_cromo->num_of_genes - 1);
                }
                while (random_gene_index == i);
                swap_gene(temp_gene, temp_cromo->genes + random_gene_index);
            }
        }

    }

}

//------------------ALLOCATE-------------------------//

POPULATION *allocate_memory_population() {
    POPULATION *new_pop = calloc(1, sizeof(POPULATION));
    if (new_pop == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POPULATION\n");
    return new_pop;
}

CROMOSSOMA *allocate_memory_cromossomas(int size) {
    CROMOSSOMA *new_cromo = calloc(size, sizeof(CROMOSSOMA));
    if (new_cromo == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR CROMOSSOMA\n");
    return new_cromo;
}

GENE *allocate_memory_genes(int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    if (new_gene == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR GENE\n");
    return new_gene;
}

//------------------AUX-------------------------//

void shuffle_genes (CROMOSSOMA *cromo, int size) {
    if (size > 1) { // has to have more than one value for swap to occur
        for (size_t i = 0; i < size - 1; ++i) {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            // swap
            GENE t = *(cromo->genes + j);
            *(cromo->genes + j) = *(cromo->genes + i);
            *(cromo->genes + i) = t;
        }
    }
}

float euclidean_dist (GENE* first, GENE *second) {
    return sqrtf(powf(second->x - first->x, 2) + powf(second->y - first->y, 2));
}

void swap_cromo (CROMOSSOMA *a, CROMOSSOMA *b) {
    CROMOSSOMA temp = *a;
    *a = *b;
    *b = temp;
}

void swap_gene (GENE *a, GENE *b) {
    GENE temp = *a;
    *a = *b;
    *b = temp;
}

