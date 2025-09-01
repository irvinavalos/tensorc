#include "matrix.h"

int allocate_matrix(matrix **mat, size_t row, size_t col) {
  if (mat == NULL) {
    return -1;
  }
  if (*mat != NULL) {
    return -1;
  }
  if (row == 0 || col == 0) {
    return -1;
  }
  if (row > SIZE_MAX / col) {
    return -2;
  }
  matrix *t_mat = malloc(sizeof(*t_mat));
  if (t_mat == NULL) {
    return -2;
  }
  t_mat->data = calloc((size_t)(row * col), sizeof(*(t_mat->data)));
  if (t_mat->data == NULL) {
    free(t_mat);
    return -2;
  }
  t_mat->n_row = row;
  t_mat->n_col = col;
  t_mat->n_ele = (size_t)row * col;
  t_mat->ref_count = 1;
  t_mat->parent = NULL;
  t_mat->stride_row = (ptrdiff_t)col;
  t_mat->stride_col = 1;
  *mat = t_mat;
  return 0;
}

int allocate_ref_matrix(matrix **dst, matrix *src, size_t row, size_t col,
                        size_t offset) {
  if (dst == NULL || src == NULL) {
    return -1;
  }
  if (*dst != NULL) {
    return -1;
  }
  if (row == 0 || col == 0) {
    return -1;
  }
  if (src->data == NULL) {
    return -2;
  }
  matrix *t_mat = malloc(sizeof(*t_mat));
  if (t_mat == NULL) {
    return -2;
  }
  t_mat->data = src->data + (ptrdiff_t)offset;
  t_mat->n_row = row;
  t_mat->n_col = col;
  t_mat->n_ele = (size_t)row * col;
  t_mat->ref_count = 1;
  t_mat->parent = src;
  t_mat->stride_row = src->stride_row;
  t_mat->stride_col = src->stride_col;
  if (src->stride_col == 1 && src->stride_row == (ptrdiff_t)src->n_col) {
    size_t parent_ele = src->n_row * src->n_col;
    if (offset >= parent_ele) {
      free(t_mat);
      return -1;
    }
    size_t last = offset + (row - 1) * (size_t)src->n_col + (col - 1);
    if (last >= parent_ele) {
      free(t_mat);
      return -1;
    }
  }
  src->ref_count++;
  *dst = t_mat;
  return 0;
}

void deallocate_matrix(matrix *mat) {
  if (mat == NULL) {
    return;
  }
  if (--mat->ref_count > 0) {
    return;
  }
  if (mat->parent != NULL) {
    deallocate_matrix(mat->parent);
  } else {
    free(mat->data);
  }
  free(mat);
}

void free_matrix(matrix **mat) {
  if (mat == NULL || *mat == NULL) {
    return;
  }
  deallocate_matrix(*mat);
  *mat = NULL;
}

int mat_set(matrix *mat, size_t row, size_t col, double val) {
  if (mat == NULL || mat->data == NULL) {
    return -1;
  }
  if (row == 0 || col == 0) {
    return -1;
  }
  *ele_ptr(mat, row, col) = val;
  return 0;
}

double mat_get(const matrix *mat, size_t row, size_t col) {
  if (mat == NULL || mat->data == NULL) {
    return -1;
  }
  if (row == 0 || col == 0) {
    return -1;
  }
  return *ele_cptr(mat, row, col);
}

void print_matrix(const matrix *mat) {
  if (mat == NULL || mat->data == NULL || mat->n_row == 0 || mat->n_col == 0) {
    return;
  }
  for (size_t r = 0; r < mat->n_row; r++) {
    printf("| ");
    for (size_t c = 0; c < mat->n_col; c++) {
      double ele = *ele_cptr(mat, r, c);
      printf("%.1f%s", ele, (c + 1 == mat->n_col) ? " |\n" : ", ");
    }
  }
}
