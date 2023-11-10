#include <MessengerAgent.hpp>
#include <Common/Config/pathConfig.hpp>

int main()
{
    MessengerAgent(config::path::pathPrefix + "MessengerApp/Database/RegisteredUserData/", std::cin);
    return 0;
}