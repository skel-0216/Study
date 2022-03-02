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
    wav 는 "RIFF" 라는 고정값 (ASCII)

__int32 RIFF_ChunkSize      [Little Endian]
    파일 전체크기 - 8byte (위의 chunk id와 chunk size를 제외한값)
       Little Endian 값(?)

__int32 RIFF_Format
    파일형식 .wav는 "WAVE" (ASCII)
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
    'fmt ' 라는 고정값

__int32 FMT_ChunkSize       [Little Endian]
    현제 헤더에서 뒤에 이어지는 값의 사이즈
        wav는 24byte가 총 FMT 헤더 사이즈이므로 16으로 고정값

__int16 FMT_AudioFormat     [Little Endian]
    PCM인 경우 1, litte endian 이므로 01 00 으로 저장


__int16 FMT_NumChannels     [Little Endian]
    음성 채널 수
        mono : 1,   stereo : 2, 3channel : 3 ..., 6channel : 6

__int32 FMT_SampleRate      [Little Endian]
    Number of Samples Per Second [Hz]
    1초를 얼마나 쪼개었는가

__int32 FMT_ByteRate        [Little Endian]
    Average Bytes Per Second
    1초를 나타내는데 필요한 byte 수

__int16 FMT_BlockAlign      [Little Endian]
    Sample Frame size
    만약 mono라면 samplesize * 1, stereo라면 samplesize * 2

__int16 FMT_BitsPerSample   [Little Endian]
    samle 한개를 몇 bit로 나타낼것인가
*/

typedef struct
{
public:
    unsigned char ChunkID[4];
    unsigned char ChunkSize[4];
} DATA;
/*
__int32 DATA_ChunkID
    고정값 "data"  (ASCII)

__int32 DATA_ChunkSize      [Little Endian]
    data의 실 사이즈
        파일 전체에서 header를 제외한 크기
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
        // ------------------------------ 채널에 따라서 다른 데이터 저장방식 2차원 배열 이용
        // ------------------------------ ex) 3채널의 경우 [0][1] 은 1번째 채널 2번째 데이터, [2][3]은 3번째 채널 4번째 데이터...
        // ------------------------------ .wav -> data의 경우도 쉽고, data-> wav의 경우도 쉬워질것.
        // ------------------------------ 그러면 중요한 방식은 한 block의 사이즈만큼 데이터를 읽는 함수가 있으면 좋을듯.
        // ------------------------------ param으로 dest, src, length... 를 넣으면 
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

            //----------------------------------------------------------- 이밑으로

            for (int i = 0; i < this->data_length; i++)
            {
                for (int j = 0; j < (short)header.Fmt.BlockAlign; i++)
                    SRCwav.get(temp_block[j]);

                for (int j = 0; j < (short)header.Fmt.BlockAlign; i++)  //@#!@#@#! 이부분
                {
                    temp = (unsigned __int8)temp_block[j] * 256;
                    temp += (unsigned __int8)temp_block[j+1];
                }
                temp = (unsigned __int8)temp_block[0] * 256;
                temp += (unsigned __int8)temp_block[1];                  //@#!@#!@#! 이까이 여기


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
        // ------------------------------ 채널에 따라서 다른 데이터 저장방식 2차원 배열 이용
        // ------------------------------ ex) 3채널의 경우 [0][1] 은 1번째 채널 2번째 데이터, [2][3]은 3번째 채널 4번째 데이터...
        // ------------------------------ .wav -> data의 경우도 쉽고, data-> wav의 경우도 쉬워질것.
        // ------------------------------ 그러면 중요한 방식은 한 block의 사이즈만큼 데이터를 읽는 함수가 있으면 좋을듯.
        // ------------------------------ param으로 dest, src, length... 를 넣으면 

        // channel만큼 열 생성.
        std::memcpy(&channels, header.Fmt.NumChannels, 2);
         std::cout << "DEBUG :: channels : " << channels << std::endl;
        audioData = new int* [channels];

        // sample 1개의 크기
        std::memcpy(&sample_size, header.Fmt.BitsPerSample, 2);
        sample_size /= 8;

        // 데이터를 넣을 행 생성
        for (int i = 0; i < channels; i++)
            audioData[i] = new int[data_length];

        //  data를 2차원 배열에 저장.
        for (int i = 0; i < this->data_length; i++)
        {
            for (int j = 0; j < channels; j++)
            {
                switch (j)
                {
                case 0:
                    // [0][i]에 저장
                    break;
                case 1:
                    // [0][i]에 저장
                    break;
                case 2:
                    // [0][i]에 저장
                    break;
                case 3:
                    // [0][i]에 저장
                    break;
                case 4:
                    // [0][i]에 저장
                    break;
                case 5:
                    // [0][i]에 저장
                    break;
                case 6:
                    // [0][i]에 저장
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

