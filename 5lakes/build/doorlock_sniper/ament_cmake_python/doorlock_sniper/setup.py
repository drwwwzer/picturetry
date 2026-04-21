from setuptools import find_packages
from setuptools import setup

setup(
    name='doorlock_sniper',
    version='0.1.0',
    packages=find_packages(
        include=('doorlock_sniper', 'doorlock_sniper.*')),
)
