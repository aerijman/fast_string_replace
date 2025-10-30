
from setuptools import setup, Extension

fast_string_replace_module = Extension(
    name="fast_string_replace",
    sources=["fast_string_replace.c"],
)

setup(
    name="fast_string_replace",
    version="0.1.0",
    description="Efficient multi-location string replacement in Python using a C backend.",
    author="Ariel Erijman   ",
    author_email="aerijman@neb.com",
    license="MIT",
    ext_modules=[fast_string_replace_module],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
