#include <cstdint>
#include <thread>
#include <vector>
#include <iostream>
#include<future>
//#include "Block.h"
using namespace std;

class ThreadBlock
{
    public:
        string sPrevHash;

        ThreadBlock(uint32_t nIndexIn, const string &sDataIn);
        void MultiThreadMine(uint32_t nDifficulty);
        string GetHash();

    private:
        uint32_t _nIndex;
        int64_t _nNonce;
        string _sData;
        string _sHash;
        time_t _tTime;
        bool lookingForHash;
        void _CalculateHash();
};