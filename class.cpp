#include "class.h"

#include <iostream>

template<typename T>
void base::f(T value){
	std::cout<< value << std::endl;
}

template void base::f<int>(int);
