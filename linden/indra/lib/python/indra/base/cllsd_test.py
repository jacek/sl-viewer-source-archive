"""\
@file cllsd_test.py
@brief 

$LicenseInfo:firstyear=2007&license=mit$

Copyright (c) 2007-2010, Linden Research, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
$/LicenseInfo$
"""
from indra.base import llsd, lluuid
from datetime import datetime
import cllsd
import time, sys

class myint(int):
    pass

values = (
    '&<>',
    u'\u81acj',
    llsd.uri('http://foo<'),
    lluuid.UUID(),
    llsd.LLSD(['thing']),
    1,
    myint(31337),
    sys.maxint + 10,
    llsd.binary('foo'),
    [],
    {},
    {u'f&\u1212': 3},
    3.1,
    True,
    None,
    datetime.fromtimestamp(time.time()),
    )

def valuator(values):
    for v in values:
        yield v

longvalues = () # (values, list(values), iter(values), valuator(values))

for v in values + longvalues:
    print '%r => %r' % (v, cllsd.llsd_to_xml(v))

a = [[{'a':3}]] * 1000000

s = time.time()
print hash(cllsd.llsd_to_xml(a))
e = time.time()
t1 = e - s
print t1

s = time.time()
print hash(llsd.LLSDXMLFormatter()._format(a))
e = time.time()
t2 = e - s
print t2

print 'Speedup:', t2 / t1
