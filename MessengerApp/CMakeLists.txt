set(TARGET_NAME MessengerApp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(MESSENGER_APP_SOURCES
    #main.cpp # uncomment to create the binary
    Common/Logger.cpp
    Connection/Client/Client.cpp
    Connection/Server/Server.cpp
    Connection/Server/Session.cpp
    Connection/Helpers/Message.cpp
    Connection/Helpers/MessageDecoder.cpp
    Connection/Helpers/MessageHandler.cpp
    MessengerAgent.cpp
    Login/AdminLoginHub.cpp
    Login/UserLoginHub.cpp
    Login/AdminLoginHubCreator.cpp
    Login/UserLoginHubCreator.cpp
    Registration/UserRegistrationHandler.cpp
    Registration/AdminRegistrationHandler.cpp
    Encryption/EncryptionManager.cpp
    Helpers/LoginHubHelper.cpp
    Helpers/UIHelper.cpp
    Database/UserDatabaseController.cpp
    Database/AdminDatabaseController.cpp
)
set(MESSENGER_APP_HEADERS
    Common/Logger.hpp
    Common/Config/pathConfig.hpp
    Connection/Client/Client.hpp
    Connection/Server/Server.hpp
    Connection/Server/Session.hpp
    Connection/Helpers/Message.hpp
    Connection/Helpers/MessageDecoder.hpp
    Connection/Helpers/MessageHandler.hpp
    MessengerAgent.hpp
    Login/AdminLoginHub.hpp
    Login/UserLoginHub.hpp
    Login/AdminLoginHubCreator.hpp
    Login/UserLoginHubCreator.hpp
    Login/LoginData.hpp
    Registration/UserRegistrationHandler.hpp
    Registration/AdminRegistrationHandler.hpp
    Encryption/EncryptionManager.hpp
    Helpers/LoginHubHelper.hpp
    Helpers/UIHelper.hpp
    Database/UserDatabaseController.hpp
    Database/AdminDatabaseController.hpp
)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${OPENSSL_LIBRARY_DIR})

add_library(${TARGET_NAME} STATIC ${MESSENGER_APP_SOURCES} ${MESSENGER_APP_HEADERS})
target_link_libraries(${TARGET_NAME}
    MessengerInterfaces
    ${OPENSSL_CRYPTO_LIBRARY}
    Boost::boost
)

enable_testing()
set(TEST_SOURCES
    Tests/common/commonFixture.cpp
    Tests/UserLoginHubTests.cpp
    Tests/AdminLoginHubTests.cpp
    Tests/EncryptionManagerTests.cpp
    Tests/UserDatabaseControllerTests.cpp
    Tests/AdminDatabaseControllerTests.cpp
    Tests/UserRegistrationHandlerTests.cpp
    Tests/AdminRegistrationHandlerTests.cpp
    Tests/MessageTests.cpp
    Tests/MessageHandlerTests.cpp
    Tests/MessageDecoderTests.cpp
)

set(UT_DRIVER ut)
add_executable(${UT_DRIVER} ${TEST_SOURCES})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock)

# uncomment to create the binary
# add_executable(${TARGET_NAME}_exec main.cpp)
# target_link_libraries(${TARGET_NAME}_exec ${TARGET_NAME})

if (BUILD_COVERAGE_UNIT_TESTS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    set_target_properties(${UT_DRIVER} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    target_link_libraries(${UT_DRIVER} ${CMAKE_CXX_COVERAGE_LIBRARY})
    setup_target_for_coverage(${UT_DRIVER}_COV ${UT_DRIVER} ${COVERAGE_REPORT_LOCATION})
endif()

add_test(tests ${UT_DRIVER})

