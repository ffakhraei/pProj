#include <cstdlib>      //provides size_t, EXIT_SUCCESS
#include <cassert>      //provides assert()
#include <iostream>
#include <cstring>      //for string manipulation
#include <cctype>       //for character manipulation

using namespace std;

//template <class item>

bool has_unique_chars(const char* string);

int main(int argc, char* argv[])
{
    assert(argc > 1);

    int string_length = strlen(argv[1]);
    if (string_length == 0)
    {
        cout << "The string was empty.\n";
        return 0;
    }

    cout << "Do you want to distinguish between lower and upper case characters? [y/n]: ";
    char answer;
    cin >> answer;
    
    char *cursor=argv[1];

    if (answer == 'n' || answer == 'N')
        while (*cursor != '\0')
        {
            *cursor=tolower(*cursor);
            cout << *cursor;
            ++cursor;
        }
    cout << endl;
            
    
    if (has_unique_chars(argv[1]))
        cout << "The string has unique characters.\n";
    else 
        cout << "Some characters are repeatd in the string.\n";
    return 0;
}

bool has_unique_chars(const char* string)
{
    
    int string_length = strlen(string);
    if (string_length == 0)
        return true;

    int key=127, index=-1;
    int hash_table[128]={0};
    while (*string != '\0')
    {
        index = (*string)%key;
        if (hash_table[index] == 1)
            return false;
        else
            hash_table[index]=1;
        ++string;
    }

    return true;
}
