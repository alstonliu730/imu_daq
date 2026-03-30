# Use GLOB to find source files in the main directory
file(GLOB SOURCES "*.c")

# register the sources and include files with dependency libraries
idf_component_register(SRCS ${SOURCES}
                INCLUDE_DIRS "include"
                REQUIRES driver
                         esp_ringbuf)
