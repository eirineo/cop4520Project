Use the command below to run the files.

Linux command
g++ -o TestChain -pthread main.cpp ThreadBlock.cpp ThreadBlockChain.cpp Block.cpp Blockchain.cpp sha256.cpp
./TestChain

Mac OS command
gcc -lstdc++ \
    -o TestChain \
    -std=c++11 \
    -stdlib=libc++ \
    -x c++ \
    -pthread \
    main.cpp ThreadBlockChain.cpp ThreadBlock.cpp Block.cpp Blockchain.cpp sha256.cpp
./TestChain