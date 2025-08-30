#include "matrix.h"

double rand_double(double lo, double hi) {
  double range = (hi - lo);
  return lo + (rand() / (RAND_MAX / range));
}

int mat_allocate(Matrix **mat, size_t ro, size_t co) {
  if (ro == 0 || co == 0) {
    return EXIT_SIZE;
  }

  Matrix *new_mat = (Matrix *)malloc(sizeof(Matrix));

  if (new_mat == NULL) {
    return EXIT_MALLOC;
  }

  new_mat->data = (double *)calloc(ro * co, sizeof(double));

  if (new_mat->data) {
    free(new_mat);
    return EXIT_MALLOC;
  }

  new_mat->rows = ro;
  new_mat->cols = co;
  new_mat->parent = NULL;
  new_mat->ref_count = 1;

  *mat = new_mat;

  return 0;
}

void mat_free(Matrix *mat) {
  if (mat == NULL) {
    return;
  }

  if (mat->parent == NULL) {
    mat->ref_count -= 1;
    if (mat->ref_count == 0) {
      free(mat->data);
      free(mat);
    }
  } else {
    mat_free(mat->parent);
    free(mat);
  }
}

int mat_alloc_ref(Matrix **dst, Matrix *src, size_t off, size_t ro, size_t co) {
  if (ro == 0 || co == 0) {
    return EXIT_SIZE;
  }

  Matrix *new_mat = (Matrix *)malloc(sizeof(Matrix));

  if (new_mat == NULL) {
    return EXIT_MALLOC;
  }

  new_mat->data = src->data + off;
  new_mat->rows = ro;
  new_mat->cols = co;
  new_mat->parent = src;
  new_mat->ref_count = 0;

  src->ref_count += 1;

  *dst = new_mat;

  return 0;
}

void mat_set(Matrix *src, size_t ro, size_t co, double val) {
  src->data[ro * src->cols + co] = val;
}

double mat_get(const Matrix *src, size_t ro, size_t co) {
  return src->data[ro * src->cols + co];
}

void matrix_rand(Matrix *mat, unsigned int seed, double lo, double hi) {
  srand(seed);

  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      mat_set(mat, i, j, rand_double(lo, hi));
    }
  }
}
