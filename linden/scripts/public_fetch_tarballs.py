#!/usr/bin/python
"""\
@file public_fetch_tarballs.py
@author Rob Lanphier
@date 2009-05-30
@brief Fetch + extract tarballs and zipfiles listed in doc/asset_urls.txt

$LicenseInfo:firstyear=2009&license=viewergpl$
Copyright (c) 2009, Linden Research, Inc.

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

# Look for indra/lib/python in all possible parent directories ...
# This is an improvement over the setup-path.py method used previously:
#  * the script may blocated anywhere inside the source tree
#  * it doesn't depend on the current directory
#  * it doesn't depend on another file being present.

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

base_dir = add_indra_lib_path()
print base_dir

import os
import sys
import re
import urllib
import zipfile
import tarfile
import optparse
import tempfile

import indra.util.helpformatter

# load + parse doc/asset_urls.txt
def get_asset_urls():
    asset_urls={}
    f = open(os.path.join(base_dir,"doc", "asset_urls.txt"))
    for line in f:
        line=line.strip()
        (name, value)=re.split("=", line, 1)
        asset_urls[name]=value
    return asset_urls

# Filename from a URL
def get_asset_filename_from_url(asseturl, targetdir):
    i = asseturl.rfind('/')
    filename = os.path.join(targetdir, asseturl[i+1:])
    return filename


# Extract .zip file to targetdir.  Called by extract_archive_sans_linden.
def extract_zipfile_sans_linden(filename, targetdir):
    archive = zipfile.ZipFile(filename, 'r')
    names = archive.namelist()
    for path in names:
        if(path=="linden/"):
            pass
        target = os.path.join(targetdir, re.sub("linden/", "", path))
        subdir = os.path.dirname(target)
        if not os.path.exists(subdir):
            os.makedirs(subdir)
        if not os.path.exists(target):
            fp = open(target, 'wb')
            fp.write(archive.read(path))
            fp.close()
    archive.close()


# Extract .tar.gz file to targetdir.  Called by extract_archive_sans_linden.
def extract_tarball_sans_linden(filename, targetdir):
    archive = tarfile.TarFile.open(filename, 'r')
    # get a series of TarInfo objects
    tarentries=archive.getmembers()
    for tarentry in tarentries:
        target = re.sub(r'^(\./)?(linden/)?', "", tarentry.name)
        if(target==""):
            continue
        fulltarget=os.path.join(targetdir, target)
        subdir = os.path.dirname(fulltarget)
        if not os.path.exists(subdir):
            os.makedirs(subdir)
        if not os.path.exists(fulltarget):
            # Reset the name property on the TarInfo object, so it writes the
            # file exactly where we want it.  It's hard telling for sure if this
            # property is intended to be written to, but it works for now.
            tarentry.name=fulltarget
            # Calling TarFile.extract with the "path" parameter doesn't work as
            # we might hope, because the path components in the tarball get
            # appended to the "path" parameter.  Hence the reason for passing in
            # the TarInfo object with the munged name property
            archive.extract(tarentry)
    archive.close()

# Extract either .tar.gz file or .zip file to targetdir, stripping off the 
# leading "linden" directory, but leaving the directory structure otherwise 
# intact.
def extract_archive_sans_linden(filename, targetdir):
    if(filename.endswith('.tar.gz')):
        extract_tarball_sans_linden(filename, targetdir)
    elif(filename.endswith('.zip')):
        extract_zipfile_sans_linden(filename, targetdir)
    else:
        raise Exception, "Unhandled archive type" 

def get_assetnames_by_platform(platform):
    assetnames=['SLASSET_ART']
    if(platform=='linux' or platform=='all'):
        assetnames.append('SLASSET_LIBS_LINUXI386')
    if(platform=='darwin' or platform=='all'):
        assetnames.append('SLASSET_LIBS_DARWIN')
    if(platform=='windows' or platform=='all'):
        assetnames.append('SLASSET_LIBS_WIN32')
    return assetnames

# adapted from install.py
def _get_platform():
    "Return appropriate platform packages for the environment."
    platform_map = {
        'darwin': 'darwin',
        'linux2': 'linux',
        'win32' : 'windows',
        'cygwin' : 'windows',
        'solaris' : 'solaris'
        }
    this_platform = platform_map[sys.platform]
    return this_platform

# copied from install.py
def _default_installable_cache():
    """In general, the installable files do not change much, so find a 
    host/user specific location to cache files."""
    user = _getuser()
    cache_dir = "/var/tmp/%s/install.cache" % user
    if _get_platform() == 'windows':
        cache_dir = os.path.join(tempfile.gettempdir(), \
                                 'install.cache.%s' % user)
    return cache_dir

# For status messages (e.g. "Loading...").  May come in handy if
# we implement a "quiet" mode.
def _report(string):
    print string


# copied from install.py
def _getuser():
    "Get the user"
    try:
        # Unix-only.
        import getpass
        return getpass.getuser()
    except ImportError:
        import win32api
        return win32api.GetUserName()

# adapted from install.py
def _parse_args():
    parser = optparse.OptionParser(
        usage="usage: %prog [options]",
        formatter = indra.util.helpformatter.Formatter(),
        description="""This script fetches and installs tarballs and \
