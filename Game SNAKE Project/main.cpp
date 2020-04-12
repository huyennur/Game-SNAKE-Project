//
//  main.cpp
//  Game SNAKE Project
//
//  Created by DO NGOC HUYEN on 4/6/20.
//  Copyright © 2020 DO NGOC HUYEN. All rights reserved.
//

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
    } catch (exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }
}

