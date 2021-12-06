#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Tree.h"
using namespace std;
int CKey(int index1,int index2)
{
    int key;
    key =index1*index1+index2*index2;
    if ( index1 > index2) key++;
    return key;
}
class dop_data
{
private:
   // int* index;
   // int len;
    int IndexandVal[3];

public:
    void Set(int i1, int i2, int val)
    {
        IndexandVal[0] = i1;
        IndexandVal[1] = i2;
        IndexandVal[2] = val;
    }

    void SetVal(int val)
    {
        IndexandVal[2] = val;
    }

    int GetVal()
    {
        return IndexandVal[2];
    }

    int* Get()
    {
        return IndexandVal;
    }

    int Key()
    {
        return CKey(IndexandVal[0], IndexandVal[1]);
    }

    void Print()
    {
            cout <<"Index:  ("<<IndexandVal[0]<<", "<<IndexandVal[1]<<")   Value:  "<< IndexandVal[2] <<endl;

    }

};


int main()
{
    binary_tree<dop_data> Tree;
    dop_data S;

    int a[5][3] = { {4, 0, 8}, {0, 66, -1}, {0, -5, 0}, {3, -3, 30}, {0, 1, 1} };
    for (int i = 0; i < 5;i++)
    {
        for (int j = 0; j < 3; j++)
        {
         if (a[i][j] != 0)
         {
            S.Set(i, j, a[i][j]);
           // S.Print();
           // cout << S.Key() <<endl;
            Tree.insert(S.Key(), &S);
           // Tree.print();
         }

        }

    }


    Tree.print();
    Tree.MulElem(5);
    Tree.print();

return 0;
}
