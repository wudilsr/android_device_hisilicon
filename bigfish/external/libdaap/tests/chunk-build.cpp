
#include <libdaap/libdaap.h>
#include <iostream>
#include <fstream>

using namespace std;

// We can't use iTunes' server-info because it has a bogus length
static const char *kTestFile = "content-codes";

int main(int argc, char *argv[])
{
    ifstream in(kTestFile);
    if (!in)
    {
        cout << "test: could not open \"" << kTestFile << "\"" << endl;
        exit(1);
    }

    try
    {
        uint8_t read[65536];
        uint32_t length;

        in.read((char *)read, sizeof(read));
        length = in.gcount();

        DAAP::Chunk *chunk = DAAP::Chunk::ReadChunk(read, length, true);

        if (chunk->BuildData() != length)
        {
            cout << "Build length != read length!" << endl;
            exit(1);
        }

        uint8_t *built = new uint8_t[length];
        chunk->BuildData(length, built);

        if (memcmp(read, built, length))
        {
            cout << "Built data != read data!" << endl;
            exit(1);
        }

        delete built;
        delete chunk;
    }
    catch (char *&err)
    {
        cout << "Caught exception: " << err << endl;
        exit(1);
    }
    catch (...)
    {
        cout << "Caught unknown exception!" << endl;
        exit(1);
    }

    return 0;
}
