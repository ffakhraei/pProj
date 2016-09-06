#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

void set_to_zero(int** array, int row_numbers, int column_numbers);

int main(int argc, char* argv[])
{
    int array[5][4]={{1, 2, 3, 0}, {1, 2, 3, 4}, {1, 0, 2, 3}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    int array_b[5][4];

    for (int i=0; i < 5; ++i)
    {
        for (int j=0; j < 4; ++j)
        {
            cout << array[i][j] << " ";
            if (array[i][j] == 0)
                array_b[i][j]=0;
            else 
                array_b[i][j]=1;
        }
        cout << endl;
    }
    cout << endl;

    for (int i=0; i < 5; ++i)
    {
        for (int j=0; j < 4; ++j)
            cout << array_b[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    
    for (int i=0; i < 5; ++i)
    {
        for (int j=0; j < 4; ++j)
        {
            if (array_b[i][j] == 0)
            {
                for (int k=0; k < 5; ++k)
                        array[k][j]=0;
                for (int l=0; l < 4; ++l)
                        array[i][l]=0;
            }
        }
        cout << endl;
    }

    for (int i=0; i < 5; ++i)
    {
        for (int j=0; j < 4; ++j)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }


    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------
//  FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

void set_to_zero(int** array, int row_numbers, int column_numbers)
{

}
