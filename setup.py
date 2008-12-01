from setuptools import distutils
from distutils.core import setup, Extension

module1 = Extension('processtitle',
                    sources = ['processtitle.c'])

setup (name = 'ProcessTitle',
       version = '0.0.1',
       description = 'Module for setting process titles',
       author = 'Purple Scout AB',
       ext_modules = [module1],
       zip_safe = False)
