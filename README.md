# adaboost
adaboost detect feet
this branch use threadpool instead

# Citation
This project uses the following two open source projects. 
1. [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page)
2. [Matplotlib-cpp](https://matplotlib-cpp.readthedocs.io/en/latest/)

# Install Dependent
```bash=
sudo apt install cmake python3-dev python3-matplotlib python3-numpy
```

# Compile & Usage
```bash=
git clone git@github.com:5568ke/adaboost.git
cd adaboost
mkdir build
cd build
cmake ..
cmake --build .
./train
```
