#include "image.h"

typedef struct RAG * rag;

extern rag create_RAG(image img, int n, int m);

static void init_moments_priv(rag,int n,int m);

static void init_father_priv(rag);

static void init_neighbors_priv(rag,int n,int m);

static void init_partition_error_priv(rag);