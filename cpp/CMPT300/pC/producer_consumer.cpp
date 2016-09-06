#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>


using namespace std;

class generators
{
    public:
        generators();
        //constructor

        ~generators();
        //destructor

        void generate(char material, queue<char> input_buffer, size_t input_buffer_size);
        //precondition: input_buffer is not full
        //postcondition: one "material" is added to the input_buffer queue 


    private:

};

class materials
{
    public:

    private:

};

class products
{
    public:

    private:
};

class operators
{
    public:
        operators();
        //constructor

        ~operators();
        //destructor

        void grab_tool();
        //postcondition: operator has acquired one tool

        void release_tool();
        //postcondition: operator has released one tool

        void grab_material();
        //postcondition: operator has acquired one material

        void release_material();
        //postcondition: operator has released one material

        void produce();
        //postcondition: a random amount between 0.01 to 1 second has passed, and a final product based on the initial materials has been produced and added to the output buffer
    private:

};

void* print_hello(void*)
{
    cout << "Hello world from thread id: " << endl;

}

int main(int argc, char* argv[])
{
    pthread_t generator1, generator2, generator3, operator1, operator2, operator3;

    int generator_ids[3];
    int operator_ids[3];

    size_t number_of_genrators=3, number_of_operators=3, number_of_tools=3;

    generator_ids[1]=pthread_create(&generator1, NULL, &print_hello, NULL);
    
    if ( generator_ids[1] )
    {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", generator_ids[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
