// CS216 Lab 4: Sorting and Searching with Pointers
// Aiden Tsang

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

const int MAX_CREATURES = 100;
const string INPUT_FILE = "in_creaturelist.txt";
const int COL_NAME = 20;
const int COL_TYPE = 15;
const int COL_NUM = 10;
const int TABLE_WIDTH = COL_NAME + COL_TYPE + COL_NUM + COL_NUM;

string toLower(const string &str);

class Creature
{
private:
  string name = "";
  string type = "";
  int health = 0;
  int strength = 0;
  string nameLower = ""; // stored once in lower case to expedite search and sort
  string typeLower = "";

public:
  Creature();
  void setRecord(const string &newType, const string &newName, int newHealth, int newStrength);
  string getName() const;
  string getType() const;
  int getHealth() const;
  int getStrength() const;
  string getNameLower() const;
  string getTypeLower() const;
  string toString() const;
};

class Army
{
private:
  Creature creatures[MAX_CREATURES];
  Creature *creaturePointers[MAX_CREATURES] = {nullptr};
  int count = 0;

  void loadCreatures(const string &filename); // private: called only by the constructor
  string line() const;
  string header() const;

public:
  Army(const string &filename = INPUT_FILE);
  void sortCreatures(int sortOption);
  string originalToString() const;
  string sortedToString() const;
  string searchCreatures(const string &searchTerm) const;
};

enum MainMenu
{
  PRINT = 1,
  SORT_MENU,
  SEARCH,
  QUIT
};
enum SortOption
{
  BY_NAME = 1,
  BY_TYPE,
  BY_HEALTH,
  BY_STRENGTH,
  BACK_TO_MAIN
};

void clearCin(const string &errorMessage);
void sortMenu(Army &army);
void searchOption(const Army &army);

int main()
{
  Army myArmy;
  int mainChoice = 0;
  do
  {
    cout << "\n\nMain Menu:\n"
            "1. Print creatures in the original order\n"
            "2. Sort menu\n"
            "3. Search by name or type\n"
            "4. Quit\n"
            "Enter your choice: ";
    cin >> mainChoice;
    switch (mainChoice)
    {
    case PRINT:
      cout << '\n'
           << myArmy.originalToString();
      break;
    case SORT_MENU:
      sortMenu(myArmy);
      break;
    case SEARCH:
      searchOption(myArmy);
      break;
    case QUIT:
      cout << "\nGoodbye!\n";
      break;
    default:
      clearCin("Invalid menu choice");
    }
  } while (mainChoice != QUIT);
  return 0;
}

Creature::Creature() {} // member variables already initialized in the class definition

void Creature::setRecord(const string &newType, const string &newName, int newHealth,
                         int newStrength)
{
  type = newType;
  name = newName;
  health = newHealth;
  strength = newStrength;
  typeLower = toLower(type); // converted once here, not repeatedly during sort/search
  nameLower = toLower(name);
}

string Creature::getName() const
{
  return name;
}

string Creature::getType() const
{
  return type;
}

int Creature::getHealth() const
{
  return health;
}

int Creature::getStrength() const
{
  return strength;
}

string Creature::getNameLower() const
{
  return nameLower;
}

string Creature::getTypeLower() const
{
  return typeLower;
}

string Creature::toString() const
{
  ostringstream out;
  out << left << setw(COL_NAME) << name << setw(COL_TYPE) << type << right << setw(COL_NUM)
      << health << setw(COL_NUM) << strength << '\n';
  return out.str();
}

Army::Army(const string &filename)
{
  loadCreatures(filename);
}

void Army::loadCreatures(const string &filename)
{
  ifstream inFile(filename);
  if (inFile.is_open())
  {
    string newType;
    string newName;
    int newHealth = 0;
    int newStrength = 0;
    while (count < MAX_CREATURES && inFile >> newType >> newName >> newHealth >> newStrength)
    {
      creatures[count].setRecord(newType, newName, newHealth, newStrength);
      creaturePointers[count] = &creatures[count]; // pointers assigned once, at load time
      count++;
    }
    inFile.close();
  }
  else
  {
    cout << "\nError: could not open " << filename << '\n';
  }
}

string Army::line() const
{
  ostringstream out;
  out << setfill('-') << setw(TABLE_WIDTH) << "" << '\n';
  return out.str();
}

string Army::header() const
{
  ostringstream out;
  out << line() << left << setw(COL_NAME) << "Name" << setw(COL_TYPE) << "Type" << right
      << setw(COL_NUM) << "Health" << setw(COL_NUM) << "Strength" << '\n'
      << line();
  return out.str();
}

