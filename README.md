### Requirements
To install Gnuplot (in linux)
```bash
sudo apt-get install gnuplot
```

Compile C++ file and run it using the Gnuplot pipelining (ensure gnuplot is installed)
```bash
g++ main.cpp -o main
./main | gnuplot
```
In this way the graph is plotted, to have the data plotted run
```bash
./main
```
another time.\
Run python code to read input data using

```bash
python3 read_data.py
```
