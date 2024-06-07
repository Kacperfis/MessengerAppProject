#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <filesystem>

#include <Database/UserDatabaseController.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Common/Config/pathConfig.hpp>

TEST(UserDatabaseControllerTests, shouldLoadUserDataFromDatabaseSuccesfully)
{
    Logger::testName_ = "UserDatabaseControllerTests_shouldLoadDataFromDatabaseSuccesfully";
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB1/";
    auto userDatabaseController = std::make_shared<database::UserDatabaseController>(path);
    userDatabaseController->loadDatabase();
    EXPECT_EQ(userDatabaseController->getData().size(), 1);
}

TEST(UserDatabaseControllerTests, shouldRegisterUserSavingDataToDatabase)
{
    Logger::testName_ = "UserDatabaseControllerTests_shouldRegisterUserSavingDataToDatabase";
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB2/";
    auto userDatabaseController = std::make_shared<database::UserDatabaseController>(path);
    auto login = "userLogin123";
    auto password = "userPassword123";

    userDatabaseController->loadDatabase();
    EXPECT_EQ(userDatabaseController->getData().size(), 0);

    userDatabaseController->registerPerson(login, password);
    userDatabaseController->loadDatabase();
    const auto& data = userDatabaseController->getData();
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data.begin()->first, "userLogin123");
    EXPECT_EQ(data.begin()->second, "userPassword123");

    clearAllFilesFromFolder(path);
    setDefaultValueForIndexFile(config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB2/", "0");
}
