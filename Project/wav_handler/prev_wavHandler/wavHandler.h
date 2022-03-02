#pragma once

#include "wavHandler.h"
#include <string>
#include <iostream>
#include <fstream>

//16���� ����(int)�� ��ȯ [Little Endian]
//Little Endian to Integer
template <std::size_t N>
int LEtoInt(int(&arr)[N]);




// .wav file's header and data
class Wave
{
    short* audioData;
    unsigned char* rawData;
    //__int8 : 1byte, __int16 : 2byte, __int32 : 4byte, __int64 : 8byte
private:
    //little endian ���� ���� �״�� ����
    bool is_empty;

    std::string name;


    unsigned char RIFF_ChunkID[4];
    unsigned char RIFF_ChunkSize[4];
    unsigned char RIFF_Format[4];
    /*
    __int32 RIFF_ChunkID
        wav �� "RIFF" ��� ������ (ASCII)

    __int32 RIFF_ChunkSize      [Little Endian]
        ���� ��üũ�� - 8byte (���� chunk id�� chunk size�� �����Ѱ�)
           Little Endian ��(?)

    __int32 RIFF_Format
        �������� .wav�� "WAVE" (ASCII)
    */
    unsigned char FMT_ChunkID[4];
    unsigned char FMT_ChunkSize[4];
    unsigned char FMT_AudioFormat[2];
    unsigned char FMT_NumChannels[2];
    unsigned char FMT_SampleRate[4];
    unsigned char FMT_ByteRate[4];
    unsigned char FMT_BlockAlign[2];
    unsigned char FMT_BitsPerSample[2];
    /*
    __int32 FMT_ChunkID
        'fmt ' ��� ������

    __int32 FMT_ChunkSize       [Little Endian]
        ���� ������� �ڿ� �̾����� ���� ������
            wav�� 24byte�� �� FMT ��� �������̹Ƿ� 16���� ������

    __int16 FMT_AudioFormat     [Little Endian]
        PCM�� ��� 1, litte endian �̹Ƿ� 01 00 ���� ����


    __int16 FMT_NumChannels     [Little Endian]
        ���� ä�� ��
            mono : 1,   stereo : 2, 3channel : 3 ..., 6channel : 6

    __int32 FMT_SampleRate      [Little Endian]
        Number of Samples Per Second [Hz]
        1�ʸ� �󸶳� �ɰ����°�

    __int32 FMT_ByteRate        [Little Endian]
        Average Bytes Per Second
        1�ʸ� ��Ÿ���µ� �ʿ��� byte ��

    __int16 FMT_BlockAlign      [Little Endian]
        Sample Frame size
        ���� mono��� samplesize * 1, stereo��� samplesize * 2

    __int16 FMT_BitsPerSample   [Little Endian]
        samle �Ѱ��� �� bit�� ��Ÿ�����ΰ�
    */
    unsigned char DATA_ChunkID[4];
    unsigned char DATA_ChunkSize[4];
    /*
    __int32 DATA_ChunkID
        ������ "data"  (ASCII)

    __int32 DATA_ChunkSize      [Little Endian]
        data�� �� ������
            ���� ��ü���� header�� ������ ũ��
    */


    int dataSize = 0;
    int frequency = 0;
    int getSize();

public:

    Wave();
    Wave(std::string srcFile);
    ~Wave();

    void open(std::string srcFile);

    int get_dataSize();

    void print_RIFF();
    void print_FMT();
    void print_DATA();
    void print_info();

    //-----  sample size�� 2byte�� �ƴϸ� �����߻�����  ------
    short* getData();

    void make_txt();

    void data_to_raw(int* arr);
    void data_to_raw(short* arr);

    void ArrToWav(int* arr, std::string name);
    void ArrToWav(short* arr, std::string name);
};

