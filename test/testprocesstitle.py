# encoding: utf-8
# vim:set shiftwidth=4 tabstop=4 expandtab textwidth=120:
# Respect whitespace settings!
"""

Copyright (c) 2009 Purple Scout. All rights reserved.

"""
import unittest
import processtitle

class TestProcessTitle(unittest.TestCase):
    def test_gettitlemaxlen(self):
        a = processtitle.gettitlemaxlen()

    def test_gettitle(self):
        s = processtitle.gettitle()
        self.assertTrue(isinstance(s, basestring))

    def test_settitle(self):
        processtitle.settitle("the cow")

    def test_getkilltitlemaxlen(self):
        a = processtitle.getkilltitlemaxlen()

    def test_getkilltitle(self):
        s = processtitle.getkilltitle()
        self.assertTrue(isinstance(s, basestring))

    def test_setkilltitle(self):
        processtitle.settitle("cow")
