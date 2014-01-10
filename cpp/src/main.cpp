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

int kd_tree_nn(int c, int count_correct, int size, data_set train)
{
    kd_tree_node * root = kd_tree(c, train);
    for (int i = 0; i < size; i++)
    {
        cout << test.get_label(test[i]) << " -> ";
        cout.flush();
        euclid_vector * l_mn = kd_tree_nn(test[i], train, c, root);
        cout << train.get_label(l_mn);
        if (test.get_label(test[i]) != train.get_label(l_mn))
            cout << " X" << endl;
        else
        {
            cout << endl;
            count_correct++;
        }
    }
    return count_correct;
}


int main() {
    FILE * train_vtrs = fopen("/Users/janetzhai/Desktop/KNN/KNN/train_vectors", "rb");
    FILE * train_labels = fopen("/Users/janetzhai/Desktop/KNN/KNN/train_labels", "rb");
    FILE * test_vtrs = fopen("/Users/janetzhai/Desktop/KNN/KNN/test_vectors", "rb");
    FILE * test_labels = fopen("/Users/janetzhai/Desktop/KNN/KNN/test_labels", "rb");
    load(train, train_vtrs);
    label(train, train_labels);
    printf("Loaded Train Set\n");
    load(test, test_vtrs);
    label(test, test_labels);
    printf("Loaded Test Set\n");
    
    int count [100] = {0};
    for (int i = 0; i < test.size(); i++)
    {
        data_set mn_nn = k_nn(test[i], train, 100);
        for (int j = 0; j < mn_nn.size(); j++)
        {
            if (mn_nn.get_label(j) == test.get_label(i))
            {
                count[j]++;
            }
        }
    }
    for (int i = 0; i < 100; i++)
    {
        if (i > 0) printf(" ");
        printf("%d", count[i]);
    }

    //kd-tree
    /*int count_correct = 0;
    int c = 0.05 * DATASIZE;
    int size = test.size();
    count_correct = kd_tree_nn(c, count_correct, size, train);
    float rate = (float)count_correct / size;
    cout << " There are " << rate << "% correct labels" << endl;
    */

    fclose(train_vtrs);
    fclose(train_labels);
    fclose(test_vtrs);
    fclose(test_labels);
    fclose(train_vtrs);
    fclose(train_labels);
    fclose(test_vtrs);
    fclose(test_labels);
}
