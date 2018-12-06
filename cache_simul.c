#include "cache_simul.h"

int main()
{
    config_();
    run();
}

/*********************** driver function ***********************/
void run() {
    /* file open */
    FILE *fd = fopen(FILE_PATH,"r");
    if (fd == NULL) {
        printf("[ERROR] file open error. Check file path.\n");
        exit(EXIT_FAILURE);
    }

    /* read instructions */
    char line[15];
    while ( fgets(line, sizeof(line), fd) ) {
        n_op++;

        /* parsing */
        char op[WORD_SIZE*2+1];
        memcpy( op, line, WORD_SIZE*2 );
        op[WORD_SIZE*2] = '\0';

        // do whatever
        get_tag(op);

        if ( !strcmp( op , TERMINATE ) ) { print_report(); break; }
    }

    /* close file */
    fclose(fd);
    exit(EXIT_SUCCESS);
}
/************************************************************************************/


/************ utils ************/
void config_() {

    /* calculate LENGTH of instructuions. */
    LEN_OP = WORD_SIZE*2;       // 1 byte takes 2 hexadigits.

    int i;
    /* calculate LEN_BLOCK_OFFSET */
    i=0;
    while ( pow(2,i) < BLOCK_SIZE*WORD_SIZE*8 ) i++;
    LEN_BLOCK_OFFSET = i;

    /* calculate LEN_BLOCK_IDX */
    i=0;
    while ( pow(2,i) < N_BLOCKS ) i++;
    LEN_BLOCK_IDX = i;

    /* calculate LEN_TAG */
    LEN_TAG = LEN_OP - ( LEN_BLOCK_IDX + LEN_BLOCK_OFFSET );
}

int get_tag(char* op) {

    strlen(op); // 8
};
int get_blk_idx(char* op) {};
int get_blk_offset(char* op) {};
void print_report() {

    printf("END.\n");
}

/******************************/