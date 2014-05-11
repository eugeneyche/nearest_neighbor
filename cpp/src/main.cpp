#include <iostream>
#include <cstdio>
#include "vector_math.h"
#include "nn.h"
#include "kd_tree.h"
#include "kd_spill_tree.h"
#include "kd_virtual_spill_tree.h"
#include "data_set.h"
#include "test.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
using namespace std;

typedef unsigned char byte;

int main() 
{
    Test<byte, byte> mTest ("data/mnist");
    mTest.generate_kd_trees();
    mTest.generate_kd_spill_trees();
    mTest.generate_kd_v_spill_trees();
}
