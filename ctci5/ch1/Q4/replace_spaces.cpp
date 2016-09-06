#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>

using namespace std;

void replace_spaces(char* str, size_t true_length);

int main(int argc, char* argv[])
{
    assert(argc == 3);
    size_t true_length=(size_t)(atoi(argv[2]));
    size_t length=strlen(argv[1]);
    assert(length > 0);
    assert(length > true_length);

    replace_spaces(argv[1], true_length);

    cout << endl << argv[1] << endl << endl;

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

void replace_spaces(char* str, size_t true_length)
{
   //cout << "Length of the string as entered is: " << strlen(str) << endl
    //    << "True length of the string is: " << true_length << endl;

    char *cursor, *end_ptr, *space_cursor;
    size_t shift_right_spots, num_chars_sofar=0, num_spaces=0;
    char replace_with[4] = "%20";


    cursor=str;
    end_ptr=str+strlen(str)+1;

    while (*cursor != '\0')
    {
    //    cout << "Number of characters scanned so far is: " << num_chars_sofar << endl;
    //    cout << "The string so far is: " << str << endl;
        while (!isspace(*cursor) && ((*cursor) != '\0'))
        {
            ++cursor;
            ++num_chars_sofar;
        }
        
        if (*cursor == '\0')
            break;

        space_cursor=cursor;
        num_spaces=0;

        while (isspace(*cursor) && ((*cursor) != '\0'))
        {
            ++cursor;
            ++num_spaces;
            ++num_chars_sofar;
        }
        
        if (*cursor == '\0')
            break;

        shift_right_spots=num_spaces * 3 - num_spaces;

        memmove(cursor + shift_right_spots, cursor, true_length - num_chars_sofar);
        for (size_t i=0; i < num_spaces; ++i)
        {
            strncpy(space_cursor, replace_with, 3);
            space_cursor += 3;
        }

        *end_ptr='\0';
        cursor += shift_right_spots;
    }
}

