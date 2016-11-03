#include <iostream>

#include <gsl/gsl_blas.h>

#include "SVD.h"
#include "SVDMKL.h"
#include "SVDGSL.h"

using namespace std;

SVD::SVD(gsl_matrix* M):
    matrix(M),
    m(M->size1),
    n(M->size2),
    U(gsl_matrix_alloc(m,m)),
    S(gsl_vector_alloc(std::min(m,n))),
    V(gsl_matrix_alloc(n,n))
{
}


SVD::~SVD(){
  gsl_matrix_free(U);
  gsl_vector_free(S);
  gsl_matrix_free(V);
}


