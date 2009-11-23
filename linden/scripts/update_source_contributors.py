#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""\
@file update_source_contributors.py
@brief Update the source contributor list in one place, instead of having 
to substitute by hand.  Derived from update_viewer_version.py

$LicenseInfo:firstyear=2006&license=viewergpl$

Copyright (c) 2006-2009, Linden Research, Inc.

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

import sys
import os.path
import string
import getopt, os, re, commands


lang_sep={"es":", ",
          "en-us":", ",
          "ru":", ",
          "hu":", ",
          "pl":", ",
          "ko":", ",
          "tr":", ",
          "it":", ",
          "da":", ",
          "pt":", ",
          "de":", ",
          "zh":", ",
          "fr":", ",
          "ja":"、",
          "uk":", "}

intro="Snowglobe includes source code contributions of the following residents: "

def add_indra_lib_path():
    root = os.path.realpath(__file__)
    # always insert the directory of the script in the search path
    dir = os.path.dirname(root)
    if dir not in sys.path:
        sys.path.insert(0, dir)

    # Now go look for indra/lib/python in the parent dies
    while root != os.path.sep:
        root = os.path.dirname(root)
        dir = os.path.join(root, 'indra', 'lib', 'python')
        if os.path.isdir(dir):
            if dir not in sys.path:
                sys.path.insert(0, dir)
            return root
    else:
        print >>sys.stderr, "This script is not inside a valid installation."
        sys.exit(1)

src_root = add_indra_lib_path()

from indra.util import llversion


def usage():
    print "Usage:"
    print sys.argv[0] + """ [options]

Options:
  --version
   Specify the version string to replace current version.
  --skip-on-branch
   Specify a regular expression against which the current branch
   is matched. If it matches, then leave version strings alone.
   Use this to avoid changing version strings on release candidate
   builds.
  --src-root
   Location of source tree
  --verbose
  --help
   Print this message and exit.
   
"""
def _getstatusoutput(cmd):
    """Return Win32 (status, output) of executing cmd
in a shell."""
    if os.path.sep != "/":
        # stupid #%#$$ windows
        cmd = 'cmd.exe /c "'+cmd+'"'
    pipe = os.popen(cmd, 'r')
    text = pipe.read()
    sts = pipe.close()
    if sts is None: sts = 0
    if text[-1:] == '\n': text = text[:-1]
    return sts, text

def get_contributors(filename):
    f = open(filename)

    credits={}
    contributors=[]
    thisres=''
    for line in f:
        m = re.search('^(\S+ +\S+)\s*$', line.strip())
        if(m):
            thisres=m.group(1)
            credits[thisres]=[]
            contributors.append(thisres)
        m = re.search('^\s+(\S+\-\d+)\s*$', line)
        if(m and thisres != ''):
            credits[thisres].append(m.group(1))
    return contributors

def main():
    global src_root
    global intro
    svn = os.path.expandvars("${SVN}")
    if not svn or svn == "${SVN}": svn = "svn"

    contributors = get_contributors(src_root + "/doc/contributions.txt")

    re_map = {}

    #re_map['filename'] = (('pattern', 'replacement'),
    #                      ('pattern', 'replacement')

    for lang in lang_sep.keys():
        filename='indra/newview/skins/default/xui/%(lang)s/floater_about.xml' % locals()
        searchpattern='%(intro)s.*\n' % {'intro':intro}
        replacelist=string.join(contributors, lang_sep[lang])
        replacement='%(intro)s%(replacelist)s\n' % {'intro':intro,'replacelist':replacelist}
        re_map[filename] = [[searchpattern, replacement]]

    verbose = False

    opts, args = getopt.getopt(sys.argv[1:],
                               "",
                               ['skip-on-branch=',
                                'src-root=',
                                'verbose',
                                'help'])
    skip_on_branch_re = None
    for o,a in opts:
        if o in ('--skip-on-branch'):
            skip_on_branch_re = re.compile(a)
        if o in ('--src-root'):
            src_root = a
        if o in ('--verbose'):
            verbose = True
        if o in ('--help'):
            usage()
            return 0

    if verbose:
        print "Source Path:", src_root
        if viewer_channel != None:
            print "Current viewer channel/version: '%(viewer_channel)s' / '%(viewer_version)s'" % locals()
        print

    # Iterate through all of the files in the map, and apply the
    # substitution filters
    for filename in re_map.keys():
        try:
            # Read the entire file into a string
            full_fn = src_root + '/' + filename
            file = open(full_fn,"r")
            file_str = file.read()
            file.close()

            if verbose:
                print "Processing file:",filename
            for rule in re_map[filename]:
                repl = rule[1]
                file_str = re.sub(rule[0], repl, file_str)

            file = open(full_fn,"w")
            file.write(file_str)
            file.close()
        except IOError:
            print "File %(filename)s not present, skipping..." % locals()
    return 0

main()

