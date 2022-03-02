#include <iostream>

#include "WAVE.h"

using namespace std;

// 240036

// �⺻ ����� ������ ������ (�������°� ����)
// main data load�� ������ �ʾҴ�.
// channel �� � ���� �ٸ��� ��ó�� �Ǿ����

int main()
{
	WAV myhb("MYHB.wav");
	cout << myhb.name << endl;

	cout << myhb.header_print(myhb.header.Riff.ChunkID, 4, LE::RIFF_ChunkID) << endl;
	cout << myhb.header_print(myhb.header.Riff.ChunkSize, 4, LE::RIFF_ChunkSize) << endl;
	cout << myhb.header_print(myhb.header.Riff.Format, 4, LE::RIFF_Format) << endl;
	cout << endl;

	cout << myhb.header_print(myhb.header.Fmt.ChunkID, 4, LE::FMT_ChunkID) << endl;
	cout << myhb.header_print(myhb.header.Fmt.ChunkSize, 4, LE::FMT_ChunkSize) << endl;
	cout << myhb.header_print(myhb.header.Fmt.AudioFormat, 2, LE::FMT_AudioFormat) << endl;
	cout << myhb.header_print(myhb.header.Fmt.NumChannels, 2, LE::FMT_NumChannels) << endl;
	cout << myhb.header_print(myhb.header.Fmt.SampleRate, 4, LE::FMT_SampleRate) << endl;
	cout << myhb.header_print(myhb.header.Fmt.ByteRate, 4, LE::FMT_ByteRate) << endl;
	cout << myhb.header_print(myhb.header.Fmt.BlockAlign, 2, LE::FMT_BlockAlign) << endl;
	cout << myhb.header_print(myhb.header.Fmt.BitsPerSample, 2, LE::FMT_BitsPerSample) << endl;
	cout << endl;

	cout << myhb.header_print(myhb.header.Data.ChunkID, 4, LE::DATA_ChunkID) << endl;
	cout << myhb.header_print(myhb.header.Data.ChunkSize, 4, LE::DATA_ChunkSize) << endl;
	cout << endl;

	cout << myhb.data_length << endl;

	myhb.getData();

	return 0;
}
