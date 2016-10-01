from distutils.command.clean import clean as _clean
from distutils.dir_util import remove_tree
from distutils import log

from setuptools import setup, find_packages, Distribution

import os
import os.path
import platform
import sys


VERSION = "0.0.1"
HERE = os.path.dirname(os.path.abspath(__file__))
CYROBUF_LIST_H = "cyrobuf_list.h"
CYROBUF_LIST_C = "cyrobuf_list.c"


class clean(_clean):
    def __clean_tree(self, tree):
        for dirpath, dirnames, filenames in os.walk(tree):
            for dirname in dirnames:
                if dirname in ('__pycache__', 'build'):
                    remove_tree(os.path.join(dirpath, dirname), verbose=self.verbose, dry_run=self.dry_run)

        for dirpath, dirnames, filenames in os.walk(tree):
            for filename in filenames:
                if any(filename.endswith(suffix) for suffix in (".so", ".dll")):
                    self.__remove_file(os.path.join(dirpath, filename))

    def __remove_file(self, full_path):
        if os.path.exists(full_path):
            if not self.dry_run:
                os.unlink(full_path)
            if self.verbose >= 1:
                log.info("removing '%s'" % full_path)

    def run(self):
        _clean.run(self)

        self.__clean_tree(os.path.join(HERE, 'cyrobuf'))
        self.__clean_tree(os.path.join(HERE, 'tests'))

        tests_out = os.path.join(HERE, 'tests', 'out')
        if os.path.isdir(tests_out):
            remove_tree(tests_out, verbose=self.verbose, dry_run=self.dry_run)

        self.__remove_file(os.path.join(HERE, 'cyrobuf', 'src', CYROBUF_LIST_H))
        self.__remove_file(os.path.join(HERE, 'cyrobuf', 'src', CYROBUF_LIST_C))

        for filename in os.listdir(HERE):
            for prefix in ("cyrobuf_list", "cyrobuf_util"):
                for suffix in (".so", ".dll"):
                    if filename.startswith(prefix) and filename.endswith(suffix):
                        self.__remove_file(os.path.join(HERE, filename))


class PyrobufDistribution(Distribution):

    def run_commands(self):
        # By now the setup_requires deps have been fetched.
        self.cyrobufize_builtins()
        Distribution.run_commands(self)

    def cyrobufize_builtins(self):
        from jinja2 import Environment, PackageLoader
        env = Environment(loader=PackageLoader('cyrobuf.protobuf', 'templates'))

        templ_h = env.get_template('cyrobuf_list_h.tmpl')
        templ_c = env.get_template('cyrobuf_list_c.tmpl')

        listdict = {
            'DoubleList':   'double',
            'FloatList':    'float',
            'IntList':      'int',
            'Int32List':    'int32_t',
            'Uint32List':   'uint32_t',
            'Int64List':    'int64_t',
            'Uint64List':   'uint64_t',
            'CharList':     'char'
        }

        path = os.path.join(HERE, 'cyrobuf', 'src', CYROBUF_LIST_C)
        if not self.dry_run:
            with open(path, 'w') as fp:
                fp.write(templ_c.render(
                    {'def': listdict, 'version_major': sys.version_info.major}
                ))
        if self.verbose >= 1:
            log.info("rendering '%s' from '%s'" % (CYROBUF_LIST_C, templ_c.filename))

        path = os.path.join(HERE, 'cyrobuf', 'src', CYROBUF_LIST_H)
        if not self.dry_run:
            with open(path, 'w') as fp:
                fp.write(templ_h.render(
                    {'def': listdict, 'version_major': sys.version_info.major}
                ))
        if self.verbose >= 1:
            log.info("rendering '%s' from '%s'" % (CYROBUF_LIST_H, templ_h.filename))

setup(
    distclass=PyrobufDistribution,
    name="cyrobuf",
    version=VERSION,
    packages=find_packages(),
    include_package_data=True,
    cmdclass={'clean': clean},
    entry_points={
        'console_scripts': ['cyrobuf = cyrobuf.__main__:main'],
        'distutils.setup_keywords': [
                'cyrobuf_modules = cyrobuf.setuptools_ext:cyrobuf_modules',
        ],
    },
    description='A C based protobuf compiler',
    long_description=open(os.path.join(HERE, 'README.md')).read(),
    url='https://github.com/tburmeister/cyrobuf',
    author='Taylor Burmeister',
    tests_require=['pytest'] + (['protobuf >= 2.6.0, <3'] if sys.version_info.major == 2 else []),
    setup_requires=['jinja2 >= 2.8', 'pytest-runner'],
    install_requires=['jinja2 >= 2.8'],
    zip_safe=False,
)
