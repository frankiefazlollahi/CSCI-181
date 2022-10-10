// Name: Frankie Fazlollahi
// note: I made the for loops using pseudocode instead of proper syntax
// because that would make it easier to understand how the system works
// than if I looped through vectors and accessing the data structures contained
// in each vector

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// data structure that contains the coin information
class PayCoin {
public:
    // constructor
    PayCoin(int id, int value, int num) : id(id), value(value), num(num) {}
    // getter functions
    int getID() { return id;}
    int getVal() { return value;}
    int getNum() { return num;}
private:
    int id;
    int value;
    int num;
};

class Blockchain {
public:
    // constructor
    Blockchain(Transaction data){
        hash = Hash(data); // assume Hash() is a function implemented that computes the hash of something
        data = &data;
    }
private:
    int hash;
    Transaction *data;
};

// defines the information of a transaction
class Transaction {
public:
    // constructor
    Transaction(int id, vector<PayCoin> consumedCoins, vector<tuple<PayCoin, int>> createdCoins, vector<int> sigs)
    {
        prev_H_Ptr = nullptr;
        type = "PayCoin";
        transactionID = id;
        consumed = consumedCoins;
        created = createdCoins;
        signatures = sigs;
    }

    bool verifyTransaction(Blockchain *h_ptr)
    {
        Blockchain *ledger = h_ptr;
        int consumed_value = 0;
        vector<PayCoin> not_verified_yet = consumed;
        // search through the ledger and check:
        // if a coin has been previously consumed
        // if a coin has been created
        // if a coin has a valid signature
        while(ledger != nullptr)
        {
            Transaction *data = ledger.data;
            for coin in not_verified_yet: // pseudocode so easier to understand
            {
                // check that coin has not already been consumed
                for prev_consumed in data.created:
                {
                    if(coin.getID() == get<0>(prev_consumed).getID() && coin.getNum() == get<0>(prev_consumed).getNum())
                    {
                        return false;   // the coin has already been consumed
                    }
                }

                // check that coin has been created
                for prev_created in data.created:
                {
                    // check if coin has been created in this transaction
                    if(coin.getID() == get<0>(prev_created).getID() && coin.getNum() == get<0>(prev_created).getNum())
                    {
                        // if coin has been created, then verify the signature
                        int verified = 0;
                        for sig in signatures:
                        {
                            // check all signatures to see if one matches
                            if(verifySignature(get<1>(prev_created), data, sig));
                            {
                                verified = 1;
                            }
                        }
                        // if the coin hasn't been verified correctly
                        if(verified == 0)
                        {
                            return false;
                        }
                        // if it was verified, then remove the coin from not_verified_yet
                        not_verified_yet.erase(not_verified_yet.begin() + i)
                    }
                }
            }
            // continue to the next block of the ledger
            ledger = data.prev_H_Ptr;
        }
        // if there are coins that still haven't been verified, that means that they don't exist in the Blockchain
        if(not_verified_yet.size() > 0)
            return false;

        // Add the values of the consumed coins and subtract the values from created coins
        int total = 0;
        for coin in consumed:
        {
            total += coin.getVal();
        }
        for coin in created:
        {
            total -= get<0>(coin).getVal();
        }

        // if the total value of coins coming out of the transaction is not equal to the total value of consumed coins, not valid transaction
        if(total != 0)
            return false;

        return true;
    }

    Blockchain addBlock(Blockchain chain)
    {
        prev_H_Ptr = chain  // assign the chain to prev_H_Ptr
        return *this;
    }
private:
    Blockchain *prev_H_Ptr;
    string type;
    int transactionID;
    vector<PayCoin> consumed;              // array of PayCoins
    vector<tuple<PayCoin, int>> created;   // array of tuples that contain {PayCoin coin, int recipient}
    vector<int> signatures;                // array of signatures of the owners of the consumed coins
};

// assume this function is already implemented
// verifies signatures and returns True/False
bool verifySignature(pubKey, message, signature);

int main()
{
    // assume some blockchain already exists so there are coins in the system
    Transaction chain = initial_chain;
    vector<PayCoin> will_consume = list_of_coins_to_consume;
    // try to create new transaction
    Transaction new_transaction = Transaction(previous_transactionID + 1, will_consume, createdCoins, sigs);

    // if it passes the verification, add to blockchain
    if(new_transaction.verifyTransaction(chain))
    {
        chain = new_transaction.addBlock(chain);
    }

    return 0;
}
