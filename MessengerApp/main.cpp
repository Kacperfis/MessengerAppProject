#include <MessengerAgent.hpp>
#include <Common/Config/pathConfig.hpp>

int main()
{
    agent::MessengerAgent(
        config::path::pathPrefix + "MessengerApp/Database/RegisteredUserData/",
        config::path::pathPrefix + "MessengerApp/Database/RegisteredAdminData/",
        std::cin);

    return 0;
}