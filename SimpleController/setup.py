from setuptools import find_packages, setup

setup(
    name="simple_controller",
    version="0.1",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    install_requires=[
        "numpy",
        "scipy==1.12.0",
        "qpsolvers[osqp]",
        "ipykernel",
        "ipympl",
        "matplotlib",
        "ply",
        "tabulate"
    ],
)