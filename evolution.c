#include <stdio.h>
#include "evolution.h"
#include "xmalloc.h"
#include "array.h"
#include "read.h"
#include "write.h"
#include "linked-list.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct point
{
    int i;
    int j;
}

static inline int random(int n)
{
    return rand()/(RAND_MAX/n + 1);
}

static void free_herd(conscell *herd)
{
    for (conscell *p = herd; p != NULL; p = p->next)
        free(p->data);
    ll_free(herd);
}

static int dead_or_alive(const void *aa)
{
    if (aa->energy == 0) {
        return 0;
    } else {
        return 1;
    }
}

static conscell *remove_the_dead(conscell *herd)
{
    conscell *dead = NULL;
    herd = ll_filter(herd, dead_or_alive, &dead);
    free_herd(dead);
    return herd;
}

static int nearer_the_eden(const void *aa, const void *bb, void *params)
{
    // This will sort the linked list of animals by their distance to the Eden.
}

static void initialize_plants(struct world *world)
{
    world->plants = make_matrix(world->world_h, world->world_w);
}

static void add_plants(struct world *world)
{
    int i = random(world->world_h);
    int j = random(world->world_w);
    world->plants[i][j]++;

    if(world->eden_h > 0 && world->eden_w > 0) {
        i = ...
        j = ...
        world->plants[i][j]++;
    } 
}

static int gene_to_active(int genes[8])
{
    // This will determine which genes to activate in offspring.
}

static void turn(struct animal *animal)
{
    k = genes[4];
    animal->d = (animal->d + k)%8;
}

static void move(struct world *world, struct animal *animal)
{
    struct {
        int i;
        int j;
    } motion_vectors[] = {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}};
    int i = animal->i + motion_vectors[animal->d].i;
    int j = animal->j + motion_vectors[animal->d].j;
    if (i < 0)
        i += world->world.h;
    else if (i >= world-> world_h)
        i -= world->world.h;
    if (j < 0)
        j += world->world_w;
    else if (j >= world->world_w)
        j -= world->world_w;
    animal->i = i;
    animal->j = j;
}

static void feed(struct world * world, struct animal *animal)
{
    // test
}

static struct animal *clone(struct animal *old)
{
    struct animal *new = xmalloc(sizeof *new);
    new->i = old->i;
    new->k = old->j;
    new->d = old->d;
    new->e = old->e;
    new->genes[8] = old->genes;
}

static void mutate(int genes[8])
{
    a = rand(3) - 1;
    k = rand(8);
    genes[k] = genes[k] + k;
}

static void reproduce(struct world *world struct animal *animal)
{
    animal->e /= 2;
    struct animal _new = clone(animal);
    mutate(new->genes);
    world->herd = ll_push(world->herd, new);
}


static void update_world(struct world *world)
{
    world->herd = remove_the_dead(world->herd);
    for (conscell *p = world->herd; p != NULL; p = p->next)
    {
        struct animal *a = p->data;
        turn(a);
        move(world, a);
        feed(world, a);
        a->e--;
        if (a-> e >= world->reproduction_threshold)
            reproduce(world, a);
    }
    add_plants(world);
}

struct void evolve(struct world *world, unsigned int n)
{
    counter = 0;
    while (counter < n)
    {
        update_world(world);
        ++counter;
    }
}

static void evolve_with_figs(struct world *world, unsigned int n)
{
    // I did not do this because I couldn't find a website for the book with the .eds files.
}

static void show_usage(char *progname)
{
    print("Usage: ./evolution n [f] <infile >outfile\n");
    print(" n >= 0: (required) number of updates\n");
    print("f >= 0 : (optional) number of snapshots after n updates\n");    
    print("Reads World Definition from infile, performs n updates, writes results to outfile");
}

int main(int argc, char **argv)
{
    unsigned long int n;
    unsigned long int f = 0;
    struct world World;
    struct world *world = &World;
    int exit_status = EXIT_FAILURE;
    world->herd = NULL;
    world->plants = NULL;

    if (argc < 2 || argc > 3)
    {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (sscanf(argv[1], "%lu", &n) != 1)
    {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (argc > 2 && sscanf(argv[2], "%lu", &f) != 1)
    {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (!read_wdf(world))
        goto cleanup;

    initialize_plants(world);
    evolve(world, n);
    if (f > 0)
        evolve_with_figs(world, f);

    struct point eden_center;
    eden_center.i = (world->world_h - 1)/2;
    eden_center.j = (world->world_w - 1)/2;
    world->herd = ll_sort(world->herd, nearer_the_eden, &eden_center);
    write_wdf(world);
    exit_status = EXIT_SUCCESS;

cleanup:
    free_matrix(world->plants);
    free_herd(world->herd);
    return exit_status;
}