#pragma once
#include "WAVE.h"

#include <iostream>
#include <fstream>
#include <string>

namespace LE
{
    extern bool RIFF_ChunkID;
    extern bool RIFF_ChunkSize;
    extern bool RIFF_Format;

    extern bool FMT_ChunkID;
    extern bool FMT_ChunkSize;
    extern bool FMT_AudioFormat;
    extern bool FMT_NumChannels;
    extern bool FMT_SampleRate;
    extern bool FMT_ByteRate;
    extern bool FMT_BlockAlign;
    extern bool FMT_BitsPerSample;

    extern bool DATA_ChunkID;
    extern bool DATA_ChunkSize;
}

typedef struct{
public:
    unsigned char ChunkID[4];
    unsigned char ChunkSize[4];
    unsigned char Format[4];
} RIFF;
/*
__int32 RIFF_ChunkID
    wav �� "RIFF" ��� ������ (ASCII)

__int32 RIFF_ChunkSize      [Little Endian]
    ���� ��üũ�� - 8byte (���� chunk id�� chunk size�� �����Ѱ�)
       Little Endian ��(?)

__int32 RIFF_Format
    �������� .wav�� "WAVE" (ASCII)
*/

typedef struct
{
public:
    unsigned char ChunkID[4];
    unsigned char ChunkSize[4];
    unsigned char AudioFormat[2];
    unsigned char NumChannels[2];
    unsigned char SampleRate[4];
    unsigned char ByteRate[4];
    unsigned char BlockAlign[2];
    unsigned char BitsPerSample[2];
} FMT;
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

typedef struct
{
public:
    unsigned char ChunkID[4];
    unsigned char ChunkSize[4];
} DATA;
/*
__int32 DATA_ChunkID
    ������ "data"  (ASCII)

__int32 DATA_ChunkSize      [Little Endian]
    data�� �� ������
        ���� ��ü���� header�� ������ ũ��
*/

typedef struct
{
    RIFF Riff;
    FMT Fmt;
    DATA Data;
} WAVE_HEADER;

class WAV
{
private:
    void open(std::string src_path);

    int set_length();

public:
    bool is_empty = true;
    int data_length = 0;
    short channels;
    short sample_size;
    int** audioData;

    std::string name;

    WAVE_HEADER header;

    WAV();
    WAV(std::string src_path);

    std::string header_print(unsigned char* arr, int byte_size, bool is_LE);

    ~WAV();

    /*
    int* getData()
    {
        // ------------------------------ ä�ο� ���� �ٸ� ������ ������ 2���� �迭 �̿�
        // ------------------------------ ex) 3ä���� ��� [0][1] �� 1��° ä�� 2��° ������, [2][3]�� 3��° ä�� 4��° ������...
        // ------------------------------ .wav -> data�� ��쵵 ����, data-> wav�� ��쵵 ��������.
        // ------------------------------ �׷��� �߿��� ����� �� block�� �����ŭ �����͸� �д� �Լ��� ������ ������.
        // ------------------------------ param���� dest, src, length... �� ������ 
        short channels;
        std::memcpy(&channels, header.Fmt.NumChannels, 2);
        if (channels == 1)
        {
            std::ifstream SRCwav;
            SRCwav.open(name + ".wav", std::ios::binary);
            if (!SRCwav)
            {
                std::cout << "Fail to open srcFile.wav\n" << std::endl;
                return NULL;
            }

            audioData = new int[this->data_length];

            //header size == 44 byte
            char c;
            for (int i = 0; i < 44; i++)
            {
                SRCwav.get(c);
            }
            char* temp_block = new char[(short)header.Fmt.BlockAlign];
            int temp = 0;

            //----------------------------------------------------------- �̹�����

            for (int i = 0; i < this->data_length; i++)
            {
                for (int j = 0; j < (short)header.Fmt.BlockAlign; i++)
                    SRCwav.get(temp_block[j]);

                for (int j = 0; j < (short)header.Fmt.BlockAlign; i++)  //@#!@#@#! �̺κ�
                {
                    temp = (unsigned __int8)temp_block[j] * 256;
                    temp += (unsigned __int8)temp_block[j+1];
                }
                temp = (unsigned __int8)temp_block[0] * 256;
                temp += (unsigned __int8)temp_block[1];                  //@#!@#!@#! �̱��� ����


                // audioData[i] = temp

            }
            SRCwav.close();
            return audioData;
        }
        else
        {
            std::cout << "WAV::init_data() ERROR - No channels setted" << std::endl;
            return NULL;
        }
    }
    */

    int* getData()
    {
        // ------------------------------ ä�ο� ���� �ٸ� ������ ������ 2���� �迭 �̿�
        // ------------------------------ ex) 3ä���� ��� [0][1] �� 1��° ä�� 2��° ������, [2][3]�� 3��° ä�� 4��° ������...
        // ------------------------------ .wav -> data�� ��쵵 ����, data-> wav�� ��쵵 ��������.
        // ------------------------------ �׷��� �߿��� ����� �� block�� �����ŭ �����͸� �д� �Լ��� ������ ������.
        // ------------------------------ param���� dest, src, length... �� ������ 

        // channel��ŭ �� ����.
        std::memcpy(&channels, header.Fmt.NumChannels, 2);
         std::cout << "DEBUG :: channels : " << channels << std::endl;
        audioData = new int* [channels];

        // sample 1���� ũ��
        std::memcpy(&sample_size, header.Fmt.BitsPerSample, 2);
        sample_size /= 8;

        // �����͸� ���� �� ����
        for (int i = 0; i < channels; i++)
            audioData[i] = new int[data_length];

        //  data�� 2���� �迭�� ����.
        for (int i = 0; i < this->data_length; i++)
        {
            for (int j = 0; j < channels; j++)
            {
                switch (j)
                {
                case 0:
                    // [0][i]�� ����
                    break;
                case 1:
                    // [0][i]�� ����
                    break;
                case 2:
                    // [0][i]�� ����
                    break;
                case 3:
                    // [0][i]�� ����
                    break;
                case 4:
                    // [0][i]�� ����
                    break;
                case 5:
                    // [0][i]�� ����
                    break;
                case 6:
                    // [0][i]�� ����
                    break;
                default:
                    break;
                }
            }
        }


        return 0;
    }
};


/*
1 mono      : [data][data][data]...
2 stereo    : [left][right][left][right]...
3 3_channel : [left][right][center][left][right][center]...
4 quad      : [front left][front right][rear left][rear right]...
5 4_channel : [left][center][right][surround]...
6 6_channel : [left center][left][center][right center][right][surround]...
*/

