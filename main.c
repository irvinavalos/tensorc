#include "matrix.h"

int main(void) {
  printf("Hello world\n");
  matrix *mat;
  allocate_matrix(&mat, 3, 2);
  print_matrix(mat);
}
