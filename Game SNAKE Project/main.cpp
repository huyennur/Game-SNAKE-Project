#include "Snake.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
// make an exception
int main(int argc, const char **arg)
{
 try
    {
    Snake s;
    return s.exec();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        // cerr: output stream for errors
        // what() : Returns a null terminated character sequence that may be used to identify the exception.
        return 1;
    }
}

