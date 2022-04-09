#include <iostream>
#include <vector>

long long sum(std::vector<int> &a);


int main()
{



    return 0;
}

long long sum(std::vector<int> &a)
{
    int length = a.size();
    long long sum = 0;
    for(int i = 0; i < length; i++ )
    {
        sum += a.at(i);
    }

    return sum;
}


// C++, C++11, C++14, C++17, C++ (Clang), C++11 (Clang), C++14 (Clang), C++17 (Clang): long long sum(std::vector<int> &a);
// a: 합을 구해야 하는 정수 n개가 저장되어 있는 배열 (0 ≤ a[i] ≤ 1,000,000, 1 ≤ n ≤ 3,000,000)
// 리턴값: a에 포함되어 있는 정수 n개의 합
