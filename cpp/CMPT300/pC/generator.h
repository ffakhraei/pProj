#ifndef GENERATOR_H
#define GENERATOR_H

class generator
{
    public:

        generator();
        //default constructuor
        
        ~generator();
        //class destructor

        void generate(char material, std::queue<char> output_buffer, std::size_t output_buffer_size);
        // precondition: material is either material_1, material_2, or material_3.
        // Postcondition: material is added 



    private:

        static const char material_1='a', material_2='b', material_3='c';
        // to represent three unique materials created by each generator
};

#endif
