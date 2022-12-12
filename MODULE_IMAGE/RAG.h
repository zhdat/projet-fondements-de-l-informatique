#include "image.h"

typedef struct RAG * rag;

extern rag create_RAG(image, int n, int m);

static void init_moments_priv(rag,int,int);

static void init_father_priv(rag);

static void init_neighbors_priv(rag,int,int);

static init_partition_error_priv(rag);