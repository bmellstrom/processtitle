from setuptools import distutils
from distutils.core import setup, Extension
import sys

name = 'ProcessTitle'
version = '0.0.1'
description = 'Module for setting process titles'
author = 'Purple Scout AB'

if sys.platform == "linux2":
    module1 = Extension('processtitle',
                        sources = ['processtitle.c'])

    setup(name = name,
          version = version,
          description = description,
          author = author,
          ext_modules = [module1],
          zip_safe = False)

else:
    setup(name = name,
          version = version,
          description = description,
          author = author,
          py_modules = ['processtitle'],
          zip_safe = True)
