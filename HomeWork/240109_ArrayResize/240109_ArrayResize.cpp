#include <iostream>
#include <ConsoleEngine/EngineDebug.h>

class IntArray
{
public:
    IntArray(int _Size)
    {
        ReSize(_Size);
    }

    IntArray(const IntArray& _Other)
    {
        Copy(_Other);
    }

    ~IntArray()
    {
        Release();
    }

    void operator=(const IntArray& _Other)
    {
        Copy(_Other);
    }

    int& operator[](int _Count)
    {
        return ArrPtr[_Count];
    }

    int& Test(int _Count)
    {
        return ArrPtr[_Count];
    }

    int Num()
    {
        return NumValue;
    }

    void Copy(const IntArray& _Other)
    {
        NumValue = _Other.NumValue;
        ReSize(NumValue);
        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = _Other.ArrPtr[i];
        }
    }

    void ReSize(int _Size)
    {
        if (0 >= _Size)
        {
            MsgBoxAssert("배열의 크기가 0일수 없습니다");
        }

        // 배열에 존재하는 값을 
        int* CopyArrPtr = nullptr;
        CopyArrPtr = new int[NumValue];
        for (int i = 0; i < NumValue; i++)
        {
            CopyArrPtr[i] = ArrPtr[i];
        }

        int CopyCount = _Size;
        if (NumValue < _Size)
        {
            CopyCount = NumValue;
        }

        NumValue = _Size;

        if (nullptr != ArrPtr)
        {
            Release();
        }

        ArrPtr = new int[NumValue];

        for (int i = 0; i < CopyCount; i++)
        {
            ArrPtr[i] = CopyArrPtr[i];
        }

        if (nullptr != CopyArrPtr)
        {
            delete[] CopyArrPtr;
            CopyArrPtr = nullptr;
        }
    }

    void Release()
    {
        if (nullptr != ArrPtr)
        {
            delete[] ArrPtr;
            ArrPtr = nullptr;
        }
    }

private:
    int NumValue = 0;
    int* ArrPtr = nullptr;
};

int main()
{
    LeckCheck;


        IntArray NewArray0 = IntArray(5);

        for (int i = 0; i < NewArray0.Num(); i++)
        {
            NewArray0[i] = i;
        }

        NewArray0.ReSize(3);

        for (int i = 0; i < NewArray0.Num(); i++)
        {
            std::cout << NewArray0[i] << std::endl;
        }

        NewArray0.ReSize(10);
        for (int i = 0; i < NewArray0.Num(); i++)
        {
            std::cout << NewArray0[i] << std::endl;
        }
}
