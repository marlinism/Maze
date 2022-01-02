# Maze

Context: This is one of the problems I have been through in my college year. By using recursion, I amm able to solve any maze. Below are four specific mazes that I have solved

Software: C++ (Recursion, Stack)

First, I implemented the isInside, isClear, markAsPath, markAsVisited and atExit methods by using conditions. Then I create a stack that contains pairs of <int, int> to store the step that the program made, with each step, the stack will push the pair of x,y of the step. Using if-else condition that if the next step is inside the maze and is clear, I can easily make the program work. However, if the next step is closed and there is no way left, the program will mark all the step it made as visited and pop the stack, then backtrack until it find the possible way. The whole if-else condition is wrap inside the do-while loop that will quit if it reaches the exit.

Output: It runs successfully with different kind of tests.
