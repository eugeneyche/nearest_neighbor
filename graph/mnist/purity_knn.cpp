#include "data_set.h"
#include "nn.h"
#include "kd_tree_node.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

int DATASIZE = 60000;
data_set train;
data_set test;

char gradient [] = {' ', '.',':',';','+','=','x','X','$','@'};

void printGlyph(euclid_vector * to_print)
{
    for (int i = 0; i < 28 * 28; i++) {
        printf("%c", gradient[(int)((*to_print)[i] / 255 * 10)]);
        if (i % 28 == 27) printf("\n");
    }
}

int main() {
    FILE * train_vtrs = fopen("data/mnist/train_vectors", "rb");
    FILE * train_labels = fopen("data/mnist/train_labels", "rb");
    FILE * test_vtrs = fopen("data/mnist/test_vectors", "rb");
    FILE * test_labels = fopen("data/mnist/test_labels", "rb");
    load(train, train_vtrs);
    label(train, train_labels);
    load(test, test_vtrs);
    label(test, test_labels);
    int count [20] = {};
    for (int n = 1; n <= 20; n++)
    {
        for (int i = 1; i <= test.size(); i++)
        {
            data_set mn_nn = k_nn(test[i], train, n);
            bool pure = true;
            for (int j = 0; j < mn_nn.size(); j++)
            {
                if (mn_nn.get_label(j) != test.get_label(i))
                {
                    pure = false;
                    break;
                }
            }
            if (pure)
            {
                count[n]++;            
            }
        }
    }
    for (int i = 0; i < 20; i++)
    {
        printf("%d %lf", i + 1, count[i] / 10000.);
    }

    fclose(train_vtrs);
    fclose(train_labels);
    fclose(test_vtrs);
    fclose(test_labels);
    fclose(train_vtrs);
    fclose(train_labels);
    fclose(test_vtrs);
    fclose(test_labels);
}
