#ifndef CACHE_SIMUL_H_
#define CACHE_SIMUL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
typedef unsigned long long ull;

/**************** CONFIG ****************/
#define INPUT_PATH "./ART.txt"
#define OUT_PATH   "./report.txt"
#define WORD_SIZE  4        /* WORD size in Bytes */
#define CACHE_SIZE 4        /* Cache size in KBs */
#define BLOCK_SIZE 1        /* Block size in WORDs */
#define N_WAY      1        /* Associativity level */

#define N_BLOCKS   CACHE_SIZE*1024/(WORD_SIZE*BLOCK_SIZE)    // # of blocks in cache
const char* TERMINATE = "FFFFFFFF";
/*****************************************/



/************ globals ************/
// Common
unsigned LEN_OP, LEN_TAG, LEN_BLOCK_IDX, LEN_BLOCK_OFFSET;  // sub-division info
unsigned tag[N_WAY][N_BLOCKS]={0};
unsigned v[N_WAY][N_BLOCKS]  ={0};
ull      n_hit=0, n_miss=0;
ull      n_op=0;
ull      total_cycle=0;

// LRU
ull      updated[N_WAY][N_BLOCKS]={0};

/*********************************/

/************ utils ************/
// Common
void      config_();
ull       hex_to_long(char* hex);
unsigned  get_tag(char* op);
unsigned  get_blk_idx(char* op);
unsigned  get_blk_offset(char* op);
void      print_report();

// LRU
bool      find_blk(unsigned cur_tag, unsigned cur_idx, ull cur_cycle);
void      place_block(unsigned cur_tag, unsigned cur_idx, ull cur_cycle);

/******************************/

/** driver function **/
void run();
/*********************/

#endif