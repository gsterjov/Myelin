
import unittest
from myelin.introspection import *



class TestType (unittest.TestCase):
    
    def runTest (self):
        self.test_creation()
    
    
    def test_creation (self):
        self.assertRaises (NotImplementedError, Type)



suite = unittest.TestSuite([TestType()])
