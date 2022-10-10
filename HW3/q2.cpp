#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <map>

using namespace std;

map<int, char> decToLetter = {
    {0,'A'},
    {1,'B'},
    {2,'C'},
    {3,'D'},
    {4,'E'},
    {5,'F'},
    {6,'G'},
    {7,'H'}
};

// outputs an array of length n with the binary representation of number
vector<int> DecimalToBinary(int number, int n);
// outputs array of integers with every n bits converted to its decimal representation
vector<int> ConvertBitArrayToInt(vector<int> k, int n);
// initializes arrays S and T following RC4
void initializeS(vector<int>& s, vector<int>& t, vector<int> key, int n);
// creates the permutation of S following RC4
void permutation(vector<int>& s, vector<int> t, int n);
// generates an array of bits (of length n * l(length of message/ciphertext))
// following the keystream generation method of RC4
vector<int> generateKeystream(vector<int>& s, int n, int l, vector<int> key);
// simple function that performs XOR of 2 arrays of bits of equal length
vector<int> xor_bits(vector<int> m, vector<int> keystream);
// converts array of binary values to a message
string binaryToText(vector<int> b, int n);

int main()
{
    // part b
    int n = 3;
    int l = 7;
    // message to be encrypted in binary (BACDDAH)
    vector<int> m = {0,0,1,0,0,0,0,1,0,0,1,1,0,1,1,0,0,0,1,1,1};
    // secret key in decimal for part B
    vector<int> keyDB = {1, 2, 3, 6};
    // secret key in binary for part B
    vector<int> keyBB = {0,0,1,0,1,0,0,1,1,1,1,0};
    vector<int> s1;
    vector<int> t1;
    initializeS(s1, t1, keyDB, n);
    permutation(s1, t1, n);
    vector<int> keystreamB = generateKeystream(s1, n, l, keyBB);
    cout << "Part B: \nKeystream: ";
    for(int i = 0; i < keystreamB.size(); i++)
    {
        cout << keystreamB[i] << " ";
    }
    cout << endl;
    // encrypt by taking xor of message and keystream
    vector<int> afterXOR = xor_bits(m, keystreamB);
    cout << "Encrypted Message: " << binaryToText(afterXOR, n) << endl << endl;

    // part c
    n = 8;
    l = 24;
    // secret key in binary for part C
    vector<int> keyBC = {1, 0, 1, 1, 1, 0, 0, 1,
                         0, 1, 0, 1, 0, 0, 1, 1,
                         1, 1, 1, 1, 1, 0, 1, 1,
                         0, 0, 1, 0, 0, 1, 0, 0,
                         0, 1, 1, 0, 0, 0, 0, 0,
                         1, 1, 0, 0, 1, 0, 1, 0,
                         0, 1, 0, 1, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1, 1, 1,
                         0, 0, 0, 1, 0, 1, 0, 1,
                         1, 1, 0, 1, 0, 0, 0, 1};
    // secret key in decimal for part C
    vector<int> keyDC = {185, 83, 251, 36, 96, 202, 81, 135, 21, 209};
    vector<int> s2;
    vector<int> t2;
    initializeS(s2, t2, keyDC, n);
    permutation(s2, t2, n);
    vector<int> keystreamC = generateKeystream(s2, n, l, keyBC);
    cout << "Part C: \nKeystream:";
    for(int i = 0; i < keystreamC.size(); i++)
    {
        if(i % 8 == 0)
            cout << " ";
        cout << keystreamC[i];
    }
    cout << endl;

    // part d
    vector<int> ciphertext = {1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0};
    //cout << ciphertext.size() << " " << keystreamC.size() << endl;
    vector<int> afterXOR2 = xor_bits(ciphertext, keystreamC);
    cout << "Bits After Performing XOR:";
    for(int i = 0; i < afterXOR2.size(); i++)
    {
        if(i % 8 == 0)
            cout << " ";
        cout << afterXOR2[i];
    }
    cout << endl;

    return 0;
}

vector<int> DecimalToBinary(int number, int n)
{
    vector<int> binary;
    // initialize array to n 0s
    for(int i = 0; i < n; i++)
    {
        binary.push_back(0);
    }
    // counter to track index of array
    int count = 0;
    while (number > 0)
    {
        // store remainder in binary array
        binary[count] = number % 2;
        // divide number by 2
        number = number / 2;
        count++;
    }
    // reverse the array for the final binary representation
    reverse(binary.begin(), binary.end());
    return binary;
}

vector<int> ConvertBitArrayToInt(vector<int> k, int n)
{
    vector<int> decimal;
    // number that will be the decimal represenation of each n bits
    int d = 0;
    // counter that keepts track of exponent for binary to decimal conversion
    int exp = 0;
    // iterate through binary array starting from back
    for(int i = k.size()-1; i >= 0; i=i)
    {
        // getting the decimal representation of each n bits starting from back
        while(exp < n & i >= 0)
        {
            if(k[i] == 1)
            {
                d += pow(2, exp);
            }
            exp++;
            i--;
        }
        // insert the value and reset d & exp to 0
        decimal.insert(decimal.begin(), d);
        d = 0;
        exp = 0;
    }
    return decimal;
}

void initializeS(vector<int>& s, vector<int>& t, vector<int> key, int n)
{
    int keylength = key.size();
    for(int i = 0; i < pow(2,n); i++)
    {
        // fill array S with numbers 0 to 2^n -1
        s.push_back(i);
        // fill array T with values from the key,
        // starting over from beginning of key once all values have been added
        t.push_back(key[i % keylength]);
    }
}

void permutation(vector<int>& s, vector<int> t, int n)
{
    int j = 0;
    int mod = pow(2,n);
    for(int i = 0; i < mod; i++)
    {
        j = (j + s[i] + t[i]) % mod;
        swap(s[i], s[j]);
    }
}

vector<int> generateKeystream(vector<int>& s, int n, int l, vector<int> key)
{
    // to hold the keystream of decimal values
    vector<int> ks;
    // to hold the keystream of binary values
    vector<int> keystream;
    // temporary array to hold the binary values of each decimal number in the keystream
    vector<int> temp;
    int i = 0;
    int j = 0;
    // 2^n
    int mod = pow(2,n);
    // to track the length of the keystream
    int count = 0;
    int t;
    while(count < n * l)
    {
        i = (i + 1) % mod;
        j = (j + s[i]) % mod;
        swap(s[i], s[j]);
        t = (s[i] + s[j]) % mod;
        ks.push_back(s[t]);
        count++;
    }
    // converting each decimal value of keystream to bits and saving it in keystream output
    for(int i = 0; i < ks.size(); i++)
    {
        temp = DecimalToBinary(ks[i], n);
        for(int j = 0; j < n; j++)
        {
            keystream.push_back(temp[j]);
        }
        temp.clear();
    }
    return keystream;
}

vector<int> xor_bits(vector<int> m, vector<int> keystream)
{
    vector<int> output;
    for(int i = 0; i < m.size(); i++)
    {
        if(m[i] == keystream[i])
            output.push_back(0);
        else
            output.push_back(1);
    }
    return output;
}

string binaryToText(vector<int> b, int n)
{
    string text = "";
    // use ConvertBitArrayToInt function to convert the binary array to decimal
    vector<int> values = ConvertBitArrayToInt(b, n);

    for(int i = 0; i < values.size(); i++)
    {
        // use the map to generate the message
        text.push_back(decToLetter[values[i]]);
    }
    return text;
}
