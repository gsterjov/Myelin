

option (BUILD_PYTHON_BINDINGS "Build and install Python bindings?")


if (BUILD_PYTHON_BINDINGS)
	add_subdirectory (python)
endif()
