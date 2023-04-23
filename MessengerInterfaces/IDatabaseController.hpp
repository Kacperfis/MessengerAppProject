#pragma once

#include <map>
#include <string>

class IDatabaseController
{
public:
    virtual ~IDatabaseController() {};
    virtual void LoadDatabase() = 0;
    virtual void registerUser(const std::string&, const std::string&) = 0;
    virtual const std::map<std::string, std::string> getRegisteredUsersData() const = 0;
};
