#include "image.h"

typedef struct RAG * rag;

extern rag create_RAG(image img, int n, int m);

static void init_moments_priv(rag r,int n,int m);

static void init_father_priv(rag r);

static void init_neighbors_priv(rag r,int n,int m);

static void init_partition_error_priv(rag r);

extern double RAG_give_closest_region(rag r, int * i, int * j);

void RAG_merge_regions(rag r, int i, int j);