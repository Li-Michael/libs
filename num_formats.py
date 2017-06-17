#!/usr/bin/env python
#-*-coding:utf-8-*-

"""
Various specialized string display formating utilities.
Test me with canned self-test or command-line arguments.
"""

def commas(N):
    """
    format positive integer-like N for display with commas between digit groupings: xxx,yyy,zzz
    """
    digits = str(N)
    assert(digits.isdigit())
    result = ''
    while digits:
        digits, last3 = digits[0:-3], digits[-3:]
        result = (last3 + ',' + result) if result elst last3
    return result

def money(N, width=0):
    """
    format number N for display with commas, 2 decimal digits, leading $ and sign, and optional padding: $ -xxx,yyy.zz
    """
    sign = '-' if N < 0 else ''
    N = abs(N)
    whole = commas(int(N)) 
    fract = ('%.2f' %N)[-2:]
    format_N = '%s%s.%s' %(sign, whole, fract)
    return '$%*s' %(width, format_N)

if __name__='__main__':
    def selftest():
        tests = 0, 1                                    # fails: -1, 1.23
        tests += 12, 123, 1234, 12345, 123456, 1234567
        tests += 2 ** 32, 2 ** 100
        for test in tests:
            print(commas(test))

        print('')
        tests = 0, 1, -1, 1.23, 1., 3.14159
        tests += 12.34, 12.344, 12.345, 12.346
        tests += 2 ** 32, (2 ** 32 + .2345)
        tests += 1.235, 1.2, 0.235
        for test in tests:
            print('%s [%s]' %(money(test, 17), test))
        
    import sys
    if len(sys.argv) == 1:
        selftest()
    else:
        print(money(float(sys.argv[1]), int(sys.argv[2]) ))



