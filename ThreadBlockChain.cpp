#include "ThreadBlockChain.h"
ThreadBlockChain::ThreadBlockChain()
{
    _vChain.emplace_back(ThreadBlock(0, "Genesis Block"));
    _nDifficulty = 3;
}

void ThreadBlockChain::AddThreadBlock(ThreadBlock bNew)
{
    bNew.sPrevHash = _GetLastBlock().GetHash();
    bNew.MultiThreadMine(_nDifficulty);
    _vChain.push_back(bNew);
}

ThreadBlock ThreadBlockChain::_GetLastBlock() const
{
    return _vChain.back();
}