
#ifndef GSLSVD_H
#define GSLSVD_H

#include "SVD.h"
#include <gsl/gsl_matrix.h>

class SVDGSL: public SVD {
 public:
  SVDGSL(gsl_matrix* M): SVD(M){}

 protected:

  void UpdateFromMatrix();
};


#endif //KGS_GSLSVD_H
