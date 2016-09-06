#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void reverse(char* str);

int main(int argc, char* argv[])
{
    assert( argc == 2 );
    assert( strlen(argv[1]) > 0);
    
    reverse(argv[1]);
    
    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

void reverse(char* str)
{
    size_t length=strlen(str);
    char *cursor;
    char *reversed_str=new char[length];

    
    cursor=str+length-1;
    
    for (size_t i=0; i<length; ++i)
    {
        *reversed_str=*cursor;
        cout << *reversed_str;
        --cursor;
        ++reversed_str;
    }
    
    *reversed_str='\0';
    reversed_str=reversed_str-length;
    cout << endl; 
    delete [] reversed_str;
}
