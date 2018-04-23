#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
just for call
"""

import sys
from distutils.core import setup,Extension
from Cython.Build import cythonize

package_list = ["rklib"]
package_dir = {"rklib": "rklib"}


#exts = cythonize([Extension("fib", sources=["cfib.c", "fib.pyx"])])

metadata = {
		"name":"rklib",
		"version":"1.0.7",
		'description': "rklib",
		'long_description': __doc__,
		'author': "michael",
		'author_email': "Lizz007sci@126.com",
		'license': "MIT",
		'platforms': ["Linux","Mac OS-X","UNIX"],
		'url': "www.basepedia.com",
		'packages': package_list,
		'package_dir': package_dir,
		'data_files': [],
		'ext_modules': cythonize("*/*.pyx"),
		}

if __name__ == '__main__':
	dist = setup(**metadata)


