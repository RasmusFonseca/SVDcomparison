#ifndef KGS_SVDMKL_H
#define KGS_SVDMKL_H

#include "SVD.h"

class SVDMKL: public SVD {
public:
    SVDMKL(gsl_matrix* M): SVD(M) {}

    void UpdateFromMatrix();
};


#endif //KGS_SVDMKL_H
