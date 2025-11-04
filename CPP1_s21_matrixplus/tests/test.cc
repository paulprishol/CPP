#include "test.h"

void fill_matrix(S21Matrix& m, double val) {
  for (int i = 0; i < m.getrows(); ++i) {
    for (int j = 0; j < m.getcols(); ++j) {
      m(i, j) = val;
    }
  }
}