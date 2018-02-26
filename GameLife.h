#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class GameLife
{
public:
  GameLife(string m, string o, string fp, string of);
  GameLife(string m, string o, int h, int w, double pd, string of);
  ~GameLife();
  void readMap(string fp);
  void createBoards();
  void populateBoard(double pd);
  void printBoard();
  string dangerZone(int row, int col);
  int getNeighbors(int row, int col);
  void printNeighbors();
  void nextGen();
  void out();
  void play();
  bool isDead();
  bool isStable();

  void setHeight(int h);
  void setWidth(int w);
  void setPop(double p);
  void setMode(string m);
  void setOutput(string o);

private:
  int height;
  int width;
  double popDensity;
  string mode;
  string output;
  char **board;
  char **nextBoard;
  int evolution;
  string outputFile;
  ofstream outStream;
};
