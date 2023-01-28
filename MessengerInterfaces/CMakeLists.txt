add_custom_target(MessengerInterfaces_HEADERS SOURCES
    Event.hpp
    EventT.hpp
    IPort.hpp
    IEventHandler.hpp
    ILoginHub.hpp
)

add_library(MessengerInterfaces INTERFACE)
add_dependencies(MessengerInterfaces ${LIBRARY_NAME}_HEADERS)
target_include_directories(MessengerInterfaces INTERFACE .)
