#include <iostream>
#include <string>
#include <filesystem>

#if defined(__linux__)
    #include <unistd.h> // readlink
    #include <limits.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

std::string getExecutablePath() {
    char buffer[PATH_MAX]; // PATH_MAX is defined inside "limits.h"

#if defined(__linux__)
    // "/proc/self/exe" is a symbolic link that points to the executable of the current running process
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        return std::string(buffer);
    }
#elif defined(_WIN32)
    GetModuleFileName(NULL, buffer, sizeof(buffer));
    return std::string(buffer);
#endif

    return std::string();
}

int main()
{
    std::cout << "*****************************************************\n";

    std::string exePath = getExecutablePath();

    if (!exePath.empty())
    {
        std::cout << "Executable Path: " << exePath << std::endl;
    }
    else
    {
        std::cerr << "Error: Unable to retrieve executable path" << std::endl;
    }

    std::cout << "*****************************************************\n";
    return 0;
}
