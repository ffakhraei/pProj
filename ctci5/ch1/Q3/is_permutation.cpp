#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

bool is_perm(const char* str1, const char* str2);

int main(int argc, char* argv[])
{
    assert( argc == 3 );
    assert( strlen(argv[1]) == strlen(argv[2]));
    assert( strlen(argv[1]) != 0 );

    if (is_perm(argv[1], argv[2]))
        cout << argv[1] << " is a permutation of " << argv[2] << endl;
    else
        cout << argv[1] << " is not a permutation of " << argv[2] << endl;

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

bool is_perm(const char* str1, const char* str2)
{
    char *str_ptr1, *str_ptr2;

    str_ptr1=new char [strlen(str1)];
    str_ptr2=new char [strlen(str2)];

    strcpy(str_ptr1, str1);
    strcpy(str_ptr2, str2);
    
    sort(str_ptr1, str_ptr1+strlen(str1));
    sort(str_ptr2, str_ptr2+strlen(str2));


    if (strstr(str_ptr1, str_ptr2))
    {
        delete [] str_ptr1;
        delete [] str_ptr2;
        return true;
    }
    else
    {
        delete [] str_ptr1;
        delete [] str_ptr2;
        return false;
    }
}
