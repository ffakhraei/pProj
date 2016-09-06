#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

void compress_string(char* str);

int main (int argc, char* argv[])
{
    size_t length=strlen(argv[1]);

    assert(argc == 2);
    assert(length >= 0);

    compress_string(argv[1]);

    cout << endl << argv[1] << endl << endl;


    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

void compress_string(char* str)
{
    size_t length=strlen(str);
    char *compressed_str;
    char *str_cursor, *compressed_cursor;

    compressed_str=new char [2 * length + 1];

    str_cursor=str;
    compressed_cursor=compressed_str;
    int count, digits;
    
    while (*str_cursor)
    {
        *compressed_cursor=*str_cursor;
        count=1;
        digits=0;
        while (*(str_cursor + 1) == *str_cursor)
        {
            ++count;
            ++str_cursor;
        }

        sprintf(compressed_cursor + 1, "%d", count);

        while (count)
        {
            count /= 10;
            ++digits;
        }

        compressed_cursor += digits+1;
        ++str_cursor;
    }

    if ( strlen(compressed_str) <= strlen(str) )
        strcpy(str, compressed_str);
}
