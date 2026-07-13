#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Global constants
const int MAX_CREATURES = 100;
const string INPUT_FILE = "in_creaturelist.txt";

// Enums for Menus
enum MainMenu
{
  PRINT = 1,
  SORT_MENU,
  SEARCH,
  QUIT
};
enum SortMenu
{
  BY_ID = 1,
  BY_NAME,
  BY_TYPE,
  BY_LEVEL,
  BACK_TO_MAIN
};

class Creature
{
private:
  int id;
  string name;
  string type;
  int level;
  string nameLower;
  string typeLower;

public:
  Creature();
  void setRecord(int cId, string cName, string cType, int cLevel);
  int getId() const;
  string getName() const;
  string getType() const;
  int getLevel() const;
  string getNameLower() const;
  string getTypeLower() const;
  void printRecord() const;
};

class Army
{
private:
  Creature creatures[MAX_CREATURES];
  Creature *creaturePointers[MAX_CREATURES];
  int count;
  string toLower(string str);

public:
  Army();
  void loadCreatures(string filename);
  void printOriginal() const;
  void printSortedPointers() const;
  void sortCreatures(int sortOption);
  void searchCreatures(string searchTerm);
};

int main()
{
  Army myArmy;
  myArmy.loadCreatures(INPUT_FILE);

  int mainChoice = 0;

  while (mainChoice != QUIT)
  {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Print Original List\n";
    cout << "2. Sort Menu (Descending)\n";
    cout << "3. Search (Name or Type)\n";
    cout << "4. Quit\n";
    cout << "Enter selection: ";

    if (!(cin >> mainChoice))
    {
      cin.clear();
      cin.ignore(10000, '\n');
      mainChoice = 0;
    }

    switch (mainChoice)
    {
    case PRINT:
      myArmy.printOriginal();
      break;

    case SORT_MENU:
    {
      int sortChoice = 0;
      while (sortChoice != BACK_TO_MAIN)
      {
        cout << "\n--- Sort Submenu (Descending) ---\n";
        cout << "1. Sort by ID\n";
        cout << "2. Sort by Name\n";
        cout << "3. Sort by Type\n";
        cout << "4. Sort by Level\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter selection: ";

        if (!(cin >> sortChoice))
        {
          cin.clear();
          cin.ignore(10000, '\n');
          sortChoice = 0;
        }

        switch (sortChoice)
        {
        case BY_ID:
        case BY_NAME:
        case BY_TYPE:
        case BY_LEVEL:
          myArmy.sortCreatures(sortChoice);
          myArmy.printSortedPointers();
          break;
        case BACK_TO_MAIN:
          cout << "Returning to main menu...\n";
          break;
        default:
          cout << "Invalid choice. Try again.\n";
        }
      }
      break;
    }

    case SEARCH:
    {
      string searchTerm;
      cout << "Enter search term (partial or full Name/Type): ";
      cin >> searchTerm;
      myArmy.searchCreatures(searchTerm);
      break;
    }

    case QUIT:
      cout << "Exiting application. Goodbye!\n";
      break;

    default:
      cout << "Invalid main menu selection.\n";
    }
  }

  return 0;
}

Creature::Creature()
{
  id = 0;
  name = "";
  type = "";
  level = 0;
  nameLower = "";
  typeLower = "";
}

void Creature::setRecord(int cId, string cName, string cType, int cLevel)
{
  id = cId;
  name = cName;
  type = cType;
  level = cLevel;

  nameLower = "";
  for (int i = 0; i < name.length(); i++)
  {
    if (name[i] >= 'A' && name[i] <= 'Z')
    {
      nameLower += (name[i] + 32);
    }
    else
    {
      nameLower += name[i];
    }
  }

  typeLower = "";
  for (int i = 0; i < type.length(); i++)
  {
    if (type[i] >= 'A' && type[i] <= 'Z')
    {
      typeLower += (type[i] + 32);
    }
    else
    {
      typeLower += type[i];
    }
  }
}