void Army::sortCreatures(int sortOption)
{
  bool swapped = true;
  while (swapped)
  {
    swapped = false;
    for (int i = 0; i < count - 1; i++)
    {
      bool toSwap = false;
      switch (sortOption)
      {
      case BY_NAME:
        toSwap = creaturePointers[i]->getNameLower() <
                 creaturePointers[i + 1]->getNameLower();
        break;
      case BY_TYPE:
        toSwap = creaturePointers[i]->getTypeLower() <
                 creaturePointers[i + 1]->getTypeLower();
        break;
      case BY_HEALTH:
        toSwap = creaturePointers[i]->getHealth() < creaturePointers[i + 1]->getHealth();
        break;
      case BY_STRENGTH:
        toSwap = creaturePointers[i]->getStrength() <
                 creaturePointers[i + 1]->getStrength();
        break;
      }
      if (toSwap)
      {
        Creature *temp = creaturePointers[i]; // swapping pointers only, done inline
        creaturePointers[i] = creaturePointers[i + 1];
        creaturePointers[i + 1] = temp;
        swapped = true;
      }
    }
  }
}

string Army::originalToString() const
{
  string result = header();
  for (int i = 0; i < count; i++)
  {
    result += creatures[i].toString();
  }
  result += line();
  return result;
}

string Army::sortedToString() const
{
  string result = header();
  for (int i = 0; i < count; i++)
  {
    result += creaturePointers[i]->toString();
  }
  result += line();
  return result;
}

string Army::searchCreatures(const string &searchTerm) const
{
  string matches;
  string searchLower = toLower(searchTerm);
  for (int i = 0; i < count; i++)
  { // one pass checks both name and type
    if (creatures[i].getNameLower().find(searchLower) != string::npos ||
        creatures[i].getTypeLower().find(searchLower) != string::npos)
    {
      matches += creatures[i].toString();
    }
  }
  string result;
  if (!matches.empty())
  {
    result = header() + matches + line();
  }
  return result;
}

string toLower(const string &str)
{
  string lowerStr;
  for (size_t i = 0; i < str.length(); i++)
  {
    lowerStr += (str[i] >= 'A' && str[i] <= 'Z') ? char(str[i] + 32) : str[i];
  }
  return lowerStr;
}

void clearCin(const string &errorMessage)
{ // reusable: clears failed input, reports the error
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << '\n'
       << errorMessage << '\n';
}

void sortMenu(Army &army)
{
  int sortChoice = 0;
  do
  {
    cout << "\n\nSort Menu (descending):\n"
            "1. Sort by name\n"
            "2. Sort by type\n"
            "3. Sort by health\n"
            "4. Sort by strength\n"
            "5. Back to main menu\n"
            "Enter your choice: ";
    cin >> sortChoice;
    switch (sortChoice)
    {
    case BY_NAME:
    case BY_TYPE:
    case BY_HEALTH:
    case BY_STRENGTH:
      army.sortCreatures(sortChoice);
      cout << '\n'
           << army.sortedToString();
      break;
    case BACK_TO_MAIN:
      cout << "\nGoing back to the main menu\n";
      break;
    default:
      clearCin("Invalid menu choice");
    }
  } while (sortChoice != BACK_TO_MAIN);
}

void searchOption(const Army &army)
{
  string searchTerm;
  cout << "\nEnter a name or type to search for (partial is ok): ";
  cin >> searchTerm;
  string result = army.searchCreatures(searchTerm);
  if (result.empty())
  {
    result = "No matching records found\n";
  }
  cout << '\n'
       << result;
}

