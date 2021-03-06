
== Myelin ==

A non intrusive C++ introspection/reflection library primarliy intended
for easy automatic language bindings,


License: LGPL


Myelin uses advanced C++ template techniques to construct introspection metadata
for an entire shared library. It does this by parsing header files (with ANTLR3)
and wrapping around public definitions such as classes and functions.

However, unlike SWIG and other language binding generators it stores callbacks
and references to the library code within the library itself (although its
perfectly acceptable to store it in a separate 'binding' library). Inspired by
GObject Introspection and its flexibility having a fully introspected library
allows us to create truly dynamic language bindings. Python bindings, for
example, doesn't need to be created or generated for each project. Instead a
generic Myelin Python module is used which automatically loads the necessary
classes and functions maintaining Pythonic code style as much as possible.

The downside of this technique is likely a decrease in performance. Not only is
metadata alive within a library but it also wont be as fast as direct binding
which SWIG does rather well.

The upside is all about maintenance. Not only does it greatly reduce the amount
of extra code in maintaining bindings for each and every language, but it also
pushes the notion of bindings upstream. C++ libraries with introspection support
only pay the extra cost in binary size and not in performance, and this can be
made entirely optional within the build configuration process. Added to this the
relative ease of generating metadata it becomes rather trivial to extend the
reach of a C++ library to languages such as Python, Ruby, C# and so on.


Only Python bindings are supported for the time being however.


== Dependencies ==

Myelin Introspection Library:
	- None
	
Viewer Component:
	- Myelin Introspection library

Generator Component:
	- Antlr3 - http://antlr.org/
	- google-ctemplate - http://code.google.com/p/google-ctemplate/


