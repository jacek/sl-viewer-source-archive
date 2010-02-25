#!/usr/bin/python
"""\
@file   test_llxmlrpc_peer.py
@author Nat Goodspeed
@date   2008-10-09
@brief  This script asynchronously runs the executable (with args) specified on
        the command line, returning its result code. While that executable is
        running, we provide dummy local services for use by C++ tests.

$LicenseInfo:firstyear=2008&license=viewergpl$

Copyright (c) 2008-2010, Linden Research, Inc.

Second Life Viewer Source Code
The source code in this file ("Source Code") is provided by Linden Lab
to you under the terms of the GNU General Public License, version 2.0
("GPL"), unless you have obtained a separate licensing agreement
("Other License"), formally executed by you and Linden Lab.  Terms of
the GPL can be found in doc/GPL-license.txt in this distribution, or
online at http://secondlifegrid.net/programs/open_source/licensing/gplv2

There are special exceptions to the terms and conditions of the GPL as
it is applied to this Source Code. View the full text of the exception
in the file doc/FLOSS-exception.txt in this software distribution, or
online at
http://secondlifegrid.net/programs/open_source/licensing/flossexception

By copying, modifying or distributing this software, you acknowledge
that you have read and understood your obligations described above,
and agree to abide by those obligations.

ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
COMPLETENESS OR PERFORMANCE.
$/LicenseInfo$
"""

import os
import sys
from threading import Thread
from SimpleXMLRPCServer import SimpleXMLRPCServer

mydir = os.path.dirname(__file__)       # expected to be .../indra/newview/tests/
sys.path.insert(0, os.path.join(mydir, os.pardir, os.pardir, "lib", "python"))
sys.path.insert(1, os.path.join(mydir, os.pardir, os.pardir, "llmessage", "tests"))
from testrunner import run, debug

class TestServer(SimpleXMLRPCServer):
    def _dispatch(self, method, params):
        try:
            func = getattr(self, method)
        except AttributeError:
            raise Exception('method "%s" is not supported' % method)
        else:
            # LLXMLRPCListener constructs XMLRPC parameters that arrive as a
            # 1-tuple containing a dict.
            return func(**(params[0]))

    def hello(self, who):
        # LLXMLRPCListener expects a dict return.
        return {"hi_there": "Hello, %s!" % who}

    def getdict(self):
        return dict(nested_dict=dict(a=17, b=5))

    def log_request(self, code, size=None):
        # For present purposes, we don't want the request splattered onto
        # stderr, as it would upset devs watching the test run
        pass

    def log_error(self, format, *args):
        # Suppress error output as well
        pass

class ServerRunner(Thread):
    def run(self):
        server = TestServer(('127.0.0.1', 8000))
        debug("Starting XMLRPC server...\n")
        server.serve_forever()

if __name__ == "__main__":
    sys.exit(run(server=ServerRunner(name="xmlrpc"), *sys.argv[1:]))