/*aidentsang@Aidens-MacBook-Pro CS216_L4_AT % "/Users/aidentsang/Pierce college Labs C++/CS216_L4_AT/main"


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 1

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
sTRolleR            Goblin                101        45
sMaUg               Dragon                102        99
rITA                Elf                   103        70
gRoG                Orc                   104        32
fLaMeR              Phoenix               105        85
rOLLer              Stroller              106        12
bOuNdEr             Troll                 107        55
dRaCuLa             Vampire               108        90
fAnG                Werewolf              109        64
sWiFt               Centaur               110        73
tInK                Pixie                 111        15
sToNeR              Golem                 112        80
sHaDoW              Wraith                113        67
sKyClAw             Griffin               114        88
aQuA                Mermaid               115        40
tAuRoS              Minotaur              116        77
sPlItTeR            Hydra                 117        95
wInGs               Pegasus               118        60
mIxUp               Chimera               119        82
sCrEeCh             Banshee               120        50
-------------------------------------------------------


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 2


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 1

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
wInGs               Pegasus               118        60
tInK                Pixie                 111        15
tAuRoS              Minotaur              116        77
sWiFt               Centaur               110        73
sTRolleR            Goblin                101        45
sToNeR              Golem                 112        80
sPlItTeR            Hydra                 117        95
sMaUg               Dragon                102        99
sKyClAw             Griffin               114        88
sHaDoW              Wraith                113        67
sCrEeCh             Banshee               120        50
rOLLer              Stroller              106        12
rITA                Elf                   103        70
mIxUp               Chimera               119        82
gRoG                Orc                   104        32
fLaMeR              Phoenix               105        85
fAnG                Werewolf              109        64
dRaCuLa             Vampire               108        90
bOuNdEr             Troll                 107        55
aQuA                Mermaid               115        40
-------------------------------------------------------


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 2

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
sHaDoW              Wraith                113        67
fAnG                Werewolf              109        64
dRaCuLa             Vampire               108        90
bOuNdEr             Troll                 107        55
rOLLer              Stroller              106        12
tInK                Pixie                 111        15
fLaMeR              Phoenix               105        85
wInGs               Pegasus               118        60
gRoG                Orc                   104        32
tAuRoS              Minotaur              116        77
aQuA                Mermaid               115        40
sPlItTeR            Hydra                 117        95
sKyClAw             Griffin               114        88
sToNeR              Golem                 112        80
sTRolleR            Goblin                101        45
rITA                Elf                   103        70
sMaUg               Dragon                102        99
mIxUp               Chimera               119        82
sWiFt               Centaur               110        73
sCrEeCh             Banshee               120        50
-------------------------------------------------------


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 3

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
sCrEeCh             Banshee               120        50
mIxUp               Chimera               119        82
wInGs               Pegasus               118        60
sPlItTeR            Hydra                 117        95
tAuRoS              Minotaur              116        77
aQuA                Mermaid               115        40
sKyClAw             Griffin               114        88
sHaDoW              Wraith                113        67
sToNeR              Golem                 112        80
tInK                Pixie                 111        15
sWiFt               Centaur               110        73
fAnG                Werewolf              109        64
dRaCuLa             Vampire               108        90
bOuNdEr             Troll                 107        55
rOLLer              Stroller              106        12
fLaMeR              Phoenix               105        85
gRoG                Orc                   104        32
rITA                Elf                   103        70
sMaUg               Dragon                102        99
sTRolleR            Goblin                101        45
-------------------------------------------------------


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 4

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
sMaUg               Dragon                102        99
sPlItTeR            Hydra                 117        95
dRaCuLa             Vampire               108        90
sKyClAw             Griffin               114        88
fLaMeR              Phoenix               105        85
mIxUp               Chimera               119        82
sToNeR              Golem                 112        80
tAuRoS              Minotaur              116        77
sWiFt               Centaur               110        73
rITA                Elf                   103        70
sHaDoW              Wraith                113        67
fAnG                Werewolf              109        64
wInGs               Pegasus               118        60
bOuNdEr             Troll                 107        55
sCrEeCh             Banshee               120        50
sTRolleR            Goblin                101        45
aQuA                Mermaid               115        40
gRoG                Orc                   104        32
tInK                Pixie                 111        15
rOLLer              Stroller              106        12
-------------------------------------------------------


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 5

Going back to the main menu


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 3

Enter a name or type to search for (partial is ok): sT

-------------------------------------------------------
Name                Type               Health  Strength
-------------------------------------------------------
sTRolleR            Goblin                101        45
rOLLer              Stroller              106        12
sToNeR              Golem                 112        80
-------------------------------------------------------


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 3

Enter a name or type to search for (partial is ok): 3242fdsaI

No matching records found


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 5

Invalid menu choice


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: Ifdsa

Invalid menu choice


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: !

Invalid menu choice


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 2


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 0

Invalid menu choice


Sort Menu (descending):
1. Sort by name
2. Sort by type
3. Sort by health
4. Sort by strength
5. Back to main menu
Enter your choice: 5

Going back to the main menu


Main Menu:
1. Print creatures in the original order
2. Sort menu
3. Search by name or type
4. Quit
Enter your choice: 4

Goodbye!
aidentsang@Aidens-MacBook-Pro CS216_L4_AT % */ 
