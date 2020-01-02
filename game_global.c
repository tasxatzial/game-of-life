/* Game of life */
/* Implementation using global variables */

#include <stdio.h>
#include <stdlib.h>

void load_world_from_file(char *);
void save_world_to_file(char *);
void next_generation();
int get_next_state(int x, int y);
int count_neighbors(int x, int y);
void unload_world();

/* the current world and the world after one generation */
char **world, **next_world;

/* fixed x,y dimensions of the worlds */
int worldX, worldY;

int main(int argc, char **argv) {
    int i;

    if (argc != 3) {
        printf("./a.out input_file output_file\n");
        return 0;
    }
    
    load_world_from_file(argv[1]);

    /* advance world by 50 generations */
    for (i = 0; i < 50; i++) {
        next_generation();
    }
    
    save_world_to_file(argv[2]);

    unload_world();

    return 0;
}

/* Reads a world from the specified filename and allocates
 * the required memory both for current and next generation worlds.
 * 
 * 4 additional 1-dimensional arrays are allocated for the cells
 * that surround the world. These cells are always dead during the simulation
 * (value = 0), as a result the world never expands
 * outside the specified grid (indicated by the first line in each input file)
 */
void load_world_from_file(char *filename) {
    FILE *fp;
    int i, j, state;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening input file %s\n", filename);
        exit(-1);
    }

    /* read world dimensions */
    fscanf(fp, "%d %d", &worldX, &worldY);
    getc(fp);

    /* allocate 1st dimension of the world and next_world (includes the
    surrounding cells) */
    world = malloc((worldX + 2) * sizeof(char *));
    if (world == NULL) {
        printf("main alloc in current world");
        exit(-1);
    }
    next_world = malloc((worldX + 2) * sizeof(char *));
    if (next_world == NULL) {
        printf("main alloc in next world");
        exit(-1);
    }

    /* allocate 2nd dimension of world and next_world (includes the
    surrounding cells */
    for (i = 0; i < worldX + 2; i++) {
        world[i] = malloc((worldY + 2) * sizeof(char));
        if (world[i] == NULL) {
            printf("line %d alloc in current world", i);
            exit(-1);
        }
        next_world[i] = malloc((worldY + 2) * sizeof(char));
        if (next_world[i] == NULL) {
            printf("line %d alloc in next world", i);
            exit(-1);
        }
    }
    
    /* initialize the surrounding cells of world and next_world to 0 */
    for (i = 0; i < worldX + 2; i++) {
        world[i][0] = world[i][worldY + 1] =
            next_world[i][0] = next_world[i][worldY + 1] = 0;

    }
    for (j = 0; j < worldY + 2; j++) {
        world[0][j] = world[worldX + 1][j] =
            next_world[0][j] = next_world[worldX + 1][j] = 0;
    }

    /* initialize the rest of the world from file data */
    for (i = 1; i < worldX + 1; i++) {
        for (j = 1; j < worldY + 1; j++) {
            getc(fp);
            (getc(fp) == '*') ? (world[i][j] = 1) : (world[i][j] = 0);
        }
        getc(fp);
        getc(fp);
    }
   
    fclose(fp);
}

/* Saves the world to the file indicated by the specified filename.
 * The surrounding cells are not saved (they are not part of the world)
 */
void save_world_to_file(char *filename) {
    FILE *fp;
    int i, j;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening output file %s\n", filename);
        exit(-1);
    }

    fprintf(fp, "%d %d\n", worldX, worldY);
    for (i = 1; i < worldX + 1; i++) {
        for (j = 1; j < worldY + 1; j++) {
            putc('|', fp);
            (world[i][j] == 1) ? putc('*', fp) : putc(' ', fp); 
        }
        putc('|', fp);
        putc('\n', fp);
    }
    fclose(fp);
}

/* Calculates the state of cells in the next world and swaps current and
 * next world.
 * The surrounding cells are always dead, their state is always 0 (dead).
 */
void next_generation() {
    int i, j;
    char **world_tmp;
    
    for (i = 1; i < worldX + 1; i++) {
        for (j = 1; j < worldY + 1; j++) {
            next_world[i][j] = get_next_state(i, j);
        }
    }
    world_tmp = world;
    world = next_world;
    next_world = world_tmp;
}

/* Calculates and returns the new state of a single cell.
 * Returns 0 if in the new world the cell is dead, 1 otherwise.
 */
int get_next_state(int x, int y) {
    int neightbours = count_neighbors(x, y);

    return (neightbours == 3 || (neightbours == 2 && world[x][y] == 1)) ? 1 : 0;
}

/* Returns the number of neighbors of a single cell that is not a
 * surrounding cell of the world.
 */
int count_neighbors(int x, int y) {
    if (x <= 0 || y <= 0 || x >= worldX + 1 || y >= worldY + 1) {
        printf("(%d, %d) does not have 8 neighbors\n", x, y);
        exit(-1);
    }
    return world[x - 1][y] + world[x + 1][y] + world[x][y - 1]
            + world[x][y + 1] + world[x - 1][y - 1] + world[x + 1][y + 1]
            + world[x + 1][y - 1] + world[x - 1][y + 1];
}

/* Frees the allocated memory for both current and next world.
 */
void unload_world() {
    int i;

    for (i = 0; i < worldX + 2; i++) {
        free(world[i]);
        free(next_world[i]);
    }
    free(world);
    free(next_world);
}