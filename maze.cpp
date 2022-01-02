//
// Created by Yusuf Pisan on 4/18/18.
//

#include "maze.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

// print maze object
ostream &operator<<(ostream &out, const Maze &maze) {
  for (int row = 0; row < maze.height; ++row) {
    for (int col = 0; col < maze.width; ++col) {
      out << maze.field[row][col];
    }
    out << endl;
  }
  out << endl;
  return out;
}

// default constructor
Maze::Maze() = default;

// Load maze file from current directory
bool Maze::load(const string &fileName) {
  ifstream inFile;
  inFile.open(fileName);
  if (!inFile) {
    cerr << "Unable to open file: " << fileName << endl;
    return false;
  }
  inFile >> width >> height;
  inFile >> exitRow >> exitColumn;
  inFile >> startRow >> startColumn;
  // ignore leftover charcaters up to newline
  inFile.ignore(INT_MAX, '\n');
  string line;
  for (int row = 0; row < height; ++row) {
    getline(inFile, line);
    field.push_back(line);
  }
  return true;
}

// true if maze can be solved
bool Maze::solve() {
  int x = startRow;
  int y = startColumn;
  stack<pair<int, int>> s;

  // starting point
  if (isInside(startRow, startColumn) && isClear(startRow, startColumn)) {
    s.push({startRow, startColumn});
    markAsPath(s.top().first, s.top().second);
  }

  do {
    if (isInside(x - 1, y) && isClear(x - 1, y)) {
      x--;
      s.push({x, y});
      markAsPath(s.top().first, s.top().second);
      path += "N";
    } else if (isInside(x + 1, y) && isClear(x + 1, y)) {
      x++;
      s.push({x, y});
      markAsPath(s.top().first, s.top().second);
      path += "S";
    } else if (isInside(x, y + 1) && isClear(x, y + 1)) {
      y++;
      s.push({x, y});
      markAsPath(s.top().first, s.top().second);
      path += "E";
    } else if (isInside(x, y - 1) && isClear(x, y - 1)) {
      y--;
      s.push({x, y});
      markAsPath(s.top().first, s.top().second);
      path += "W";
    } else {
      markAsVisited(s.top().first, s.top().second);
      s.pop();
      x = s.top().first;
      y = s.top().second;
      path.pop_back();
      if (x == startRow && y == startColumn) {
        markAsVisited(s.top().first, s.top().second);
        return false;
      }
    }
  } while (!atExit(x, y));

  return true;
}

// path to exit
string Maze::getPath() const { return path; }

// true if row, column is the exit
bool Maze::atExit(int row, int column) const {
  return row == exitRow && column == exitColumn;
}

// true if row, column is inside the maze
bool Maze::isInside(int row, int col) const {
  return row >= 0 && col >= 0 && row < field.size() && col < field[row].size();
}

// true if row, column is clear to move
bool Maze::isClear(int row, int col) const {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  return field[row][col] == CLEAR;
}

// mark location as part of the path to exit
void Maze::markAsPath(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = PATH;
}

// mark location as visited, not part of the path to exit
void Maze::markAsVisited(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = VISITED;
}
