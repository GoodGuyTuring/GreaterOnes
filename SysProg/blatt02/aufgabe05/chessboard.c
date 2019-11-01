/*     board_t: int visited_fields
 *              int** fields: nxn array
 *              int[2] springerposi
*      int init_board(struct board_t* chess_board, size_t n, int start_x, int start_y)
 *      void free_board(struct board_t *b)
 *          gibt speicher wieder frei
 *      void new_jump(struct board_t* b, int x, int y)
 *      void remove_jump(struct board_t* b, int x, int y)
 *      int isfree(struct board_t* b, int x, int y)
 *          prüft, ob sprungziel frei / existent
 *      int visited_fields(struct board_t* b)
 *          liefert anzahl der besuchten felder
*       void print_board(struct board_t * b)
 *          printed aktuelles Schachfeld aus wie in pdf*/

#include <stdio.h>
#include <stdlib.h>

struct board_t {
    int** fields;
    int size;
    int knight_pos[2];
    int visited_fields;
};

int init_board(struct board_t* b, int n, int x, int y){
    //init size
    b -> size = n;

    //allocate memory for 2d array
    b -> fields = malloc(n * sizeof(int*));
    if(b->fields == NULL){
        return 1;
    }

    for(int i = 0; i < n; i++){
        (b->fields)[i] = malloc(n * sizeof(int));
        if((b->fields)[i] == NULL)
            return 1;
    }
    //b -> fields = (int*) malloc(n* n * sizeof(int));

    //initialize 2d array with zeros
    for(int i = 0; i< n; i++){
        for(int j = 0; j < n; j++){
            (b->fields)[i][j] = 0;
        }
    }
    // starting position in 2d array := 1, visited fields = 1
    b->fields[x][y] = 1;
    b->visited_fields = 1;

    //init knight pos
    b -> knight_pos[0] = x;
    b -> knight_pos[1] = y;
    return 0;
}

void free_board(struct board_t *b){
    //free every subarray of 2d array
    for(int i = 0; i < b -> size; i++){
        free((b->fields)[i]);
    }
    //free normal vars
    free(b->fields);
}

void new_jump(struct board_t *b, int x, int y){
    // inc visited fields and set field in 2d array to step count
    (b -> fields)[(b->knight_pos)[0]+x][(b->knight_pos)[1]+y] = ++(b->visited_fields);

    // renew knight_pos
    (b -> knight_pos)[0] += x;
    (b -> knight_pos)[1] += y;
}

void remove_jump(struct board_t *b, int x, int y){
    //remove old mark in field
    (b -> fields)[(b -> knight_pos)[0]][(b -> knight_pos)[1]] = 0;

    //refresh knight pos
    (b->knight_pos)[0] -= x;
    (b->knight_pos)[1] -= y;

    //dec visited_fields
    (b->visited_fields) --;

}

int isfree(struct board_t *b, int x, int y){
    // new might be position
    int new_x = (b -> knight_pos)[0] + x;
    int new_y = (b -> knight_pos)[1] + y;

    // index out of bounds
    if(new_x >= b -> size || new_y >= b ->size || new_x < 0 || new_y < 0)
        return 0;

    // knight was already on future position
    if((b->fields)[new_x][new_y] != 0)
        return 0;

    return 1;
}

int visited_fields(struct board_t *b){
    return b->visited_fields;
}

void print_board(struct board_t *b){

    //first line
    printf("+");
    for(int i = 0; i < b -> size; i++){
        printf("---+");
    }
    printf("\n");

    for(int i = 0; i < b -> size; i++){
        printf("+");
        //lines with field content
        for(int j = 0; j < b-> size; j++){
            printf("%3i+", (b->fields)[i][j]);
        }
        printf("\n+");

        //separation between lines
        for(int i = 0; i < b -> size; i++){
            printf("---+");
        }
        printf("\n");
    }

}