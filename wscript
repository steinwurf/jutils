#! /usr/bin/env python
# encoding: utf-8

APPNAME = "jutils"
VERSION = "2.2.0"


def configure(conf):

    conf.check_cxx(lib="android")


def build(bld):

    bld.recurse("src/jutils")

    if bld.is_toplevel():

        # Only build tests when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse("test")
