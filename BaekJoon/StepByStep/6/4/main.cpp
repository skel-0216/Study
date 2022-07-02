#include <iostream>
#include <string>

using namespace std;

int main()
{
    int case_num;

    cin >> case_num;

    int* repeat_times = new int[case_num];
    string* inputs = new string[case_num];
    
    for(int i = 0; i < case_num; i++)
    {
        cin >> repeat_times[i];
        cin >> inputs[i];
    }

    for(int i = 0; i < case_num; i++)
    {
        for(int j = 0; j < inputs[i].length(); j++)
        {
            for(int k = 0; k < repeat_times[i]; k++)
            {
                cout << inputs[i][j];
            }
        }
        cout << endl;
    }
}