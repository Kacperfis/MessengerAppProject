add_custom_target(MessengerInterfaces_HEADERS SOURCES
    ILoginHubFactory.hpp
    ILoginHub.hpp
    IDatabaseController.hpp
)

add_library(MessengerInterfaces INTERFACE)
add_dependencies(MessengerInterfaces ${LIBRARY_NAME}_HEADERS)
target_include_directories(MessengerInterfaces INTERFACE .)
