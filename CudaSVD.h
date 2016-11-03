#ifndef KGS_CUDASVD_H
#define KGS_CUDASVD_H

#include "SVD.h"

class CudaSVD: public SVD {
 public:
  CudaSVD(gsl_matrix* M): SVD(M) {}

  void UpdateFromMatrix();
 private:
};


#endif //KGS_CUDASVD_H
