#include <cstdio>
#include <cstring>
#include <iostream>
#include "ex_struct.h"
#include "library.h"


class StructExample
{
public:
    StructExample();       // constructor
    //StructExample(const StructExample& copy_from); //copy constructor
    //StructExample& operator=(const StructExample& copy_from); //copy assignment
    ~StructExample()=default;                    // destructor
    void PrintStruct(ex_str_level_0_t& exStruct);
    void BuildExampleStruct();

    ex_str_level_0_t exInStruct, exOutStruct;
    ex_str_level_0_t* pexOutStruct;;
private:
};

StructExample::StructExample()//constructor
{
    pexOutStruct = (ex_str_level_0_t*) nullptr;
    // Build Struct Components
    BuildExampleStruct();
}

void StructExample::PrintStruct(ex_str_level_0_t& exStruct)
{
    std::cout << "a = " << exStruct.a << ", b = " << exStruct.b << std::endl;
    std::vector<double>::iterator it;
    int cnt;
    for(cnt =0, it = exStruct.c.begin(); it != exStruct.c.end(); it++, cnt++)
    {
        std::cout << std::endl << "---------" << std::endl;
        std::cout << "c vector element # "<< cnt << "value: " << *it << ":" << std::endl;    }
    std::cout << std::endl;
}

void StructExample::BuildExampleStruct()
{
    exInStruct.a   = 1000;
    exInStruct.b   = 2000;
    exInStruct.c = {1, 2, 3, 4, 5}; // c++11 instead of push back
}

int main()
{
    bool retVal;
    StructExample StructEx;

    // Print Example Struct
    StructEx.PrintStruct(StructEx.exInStruct);

    // Use Singleton to ensure the Python interpreter remains active till direct release command,
    // and pass Struct arguments to operate ex
    Library& lib = Library::getInstance();

    retVal = lib.Api((const ex_str_level_0_t*)&StructEx.exInStruct, &StructEx.pexOutStruct);

    if (retVal == true)
    {
        // Print returned Struct
        std::cout << std::endl << "Print received  Struct from ex" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        StructEx.PrintStruct(*StructEx.pexOutStruct);
    }
    else
    {
        std::cout << "\nLibrary returned false, actually = " << retVal << std::endl;
    }
    return 0;
}