## Global Routing
Given the problem size (the number of horizontal and vertical tiles), capacity, and a netlist,
the global router routes all nets in the routing region. The objective is to minimize the total
overflows first and then the total wirelength. Here the overflow on a tile boundary is calculated
as the amount of demand that exceeds the capacity, i.e., overflow = max(0, demand - capacity). 
### Sample Case
![N|Solid](/samplecase.png)
![N|Solid](/sampleinput.png)
![N|Solid](/sampleoutput.png)
### Environment
* Python 3.6
* Numpy: 1.15
* Scipy: 1.1.0
* Pandas: 0.23.4
* Keras: 2.1.6
* Jieba 0.39
* Gensim 3.6.0
* Emoji 0.5.1
### Usage
* Compile 
```sh
$ g++ router.cpp -std=c++11 -o router -O2
```
* Run
```sh
$ ./router [input file name] [output file name]
```
