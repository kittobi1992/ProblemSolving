![ICPC](https://github.com/kittobi1992/ProblemSolving/blob/master/icpc.png "International Competitive Programming Contest")

The ACM ICPC competition is an annual competitive programming competition among universities of the world. Teams compete in regional contests to qualify for the World Finals. During that contests between 8 and 15 problems have to be solved in a time period usually around 5 hours. The problems covers a large range of topics in computer science.

During my studies of computer science I participated three times for the German team of the Karlsruher Institute of Technology on regional contests. In this repository you will find solved problems from various competitive programming resources and several basic algorithms. In contrast to other ICPC repositories on github I focus on readibility and understanding of the algorithms, while simultanously ensure that the implementations are short and easy to integrate into solutions of problems.

## Algorithms

In this Section, I list several algorithms you can find in this repository with its links to the source code.

### Graph

1. [Single Source Shortest Path (Dijkstra's Algorithm)](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Graph/dijkstra.cpp)
2. [Maximum Flow (Edmond-Karps Algorithm)](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Graph/flow.cpp)
3. [Minimum Spanning Tree (Kruskal's and Jarnik-Prims Algorithm)](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Graph/mst.cpp)
4. [Strongly Connected Components (Tarjan's Algorithm)](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Graph/tarjan.cpp)

### Data Structures

1. [Range Minimum Query](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/rmq.cpp)
2. [Lowest Common Ancestor](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/lca.cpp)
3. [Generic Segment Tree](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/segment_tree.cpp)  
You can use this segment tree to implement all kinds of applications, which can be solved with this data structure without changing the implementation. In the source code I provide detailed examples how to implement e.g.:  
a. Range Minimum Query  
b. Range Maximum Query  
c. Range Minmax Query  
d. Interval Sum  
e. Interval Product
4. [2D Range Search](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/2D_range_search.cpp)  
Given a rectangle the data structure returns all points inside the rectangle.
5. [2D Range Maximum Query (K2Treap)](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/segment_tree.cpp)  
Given a rectangle the data structure returns the point with maximum weight inside the rectangle.
6. [Fenwick Tree](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Datastructures/fenwick_tree.cpp)  
Implements interval sum in O(1) with update functionallity in O(log(n))

### String
1. [Suffix Array](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/String/suffix_array.cpp)
2. [Trie](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/String/trie.cpp)
3. [Wavelet Tree](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/String/wavelet_tree.cpp)

### Primes
1. [Sieve of Eratosthenes and Factorization](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Primes/primes.cpp)

### Sequences
1. [Longest Common Subsequence](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Sequence/sequence.cpp#L49)  
Special Implementation which runs on random inputs in O(n*log(n)) time.
2. [Longest Increasing Subsequence](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Sequence/sequence.cpp#L100)  
Implementation returns longest increasing subsequence in O(n*log(n)) time.

### Others
1. [Bit Vector](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Others/bitvector.cpp)
2. [Centered Interval Tree](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Others/interval_tree.cpp)
3. [x-Fast-Trie](https://github.com/kittobi1992/ProblemSolving/blob/master/Implementation/Others/x_fast_trie.cpp)
