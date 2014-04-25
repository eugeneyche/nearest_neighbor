#include <iostream>
#include <cstdio>
#include "vector_math.h"
#include "nn.h"
#include "kd_tree.h"
#include "spill_tree.h"
#include "virtual_spill_tree.h"
#include "data_set.h"
#include "test.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
using namespace std;

typedef unsigned char byte;

int main() 
{
    //Test<byte, byte> mTest ("/Users/janetzhai/Desktop/nn-xcode/nn-xcode");
    //mTest.generate_error_data("Users/janetzhai/Desktop/nn-xcode/nn-xcode/output");

    double data[] = { 1.0  , 1/2.0, 1/3.0, 1/4.0,
        1/2.0, 1/3.0, 1/4.0, 1/5.0,
        1/3.0, 1/4.0, 1/5.0, 1/6.0,
        1/4.0, 1/5.0, 1/6.0, 1/7.0 };
    
    gsl_matrix_view m = gsl_matrix_view_array (data, 4, 4); // input data and the dimension of the matrix
    
    gsl_vector *eval = gsl_vector_alloc (4); //eigen value space
    gsl_matrix *evec = gsl_matrix_alloc (4, 4); //eigen vector space
    
    gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (4); //eigen workspace
    
    gsl_eigen_symmv (&m.matrix, eval, evec, w);
    
    gsl_eigen_symmv_free (w); //free space
    
    gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_ASC); //sort
    
    //print here
    {
        int i;
        
        for (i = 0; i < 4; i++)
        {
            double eval_i = gsl_vector_get (eval, i);
            gsl_vector_view evec_i = gsl_matrix_column (evec, i);
            
            printf ("eigenvalue = %g\n", eval_i);
            printf ("eigenvector = \n");
            gsl_vector_fprintf (stdout, &evec_i.vector, "%g");
        }
    }
    
    //free space here
    gsl_vector_free (eval);
    gsl_matrix_free (evec);
    
    return 0;
}
