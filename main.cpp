#include "Blockchain.h"
#include "ThreadBlockChain.h"
// #include "ThreadBlock.h"
#include <chrono>
#include <fstream>

using namespace std::chrono;

void testBlockChain(int blocks)
{
    Blockchain bChain = Blockchain();

    auto start = high_resolution_clock::now();
    //cout << "Mining block 1..." << endl;
    for(int i = 1; i <= blocks;i++)
    {
        bChain.AddBlock(Block(i, "Block Data"));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    ofstream file;
    file.open("block_result.txt",ofstream::app);
    file << duration.count() << "\n";
    file.close();
}
void testThreadBlockChain(int blocks)
{
    ThreadBlockChain pBlockChain = ThreadBlockChain();

    auto start = high_resolution_clock::now();
    for(int i = 1; i <= blocks;i++)
    {

        pBlockChain.AddThreadBlock(ThreadBlock(i, "Thread Block 1 Data"));
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    ofstream tFile;
    tFile.open("thread_block_result.txt",ofstream::app);
    tFile << duration.count() << "\n";
    tFile.close();
}
void testBlock()
{
    ThreadBlock tBlock = ThreadBlock(0, "Genesis Block");
    tBlock.MultiThreadMine(6);
}
int main()
{
    int numberOfBlocksToAdd = 10;

    for(int i = 0; i < 100;i++){
    testBlockChain(numberOfBlocksToAdd);

    testThreadBlockChain(numberOfBlocksToAdd);
    std::cout << i << "chains completed\n";
    }
    std::cout << "Program complete\n";

    return 0;
}
