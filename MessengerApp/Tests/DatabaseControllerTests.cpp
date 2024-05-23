#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <filesystem>

#include <Database/DatabaseController.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Common/Config/pathConfig.hpp>

TEST(databaseControllerTests, shouldLoadDataFromDatabaseSuccesfully)
{
    Logger::testName_ = "databaseControllerTests_shouldLoadDataFromDatabaseSuccesfully";
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB1/";
    auto databaseController = std::make_shared<database::DatabaseController>(path);
    databaseController->LoadDatabase();
    EXPECT_EQ(databaseController->getRegisteredUsersData().size(), 1);
}

TEST(databaseControllerTests, shouldRegisterUserSavingDataToDatabase)
{
    Logger::testName_ = "databaseControllerTests_shouldRegisterUserSavingDataToDatabase";
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB2/";
    auto databaseController = std::make_shared<database::DatabaseController>(path);
    auto login = "userLogin123";
    auto password = "userPassword123";

    databaseController->LoadDatabase();
    EXPECT_EQ(databaseController->getRegisteredUsersData().size(), 0);

    databaseController->registerUser(login, password);
    databaseController->LoadDatabase();
    const auto& data = databaseController->getRegisteredUsersData();
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data.begin()->first, "userLogin123");
    EXPECT_EQ(data.begin()->second, "userPassword123");

    clearAllFilesFromFolder(path);
    setDefaultValueForIndexFile(config::path::pathPrefix + "MessengerApp/Tests/testDatabases/databaseControllerDB2/", "0");
}
