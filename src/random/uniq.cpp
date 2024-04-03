// g++ -o uniq uniq.cpp

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main(void) 
{

    std::vector<int> numbers;

    for(int i=0; i<100; i++)       // add 0-99 to the vector
        numbers.push_back(i);

    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	std::random_device rd;
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rd()));

    for(int i=0; i<40; i++)        // print the first 40 randomly sorted numbers
        std::cout << numbers[i] << std::endl;

}
