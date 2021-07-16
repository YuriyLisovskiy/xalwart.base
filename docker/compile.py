#!/usr/bin/env python3
import os
import argparse
from jinja2 import Environment, FileSystemLoader

cc2cxx = {
    'gcc': 'g++',
    'clang': 'clang++',
}

parser = argparse.ArgumentParser()
parser.add_argument('--out')
parser.add_argument('--os')
parser.add_argument('--compiler')
args = parser.parse_args()

file_loader = FileSystemLoader(os.path.join(os.path.dirname(os.path.abspath(__file__))))
env = Environment(loader=file_loader)

system, system_version = args.os.split('-')
template = env.get_template('{}/Dockerfile'.format(system))

compiler, compiler_version = args.compiler.split('-')
cc, cxx = compiler, cc2cxx[compiler],
output = template.render(
    os_version=system_version, cc=cc, cxx=cxx, compiler_version=compiler_version
)
with open(args.out, 'w') as file:
    file.write(output)
