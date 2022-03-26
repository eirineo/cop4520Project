#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;

class Blockchain
{
    public:
        Blockchain();
        
        void AddBlock(Block bNew);
    protected:
        uint32_t _nDifficulty;
        vector<Block> _vChain;

        Block _GetLastBlock() const;
    

};//end class