int Creature::getId() const { return id; }
string Creature::getName() const { return name; }
string Creature::getType() const { return type; }
int Creature::getLevel() const { return level; }
string Creature::getNameLower() const { return nameLower; }
string Creature::getTypeLower() const { return typeLower; }

void Creature::printRecord() const
{
  cout << left << setw(10) << id
       << setw(20) << name
       << setw(15) << type
       << right << setw(10) << level << endl;
}

Army::Army()
{
  count = 0;
}

string Army::toLower(string str)
{
  string lowerStr = "";
  for (int i = 0; i < str.length(); i++)
  {
    if (str[i] >= 'A' && str[i] <= 'Z')
    {
      lowerStr += (str[i] + 32);
    }
    else
    {
      lowerStr += str[i];
    }
  }
  return lowerStr;
}

void Army::loadCreatures(string filename)
{
  ifstream inFile(filename);
  int id, level;
  string type, name;

  if (inFile.is_open())
  {
    while (count < MAX_CREATURES && inFile >> type >> name >> id >> level)
    {
      creatures[count].setRecord(id, name, type, level);
      count++;
    }
    inFile.close();
  }
  else
  {
    cout << "Error: Could not open file " << filename << endl;
  }

  for (int i = 0; i < count; i++)
  {
    creaturePointers[i] = &creatures[i];
  }
}

void Army::printOriginal() const
{
  cout << "\n-----------------------------------------------------\n";
  cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Type" << right << setw(10) << "Level" << endl;
  cout << "-----------------------------------------------------\n";
  for (int i = 0; i < count; i++)
  {
    creatures[i].printRecord();
  }
  cout << "-----------------------------------------------------\n";
}

void Army::printSortedPointers() const
{
  cout << "\n-----------------------------------------------------\n";
  cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Type" << right << setw(10) << "Level" << endl;
  cout << "-----------------------------------------------------\n";
  for (int i = 0; i < count; i++)
  {
    creaturePointers[i]->printRecord();
  }
  cout << "-----------------------------------------------------\n";
}

void Army::sortCreatures(int sortOption)
{
  bool swapped = true;
  int i = 0;
  Creature *temp = NULL;

  while (swapped)
  {
    swapped = false;
    i = 0;
    while (i < count - 1)
    {
      bool toSwap = false;

      switch (sortOption)
      {
      case BY_ID:
        toSwap = creaturePointers[i]->getId() < creaturePointers[i + 1]->getId();
        break;
      case BY_NAME:
        toSwap = creaturePointers[i]->getNameLower() < creaturePointers[i + 1]->getNameLower();
        break;
      case BY_TYPE:
        toSwap = creaturePointers[i]->getTypeLower() < creaturePointers[i + 1]->getTypeLower();
        break;
      case BY_LEVEL:
        toSwap = creaturePointers[i]->getLevel() < creaturePointers[i + 1]->getLevel();
        break;
      }

      if (toSwap)
      {
        temp = creaturePointers[i];
        creaturePointers[i] = creaturePointers[i + 1];
        creaturePointers[i + 1] = temp;
        swapped = true;
      }
      i++;
    }
  }
}

void Army::searchCreatures(string searchTerm)
{
  string searchLower = toLower(searchTerm);
  bool foundAny = false;

  cout << "\n-----------------------------------------------------\n";
  cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Type" << right << setw(10) << "Level" << endl;
  cout << "-----------------------------------------------------\n";

  for (int i = 0; i < count; i++)
  {
    if (creatures[i].getNameLower().find(searchLower) != string::npos ||
        creatures[i].getTypeLower().find(searchLower) != string::npos)
    {
      creatures[i].printRecord();
      foundAny = true;
    }
  }
  cout << "-----------------------------------------------------\n";

  if (!foundAny)
  {
    cout << "No matching records found.\n";
  }
}