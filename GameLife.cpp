#include "GameLife.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

GameLife::GameLife(string m, string o, string fp, string of)
{
  srand(time(NULL)); //random seed from computer's time
  mode = m;
  output = o;
  evolution = 0;
  outputFile = of;
  ofstream outStream;
}

GameLife::GameLife(string m, string o, int h, int w, double pd, string of)
{
  srand(time(NULL)); //random seed from computer's time
  mode = m;
  output = o;
  height = h;
  width = w;
  evolution = 0;
  outputFile = of;
  ofstream outStream;
  createBoards();
  populateBoard(pd);
}

GameLife::~GameLife()
{

}

void GameLife::setHeight(int h)
{ height = h;}
void GameLife::setWidth(int w)
{ width = w;}
void GameLife::setPop(double p)
{ popDensity = p;}
void GameLife::setMode(string m)
{ mode = m;}
void GameLife::setOutput(string o)
{ output = o;}

void GameLife::readMap(string fp)
{
  ifstream inputPath;
  cout << fp << endl;
  inputPath.open(fp);
  if (!inputPath.is_open()) //file did not open
    cout << "Error: Unable to open map file." << endl;
  else
  {
    inputPath >> height;
    inputPath >> width;
    createBoards();
    string fileRow;
    int row = 0;
    while (getline(inputPath, fileRow))
    {
     if (fileRow.size() == width+1 || fileRow.size() == width) //not empty or irrelevant row
      {
        int column = 0;
        for (int cell=0; cell < fileRow.size(); ++cell)
        {
          board[row][column++] = fileRow[cell];
        }
          row++;
      }
    }
    inputPath.close();
    printBoard();
  }
}

void GameLife::createBoards()
{
  board = new char*[width];
  for (int row = 0; row < height; ++row)
  {
    board[row] = new char[height];
  }
  nextBoard = new char*[width];
  for (int row = 0; row < height; ++row)
  {
    nextBoard[row] = new char[height];
  }
}

void GameLife::populateBoard(double pd)
{
  char cell;
  int random;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      //randomizes placement of cells according to popDensity
      random = rand() % 100;
      if (random <= (pd*100))
        board[row][col] = 'X';
      else
        board[row][col] = '-';
    }
  }
}

void GameLife::printBoard()
{
  if (output == "file")
    outStream << "Evolution: " << evolution << endl;
  else
    cout << "Evolution: " << evolution << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      if (col == width-1) //last cell in row
      {
        if (output == "file")
          outStream << board[row][col] << endl;
        else
          cout << board[row][col] << endl;
      }
      else
      {
        if (output == "file")
          outStream << board[row][col];
        else
          cout << board[row][col];
      }
    }
  }
}

string GameLife::dangerZone(int row, int col)
{
  if (row == 0 && col == 0)
    return "tlc"; //top left corner
  else if (col == width-1 && row == 0)
    return "trc"; //top right corner
  else if (col == 0 && row == height-1)
    return "blc"; //bottom left corner
  else if (row == height-1 && col == width-1)
    return "brc"; //bottom right corner
  else if (row == 0 && col != 0 && col != width-1)
    return "top";
  else if (row == height-1 && col != 0 && col !=width-1)
    return "bottom";
  else if (col == 0 && row != 0 && row != height-1)
    return "left";
  else if (col == width-1 && row != 0 && row != height-1)
    return "right";
  else
    return "none";
}

