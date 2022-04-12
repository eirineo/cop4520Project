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

string ThreadBlock::_CalculateHash(promise<string> && prms)
{
    string result = "";
    stringstream ss;
    _nNonce++;
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

    result = sha256(ss.str());
    prms.set_value(result);
    return result;
}

void ThreadBlock::MultiThreadMine(uint32_t nDifficulty)
{
    const int numThreads = 1;
    thread blockThreads[numThreads];
    future<string> fufilledGurantees[numThreads];
    int nextIndex = 0;

    char cstr[nDifficulty + 1];
    for(uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }

    cstr[nDifficulty] = '\0';

    string str(cstr);
    
    //starts threads
    for(int i = 0; i < numThreads; i++)
    {
        promise<string> gurantee;

        fufilledGurantees[i] = gurantee.get_future();
        blockThreads[i] = thread(&ThreadBlock::_CalculateHash,this, move(gurantee));
    }
    //loops until hash is found
    do
    {   
        //finds next available thread
        for(nextIndex = 0;!blockThreads[nextIndex].joinable(); nextIndex++)
        {
            nextIndex++;
            nextIndex %= numThreads;
        }//end for loop

        //retrieved promised value
        _sHash = fufilledGurantees[nextIndex].get();
        //resets thread
        blockThreads[nextIndex].join();

        promise<string> gurantee;
        fufilledGurantees[nextIndex] = gurantee.get_future();
        blockThreads[nextIndex] = thread(&ThreadBlock::_CalculateHash,this, move(gurantee));

    } while (_sHash.substr(0, nDifficulty) != str);
    for(int i = 0; i < numThreads; i++)
    {

        blockThreads[i].join();
    }
}