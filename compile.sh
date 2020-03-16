clang++ -std=c++11 $(pkg-config --cflags --libs opencv4) disparity.cpp -o disparity
g++ -std=c++11 $(pkg-config --cflags --libs opencv4) stereogram.cpp -o stereogram