int GameLife::getNeighbors(int row, int col)
{
  int neighbors = 0;
  string dz = dangerZone(row, col);
  if (mode == "classic")
  {
    if (dz == "none")
    {
      //check left
      for (int i=row+1; i >= row-1; --i)
      {
        if (board[i][col-1] == 'X')
          neighbors++;
      }
      //check top
      if (board[row-1][col] == 'X')
          neighbors++;
      //check right
      for (int i=row+1; i >= row-1; --i)
      {
        if (board[i][col+1] == 'X')
          neighbors++;
      }
      //check bottom
      if (board[row+1][col] == 'X')
        neighbors++;
     }//end no danger zone
     else if (dz == "left")
     {
       if (board[row+1][col] == 'X')
         neighbors++;
       if (board[row-1][col] == 'X')
         neighbors++;
       for (int i=row+1; i >= row-1; --i)
       {
         if (board[i][col+1] == 'X')
           neighbors++;
       }
     }
     else if (dz == "right")
     {
       if (board[row+1][col] == 'X')
         neighbors++;
       if (board[row-1][col] == 'X')
         neighbors++;
       for (int i=row+1; i >= row-1; --i)
       {
         if (board[i][col-1] == 'X')
           neighbors++;
       }
     }
     else if (dz == "top")
     {
       for (int i = col-1; i < col+1; ++i)
       {
         if (board[row+1][i] == 'X')
          neighbors++;
       }
       if (board[row][col-1] == 'X')
        neighbors++;
       if (board[row][col+1] == 'X')
        neighbors++;
     }
     else if (dz == "bottom")
     {
       for (int i = col-1; i < col+1; ++i)
       {
         if (board[row-1][i] == 'X')
          neighbors++;
       }
       if (board[row][col-1] == 'X')
        neighbors++;
       if (board[row][col+1] == 'X')
        neighbors++;
     }
     else if (dz == "tlc")
     {
       if (board[row][col+1] == 'X') //right
        neighbors++;
       if (board[row+1][col] == 'X') //bottom
        neighbors++;
       if (board[row+1][col+1] == 'X')//diag
        neighbors++;
     }
     else if (dz == "blc")
     {
       if (board[row-1][col] == 'X') //top
        neighbors++;
       if (board[row][col+1] == 'X')//right
        neighbors++;
       if (board[row-1][col+1] == 'X')
        neighbors++;
     }
     else if (dz == "trc")
     {
       if (board[row][col-1] == 'X')
        neighbors++;
       if (board[row+1][col] == 'X')
        neighbors++;
       if (board[row+1][col-1] == 'X')
        neighbors++;
     }
     else if (dz == "brc")
     {
       if (board[row][col-1] == 'X')
        neighbors++;
       if (board[row-1][col] == 'X')
        neighbors++;
       if (board[row-1][col-1] == 'X')
        neighbors++;
     }
    return neighbors;
  }
  else if (mode == "donut")
  {
    cout << "Donut mode has not been finished" << endl;
  }
  else if (mode == "mirror")
  {
    cout << "Mirror mode has not been finished." << endl;
  }
}

void GameLife::printNeighbors()
{
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      if (col == width-1)
        cout <<  getNeighbors(row,col) << endl;
      else
        cout << getNeighbors(row, col);
    }
  }
}

void GameLife::nextGen()
{
  for (int row=0; row < height; ++row)
  {
    for (int col=0; col < width; ++col)
    {
      int neighbors = getNeighbors(row,col);
      if (neighbors <= 1)
        nextBoard[row][col] = '-';
      else if (neighbors == 2)
      {
        nextBoard[row][col] = board[row][col];
      }
      else if (neighbors == 3)
        nextBoard[row][col] = 'X';
      else if (neighbors >= 4)
        nextBoard[row][col] = '-';
    }
  }
}

void GameLife::out()
{
  if (isStable())
  {
    cout << "Your colony has stabilized. Press enter to quit:" << endl;
    cin.get();
    cin.get();
    exit(0);
  }
  for (int row=0; row < height; ++row)
  {
    for (int col=0; col < width; ++col)
    {
      board[row][col] = nextBoard[row][col];
    }
  }
  evolution++;
  if (output == "delay")
  {
    sleep(1);
    printBoard();
  }
  else if (output == "enter")
  {
    cout << "Press enter for next evolution: " << endl;
    if (evolution == 1)
      cin.get(); //extra newline
    cin.get();
    printBoard();
  }
  else if (output == "file")
  {
    cout << "Printing to file..." << endl;
    printBoard();
  }
}

void GameLife::play()
{
  if (output == "file")
  {
    outStream.open(outputFile);
    if (!outStream.is_open())
    {
      cout << "Error: Cannot open output file." << endl;
      exit(1);
    }
  }
  while (!isDead())
  {
    nextGen();
    out();
  }
  if (isDead())
  {
    cout << "Your bacteria colony has died out. Press enter to quit:" << endl;
    cin.get();
    cin.get();
    exit(0);
  }
}

bool GameLife::isDead()
{
  bool dead = false;
  int alive = 0;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      if (board[row][col] == 'X')
        alive++;
    }
  }
  if (alive == 0)
    dead =true;
  return dead;
}

bool GameLife::isStable()
{
  bool same = true;
  if (evolution == 0 || evolution == 1)
    same = false;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++ col)
    {
      if (board[row][col] != nextBoard[row][col])
      {
        same = false;
        break;
      }
    }
  }
  return same;
}
