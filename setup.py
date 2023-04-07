import sys

try:
    from skbuild import setup
    import nanobind
except ImportError:
    print(
        "The preferred way to invoke 'setup.py' is via pip, as in 'pip "
        "install .'. If you wish to run the setup script directly, you must "
        "first install the build dependencies listed in pyproject.toml!",
        file=sys.stderr,
    )
    raise

setup(
    name="nanobind_opencv_example",
    version="0.0.1",
    author="Ryota Maeda",
    author_email="maeda.ryota.elerac@gmail.com",
    description="nanobind typecaster for opencv types",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/elerac/nanobind_opencv",
    python_requires=">=3.8",
    license="MIT",
    packages=["nanobind_opencv_example"],
    package_dir={"": "src"},
    cmake_install_dir="src/nanobind_opencv_example",
    include_package_data=True,
)
