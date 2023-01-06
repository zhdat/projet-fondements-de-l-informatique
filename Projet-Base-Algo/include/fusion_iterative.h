#ifndef FUSION_ITERATIVE_H
#define FUSION_ITERATIVE_H
#include "moment.h"
#include "RAG.h"
#include "image.h"
#include "point.h"
#include "type_obj.h"

void perform_merge(rag r, double seuil);

image create_output_image(rag r, int n, int m);
#endif
