#include <sstream>
#include <future>
#include <vector>
#include "ThreadBlock.h"
#include "sha256.h"
using namespace std;

ThreadBlock::ThreadBlock(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn),_sData(sDataIn)
{
    _nNonce = -1;
    _tTime = time(nullptr);
}

string ThreadBlock::GetHash()
{
    return _sHash;
}

void ThreadBlock::_CalculateHash()
{
    while(lookingForHash)
    {
        string result = "";
        stringstream ss;
        int diff = 6;
        char cstr[diff + 1];
        for(uint32_t i = 0; i < diff; ++i)
        {
            cstr[i] = '0';
        }
        cstr[diff] = '\0';
        string str(cstr);
        
        _nNonce++;
        ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

        result = sha256(ss.str());

        if(str == result.substr(0, diff))
        {
            _sHash = result;
            lookingForHash = false;
        }//end if
    }//end hwile loop
}//end calchash

void ThreadBlock::MultiThreadMine(uint32_t nDifficulty)
{
    const int numThreads = 8;
    thread blockThreads[numThreads];
    // future<string> fufilledGurantees[numThreads];
    int nextIndex = 0;

    char cstr[nDifficulty + 1];
    // for(uint32_t i = 0; i < nDifficulty; ++i)
    // {
    //     cstr[i] = '0';
    // }

    // cstr[nDifficulty] = '\0';

    // string str(cstr);
    
    //starts threads
    for(int i = 0; i < numThreads; i++)
    {
        // promise<string> gurantee;
        // fufilledGurantees[i] = gurantee.get_future();
        blockThreads[i] = thread(&ThreadBlock::_CalculateHash,this);
    }
    //loops until hash is found
    // do
    // {   
    //     //finds next available thread
    //     for(nextIndex = 0;!blockThreads[nextIndex].joinable(); nextIndex++)
    //     {
    //         nextIndex++;
    //         nextIndex %= numThreads;
    //     }//end for loop

    //     //retrieved promised value
    //     // _sHash = fufilledGurantees[nextIndex].get();
    //     //resets thread
    //     blockThreads[nextIndex].join();

    //     // promise<string> gurantee;
    //     // fufilledGurantees[nextIndex] = gurantee.get_future();
    //     blockThreads[nextIndex] = thread(&ThreadBlock::_CalculateHash, this);

    // } while (lookingForHash);
    while(lookingForHash){}
    for(int i = 0; i < numThreads; i++)
    {

        blockThreads[i].join();
    }
}//mine