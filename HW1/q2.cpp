// Name: Frankie Fazlollahi
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
// name of file that contains ciphertext
const string CIPHER_FILE = "vigenere-cipher.txt";
// the keyword for decryption we found in class
const string KEYWORD = "SECTION";

// map for encoding numbers to letters
map<int, char> numToLetter = {
    {0,'A'},
    {1,'B'},
    {2,'C'},
    {3,'D'},
    {4,'E'},
    {5,'F'},
    {6,'G'},
    {7,'H'},
    {8,'I'},
    {9,'J'},
    {10,'K'},
    {11,'L'},
    {12,'M'},
    {13,'N'},
    {14,'O'},
    {15,'P'},
    {16,'Q'},
    {17,'R'},
    {18,'S'},
    {19,'T'},
    {20,'U'},
    {21,'V'},
    {22,'W'},
    {23,'X'},
    {24,'Y'},
    {25,'Z'}
};

// map for encoding letters to numbers
map<char, int> letterToNum = {
    {'A',0},
    {'B',1},
    {'C',2},
    {'D',3},
    {'E',4},
    {'F',5},
    {'G',6},
    {'H',7},
    {'I',8},
    {'J',9},
    {'K',10},
    {'L',11},
    {'M',12},
    {'N',13},
    {'O',14},
    {'P',15},
    {'Q',16},
    {'R',17},
    {'S',18},
    {'T',19},
    {'U',20},
    {'V',21},
    {'W',22},
    {'X',23},
    {'Y',24},
    {'Z',25}
};

string vigenereEncryption(string plaintext, string keyword);
string vigenereDecryption(string ciphertext, string keyword);

int main()
{
    // opening file that contains the ciphertext
    ifstream input;
    input.open(CIPHER_FILE);
    if (!input.is_open()) {
        cout << "Could not open the file";
        return 0;
    }
    string ciphertext;
    getline(input, ciphertext);
    input.close();
    // converting the ciphertext to uppercase (because the maps I made are in uppercase)
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(),[](unsigned char c){ return toupper(c); });
    // display original ciphertext
    cout << "Ciphertext: " << ciphertext << endl;
    // perform decryption and display result
    string plaintext = vigenereDecryption(ciphertext, KEYWORD);
    cout << "Plaintext: " << plaintext << endl;
    // encrypt the found plaintext to get back to the original ciphertext
    cout << "Back to Ciphertext: " << vigenereEncryption(plaintext, KEYWORD) << endl;

    return 0;
}

string vigenereEncryption(string plaintext, string keyword)
{
    // the ciphertext that will be returned
    string ciphertext = "";
    // length of the keyword
    int keyLength = keyword.length();
    // counter to track index of keyword we are on
    int counter = 0;
    // the amount a letter will be shifted
    int shift;
    // the number corresponding to the current plaintext letter
    int m;
    // the number corresponding to ciphertext of the current plaintext letter
    int c;
    for(int i = 0; i < plaintext.length(); i++)
    {
        // we shift according to the current keyword letter's number encoding
        shift = letterToNum[keyword[counter++]];
        // reset counter to 0 if it exceeds keyLength
        if(counter >= keyLength)
            counter = 0;
        // set m
        m = letterToNum[plaintext[i]];
        // perform the shift (mod 26)
        c = (m + shift)%26;
        // append the ciphertext letter
        ciphertext.push_back(numToLetter[c]);
    }
    return ciphertext;
}
string vigenereDecryption(string ciphertext, string keyword)
{
    // the plaintext that will be returned
    string plaintext = "";
    // length of the keyword
    int keyLength = keyword.length();
    // counter to track index of keyword we are on
    int counter = 0;
    // the amount a letter will be shifted
    int shift;
    // the number corresponding to current ciphertext letter
    int c;
    // the number corresponding to plaintext of current ciphertext letter
    int m;
    for(int i = 0; i < ciphertext.length(); i++)
    {
        // we shift according to current keyword letter's number encoding
        shift = letterToNum[keyword[counter++]];
        // reset counter to 0 if it exceeds keyLength
        if(counter >= keyLength)
            counter = 0;
        // set c
        c = letterToNum[ciphertext[i]];
        // perform the shift
        m = c - shift;
        // if we get a negative number, add 26
        if(m < 0)
            m+=26;
        // append the plaintext letter
        plaintext.push_back(numToLetter[m]);
    }
    return plaintext;
}
