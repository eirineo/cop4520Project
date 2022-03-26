Use the command below to run the files.

gcc -lstdc++ \
    -o TestChain \
    -std=c++11 \
    -stdlib=libc++ \
    -x c++ \
    -pthread \
    main.cpp ThreadBlock.cpp Block.cpp Blockchain.cpp sha256.cpp
./TestChain