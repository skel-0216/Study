#pragma once

#include <iostream>

//16진수 정수(int)로 변환 [Little Endian]
//Little Endian to Integer
template <std::size_t N>
int le2int(int(&arr)[N]);