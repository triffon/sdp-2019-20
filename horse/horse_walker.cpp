#include <iostream>
#include "horse_walker.h"

HorseWalker::HorseWalker(unsigned n) {
  for(int i = 0; i < n; i++)
    board.push_back(Chessrow(n));
}

void HorseWalker::printBoard() const {
  /*  for(int i = 0; i < board.size(); i++) {
    for(int j = 0; j < board.size(); j++)
      std::clog << (board[i][j] ? '*' : '_');
    std::clog << std::endl;
    }*/
  for(auto row : board) {
    for(auto b : row)
      std::clog << (b ? '*' : '_');
    std::clog << std::endl;
  }
}

std::ostream& operator<<(std::ostream& os, Position const& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}


bool HorseWalker::findPathRec(Position start, Position end) {
  if (!insideBoard(start))
    // излязохме извън дъската
    return false;

  if (board[start.first][start.second])
    // вече сме стъпвали тук
    return false;

  std::clog << "Стъпка напред върху " << start << std::endl;
  path.push(start);
  board[start.first][start.second] = true;

  if (start == end) {
    // намерихме път
    printPath();
    return true;
  }

  for(int dx = -2; dx <= 2; dx++)
    if (dx != 0)
      for(int sign : {-1, 1}) {
        int dy = sign * (3 - std::abs(dx));
        Position newstart(start.first + dx, start.second + dy);
        if (findPathRec(newstart, end))
          return true;
      }

  std::clog << "Стъпка назад от " << start << std::endl;
  path.pop();
  return false;
}

bool HorseWalker::findPathStack(Position start, Position end) {
  // стартова стекова рамка: единствена възможност за стартиране
  StackFrame startFrame;
  startFrame.push(start);
  stack.push(startFrame);

  while(!stack.empty()) {

    StackFrame& currentFrame = stack.peek();
    Position current = currentFrame.peek();
  
    if (!insideBoard(current) || board[current.first][current.second]) {
      // излязохме извън дъската или вече сме стъпвали тук
      // отказваме се от current
      currentFrame.pop();
      // да не би стековата рамка да се изчерпи?
      if (currentFrame.empty()) {
        std::clog << "Стъпка назад от " << path.peek() << std::endl;
        // премахваме стековата рамка от стека
        stack.pop();
        path.pop();
      }
    } else {
      std::clog << "Стъпка напред върху " << current << std::endl;
      path.push(current);
      board[current.first][current.second] = true;

      if (current == end) {
        // намерихме път
        printPath();
        return true;
      }

      // създаваме нова стекова рамка
      StackFrame newFrame;
      
      for(int dx = -2; dx <= 2; dx++)
        if (dx != 0)
          for(int sign : {-1, 1}) {
            int dy = sign * (3 - std::abs(dx));
            // добавяме всички възможности във новата стекова рамка
            newFrame.push(Position(current.first + dx, current.second + dy));
          }

      // добавяме новата стекова рамка в стека
      stack.push(newFrame);
    }
  }

  return false;
}

bool HorseWalker::findPathQueue(Position start, Position end) {
  queue.enqueue(start);

  Position current;
  StepStack history;

  while (!queue.empty() && (current = queue.dequeue()) != end) {
    std::clog << "Разглеждаме позиция " << current << std::endl;
    if (insideBoard(current) && !board[current.first][current.second]) {
      // маркираме позицията за обходена
      board[current.first][current.second] = true;
      for(int dx = -2; dx <= 2; dx++)
        if (dx != 0)
          for(int sign : {-1, 1}) {
            int dy = sign * (3 - std::abs(dx));
            // добавяме всички възможности в опашката
            Position newPos(current.first + dx, current.second + dy);
            queue.enqueue(newPos);
            history.push(Step(current, newPos));
          }
    }
  }
  // queue.empty() - няма как да стигнем до end
  // current == end - стигнали сме до end
         
  if (current == end) {
    // възстановяваме пътя
    // първо извеждаме последната позиция
    std::clog << current;
    while(!history.empty()) {
      Step step = history.pop();
      if (step.second == current) {
        current = step.first;
        std::clog << " <- " << current;
      }
    }
    std::clog << std::endl;
    return true;
  }
  return false;
}


void HorseWalker::printPath() const {
  Path copy = path;
  Position prev = copy.pop();
  std::clog << prev;
  while (!copy.empty()) {
    Position current = copy.pop();
    std::clog << " <- " << current;
    if (std::abs((int)prev.first - (int)current.first) + std::abs((int)prev.second - (int)current.second) != 3) {
      std::cerr << "GOTCHA! ";
      //exit(1);
    }
    prev = current;
  }
  std::clog << std::endl;
}
