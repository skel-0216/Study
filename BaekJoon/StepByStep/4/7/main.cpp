#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;

    double* results = new double[cases];

    for(int i = 0; i < cases; i++)
    {
        int num;
        cin >> num;

        int* list = new int[num];
        for(int n = 0; n < num; n++)
        {
            cin >> list[n];
        }

        int sum = 0;
        double mean;

        for(int n = 0; n < num; n++)
        {
            sum += list[n];
        }
        mean = (double)sum / num;

        int cnt = 0;
        for(int n = 0; n < num; n++)
        {
            if(mean < list[n])
                cnt++;
        }
        results[i] = (double)cnt / num * 100;


    }

    for(int i = 0; i < cases; i++)
        printf("%.3lf%%\n", results[i]);
    return 0;
}