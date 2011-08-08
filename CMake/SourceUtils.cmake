
#- Set a list of files prepending each header with the specified path
#
#  SET_HEADERS(<var_name> [PATH <path>] <header1> [<header2> ...])
#
function (set_headers var_name)
	
	if (${ARGV1} STREQUAL "PATH")
		set (path "${ARGV2}/")
		list (REMOVE_AT ARGN 0 1)
	endif()
	
	
	# create list of headers
	set (header_list)
	
	foreach (hdr IN LISTS ARGN)
		
		# get the absolute path
		if (NOT IS_ABSOLUTE "${hdr}")
			
			if (NOT ${path} STREQUAL "")
				#prepend path
				set (hdr "${path}${hdr}")
			endif()
			
		endif()
		
		# add to list
		list (APPEND header_list "${hdr}")
		
	endforeach()
	
	
	set (${var_name} ${header_list} PARENT_SCOPE)
	
endfunction()
