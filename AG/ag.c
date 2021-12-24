//
// Created by Vitor Hugo on 28/11/2021.
//

#include "ag.h"

//------------------AG-------------------------//

void intialize_genetic_algorithm (COUNTRY *country, int num_iterations, int size_population, int num_elitism, float mutation_probability) {
    GENERATION *head = NULL;
    uint32_t AG_count = 1;

    if (size_population % 2 != 0 || size_population == 0) {
            fprintf(stderr, "ERROR: POPULATION SIZE MUST BE PAIR AND POSITIVE\n");
            return;
    }
    if (num_elitism % 2 != 0 || num_elitism >= country->size_trip_cities) {
            fprintf(stderr, "ERROR: ELITISM NUMBER MUST BE PAIR AND SMALLER THAN NUMBER OF GENES\n");
            return;
    }

    GENERATION *next_generation = NULL;
    GENERATION *current_generation = NULL;

    while (AG_count <= num_iterations) {

        current_generation = next_generation;
        if (AG_count == 1) { // checks if is first generation
            current_generation = insert_generation(&head, false);
            current_generation->parent = create_initial_population(country, size_population);
        }
        current_generation->child = create_next_population(*current_generation->parent, num_elitism, mutation_probability);
        next_generation = insert_generation(&head, false);
        next_generation->parent = current_generation->child;

        insert_fittest_chromosomes(current_generation);
        current_generation->id = AG_count;
        AG_count += 1;
    }
    printf ("Best route to take: \n");
    GENE *temp_gene;
    for (size_t i = 0; i < country->size_trip_cities; ++i) {
        temp_gene = current_generation->parent->chromosomes->genes + i;
        printf("City %d (x: %.2f, y: %.2f)\n", temp_gene->id, temp_gene->x, temp_gene->y);
    }

    free_generation_list(&head);
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
        while (temp_generation->next_generation != NULL) {
            temp_generation = temp_generation->next_generation;
        }
        temp_generation->next_generation = new_generation;
    }

    return new_generation;

}

GENERATION* search_generation (GENERATION **head, uint32_t generation_id) {
    if (is_generation_list_empty(head)) {
        fprintf(stderr, "ERROR: NO GENERATIONS FOUND\n");
        return NULL;
    }

    GENERATION *temp_generation = *head;

    while (temp_generation != NULL) {
        if (temp_generation->id == generation_id) {
            printf("Generation %d found.\n", temp_generation->id);
            return temp_generation;
        }

        temp_generation = temp_generation->next_generation;
    }
    fprintf(stderr, "ERROR: GENERATION NOT FOUND\n");
    return NULL;
}

GENERATION* search_generation_via_fitness (GENERATION **head, int fitness_value) {
    if (is_generation_list_empty(head)) {
        fprintf(stderr, "ERROR: NO GENERATIONS FOUND\n ");
        return NULL;
    }

    GENERATION *temp_generation = *head;

    while (temp_generation != NULL) {

        temp_generation = temp_generation->next_generation;
    }
    fprintf(stderr, "ERROR: GENERATIONS WITH FITNESS VALUE OVER %d NOT FOUND\n", fitness_value);
    return NULL;
}

GENERATION * allocate_memory_generation() {
    GENERATION *new_generation = calloc(1, sizeof(GENERATION));
    return new_generation;
}

int is_generation_list_empty(GENERATION **head) {
    return *head == NULL;
}

void free_generation_list (GENERATION **head) {
    GENERATION *temp_generation = NULL;

    while (*head != NULL) {
        temp_generation = *head;
        *head = temp_generation->next_generation;
        free(temp_generation);
    }
}

//------------------POPULATION-------------------------//

POPULATION* create_initial_population (COUNTRY *country_to_visit, int size_of_population) {

    POPULATION *new_population = allocate_memory_population();
    new_population->num_of_chromosomes = size_of_population;
    insert_cromossomas (new_population, country_to_visit);
    sort_cromo_by_fitness(new_population);
    return new_population;
}

POPULATION* create_next_population (POPULATION population, int elitism_amount, float mutation_prob) {

    POPULATION *new_population = allocate_memory_population();
    *new_population = population;

    parent_selection(new_population, elitism_amount);
    breed_population(new_population, elitism_amount);
    mutation(new_population, mutation_prob);

    for (size_t i = 0; i < new_population->num_of_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = new_population->chromosomes + i;
        temp_chromo->fitness_value = fitness(temp_chromo);
    }

    return new_population;
}

//------------------CROMO-------------------------//

void insert_cromossomas (POPULATION *population, COUNTRY *country) {

    population->chromosomes = allocate_memory_cromossomas(population->num_of_chromosomes);
    CHROMOSOME *temp_chromo;
    for (int i = 0; i < population->num_of_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;
        temp_chromo->num_of_genes = country->size_trip_cities;
        insert_gene (temp_chromo, country);
        shuffle_genes(temp_chromo, temp_chromo->num_of_genes);
        temp_chromo->fitness_value = fitness(temp_chromo);
    }

}

void insert_fittest_chromosomes (GENERATION* generation) {
    generation->fittest_chromosomes = allocate_memory_cromossomas(2);
    CHROMOSOME *temp_chromo;
    for (size_t i = 0; i < 2; ++i) {
        temp_chromo = generation->fittest_chromosomes + i;
        CHROMOSOME *temp_fittest = generation->parent->chromosomes + i;
        *temp_chromo = *temp_fittest;
    }
}

//------------------GENE-------------------------//

