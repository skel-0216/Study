#pragma once

#include "wavHandler.h"
#include <string>
#include <iostream>
#include <fstream>

//16진수 정수(int)로 변환 [Little Endian]
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
    //little endian 수정 없이 그대로 저장
    bool is_empty;

    std::string name;


    unsigned char RIFF_ChunkID[4];
    unsigned char RIFF_ChunkSize[4];
    unsigned char RIFF_Format[4];
    /*
    __int32 RIFF_ChunkID
        wav 는 "RIFF" 라는 고정값 (ASCII)

    __int32 RIFF_ChunkSize      [Little Endian]
        파일 전체크기 - 8byte (위의 chunk id와 chunk size를 제외한값)
           Little Endian 값(?)

    __int32 RIFF_Format
        파일형식 .wav는 "WAVE" (ASCII)
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
    unsigned char DATA_ChunkID[4];
    unsigned char DATA_ChunkSize[4];
    /*
    __int32 DATA_ChunkID
        고정값 "data"  (ASCII)

    __int32 DATA_ChunkSize      [Little Endian]
        data의 실 사이즈
            파일 전체에서 header를 제외한 크기
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

    //-----  sample size가 2byte가 아니면 오류발생가능  ------
    short* getData();

    void make_txt();

    void data_to_raw(int* arr);
    void data_to_raw(short* arr);

    void ArrToWav(int* arr, std::string name);
    void ArrToWav(short* arr, std::string name);
};

