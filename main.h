#ifndef MAIN_H_
#define MAIN_H_

/**************** CONFIG ****************/
#define FILE_PATH "./ART.txt"
#define CACHE_SIZE 4        /* Cache size in KBs */
#define BLOCK_SIZE 1        /* Block size in WORDs */
#define N_WAY      1        /* Associativity level */
#define WORD_LEN   4        /* WORD size in Bytes */
#define N_BLOCKS   CACHE_SIZE*1024/(WORD_LEN*BLOCK_SIZE)    // # of blocks in cache
/*****************************************/

#endif