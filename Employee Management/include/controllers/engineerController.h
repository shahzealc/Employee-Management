#pragma once

#include "../Engineer.h"
class Engineer;

class EngineerController {
public:
    static bool insertEngineerController(Engineer& dept);
    static bool deleteEngineerController(Engineer& dept, std::string attribute);
    static bool updateEngineerController(Engineer& dept, std::string attribute);
    static bool viewEngineerController(std::string selectQuery);
};