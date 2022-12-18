
#include <libdaap/libdaap.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

static const char *kTestFile = "server-info";

int main(int argc, char *argv[])
{
    ifstream in(argc == 2 ? argv[1] : kTestFile);
    if (!in)
    {
        cout << "test: could not open \"" << kTestFile << "\"" << endl;
        exit(1);
    }

//    try
//    {
        uint8_t data[65536];
        uint32_t length;

        in.read((char *)data, sizeof(data));
        length = in.gcount();

        DAAP::Chunk *chunk = DAAP::Chunk::ReadChunk(data, length, true);
        cout << "*** BEGIN PARSED OUTPUT ***" << endl;
        const char* tmp = DAAP::Chunk::GetValueOf(chunk, "dmap.itemname");
        cout << tmp << endl;
        delete tmp;
        cout << *chunk << endl;
        cout << "*** END PARSED OUTPUT ***" << endl;
        delete chunk;
//    }
//    catch (char *&err)
//    {
//        cout << "Caught exception: " << err << endl;
//        exit(1);
//    }
//    catch (...)
//    {
//        cout << "Caught unknown exception!" << endl;
//        exit(1);
//    }

    return 0;
}
