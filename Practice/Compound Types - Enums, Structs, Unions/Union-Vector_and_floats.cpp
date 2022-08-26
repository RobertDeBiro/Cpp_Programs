/*
 * Unions
 * - more info: https://www.youtube.com/watch?v=6uqU9Y578n4
 */

#include <iostream>

struct Vector2
{
    float x, y;
};

struct Vector4
{
    /* 
        Union containing 2 structs
         - union won't allocate the memory size needed to cover both structs,
           but rather only the memory size needed to cover bigger element, i.e. bigger struct
         - in this particular example both structs have the same size
         - so, union won't allocate memory for 8 floats (32 bytes), but rather for 4 floats (16 bytes)
         - memory location is reserved in following way (but, only if union and structs are anonymous???!):
           float x = a.x
           float y = a.y
           float z = b.x
           float w = b.y
    */
    union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            Vector2 a, b; // these are actually 4 float variables, so the same size as upper struct
        };
    };
};

void printVector2(const Vector2& vector)
{
    std::cout << vector.x << ", " << vector.y << std::endl;
}

int main()
{
    // Initialize 4 memory locations for vector
    Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };

    printVector2(vector.a);
    printVector2(vector.b);

    std::cout << "------------------------" << std::endl;
    
    vector.z = 500.0f;
    printVector2(vector.a);
    printVector2(vector.b);
    
    return 0;
}