void insert_gene (CHROMOSOME *cromo, COUNTRY *arr_of_countries) {
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
    CHROMOSOME *a;
    CHROMOSOME *b;
    for (int i = 0; i < population->num_of_chromosomes - 1; ++i) {
        for (int j = i + 1; j < population->num_of_chromosomes; ++j) {
            a = population->chromosomes + i;
            b = population->chromosomes + j;
            if (b->fitness_value > a->fitness_value) {
                swap_cromo(a, b);
            }

        }
    }

}

float fitness (CHROMOSOME *cromo) {
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
    CHROMOSOME *temp_chromo;
    for (size_t i = 0; i < population->num_of_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;
        sum += temp_chromo->fitness_value; // fitness_value of each individual
    }
    return sum;
}

//------------------CROSSOVER-------------------------//

void breed_population (POPULATION *population, int elitism_amount) {

    CHROMOSOME *temp_chromo;
    CHROMOSOME *parent_one;
    CHROMOSOME *parent_two;
    POPULATION *population_after_breeding = allocate_memory_population();
    *population_after_breeding = *population;

    for (size_t i = elitism_amount; i < population->num_of_chromosomes; ++i) {
        parent_one = population->chromosomes + i;
        parent_two = population->chromosomes + population->num_of_chromosomes - i - 1;
        temp_chromo = cross_over(parent_one, parent_two);
        *(population_after_breeding->chromosomes + i) = *temp_chromo;
    }

    *population = *population_after_breeding;

    free (population_after_breeding);

}

CHROMOSOME* cross_over (CHROMOSOME *parent_one, CHROMOSOME *parent_two) {

    // choose random non-repeating numbers from parent one
    int num_of_random_numbers = parent_one->num_of_genes / 2;
    CHROMOSOME *child = parent_one; // copies parent_one
    child->fitness_value = 0; // makes sure that fitness value is 0
    shuffle_genes(child, child->num_of_genes); // shuffles genes
    child->num_of_genes = num_of_random_numbers;

    // fill the rest of child_cromo with parent_two genes
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

    float cumulative_prob [population->num_of_chromosomes];
    calculate_cumulative_prob(population, cumulative_prob);

    CHROMOSOME *temp_chromo;
    // via elitism n chromosomes with the best fitness stay to be crossed-over
    for (size_t i = elitism_amount; i < population->num_of_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;
        temp_chromo = fitness_proportional_selection(population, cumulative_prob);
    }

}

CHROMOSOME* fitness_proportional_selection (POPULATION *population, const float *cumulative_prob) {

    float p_range = float_rand(0.0f, 1.0f);

    for (size_t i = 1; i < population->num_of_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population->chromosomes + i;
        if (p_range <= cumulative_prob[i] && p_range > cumulative_prob [i - 1]) {
            return temp_chromo;
        }
    }
    return population->chromosomes; // return first chromo
}

//------------------MUTATION-------------------------//

void mutation (POPULATION * population, float mutation_prob) {

    int random_gene_index = 0;

    CHROMOSOME *temp_chromo;
    for (size_t i = 0; i < population->num_of_chromosomes; ++i) {
        temp_chromo = population->chromosomes + i;
        GENE *temp_gene;
        for (size_t j = 0; j < temp_chromo->num_of_genes; ++j) {
            temp_gene = temp_chromo->genes + j;
            float p_range = float_rand(0.0f, 1.0f);
            if (p_range < mutation_prob) {
                do {
                    random_gene_index = int_rand(0, temp_chromo->num_of_genes - 1);
                }
                while (random_gene_index == i);
                swap_gene(temp_gene, temp_chromo->genes + random_gene_index);
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

CHROMOSOME *allocate_memory_cromossomas(int size) {
    CHROMOSOME *new_chromo = calloc(size, sizeof(CHROMOSOME));
    if (new_chromo == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR CROMOSSOMA\n");
    return new_chromo;
}

GENE *allocate_memory_genes(int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    if (new_gene == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR GENE\n");
    return new_gene;
}

//------------------AUX-------------------------//

void shuffle_genes (CHROMOSOME *chromo, int size) {
    if (size > 1) { // has to have more than one value for swap to occur
        for (size_t i = 0; i < size - 1; ++i) {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            // swap
            GENE t = *(chromo->genes + j);
            *(chromo->genes + j) = *(chromo->genes + i);
            *(chromo->genes + i) = t;
        }
    }
}

float euclidean_dist (GENE* first, GENE *second) {
    return sqrtf(powf(second->x - first->x, 2) + powf(second->y - first->y, 2));
}

void swap_cromo (CHROMOSOME *a, CHROMOSOME *b) {
    CHROMOSOME temp = *a;
    *a = *b;
    *b = temp;
}

void swap_gene (GENE *a, GENE *b) {
    GENE temp = *a;
    *a = *b;
    *b = temp;
}

void calculate_cumulative_prob(POPULATION *population, float *cumulative_prob) {

    float sum_Aj = sum_population_fitness(population);
    float roulette [population->num_of_chromosomes];

    CHROMOSOME *temp_chromo;
    for (size_t i = 0; i < population->num_of_chromosomes; ++i) { // roulette
        temp_chromo = population->chromosomes + i;
        roulette[i] = temp_chromo->fitness_value / sum_Aj;
        if (i > 0) cumulative_prob [i] = roulette [i] + cumulative_prob [i - 1]; // cumulative probability
        else cumulative_prob [i] = roulette [i];
    }

}

