
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

#include "SVD.h"
#include "CudaSVD.h"
#include "SVDMKL.h"
#include "SVDGSL.h"

using namespace std;

/** Read gsl_matrix from text-file */
gsl_matrix* readMatrix(const string& fname){
	cout<<"readMatrix("<<fname<<")"<<endl;
	int rows =  0, r=0;
	int cols = -1, c=0;
	gsl_matrix* ret = NULL;

	//Count lines
	ifstream tmp(fname.c_str());
	rows = count(istreambuf_iterator<char>(tmp), istreambuf_iterator<char>(), '\n');
	tmp.close();

	ifstream infile(fname.c_str());
	string line;
	while(getline(infile, line)){
		if(cols<0) {
			cols = count(line.begin(), line.end(), ' ')+1;
			ret = gsl_matrix_alloc(rows,cols);
		}
		istringstream iss(line);
		for(c=0;c<cols;c++){
			float val;
			iss>>val;
			gsl_matrix_set(ret, r,c, val);
		}

		r++;
	}
	cout<<".. done reading"<<endl;
	infile.close();

	return ret;
}

/** Print matrix to cout */
void gsl_matrix_cout (const gsl_matrix *m) {
  for (int i=0; i<m->size1; ++i) {
    for (int j=0; j<m->size2; ++j){
      cout << gsl_matrix_get(m,i,j);
      if(j == (m->size2-1))
        cout << endl;
      else
        cout << " ";
    }
  }
}

/** Print vector to cout */
void gsl_vector_cout (const gsl_vector *v) {
  for (int i=0; i<v->size; ++i)
    cout << gsl_vector_get(v,i) << "\t";
  cout << endl;
}



int main(int argc, char* argv[]){
  if(argc!=3){
    cout<<"Usage: "<<argv[0]<<" <MKL|CUDA|GSL> <fname>"<<endl;
    return -1;
  }

  gsl_matrix* m = readMatrix(string(argv[2]));

  clock_t start = clock();

  SVD* svd = NULL;
  if(string(argv[1])=="MKL"){
    cout<<"Computing SVD with MKL"<<endl;
    svd = new SVDMKL(m);
  }else if(string(argv[1])=="GSL"){
    cout<<"Computing SVD with GSL"<<endl;
    svd = new SVDGSL(m);
  }else if(string(argv[1])=="CUDA"){
    cout<<"Computing SVD with CUDA"<<endl;
    svd = new CudaSVD(m);
  }else{
    cerr<<"Unrecognized SVD method: "<<argv[1]<<endl;
    return -1;
  }

  svd->UpdateFromMatrix();

  clock_t end = clock();

  //cout<<"Input:"<<endl;
  //gsl_matrix_cout(m);
  //cout<<"S:"<<endl;
  //gsl_vector_cout(svd->S);
  //cout<<"V:"<<endl;
  //gsl_matrix_cout(svd->V);

  cout<<".. done. Took: "<<((end-start)*1000.0)/CLOCKS_PER_SEC<<" ms"<<endl;

  return 1;
}
