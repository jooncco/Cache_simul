#include "cache_simul.h"

int main()
{
    config_();
    run();
}

/*********************** driver function ***********************/
void run() {
    /* file open */
    FILE *fd = fopen(INPUT_PATH,"r");
    if (fd == NULL) {
        printf("[ERROR] file open error. (IN)\n");
        exit(EXIT_FAILURE);
    }

    /* read instructions */
    char line[15];
    while ( fgets(line, sizeof(line), fd) ) {
        n_op++;

        /* parsing */
        char op[LEN_OP/8*2+1];      // 1 byte takes 2 digits of hex string.
        memcpy( op, line, LEN_OP/8*2 );
        op[LEN_OP/8*2] = '\0';

        /* search for the block */
        unsigned cur_tag = get_tag(op);
        unsigned cur_idx = get_blk_idx(op);
        if ( find_blk(cur_tag, cur_idx, total_cycle) ) {
            // HIT
            n_hit++;
            total_cycle++;      // update total cycle time
        }
        else {
            // MISS
            n_miss++;
            total_cycle += ( 10 + BLOCK_SIZE );         // update total cycle time
            place_block(cur_tag, cur_idx, total_cycle); // place the missing block
        }

        // if the operation WORD is "FFFFFFFF", print the report and terminate.
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
    LEN_OP = WORD_SIZE*8;       // 1 byte = 8 bits.

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

    // printf("Config status: %d, %d, %d, %d\n", LEN_OP, LEN_BLOCK_OFFSET, LEN_BLOCK_IDX, LEN_TAG);
}

ull hex_to_long(char* hex) {

    /* This function convers hex string into long integer. (up to 2^64) */
    ull val=0;
    while (*hex) {
        unsigned byte = *hex++;
        if ( byte >= '0' && byte <= '9' ) byte = byte-'0';
        else if ( byte >= 'a' && byte <= 'f' ) byte = byte-'a'+10;
        else if ( byte >= 'A' && byte <= 'F' ) byte = byte-'A'+10;

        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

unsigned get_tag(char* op) {

    /* This function extracts TAG value from instruction hex string */
    const ull op_int = hex_to_long(op);
    int lsb = LEN_BLOCK_OFFSET + LEN_BLOCK_IDX;
    unsigned val=0;
    int idx=0;
    while ( lsb+idx < 32 ) {
        if ( op_int & ( 1 << (lsb+idx) ) ) val += ( 1 << idx );
        idx++;
    }
    return val;
}

unsigned get_blk_idx(char* op) {

    /* This function extracts BLOCK INDEX value from instruction hex string */
    const ull op_int = hex_to_long(op);
    int lsb = LEN_BLOCK_OFFSET;
    unsigned val=0;
    int idx=0;
    while ( lsb+idx < LEN_BLOCK_OFFSET + LEN_BLOCK_IDX ) {
        if ( op_int & ( 1 << (lsb+idx) ) ) val += ( 1 << idx );
        idx++;
    }
    return val;
}

unsigned get_blk_offset(char* op) {

    /* This function extracts BLOCK OFFSET value from instruction hex string */
    const ull op_int = hex_to_long(op);
    int lsb = 0;
    unsigned val=0;
    int idx=0;
    while ( lsb+idx < LEN_BLOCK_OFFSET ) {
        if ( op_int & ( 1 << (lsb+idx) ) ) val += ( 1 << idx );
        idx++;
    }
    return val;
}

bool find_blk(unsigned cur_tag, unsigned cur_idx, ull cur_cycle) {

    bool flag=0;
    for (int way = 0; way < N_WAY; way++)
        if ( v[way][cur_idx] && tag[way][cur_idx] == cur_tag ) {
            /* if the block is in cache, update the last visited time. */
            flag=1;
            updated[way][cur_idx] = cur_cycle;
        }
    return flag;
}

void place_block(unsigned cur_tag, unsigned cur_idx, ull cur_cycle) {

    unsigned way_victim;
    ull      way_oldest_cycle=LONG_MAX;
    for (int way = 0; way < N_WAY; way++)
        if ( !v[way][cur_idx] && !tag[way][cur_idx] ) {     // empty block found
            v[way][cur_idx] = 1;
            tag[way][cur_idx] = cur_tag;
            updated[way][cur_idx] = cur_cycle;
            return;
        }
        else {
            if ( way_oldest_cycle > updated[way][cur_idx] ) {
                way_oldest_cycle = updated[way][cur_idx];
                way_victim = way;
            }
        }

    /* All ways are FULL. Kick out the oldest block */
    v[way_victim][cur_idx] = 1;
    tag[way_victim][cur_idx] = cur_tag;
    updated[way_victim][cur_idx] = cur_cycle;       // update newly 'in' time
}

void print_report() {

    /* file open */
    FILE *fd = fopen(OUT_PATH,"r");
    if (fd == NULL) {
        printf("[ERROR] file open error. (OUT)\n");
        exit(EXIT_FAILURE);
    }

    fprintf (fp, "This is line\n",);

    /* close file */
    fclose(fd);
}

/******************************/