zipfiles ("asset bundles") listed in doc/asset_urls.txt

If no asset bundles are specified on the command line, then the default \
behavior is to install all known asset bundles appropriate for the platform \
specified.  You can specify more than one asset bundle on the command line.

Example:
  %prog SLASSET_ART

  This looks for the "SLASSET_ART" entry in doc/asset_urls.txt, and extracts
  the corresponding asset bundle into your source tree.
""")
    parser.add_option(
        '-p', '--platform', 
        type='choice',
        default=_get_platform(),
        dest='platform',
        choices=['windows', 'darwin', 'linux', 'solaris', 'all'],
        help="""Override the automatically determined platform. \
You can specify 'all' to get assets for all platforms.  Choices: windows, \
darwin, linux, solaris, or all.  Default: autodetected (%s)""" % \
             _get_platform())
    parser.add_option(
        '--cache-dir', 
        type='string',
        default=_default_installable_cache(),
        dest='cache_dir',
        help='Where to download files. Default: %s'% \
             (_default_installable_cache()))
    parser.add_option(
        '--install-dir', 
        type='string',
        default=base_dir,
        dest='install_dir',
        help='Where to unpack the installed files.  Default: %s' % base_dir)

    return parser.parse_args()

def main(argv):
    options, args = _parse_args()
    # 1. prepare cache dir
    if not os.path.exists(options.cache_dir):
        os.makedirs(options.cache_dir)

    # 2. read doc/asset_urls.txt
    asseturls=get_asset_urls()

    # 3. figure out which asset bundles we'll be downloading
    if len(args)>0:
        assetnames=args
    else:
        assetnames=get_assetnames_by_platform(options.platform)

    # 4. download and extract each asset bundle
    for asset in assetnames:
        # 4a. get the URL for the asset bundle
        try:
            asseturl=asseturls[asset]
        except:
            print "No asset in doc/asset_urls.txt named %s" % asset
            sys.exit(2)
        # 4b. figure out where to put the downloaded asset bundle
        filename=get_asset_filename_from_url(asseturl, options.cache_dir)

        # 4c. see if we have it, and if not, get it
        if os.path.exists(filename):
            _report("Using already downloaded "+filename+" ...")
        else:
            _report("Downloading "+filename+" ...")
            urllib.urlretrieve(asseturl, filename)
        # 4d. extract it into the tree
        extract_archive_sans_linden(filename, options.install_dir)

# execute main() only if invoked directly:
if __name__ == "__main__":
    sys.exit(main(sys.argv))

