from distutils.core import setup, Extension
import sys

version = '0.1.0'
author = 'Purple Scout AB'
description = 'Module for setting process titles'
author_email = "info@purplescout.se"

if sys.platform == "linux2":
    name = "processtitle"
    processtitle = Extension('processtitle', sources = ['processtitle.c'])

    setup(name = name,
          version = version,
          author = author,
          author_email = author_email,
          url = "http://www.purplescout.se",
          description = description,
          ext_modules = [processtitle])

else:
    name = 'ProcessTitle'

    setup(name = name,
          version = version,
          description = description,
          author = author,
          py_modules = ['processtitle'],
          zip_safe = True)
