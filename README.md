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
