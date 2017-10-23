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
    parser.list_type_map = {
        'float':    'cyrobuf_float_list',
        'double':   'cyrobuf_double_list',
        'enum':     'cyrobuf_int32_list',
        'int32':    'cyrobuf_int32_list',
        'sint32':   'cyrobuf_int32_list',
        'sfixed32': 'cyrobuf_int32_list',
        'uint32':   'cyrobuf_uint32_list',
        'fixed32':  'cyrobuf_uint32_list',
        'bool':     'cyrobuf_uint32_list',
        'int64':    'cyrobuf_int64_list',
        'sint64':   'cyrobuf_int64_list',
        'sfixed64': 'cyrobuf_int64_list',
        'uint64':   'cyrobuf_uint64_list',
        'fixed64':  'cyrobuf_uint64_list',
        'string':   'cyrobuf_string_list',
        'bytes':    'cyrobuf_bytes_list'
    }

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

def add_extra_data(message):
    str_format_map = {
        'float':    '"f"',
        'double':   '"f"',
        'enum':     '"d"',
        'int32':    'PRId32',
        'sint32':   'PRId32',
        'sfixed32': 'PRId32',
        'uint32':   'PRIu32',
        'fixed32':  'PRIu32',
        'bool':     '"u"',
        'int64':    'PRId64',
        'sint64':   'PRId64',
        'sfixed64': 'PRId64',
        'uint64':   'PRIu64',
        'fixed64':  'PRIu64',
        'string':   '"s"'
    }

    getter_type_map = {
        'enum':     'int32_t',
        'timestamp':'int32_t',
        'int32':    'int32_t',
        'sint32':   'int32_t',
        'sfixed32': 'int32_t',
        'uint32':   'int32_t',
        'fixed32':  'int32_t',
        'bool':     'int32_t',
        'int64':    'int64_t',
        'sint64':   'int64_t',
        'sfixed64': 'int64_t',
        'uint64':   'int64_t',
        'fixed64':  'int64_t'
    }

    for field in message.fields:
        field.str_format = str_format_map.get(field.type)
        field.getter_type = getter_type_map.get(field.type)

    for submessage in message.messages.values():
        add_extra_data(submessage)

def generate(fname, out, parser, templ_h, templ_c):

    print("generating {0}".format(fname))

    m, _ = os.path.splitext(os.path.basename(fname))

    name_h = "%s_proto.h" % m
    name_c = "%s_proto.c" % m

    msgdef = parser.parse_from_filename(fname)
    msgdef['fname'] = m
    msgdef['header_block'] = "%s_PROTO_H" % m.upper()
    for message in msgdef['messages']:
        add_extra_data(message)

    with open(os.path.join(out, name_h), 'w') as fp:
        fp.write(templ_h.render(msgdef, version_major=sys.version_info.major))

    with open(os.path.join(out, name_c), 'w') as fp:
        fp.write(templ_c.render(msgdef, version_major=sys.version_info.major))


if __name__ == "__main__":
    main()
