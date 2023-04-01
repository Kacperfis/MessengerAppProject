#include <fstream>
#include <Tests/common/commonFixture.hpp>

void clearFile(const std::string& path)
{
    std::ofstream file(path);
    file << "";
}

