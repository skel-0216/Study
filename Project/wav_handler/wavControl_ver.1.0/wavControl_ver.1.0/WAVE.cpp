#include "WAVE.h"

namespace LE
{
    bool RIFF_ChunkID = false;
    bool RIFF_ChunkSize = true;
    bool RIFF_Format = false;

    bool FMT_ChunkID = false;
    bool FMT_ChunkSize = true;
    bool FMT_AudioFormat = true;
    bool FMT_NumChannels = true;
    bool FMT_SampleRate = true;
    bool FMT_ByteRate = true;
    bool FMT_BlockAlign = true;
    bool FMT_BitsPerSample = true;

    bool DATA_ChunkID = false;
    bool DATA_ChunkSize = true;
}

WAV::WAV()
{
    unsigned char zeroByte_2[2] = { 0, 0 };
    unsigned char zeroByte_4[4] = { 0, 0, 0, 0 };

    //set RIFF
    memcpy(header.Riff.ChunkID, zeroByte_4, 4);
    memcpy(header.Riff.ChunkSize, zeroByte_4, 4);
    memcpy(header.Riff.Format, zeroByte_4, 4);

    //get FMT
    memcpy(header.Fmt.ChunkID, zeroByte_4, 4);
    memcpy(header.Fmt.ChunkSize, zeroByte_4, 4);
    memcpy(header.Fmt.AudioFormat, zeroByte_2, 2);
    memcpy(header.Fmt.NumChannels, zeroByte_2, 2);
    memcpy(header.Fmt.SampleRate, zeroByte_4, 4);
    memcpy(header.Fmt.ByteRate, zeroByte_4, 4);
    memcpy(header.Fmt.BlockAlign, zeroByte_2, 2);
    memcpy(header.Fmt.BitsPerSample, zeroByte_2, 2);

    //get DATA
    memcpy(header.Data.ChunkID, zeroByte_4, 4);
    memcpy(header.Data.ChunkSize, zeroByte_4, 4);
    return;
};

WAV::WAV(std::string src_path)
{
    this->name = src_path.substr(src_path.rfind('\\') + 1);
    unsigned char zeroByte_2[2] = { 0, 0 };
    unsigned char zeroByte_4[4] = { 0, 0, 0, 0 };

    //set RIFF
    memcpy(header.Riff.ChunkID, zeroByte_4, 4);
    memcpy(header.Riff.ChunkSize, zeroByte_4, 4);
    memcpy(header.Riff.Format, zeroByte_4, 4);

    //get FMT
    memcpy(header.Fmt.ChunkID, zeroByte_4, 4);
    memcpy(header.Fmt.ChunkSize, zeroByte_4, 4);
    memcpy(header.Fmt.AudioFormat, zeroByte_2, 2);
    memcpy(header.Fmt.NumChannels, zeroByte_2, 2);
    memcpy(header.Fmt.SampleRate, zeroByte_4, 4);
    memcpy(header.Fmt.ByteRate, zeroByte_4, 4);
    memcpy(header.Fmt.BlockAlign, zeroByte_2, 2);
    memcpy(header.Fmt.BitsPerSample, zeroByte_2, 2);

    //get DATA
    memcpy(header.Data.ChunkID, zeroByte_4, 4);
    memcpy(header.Data.ChunkSize, zeroByte_4, 4);

    open(src_path);

    return;
};

WAV::~WAV()
{
    for (int i = 0; i < channels; i++)
        delete audioData[i];
    delete audioData;
};

void WAV::open(std::string src_path)
{
    if (name == "")
    {
        this->name = src_path.substr(src_path.rfind('\\') + 1);
    }

    std::ifstream src_wav;
    src_wav.open(src_path);
    if (!src_wav)
    {
        std::cout << "ERROR!!! - Fail to open [" << src_path << "]\n" << std::endl;
        return;
    }

    is_empty = false;

    __int8 bufferByte = 0;

    //get RIFF
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Riff.ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Riff.ChunkSize[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Riff.Format[i] = bufferByte;
    }

    //get FMT
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.ChunkSize[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.AudioFormat[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.NumChannels[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.SampleRate[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.ByteRate[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.BlockAlign[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        src_wav.get(bufferByte);
        header.Fmt.BitsPerSample[i] = bufferByte;
    }

    //get DATA
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Data.ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        src_wav.get(bufferByte);
        header.Data.ChunkSize[i] = bufferByte;
    }

    set_length();

    src_wav.close();
    return;
}


std::string WAV::header_print(unsigned char* arr, int byte_size, bool is_LE)
{
    std::string temp_string = "";

    if (is_LE == true)
    {
        if (byte_size == 4)
        {
            int result;
            std::memcpy(&result, arr, byte_size);
            std::cout << result;
        }
        else if (byte_size == 2)
        {
            short result;
            std::memcpy(&result, arr, byte_size);
            std::cout << result;
        }
        else
            std::cout << "ERROR ::: type_size error" << std::endl;
    }
    else
    {
        for (int i = 0; i < byte_size; i++)
        {
            std::cout << (unsigned char)(*(arr + i));
        }
    }
    return temp_string;
}
// 시행착오 (아래)
/*
*   시행착오라기보다... string으로 받는게 좋으면 이걸 쓰는게 호환성이 좋다.
*
std::string WAV::header_print(unsigned char* arr, int byte_size, bool is_LE)
{
    std::string result;
    if (is_LE == true)
    {
        if(byte_size == 4)
        {
            int temp;
            std::memcpy(&temp, arr, byte_size);
            std::cout << temp;
            result = std::to_string(temp);
        }
        else if (byte_size == 4)
        {
            short temp;
            std::memcpy(&temp, arr, byte_size);
            std::cout << temp;
            result = std::to_string(temp);
        }
        else
            std::cout << "ERROR ::: type_size error" << std::endl;
    }
    else
    {
        for (int i = 0; i < byte_size; i++)
        {
            std::cout << (unsigned char)(*(arr + i));
            result.push_back((unsigned char)(*(arr + i)));
        }
    }
    return result;
}
*/

int WAV::set_length()
{
    int total_size;
    short block_size;

    std::memcpy(&total_size, header.Data.ChunkSize, 4);
    std::memcpy(&block_size, header.Fmt.BlockAlign, 2);
    int temp = (int)block_size;

    int n = total_size / temp;

    this->data_length = n;
    return n;
}