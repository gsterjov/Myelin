

find_package (PythonInterp REQUIRED)


execute_process (COMMAND
	${PYTHON_EXECUTABLE} -c "from distutils import sysconfig; print sysconfig.get_python_lib(True,prefix='${CMAKE_INSTALL_PREFIX}')"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
	OUTPUT_STRIP_TRAILING_WHITESPACE)


install (DIRECTORY myelin DESTINATION ${PYTHON_SITE_PACKAGES})
