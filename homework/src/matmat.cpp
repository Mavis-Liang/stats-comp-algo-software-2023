#include <Rcpp.h>

using Rcpp::NumericMatrix;
using Rcpp::NumericVector;

// [[Rcpp::export]]
NumericMatrix row_col_dot_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_col_out = B.ncol();
  int n_inner = A.ncol();
  NumericMatrix result(n_row_out, n_col_out);
  
  for(int i = 0; i < n_row_out; i++) {
    for(int j = 0; j < n_col_out; j++) {
      double sum = 0;
      for(int k = 0; k < n_inner; k++) {
        sum += A(i, k) * B(k, j);
      }
      result(i, j) = sum;
    }
  }
  
  return result;
}

// [[Rcpp::export]]
NumericMatrix col_oriented_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_col_out = B.ncol();
  NumericMatrix result(n_row_out, n_col_out);
  for (int j = 0; j < n_col_out; ++j) {
    // Calculate result[, j] = A %*% B[, j] in column-oriented manner for each j
    NumericVector bj = B(Rcpp::_, j);
    for(int i = 0; i < n_row_out; i++) {
      NumericVector ai = A(i, Rcpp::_);
      result(i, j) = sum(ai * bj);
    }
    
  }
  return result;
}
