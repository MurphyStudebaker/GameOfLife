#include <iostream>
#include <string>
using namespace std;

class Menu
{
public:
Menu();

void init();
void chooseMode();
void chooseInput();
void chooseOutput();
bool readMap(string fp);

private:
int height;
int width;
double popDensity;
string mode;
string output;
string outputFile;
string filePath;
bool fromFile;
};
