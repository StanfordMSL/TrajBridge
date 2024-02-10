from setuptools import find_packages, setup

setup(
    name="spline_controller",
    version="0.1",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    install_requires=[
        "numpy",
        "scipy",
        "qpsolvers[osqp]",
        "ipykernel",
        "ipympl",
        "matplotlib"
    ],
)