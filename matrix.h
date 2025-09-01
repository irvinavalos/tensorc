#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
  size_t n_row;
  size_t n_col;
  size_t n_ele;
  double *data;
  size_t ref_count;
  struct matrix *parent;
  ptrdiff_t stride_row;
  ptrdiff_t stride_col;
} matrix;

int allocate_matrix(matrix **mat, size_t row, size_t col);

int allocate_ref_matrix(matrix **dst, matrix *src, size_t row, size_t col,
                        size_t offset);

void deallocate_matrix(matrix *mat);

void free_matrix(matrix **mat);

static inline double *ele_ptr(const matrix *mat, size_t row, size_t col) {
  return mat->data + (ptrdiff_t)row * mat->stride_row +
         (ptrdiff_t)col * mat->stride_col;
}

static inline const double *ele_cptr(const matrix *mat, size_t row, size_t col) {
  return mat->data + (ptrdiff_t)row * mat->stride_row +
         (ptrdiff_t)col * mat->stride_col;
}

int mat_set(matrix *mat, size_t row, size_t col, double val);

double mat_get(const matrix *mat, size_t row, size_t col);

void print_matrix(const matrix *mat);

#endif // MATRIX_H
