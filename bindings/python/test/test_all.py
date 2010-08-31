
import unittest
import os.path
import sys

sys.path.append (os.path.pardir)

import test_introspection


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity=2).run (test_introspection.suite)
