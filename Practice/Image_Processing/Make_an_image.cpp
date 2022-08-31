/*
 * Create .ppm image
 *  - more info:
 *     - https://www.youtube.com/watch?v=fbH005SzEMc&ab_channel=MarcusMathiassen
 *     - https://www.youtube.com/watch?v=Tw2tfYWWeVw&ab_channel=kupala
 */

#include <fstream>

void makeBiggerPpm();
void makeSmallerPpm();

int main()
{
    //makeBiggerPpm();
    makeSmallerPpm();
    
    return 0;
}

void makeBiggerPpm()
{
    std::ofstream img("bigger_picture.ppm");
    img << "P3" << std::endl;

    const int width = 255;
    const int height = 255;
    img << width << " " << height << std::endl;
    
    img << "255" << std::endl;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = x % 255;
            int g = y % 255;
            int b = y * x % 255;

            img << r << " " << g << " " << b << std::endl;
        }
    }

    system("explorer bigger_picture.ppm");
}

void makeSmallerPpm()
{
    std::ofstream img("smaller_picture.ppm");

    // Create Image .ppm tag
    img << "P3" << std::endl;
    const int width = 2;
    const int height = 2;
    img << width << " " << height << std::endl;
    img << "255" << std::endl;
    
    // Pixel must be created in following manner:
    // img << r << " " << g << " " << b << std::endl;

    // Create:
    //      RED     CYAN
    //      BLUE    MAGENTA
    img << 255 << " " << 0 << " " << 0 << std::endl; // RED
    img << 0 << " " << 255 << " " << 255 << std::endl; // CYAN
    img << 0 << " " << 0 << " " << 255 << std::endl; // BLUE
    img << 255 << " " << 0 << " " << 255 << std::endl; // MAGENTA

    // Create:
    //      BLACK   WHITE
    //      WHITE   BLACK
    // img << 0 << " " << 0 << " " << 0 << std::endl; // BLACK
    // img << 255 << " " << 255 << " " << 255 << std::endl; // WHITE
    // img << 255 << " " << 255 << " " << 255 << std::endl; // WHITE
    // img << 0 << " " << 0 << " " << 0 << std::endl; // BLACK

    system("explorer smaller_picture.ppm");
}