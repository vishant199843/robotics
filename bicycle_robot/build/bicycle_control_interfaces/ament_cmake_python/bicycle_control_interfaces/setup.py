from setuptools import find_packages
from setuptools import setup

setup(
    name='bicycle_control_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('bicycle_control_interfaces', 'bicycle_control_interfaces.*')),
)
