# Algorithm-Projects
## Maximum Planar Subset
Given is a set C of n chords of a circle (see Figure 2 (a)). We assume that no two chords of C share an endpoint.
Number the endpoints of these chords from 0 to 2n − 1, clockwise around the circle (see Figure 2 (c)). Let
M(i, j), i ≤ j, denote the number of chords in the maximum planar subset (i.e., no two chords overlap each
other in the subset) in the region formed by the chord ij and the arc between the endpoints i and j (see
Figure 2 (d)). As the example shown in Figure 2 (a), M(2, 7) = 1, M(3, 3) = 0, and M(0, 11) = 3. You are
asked to write a program that computes the number of chords in the maximum planar subset in a circle of n
chords, i.e., compute M(0, 2n − 1), and reports the details of each chords, as shown in Figure 2 (b).
![N|Solid](problem.PNG)
### Usage
* Compile 
```sh
$ g++ maxPlanarSubset.cpp -std=c++11 -o mps -O2

```
* Run
```sh
$ ./mps [input file name] [output file name]
```
## Global Routing
Given the problem size (the number of horizontal and vertical tiles), capacity, and a netlist,
the global router routes all nets in the routing region. The objective is to minimize the total
overflows first and then the total wirelength. Here the overflow on a tile boundary is calculated
as the amount of demand that exceeds the capacity, i.e., overflow = max(0, demand - capacity). 
### Sample Case
![N|Solid](samplecase.JPG)
![N|Solid](sampleinput.PNG)
![N|Solid](sampleoutput.PNG)
### Usage
* Compile 
```sh
$ g++ router.cpp -std=c++11 -o router -O2
```
* Run
```sh
$ ./router [input file name] [output file name]
```
## Indexing and Sorting
Apply Insertion Sort, Merge Sort, Heap Sort, and Quicksort to develop
FOUR word processors with indexing and sorting (common hidden operations for web search) 
* Compile 
```sh
$ g++ xxxSort.cpp parser.cpp -std=c++11 -o xxxSort -O2
```
* Run
```sh
$ ./xxxSort [input file name] [output file name]
```
