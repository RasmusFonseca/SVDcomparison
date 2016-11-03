
#ifndef SVD_H
#define SVD_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

/**
 * Computes, stores, and maintains a singular value decomposition of a gsl_matrix.
 *
 * A matrix-pointer is passed to the SVD on construction. This pointer is kept through
 * the life-time of the SVD object (but ownership is not assumed). If the contents
 * of the matrix is changed, the SVD can be update to reflect the change using the
 * abstract UpdateFromMatrix function. This is not automatically done on construction.
 */
class SVD{
 protected:
  const int m, n; ///< Dimensions of matrix

  /** Decomposes M into U*S*V^t.  */
  SVD(gsl_matrix* M);
 public:

  gsl_matrix * const matrix;  //TODO: Make private
  gsl_matrix * const U;       //TODO: Make private
  gsl_matrix * const V;       //TODO: Make private
  gsl_vector * const S;       //TODO: Make private

  virtual ~SVD();

  /** Update U, V_t and S to reflect the decomposition of matrix. */
  virtual void UpdateFromMatrix() = 0;

  /** Print the SVD to standard out */
  void print() const;

};

#endif
