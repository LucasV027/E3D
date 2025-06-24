#pragma once

#include <cassert>

namespace E3D {
    #define panic(error) assert(false && error);
}
