// Name: Frankie Fazlollahi
#include <iostream>
#include <map>
//#include <fstream>
//#include <string>
//#include <algorithm>
#include <vector>

using namespace std;
// name of file containing ciphertext (not currently using because had problems extracting the ciphertext)
const string CIPHERTEXT = "hw-cipher.txt";
// my guess of the length of the keyword (k)
const int KEYLENGTH = 5;

// map for encoding letters to numbers
map<char, int> letterToNum = {
    {'a',0},
    {'b',1},
    {'c',2},
    {'d',3},
    {'e',4},
    {'f',5},
    {'g',6},
    {'h',7},
    {'i',8},
    {'j',9},
    {'k',10},
    {'l',11},
    {'m',12},
    {'n',13},
    {'o',14},
    {'p',15},
    {'q',16},
    {'r',17},
    {'s',18},
    {'t',19},
    {'u',20},
    {'v',21},
    {'w',22},
    {'x',23},
    {'y',24},
    {'z',25}
};

// counts frequencies of each letter in each array of characters from the ciphertext
vector<vector<int>> frequency(vector<vector<char>> letters);

int main()
{
    // the ciphertext (wasn't able to download the file on camino)
    string ct = "ptugycymhzgvvzvfxklzgypvjhzlsdsmyckvxvvvatzewfxzldoglzvfrmvzrtfqffgprxhalaycelwtvhvpncoshwwelmehhjlmfvojfffhwjogksmfavqvfhvqnolalvtbywkhhlrkskdlzzxdezhbukwckalvfxzxkcvvqvwgalvfxdejdelrkmhmxzaxastcgaiddehxvhalwyowvajowceeqbukrqkvwjhalxzzxzekhalfrgxvjkvxhpkokyezzpoiekxmmigmhviwolhkvxueifhdswhalechxyvrwejsmsklhfbefejatspgckamfbhmxysmymrbzcprfmppvgtuhsmmoivbwvjdolzecahzxkvxlrkwklxiwtukcsphwzbloeucpdlvbbhwbswtcjsemhzrmoijvtksnqhciivtsjkvxhvvoboeubmzxmrblhrbrmsiatskvcflximrlxsjmpjzuoyiu";
    vector<vector<char>> letters;
    vector<char> l;
    // counter always <= k-1
    int counter = 0;
    // looping through the ciphertext and putting all the characters in positions 0,k,2k,... in its own vector
    // and doing the same for characters in positions 1, k+1, 2k+1, etc
    for(int i = 0; i < ct.length(); i++)
    {
        // making the initial vectors
        if(i < KEYLENGTH)
        {
            l.push_back(ct[i]);
            letters.push_back(l);
            l.clear();
        }
        // adding the rest of the characters to their respective vector
        else
        {
            letters[counter].push_back(ct[i]);
            counter++;
            // reset counter if it exceeds k
            if(counter >= KEYLENGTH)
                counter = 0;
        }
    }

    vector<vector<int>> frequencies;
    // calling the function to get the frequencies in each vector
    frequencies = frequency(letters);
    // displaying the results
    for(int i = 0; i < KEYLENGTH; i++)
    {
        cout << "Histogram " << i+1 << ": [";
        for(int j = 0; j < 26; j++)
        {
            cout << frequencies[i][j];
            if(j < 25)
                cout << ",";
        }
        cout << "]\n";
    }


    return 0;
}

vector<vector<int>> frequency(vector<vector<char>> letters)
{
    // vector of vectors containing the frequencies that will be returned
    vector<vector<int>> freq;
    // used for setting the initial vectors frequencies to all 0
    vector<int> initial;
    // holds individual letter
    int let;
    // initializing frequencies to 0
    for(int i = 0; i < 26; i++)
    {
        initial.push_back(0);
    }
    for(int i = 0; i < KEYLENGTH; i++)
    {
        freq.push_back(initial);
    }
    // iterating through each character of each vector and incrementing its frequency
    for(int i = 0; i < KEYLENGTH; i++)
    {
        for(int j = 0; j < letters[i].size(); j++)
        {
            let = letterToNum[letters[i][j]];
            freq[i][let]++;
        }
    }
    return freq;
}
