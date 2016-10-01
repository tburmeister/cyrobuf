import re
import os
import sys
import glob
import argparse
from distutils.core import setup

from jinja2 import Environment, PackageLoader

from pyrobuf.parse_proto import Parser


HERE = os.path.dirname(os.path.abspath(__file__))

def main():
    args = cli_argument_parser()
    gen_message(args.source, out=args.out_dir, build=args.build_dir, install=args.install)

def cli_argument_parser():
    parser = argparse.ArgumentParser("cyrobuf", description="a Cython based protobuf compiler")
    parser.add_argument('source', type=str,
                        help="filename.proto or directory containing proto files")
    parser.add_argument('--out-dir', default='out',
                        help="output directory [default: out]")
    parser.add_argument('--build-dir', default='build',
                        help="C compiler build directory [default: build]")
    parser.add_argument('--install', action='store_true',
                        help="install the extension [default: False]")
    return parser.parse_args()

def gen_message(fname, out="out", build="build", install=False):

    parser = Parser()

    env = Environment(loader=PackageLoader('cyrobuf.protobuf', 'templates'))
    templ_h = env.get_template('proto_h.tmpl')
    templ_c = env.get_template('proto_c.tmpl')

    try:
        os.makedirs(out)
    except:
        pass

    script_args = ['build', '--build-base={0}'.format(build)]
    if install:
        script_args.append('install')

    if os.path.isdir(fname):
        for spec in glob.glob(os.path.join(fname, '*.proto')):
            generate(spec, out, parser, templ_h, templ_c)

        _, name = os.path.split(fname)
        c = os.path.join(out, '*.c')

    else:
        name, _ = os.path.splitext(os.path.basename(fname))
        if not name:
            print("not a .proto file")
            return

        generate(fname, out, parser, templ_h, templ_c)

        c = os.path.join(out, "%s_proto.c" % name)

    setup(name=name, script_args=script_args)

def generate(fname, out, parser, templ_h, templ_c):

    print("generating {0}".format(fname))

    m, _ = os.path.splitext(os.path.basename(fname))

    name_h = "%s_proto.h" % m
    name_c = "%s_proto.c" % m

    msgdef = parser.parse_from_filename(fname)
    msgdef['fname'] = m
    msgdef['header_block'] = "%s_PROTO_H" % m.upper()

    with open(os.path.join(out, name_h), 'w') as fp:
        fp.write(templ_h.render(msgdef, version_major=sys.version_info.major))

    with open(os.path.join(out, name_c), 'w') as fp:
        fp.write(templ_c.render(msgdef, version_major=sys.version_info.major))


if __name__ == "__main__":
    main()
