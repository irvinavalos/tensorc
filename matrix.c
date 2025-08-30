#include "matrix.h"

double rand_double(double low, double high) {
  double range = (high - low);
  return low + (rand() / (RAND_MAX / range));
}

int mat_allocate(Matrix **mat, size_t rows, size_t cols) {
  if (rows < 0 || cols < 0) {
    return EXIT_SIZE;
  }

  Matrix *new_mat = malloc(sizeof(Matrix));

  if (new_mat == NULL) {
    return EXIT_MALLOC;
  }

  new_mat->data = calloc(rows * cols, sizeof(double));

  if (new_mat->data) {
    free(new_mat);
    return EXIT_MALLOC;
  }

  new_mat->rows = rows;
  new_mat->cols = rows;
  new_mat->parent = NULL;
  new_mat->ref_count = 1;

  *mat = new_mat;

  return EXIT_SUCCESS;
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
    } else {
      mat_free(mat->parent);
      free(mat);
    }
  }
}

int mat_alloc_ref(Matrix **dst, Matrix *src, size_t offset, size_t row,
                  size_t col) {
  if (row < 0 || col < 0) {
    return EXIT_SIZE;
  }

  Matrix *new_mat = malloc(sizeof(Matrix));

  if (new_mat == NULL) {
    return EXIT_MALLOC;
  }

  new_mat->data = src->data + offset;
  new_mat->rows = row;
  new_mat->cols = col;
  new_mat->parent = src;

  src->ref_count += 1;

  *dst = new_mat;

  return EXIT_SUCCESS;
}

void mat_set(Matrix *src, size_t row, size_t col, double val) {
  src->data[row * src->cols + col] = val;
}

double mat_get(const Matrix *src, size_t row, size_t col) {
  return src->data[row * src->cols + col];
}

void matrix_rand(Matrix *mat, unsigned int seed, double low, double high) {
  srand(seed);

  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
    }
  }
}
