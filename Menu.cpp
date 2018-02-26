#include "Menu.h"
#include "GameLife.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

Menu::Menu()
{
  int height=0;
  int width=0;
  double popDensity=0;
  string mode="";
  string output="";
  string filePath="";
  string outputFile = "";
  bool fromFile = false;
}

void Menu::init()
{
  cout << "Welcome to the Game of Life!" << endl;
  chooseInput();
  chooseOutput();
  chooseMode();
  if (fromFile)
  {
    GameLife theGame(mode, output, filePath, outputFile);
    theGame.readMap(filePath);
    theGame.play();
  }
  else
  {
    GameLife theGame(mode, output, height, width, popDensity, outputFile);
    theGame.play();
  }
}
void Menu::chooseInput()
{
  cout << "Select how to start: " << endl
       << "1) Input map from file " << endl
       << "2) Randomly start" << endl;
  int selection;
  cin >> selection;
  if (selection == 1)
  {
    fromFile = true;
    cout << "Enter the map file path: " << endl;
    cin >> filePath;
    cout << "Generating a game from " << filePath << endl;
  }
  else if (selection == 2)
  {
    cout << "Starting width: " << endl;
    cin >> width;
    cout << "Starting height: " << endl;
    cin >> height;
    cout << "Starting population density: " << endl;
    cin >> popDensity;
  }
  else
  {
    cout << "Fatal Error: Invalid input." << endl;
  }
}
void Menu::chooseMode()
{
  cout << "Select your game mode: " << endl
       << "1) Classic" << endl
       << "2) Mirror" << endl
       << "3) Donut" << endl;
  int selection;
  cin >> selection;
  if (selection == 1)
    mode = "classic";
  else if (selection == 2)
    mode = "mirror";
  else if (selection == 3)
    mode = "donut";
  else
  {
    cout << "Fatal Error: Invalid Selection" << endl;
    exit(1);
  }
}
void Menu::chooseOutput()
{
  cout << "Select your output option: " << endl
       << "1) Delay 1 second between each evolution" << endl
       << "2) Press enter between each evolution" << endl
       << "3) Output each evolution to a file" << endl;
  int selection;
  cin >> selection;
  if (selection == 1)
    output = "delay";
  else if (selection == 2)
    output = "enter";
  else if (selection == 3)
  {
    output = "file";
    cout << "Enter path to output file: " << endl;
    cin >> outputFile;
  }
  else
  {
    cout << "Error: Invalid selection." << endl;
    exit(1);
  }
}
