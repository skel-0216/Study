#pragma once

#include <iostream>

//16���� ����(int)�� ��ȯ [Little Endian]
//Little Endian to Integer
template <std::size_t N>
int le2int(int(&arr)[N]);