#include <iostream>

int main()
{
    int num;

    std::cin >> num;

    int* grade = new int[num];

    int temp_max = INT32_MIN;
    int sum = 0;
    for(int i = 0; i < num; i++)
    {
        std::cin >> grade[i];
        sum += grade[i];
        if(temp_max < grade[i])
            temp_max = grade[i];
    }
    double mean;

    mean = (double)sum / num / temp_max * 100;

    printf("%lf\n", mean);
    return 0;
}