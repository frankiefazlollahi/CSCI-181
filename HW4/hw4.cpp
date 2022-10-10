#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

const string INPUT = "sha3in.txt"; // name of file that contains 1600 bits to input to program

// performs XOR operation
int XOR(int a, int b);
// turns 1-dimensional array of length 1600 v[0 ...1599], to a 3-dimensional
// array a[0 ...4][0 ...4][0 ...63] such that a[i][j][k] = v[64(5j + i) + k]
vector<vector<vector<int>>> inputSHA3(vector<int> v);
// turns a 3-dimensional array a[0 ...4][0 ...4][0 ...63] into a 1-dimensional
// array of length 1600, v[0 ...1599], such that v[64(5j + i) + k] = a[i][j][k]
vector<int> outputSHA3(vector<vector<vector<int>>> a);
// computes theta step of SHA3
vector<vector<vector<int>>> theta(vector<vector<vector<int>>> a_in);

int main()
{
    ifstream inputFile;
    char bit;
    vector<int> input;
    // taking input file of 1600 bits and arranging them in a vector
    inputFile.open(INPUT);
    if (!inputFile.is_open()) {
        cout << "Could not open the file";
        return 0;
    }
    while(inputFile.get(bit))
    {
        if(bit == '0')
            input.push_back(0);
        else
            input.push_back(1);
    }
    inputFile.close();
    // a_in becomes the 3-dimensional vector of the input
    vector<vector<vector<int>>> a_in = inputSHA3(input);
    // apply theta step to a_in
    vector<vector<vector<int>>> test = theta(a_in);
    cout << "Checking work:\nOutput bits [4][3][9...18]: ";
    for(int i = 9; i < 19; i++)
    {
        cout << test[4][3][i];
    }
    cout << "\nExpected bits: 0011011000\n\n";
    cout << "Question 5:\nBits [2][3][15...24]: ";
    for(int i = 15; i < 25; i++)
    {
        cout << test[2][3][i];
    }
    cout << endl;

    return 0;
}

int XOR(int a, int b)
{
    if(a == b)
        return 0;
    else
        return 1;
}

vector<vector<vector<int>>> inputSHA3(vector<int> v)
{
    // initializing vector for output
    vector<vector<vector<int>>> output(5, vector<vector<int>>(5, vector<int>(64, 0)));
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 64; k++)
            {
                output[i][j][k] = v[64 * (5 * j + i) + k];
            }
        }
    }
    return output;
}

vector<int> outputSHA3(vector<vector<vector<int>>> a)
{
    // initializing vector for output
    vector<int> output(1600, 0);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 64; k++)
            {
                output[64 * (5 * j + i) + k] = a[i][j][k];
            }
        }
    }
    return output;
}

vector<vector<vector<int>>> theta(vector<vector<vector<int>>> a_in)
{
    // initializing vecvtor for output
    vector<vector<vector<int>>> a_out(5, vector<vector<int>>(5, vector<int>(64, 0)));
    int sum1;
    int sum2;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 64; k++)
            {
                // first summation (the if statements for if i or x == 0 are for performing mod operation)
                for(int x = 0; x < 5; x++)
                {
                    if(x == 0)
                    {
                        if(i == 0)
                            sum1 = a_in[i-1+5][x][k];
                        else
                            sum1 = a_in[(i-1)%5][x][k];
                    }
                    else
                    {
                        if(i == 0)
                            sum1 = XOR(sum1, a_in[i-1+5][x][k]);
                        else
                            sum1 = XOR(sum1, a_in[(i-1)%5][x][k]);
                    }
                }
                // second summation
                for(int x = 0; x < 5; x++)
                {
                    if(x == 0)
                    {
                        if(k == 0)
                            sum2 = a_in[(i+1)%5][x][k-1+64];
                        else
                            sum2 = a_in[(i+1)%5][x][(k-1)%64];
                    }
                    else
                    {
                        if(k == 0)
                            sum2 = XOR(sum2, a_in[(i+1)%5][x][k-1+64]);
                        else
                            sum2 = XOR(sum2, a_in[(i+1)%5][x][(k-1)%64]);
                    }
                }
                // a_out[i][j][k] = a_in[i][j][k] XOR sum1 XOR sum2
                a_out[i][j][k] = XOR(a_in[i][j][k], sum1);
                a_out[i][j][k] = XOR(a_out[i][j][k], sum2);
            }
        }
    }

    return a_out;
}
