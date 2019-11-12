#include <stdlib.h>
#include <stdio.h>

void print_matrix(int n, int m, int* M);
void m_add(int n, int m, int* M1, int* M2, int* M);

int main() {
  int A[] = { /* 3x4-Matrix */
    12,2,-3,5,
    0,19,5,9,
    2,-1,13,-3
  };
  print_matrix(3, 4, A);

  int B[] = { /* 3x4-Matrix */
    30,2,-1,-47,
    0,23,2,-2,
    7,-5,-55,9
  };
  print_matrix(3, 4, B);

  int C[12]; /* 3x4-Matrix */
  m_add(3, 4, A, B, C); /* C = A + B */
  print_matrix(3, 4, C);

  return 0;
}

void print_matrix(int n, int m, int* M) {
  int x;
  int y;
  printf("\n");
  for (y=0; y<n; y++) {
    for (x=0; x<m; x++) {
      printf ("%5d", M[y*m+x]);
    }
    printf("\n");
  }
  printf("\n");
}

