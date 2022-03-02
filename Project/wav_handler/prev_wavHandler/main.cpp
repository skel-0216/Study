#include <iostream>

#include <string>

#include "wavHandler.h"

using namespace std;

int main()
{
	Wave wav("MYHB.wav");
	cout << "@@@@@@@@@@@@@ --- wav.print_iofo()" << endl;
	wav.print_info();

	short* original_data;

	//Ãâ·Â
	/*
	original_data = wav.getData();
	wav.data_to_raw(original_data);
	
	for (int i = 0; i < wav.get_dataSize(); i++)
	{
		cout << original_data[i] << endl;
	}
	*/

	return 0;
}