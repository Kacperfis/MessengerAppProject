#include <gtest/gtest.h>
#include <iostream>

#include <Database/DatabaseController.hpp>
#include <Tests/common/commonFixture.hpp>

TEST(databaseControllerTests, shouldLoadDataFromDatabaseSuccesfully)
{
    const std::string path = "/workspaces/MessengerAppProject/MessengerApp/Tests/testDatabases/testLoadDatabase.txt";
    auto databaseController = std::make_shared<DatabaseController>(path);
    databaseController->LoadDatabase();
    EXPECT_EQ(databaseController->getRegisteredUsersData().size(), 2);
}

TEST(databaseControllerTests, shouldRegisterUserSavingDataToDatabase)
{
    const std::string path = "/workspaces/MessengerAppProject/MessengerApp/Tests/testDatabases/testSaveDatabase.txt";
    auto databaseController = std::make_shared<DatabaseController>(path);
    auto login = "userLogin123";
    auto password = "userPassword123";
    databaseController->LoadDatabase();
    EXPECT_EQ(databaseController->getRegisteredUsersData().size(), 0);
    databaseController->registerUser(login, password);
    databaseController->LoadDatabase();
    const auto& data = databaseController->getRegisteredUsersData();
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data.begin()->first, "userLogin123");
    EXPECT_EQ(data.begin()->second, "userPassword123\n");
    clearFile(path);
}
