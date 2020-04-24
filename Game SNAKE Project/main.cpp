
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
        return 1;
    }
}

