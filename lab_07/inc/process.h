#ifndef PROCESS_H__
#define PROCESS_H__

#include <stdio.h>

#include "bin_tree.h"
#include "avl_tree.h"
#include "hash_table.h"

int read_avl(FILE *f, avl_t **avl);

int read_tree(FILE *f, tree_t **tree);

int read_hash(FILE *f, hash_t **tree);

int read_str(char **buf);

#endif