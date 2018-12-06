#include "cache_simul.h"

int main()
{
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
        char op[WORD_LEN*2+1];
        memcpy( op, line, WORD_LEN*2 );
        op[WORD_LEN*2] = '\0';

        // do whatever


        if ( !strcmp( op , TERMINATE ) ) { print_report(); break; }
    }

    /* close file */
    fclose(fd);
    exit(EXIT_SUCCESS);
}
/************************************************************************************/


/************ utils ************/
int get_tag(char* op) {};
int get_blk_idx(char* op) {};
int get_blk_offset(char* op) {};
void print_report() {

    printf("END.\n");
}

/******************************/