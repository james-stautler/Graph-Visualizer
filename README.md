# Graph Visualizer
A simple C++ based project implemented with the SFML libray to visualize BFS and DFS on an unweighted graph. Custom graph creation as well as random graph generation are supported.

![alt text](https://pub-9593df70cbf747228fd5fda3ece131d2.r2.dev/Graph%20Visualizer%20Cover.png "Graph Visualizer Image")

## Running the Project
Must have cmake installed on your local device. Clone the repository and enter the following commands to run the project:\
\
`cd build`\
`cmake --build .`\
`./bin/Debug/gv`

## Runing Tests
Unit tests have been created and can be found in the same directory as the project exectuable. After building, can simply run tests with:\
\
`ctest`

## Functionality
Users are able to create nodes by selecting the "Create Node" option and clicking on the canvas, though nodes can not be physically touching (this is done to ensure all edges remain visible). To create an unweighted edge between two nodes, click on two nodes while the "Create Node" option is selected; the same functionality applies to removing edges. If there is an edge present between two nodes when those nodes are selected, the edge is removed.\
\
Selecting "Start Node" and "End Node" allows users to select from which node a search algorithm starts and which one is the target. Both a start and end node must be selected in order to start a search. From there, select BFS or DFS to perform the desired search. If a path is found it is highlighted green at the end of the search. If a path could not be found, the entire graph becomes red.

## Adjusting Program Parameters:
The program allows users to change the number of random nodes and edges during random graph generation. To do so, look for the variables `RANDOM_NODES` and `RANDOM_EDGES` in gv.cpp and change those to your liking. Keep in mind that it can be hard to discern what is happening on the screen as the number of nodes and edges continues to increase. The default values are currently 20 nodes and 30 edges.\
\
You can also adjust the speed at which the animation occurs. The `ALGORITHM_SPEED` variable controls this and is currently set to 1. The higher the value, the faster the animation proceeds.

