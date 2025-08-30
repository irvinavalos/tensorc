#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define EXIT_SIZE -1
#define EXIT_MALLOC -2

typedef struct Matrix {
  size_t rows;
  size_t cols;
  double *data;
  int ref_count;
  struct Matrix *parent;
} Matrix;

double rand_double(double lo, double hi);

int mat_alloc(Matrix **mat, size_t ro, size_t co);

void mat_free(Matrix *mat);

int mat_alloc_ref(Matrix **dst, Matrix *src, size_t off, size_t ro, size_t co);

void mat_set(Matrix *src, size_t ro, size_t co, double val);

double mat_get(const Matrix *src, size_t ro, size_t co);

void mat_rand(Matrix *mat, unsigned int seed, double lo, double hi);

#endif // MATRIX_H
