#include <fstream>
#include <iostream>
#include <string>
#define REGULAR_RESULTS_FILE "block_result.txt"
#define MULTITHREAD_RESULTS_FILE "thread_block_result.txt"

int main()
{
    std::string line;
    std::ifstream file (REGULAR_RESULTS_FILE);
    int count = 0.0;
    double sum = 0;
    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            sum += std::stof(line);
            count++;
        }
        file.close();
    }
    std::cout << std::fixed << std::setprecision(3) << "Control results: " << ((sum / count) / 1000) << " seconds on average\n";

    std::ifstream threadFile (MULTITHREAD_RESULTS_FILE);
    count = 0.0;
    sum = 0;
    if(threadFile.is_open())
    {
        while(std::getline(threadFile, line))
        {
            sum += std::stof(line);
            count++;
        }
        threadFile.close();
    }
    std::cout << std::fixed << std::setprecision(3) << "Concurrent results: " << ((sum / count) / 1000) << " seconds on average\n";  
    return 0;
}//end of main