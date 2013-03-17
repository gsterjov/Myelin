import sys
sys.path.insert (0, ".")

from waflib import Utils
from waflib.Build import BuildContext


top = "."
out = "build"
includes = "include"



class TestContext (BuildContext):
	'''build and run the test suite'''
	cmd = 'test'
	fun = 'test'


class GeneratedContext (BuildContext):
	'''generate content needed to build the project'''
	cmd = 'generate'
	fun = 'generate'


def options (opt):
	opt.load ("compiler_c")
	opt.load ("compiler_cxx")

	opt.recurse ("src")


def configure (conf):
	# include source headers and generated headers
	src_inc_path = conf.path.abspath() + "/" + includes
	bld_inc_path = conf.path.get_bld().abspath() + "/" + includes

	conf.env.append_value ("CXXFLAGS", ['-fPIC'])
	conf.env.append_value ('INCLUDES', [src_inc_path, bld_inc_path])

	conf.load ("compiler_c")
	conf.load ("compiler_cxx")

	conf.recurse ("src")


def build (bld):
	if bld.options.enable_tests: bld.recurse ("test")

	bld.recurse ("src")


def generate (ctx):
	ctx.recurse ("src")


def test (ctx):
	ctx.recurse ("src")
	# ctx.recurse ("test")