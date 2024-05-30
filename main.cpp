#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

int main(int argc, char** argv)
{
    if (argc == 0)
    {
        cerr << "too few arguments.\n";
        return 1;
    }

    char* program_path = argv[0];

    if (argc < 3)
    {
        cerr << "too few arguments.\n";
        cout << "usage: " << program_path << " ./file/to/watch ./command/to/run\n";
        return 1;
    }

    char* file_path = argv[1];
    char* command = argv[2];
    string compare;

    while (true)
    {
        ifstream file(file_path);
        string buffer;
        char read;

        while (file >> read) buffer += read;

        if (compare != buffer)
        {
            cout << "file changed: " << command << "\n";
            system(command);
            compare = buffer;
        }

        this_thread::sleep_for(chrono::seconds(5));
    }
}
