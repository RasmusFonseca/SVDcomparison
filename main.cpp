
#include <iostream>
#include <string>

#include "SVD.h"
#include "CudaSVD.h"
#include "SVDMKL.h"
#include "SVDGSL.h"

using namespace std;

gsl_matrix* readMatrix(const string& fname){


}


int main(int argc, char* argv[]){
  if(argc!=3){
    cout<<"Usage: "<<argv[0]<<" <MKL|CUDA|GSL> <fname>"<<endl;
    return -1;
  }

  gsl_matrix* m = readMatrix(string(argv[2]));

  SVD* svd = NULL;
  if(string(argv[1])=="MKL"){
    cout<<"Using MKL SVD"<<endl;
    svd = new SVDMKL(m);
  }else if(string(argv[1])=="GSL"){
    cout<<"Using GSL SVD"<<endl;
    svd = new SVDGSL(m);
  }else if(string(argv[1])=="CUDA"){
    cout<<"Using CUDA SVD"<<endl;
    svd = new CudaSVD(m);
  }else{
    cerr<<"Unrecognized SVD method: "<<argv[1]<<endl;
    return -1;
  }

  svd->UpdateFromMatrix();

  return 1;
}
