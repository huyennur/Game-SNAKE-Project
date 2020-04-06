//
//  Check.h
//  Game SNAKE Project
//
//  Created by DO NGOC HUYEN on 4/6/20.
//  Copyright © 2020 DO NGOC HUYEN. All rights reserved.
//

#ifndef Check_h
#define Check_h

#pragma once
//#pragma once dùng để tránh việc include trùng lặp qua các file
#include <stdexcept>
#include <string>

using namespace std;

#define SDL_CHECK(x, msg) if (!(x))throw runtime_error(string(msg": ") + SDL_GetError());


#endif /* Check_h */
