#!/usr/bin/env python
"""\
@file start-client.py
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
import sys, getopt
import os
import llstart

def usage():
    print """start-client.py
    
    --grid <grid>
    --farm <grid>
    --region <starting region name>
    """

def start_client(grid, slurl, build_config, my_args):
    login_url = "https://login.%s.lindenlab.com/cgi-bin/login.cgi" % (grid)

    viewer_args = { "--grid" : grid,
                    "--loginuri" : login_url }
    viewer_args.update(my_args)
    # *sigh*  We must put --url at the end of the argument list.
    if viewer_args.has_key("--url"):
        slurl = viewer_args["--url"]
        del(viewer_args["--url"])
    viewer_args = llstart.get_args_from_dict(viewer_args)
    if slurl is not None:
        viewer_args += " --url %s" % slurl

    # Figure out path stuff.
    # The client should run from indra/newview
    # but the exe is at indra/build-<xxx>/newview/<target>
    build_path = os.path.dirname(os.getcwd());    
    f = open("start-client.log", "w")
    print >>f, "Viewer startup arguments:"
    llstart.start("viewer", "../../newview", 
        "%s/newview/%s/secondlife-bin.exe" % (build_path, build_config),
        viewer_args, f)
    f.close()

if __name__ == "__main__":
    grid = llstart.get_config("grid")
    
    if grid == None:
        grid = "aditi"
        
    build_config = llstart.get_config("build_config")
    my_args = llstart.get_config("viewer_args", force_dict = True)
    opts, args = getopt.getopt(sys.argv[1:], "u:r:f:g:i:h",
        ["region=", "username=", "farm=", "grid=", "ip=", "help"])
    region = None
    for o, a in opts:
        if o in ("-r", "--region", "-u", "--username"):
            region = a
        if o in ("-f", "--farm", "-g", "--grid"):
            grid = a
        if o in ("-h", "--help"):
            usage()
            sys.exit(0)
            
    slurl = llstart.get_config("slurl")            
    if slurl == None:
        if region is None:
            region = llstart.get_user_name()
        slurl = "//%s/128/128/" % (region)
    # Ensure the slurl has quotes around it.
    if slurl is not None:
        slurl = '"%s"' % (slurl.strip('"\''))
    
    start_client(grid, slurl, build_config, my_args)
