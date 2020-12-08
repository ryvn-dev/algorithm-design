#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int size = 0;
int outputpoints = 0;
double bezier(double t, double **ptr, int n);

int main(int argc, const char * argv[]) {
    
    ifstream InputFile;
    ofstream OuputFile;
    InputFile.open(argv[1],ifstream::in);
    OuputFile.open(argv[2],ofstream::out);
    InputFile >> size;
    
    if (!size) {
        cout << "ERROR: there is no any point!"<<endl;
    } else {
        
    double **a = nullptr, **b = nullptr;
    
    a = (double**)malloc(sizeof(double*)*size);
    b = (double**)malloc(sizeof(double*)*size);
    
    for (int i=0; i<size; i++) {
        a[i] = (double*)malloc(sizeof(double*)*size);
        b[i] = (double*)malloc(sizeof(double*)*size);
    }
    
    for (int i=0; i<size; i++) {
        InputFile >> a[0][i] >> b[0][i];
    }

    InputFile >> outputpoints;
    
    int w = 1;
    double x, y;
    double t = 0.00;
    double d = 1.00/(outputpoints-1.00);
    while (w <= outputpoints) {
        x = bezier(t, a, size);
        y = bezier(t, b, size);
        OuputFile << fixed << setprecision(2) << x <<'\t'<< y << endl;
        t = t + d;
        w++;
    }
    }
    return 0;
}

double bezier(double t, double **ptr, int n)
{
    for(int j = 1; j < n; j++)
    {
        for(int i = 0; i < n - j; i++)
        {
            *(*(ptr+j)+i) = *(*(ptr+j-1)+i) * (1-t) + *(*(ptr+j-1)+i+1) * t;
        }
    }
    return *(*(ptr+n-1)+0);
}



