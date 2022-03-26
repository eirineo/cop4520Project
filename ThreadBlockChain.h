#include <cstdint>
#include <vector>
#include "ThreadBlock.h"


using namespace std;

class ThreadBlockChain
{
    public:
        ThreadBlockChain();
        
        void AddThreadBlock(ThreadBlock bNew);
    protected:
        uint32_t _nDifficulty;
        vector<ThreadBlock> _vChain;

        ThreadBlock _GetLastBlock() const;
    

};//end class