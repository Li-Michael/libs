#!/usr/bin/env python
#-*-coding:utf-8-*-

"""
reloadall.py: transitively reload nested modules
"""

import types
#from imp import reload  # from required in 3.0

def status(module):
    print('reloading '+ module.__name__)

def transitive_reload(module, visited):             
    if not module in visited:                       # Trap cycles, duplicates
        status(module)                              # Reload this module
        reload(module)                              # And visit children
        visited[module] = None
        for attrobj in module.__dict__.values():    # For all attrs Recur if module
            if type(attrobj) == types.ModuleType:   # if isinstance(attrobj, types.ModuleType)
                transitive_reload(attrobj, visited)

def reload_all(*args):
    visited = {}
    for arg in args:
        if type(arg) == types.ModuleType:
            transitive_reload(arg, visited)

if __name__=='__main__':                             # Test code:reload myself, should reload this, types
    import reloadall
    reload_all(reloadall)

