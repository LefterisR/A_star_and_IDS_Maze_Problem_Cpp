# A_star_and_IDS_Maze_Problem_Cpp
**Intelligent Agents**: Implementation of A and Iterative Deepening Search Algorithms in C++ for Finding the Exit from a Square Maze with Blocks and Tolls.
## Author Lefteris Rizos  

### Purpose of the project.
The **state space** is created using parameters provided by the user. The user inputs the dimensions of the maze and the percentages of blocks (X) and tolls (T). The maze is then generated in **spacestate.cpp**, and the robot randomly spawns in one of four predefined positions:

std::map<int, std::pair<int, int>> robotPos = {
    {0, {d / 2, d / 2}},
    {1, {d / 2 + 1, d / 2}},
    {2, {d / 2, d / 2 + 1}},
    {3, {d / 2 + 1, d / 2 + 1}}
};

where **d** is the dimension of the maze.

This file translates the maze into an undirected graph (using a vector-based implementation). The search algorithms operate on this undirected graph and return a path from the robot (**R**) to one of the two maze exits: **Top Left** or **Bottom Right**.

Each movement has a cost of 1, but if R passes through a toll (**T**), the cost increases to 2. **Movements to and from blocked cells (X) are not allowed.**

**The entire process is managed by main.cpp. For more details, refer to the documentation within the respective files.**

## Execution Example

![image](https://github.com/user-attachments/assets/4bebd860-09a2-4204-8e9e-54049e65d0ba)
![image](https://github.com/user-attachments/assets/e648d73d-f3e9-44e8-b17f-125822732ba6)
![image](https://github.com/user-attachments/assets/815e9f0b-28d5-4632-b51b-db37ea17bced)
![image](https://github.com/user-attachments/assets/d0f9c6c0-0e0d-4bbe-815a-245d3a7960c4)



