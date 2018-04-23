#!/usr/bin/env python
#coding:utf-8

"""
=================time the func==================
## Python标准库有 timeit 模块， 并且有profile/cProfile 模块测试程序性能
测试函数运行时间

timer(func, 1, 2, a=3, b=4, _reps=1000) calls and times func(1, 2, a=3, b=4) _reps times, and returns total time for all runs, with final result;

best(func, 1, 2, a=3, b=4, _reps=10) runs best-of-N timer to filter out any system load variation, and returns best time among _reps tests

"""

import time, sys

timefunc = time.cloack if sys.platform[:3]=="win" else time.time

def trace(*args):
    pass

def timer(func, *args, **kw):
    """
    timer(func, *args, **kw) => return (elasped->time, avg->average, ret->func(*args, **kw))
    time the func(*args, **kw) 测试func(*args, **kw)函数的运行时间
    """
    _reps = kw.pop('_reps', 1000)
    trace(func, args, kw, _reps)
    repslist = range(_reps)
    
    start = timefunc()
    for i in repslist:
        ret = func(*args, **kw)
    elasped = timefunc() - start

    return (elasped, elasped, ret)

def best(func, *args, **kw):
    """
    best(func, *args, **kw) => return (best, average->average of N times, ret->func(*args, **kw))
    best-of-_reps times 
    """
    _reps = kw.pop('_reps', 10)
    best = 2 ** 32
    sum_time = 0

    for i in range(_reps):
        (time, avg, ret) = timer(func, *args, _reps=1,  **kw)
        if time < best:
            best = time
            sum_time += avg

        return (best, sum_time/_reps, ret)


"""
========================test.py================
import sys, timer
reps = 1000
repslist = range(reps)

def forLoop():...

def listComp():...

def mapCall():...

def genExpr():...

def genFunc():...

print(sys.version)
for tester in (timer.timer, timer.best):
    print('<%s>' % tester.__name__)
    
    for test in (forLoop, listComp, mapCall, genExpr, genFunc):
        elasped, average, ret = tester(test)
        print('-' * 35)
        print('%-9s: best=%.5f \t average=%.5f => result: %s' % (test.__name__, elasped, average, ret))

"""

if __name__=="__main__":
    print("timer.py")
    print(sys.version)
