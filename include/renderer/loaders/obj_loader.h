#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <renderer/mesh.h>

class Obj_loader{
public:
    Mesh load_obj(const char* filename);
};