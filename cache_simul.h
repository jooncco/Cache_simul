#ifndef CACHE_SIMUL_H_
#define CACHE_SIMUL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;

/**************** CONFIG ****************/
#define FILE_PATH "./ART.txt"
#define CACHE_SIZE 4        /* Cache size in KBs */
#define BLOCK_SIZE 1        /* Block size in WORDs */
#define N_WAY      1        /* Associativity level */
#define WORD_LEN   4        /* WORD size in Bytes */
#define N_BLOCKS   CACHE_SIZE*1024/(WORD_LEN*BLOCK_SIZE)    // # of blocks in cache
const char* TERMINATE = "FFFFFFFF";
/*****************************************/





/************ globals ************/
// Common
int tag[N_BLOCKS]={0};
int n_hit=0, n_miss=0;
int n_op=0;
ll  total_cycle=0;

// LRU

/*********************************/

/************ utils ************/
// Common
int get_tag(char* op);
int get_blk_idx(char* op);
int get_blk_offset(char* op);
void print_report();

// LRU

/******************************/

/** driver function **/
void run();
/*********************/

#endif