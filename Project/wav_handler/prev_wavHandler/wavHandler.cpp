#include "wavHandler.h"

//template <typename T, std::size_t N>
//int LEtoInt(T (&arr)[N])//little endian to integer
//{
//    unsigned int integer = 0;
//    for (int i = 0, j = 1; i < N; i++, j *= 256)
//    {
//        integer += arr[i] * j;
//    }
//    return integer;
//}


int LEtoInt(unsigned char* arr, int byte_size = 4)    //little endian to integer
{
    unsigned int integer = 0;
    for (int i = 0, j = 1; i < byte_size; i++, j *= 256)
    {
        integer += arr[i] * j;
    }
    return integer;
}

//=====================================   Wave   ================================================
Wave::Wave()
{
    is_empty = true;
    unsigned char zeroByte = 0;

    audioData = NULL;
    rawData = NULL;

    //set RIFF
    for (int i = 0; i < 4; i++) RIFF_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) RIFF_ChunkSize[i] = zeroByte;
    for (int i = 0; i < 4; i++) RIFF_Format[i] = zeroByte;

    //get FMT
    for (int i = 0; i < 4; i++) FMT_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_ChunkSize[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_AudioFormat[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_NumChannels[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_SampleRate[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_ByteRate[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_BlockAlign[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_BitsPerSample[i] = zeroByte;

    //get DATA
    for (int i = 0; i < 4; i++) DATA_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) DATA_ChunkSize[i] = zeroByte;

    return;
}

Wave::Wave(std::string srcFile)
{
    is_empty = false;
    this->name = srcFile
    unsigned char zeroByte = 0;

    //set RIFF
    for (int i = 0; i < 4; i++) RIFF_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) RIFF_ChunkSize[i] = zeroByte;
    for (int i = 0; i < 4; i++) RIFF_Format[i] = zeroByte;

    //get FMT
    for (int i = 0; i < 4; i++) FMT_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_ChunkSize[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_AudioFormat[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_NumChannels[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_SampleRate[i] = zeroByte;
    for (int i = 0; i < 4; i++) FMT_ByteRate[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_BlockAlign[i] = zeroByte;
    for (int i = 0; i < 2; i++) FMT_BitsPerSample[i] = zeroByte;

    //get DATA
    for (int i = 0; i < 4; i++) DATA_ChunkID[i] = zeroByte;
    for (int i = 0; i < 4; i++) DATA_ChunkSize[i] = zeroByte;

    open(name);

    return;
}

Wave::~Wave()
{
    delete[] audioData;
    delete[] rawData;
}

void Wave::print_RIFF()
{
    std::cout << "RIFF_ChunkID : \t\t\""; for (int i = 0; i < 4; i++) std::cout << RIFF_ChunkID[i];
    std::cout << "\"" << std::endl;
    std::cout << "RIFF_ChunkSize : \t" << LEtoInt(RIFF_ChunkSize) << std::endl << std::endl;
    std::cout << "RIFF_Format : \t\t\""; for (int i = 0; i < 4; i++) std::cout << RIFF_Format[i];
}

void Wave::print_FMT()
{
    std::cout << "\"" << std::endl;
    std::cout << "FMT_ChunkID : \t\t\""; for (int i = 0; i < 4; i++) std::cout << FMT_ChunkID[i];
    std::cout << "\"" << std::endl;
    std::cout << "FMT_ChunkSize : \t" << LEtoInt(FMT_ChunkSize) << std::endl;
    std::cout << "FMT_AudioFormat : \t" << LEtoInt(FMT_AudioFormat, 2) << std::endl;
    std::cout << "FMT_NumChannels : \t" << LEtoInt(FMT_NumChannels, 2) << std::endl;
    std::cout << "FMT_SampleRate : \t" << LEtoInt(FMT_SampleRate) << std::endl;
    std::cout << "FMT_ByteRate : \t\t" << LEtoInt(FMT_ByteRate) << std::endl;
    std::cout << "FMT_BlockAlign : \t" << LEtoInt(FMT_BlockAlign, 2) << std::endl;
    std::cout << "FMT_BitsPerSample : \t" << LEtoInt(FMT_BitsPerSample, 2) << std::endl << std::endl;
}

void Wave::print_DATA()
{
    std::cout << "DATA_ChunkID : \t\t\""; for (int i = 0; i < 4; i++) std::cout << DATA_ChunkID[i];
    std::cout << "\"" << std::endl;
    std::cout << "DATA_ChunkSize : \t" << LEtoInt(DATA_ChunkSize) << std::endl;
}

void Wave::print_info()
{
    print_RIFF();
    print_FMT();
    print_DATA();
    return;
}

void Wave::open(std::string srcFile)
{
    if (name == "")
    {

        this->name = srcFile.substr(0, srcFile.length() - 4);;
    }

    std::ifstream SRCwav;
    SRCwav.open(srcFile);
    if (!SRCwav)
    {
        std::cout << "ERROR!!! - Fail to open srcFile.wav\n" << std::endl;
        return;
    }

    is_empty = false;

    __int8 bufferByte = 0;
    
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        RIFF_ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        RIFF_ChunkSize[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        RIFF_Format[i] = bufferByte;
    }

    //get FMT
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        FMT_ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        FMT_ChunkSize[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        SRCwav.get(bufferByte);
        FMT_AudioFormat[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        SRCwav.get(bufferByte);
        FMT_NumChannels[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        FMT_SampleRate[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        FMT_ByteRate[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        SRCwav.get(bufferByte);
        FMT_BlockAlign[i] = bufferByte;
    }
    for (int i = 0; i < 2; i++)
    {
        SRCwav.get(bufferByte);
        FMT_BitsPerSample[i] = bufferByte;
    }

    //get DATA
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        DATA_ChunkID[i] = bufferByte;
    }
    for (int i = 0; i < 4; i++)
    {
        SRCwav.get(bufferByte);
        DATA_ChunkSize[i] = bufferByte;
    }

    getSize();

    SRCwav.close();
    return;
}

int Wave::getSize()
{
    //전체 데이터사이즈(4,LE) / (비트퍼샘플(2, LE)) * (1 / 8) = 샘플 수(행열 크기)
    int total_size = LEtoInt(DATA_ChunkSize);
    int sample_size = LEtoInt(FMT_BitsPerSample, 2) / 8;

    //std::cout << "          DBG::total_size " << total_size << std::endl;
    //std::cout << "          DBG::sample_size " << sample_size << std::endl;

    //numbers of sample
    int n = total_size / sample_size;
    //std::cout << "          DBG::n :" << n << std::endl;

    this->dataSize = n;
    return n;
}

int Wave::get_dataSize()
{
    return this->dataSize;
}

short* Wave::getData()
{
    if (LEtoInt(FMT_NumChannels, 2) == 1)
    {
        std::ifstream SRCwav;
        SRCwav.open(name + ".wav", std::ios::binary);
        if (!SRCwav)
        {
            std::cout << "Fail to open srcFile.wav\n" << std::endl;
            return NULL;
        }

        audioData = new short[get_dataSize()];

        //header size == 44 byte
        char c;
        for (int i = 0; i < 44; i++)
        {
            SRCwav.get(c);
        }

        char temp1, temp2;
        short temp = 0;
        for (int i = 0; i < get_dataSize(); i++)
        {
            SRCwav.get(temp1);
            SRCwav.get(temp2);

            temp = (unsigned __int8)temp2 * 256;
            temp += (unsigned __int8)temp1;

            audioData[i] = temp;
        }
        SRCwav.close();
        std::cout << "NOW TEST FUNC :: " << get_dataSize() << std::endl;
        return audioData;
    }
    else return NULL;
}

//============================================  이 아래 편의성 함수들 싹다 고쳐야함    ========================================
// 어레이 데이터 텍스트로 만들기, 어레이 데이터 웨이브로 만들기 정도만 구현해도 될듯 (data to raw는 convert little endian 구현했던거같음)
// data to raw 해야지 우리가 원하는 일반적인 길이의 데이터 획득가능

//void 함수(경로, 파일이름 = default 이름)
//wav.함수() 로 이용
//name = "EMPTY" 랑 if(name == "EMPTY") 이용해서 디폴트 매개변수와 같은 효과 만들지뭐....

void Wave::make_txt()
{
    std::ofstream fout;

    int temp;
    fout.open("Txts/" + name + ".txt");
    int n = get_dataSize();
    for (int i = 0; i < n; i++)
    {
        temp = audioData[i];
        fout << temp << std::endl;
    }
    fout.close();
}

void Wave::data_to_raw(int* arr)
{
    rawData = new unsigned char[get_dataSize() * 2];

    for (int i = 0; i < get_dataSize(); i++)
    {
        unsigned int tempSrc = arr[i];
        rawData[i * 2] = tempSrc % 256;
        rawData[i * 2 + 1] = tempSrc / 256;

    }
}
void Wave::data_to_raw(short* arr)
{
    rawData = new unsigned char[get_dataSize() * 2];

    for (int i = 0; i < get_dataSize(); i++)
    {
        unsigned short tempSrc = arr[i];
        rawData[i * 2] = tempSrc % 256;
        rawData[i * 2 + 1] = tempSrc / 256;
    }
}

void Wave::ArrToWav(int* arr, std::string name)
{
    std::ofstream write_wav;
    if (name != this->name)
        write_wav.open("Waves/" + name + ".wav", std::ios::binary);
    else
        write_wav.open("Waves/" + this->name + ".wav", std::ios::binary);
    data_to_raw(arr);

    unsigned char bytes[44] = { 82,73,70,70,164,169,3,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,160,15,0,0,64,31,0,0,2,0,16,0,100,97,116,97,128,169,3,0 };

    for (int i = 0; i < 44; i++)  write_wav.put(bytes[i]);

    int cnt = 0;

    while (cnt < get_dataSize() * 2)
    {
        write_wav.put(rawData[cnt]);

        cnt++;
    }
    write_wav.close();
}
void Wave::ArrToWav(short* arr, std::string name)
{
    std::ofstream write_wav;
    if(name != this->name)
        write_wav.open("Waves/" + name + ".wav", std::ios::binary);
    else
        write_wav.open("Waves/" + this->name + ".wav", std::ios::binary);

    data_to_raw(arr);

    unsigned char bytes[44] = { 82,73,70,70,164,169,3,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,160,15,0,0,64,31,0,0,2,0,16,0,100,97,116,97,128,169,3,0 };

    for (int i = 0; i < 44; i++)  write_wav.put(bytes[i]);

    int cnt = 0;

    while (cnt < get_dataSize() * 2)
    {
        write_wav.put(rawData[cnt]);

        cnt++;
    }
    write_wav.close();
}


//===============================================================================================