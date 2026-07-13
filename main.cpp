//Aiden Tsang
//Lab 4

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

/*Output
aidentsang@Aidens-MacBook-Pro CS216_L4_AT % "/Users/aidentsang/Pierce college Labs C++/CS216_L4_AT/main"

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 1

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
101       sTRolleR            Goblin                 45
102       sMaUg               Dragon                 99
103       rITA                Elf                    70
104       gRoG                Orc                    32
105       fLaMeR              Phoenix                85
106       rOLLer              Stroller               12
107       bOuNdEr             Troll                  55
108       dRaCuLa             Vampire                90
109       fAnG                Werewolf               64
110       sWiFt               Centaur                73
111       tInK                Pixie                  15
112       sToNeR              Golem                  80
113       sHaDoW              Wraith                 67
114       sKyClAw             Griffin                88
115       aQuA                Mermaid                40
116       tAuRoS              Minotaur               77
117       sPlItTeR            Hydra                  95
118       wInGs               Pegasus                60
119       mIxUp               Chimera                82
120       sCrEeCh             Banshee                50
-----------------------------------------------------

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 2

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 1

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
120       sCrEeCh             Banshee                50
119       mIxUp               Chimera                82
118       wInGs               Pegasus                60
117       sPlItTeR            Hydra                  95
116       tAuRoS              Minotaur               77
115       aQuA                Mermaid                40
114       sKyClAw             Griffin                88
113       sHaDoW              Wraith                 67
112       sToNeR              Golem                  80
111       tInK                Pixie                  15
110       sWiFt               Centaur                73
109       fAnG                Werewolf               64
108       dRaCuLa             Vampire                90
107       bOuNdEr             Troll                  55
106       rOLLer              Stroller               12
105       fLaMeR              Phoenix                85
104       gRoG                Orc                    32
103       rITA                Elf                    70
102       sMaUg               Dragon                 99
101       sTRolleR            Goblin                 45
-----------------------------------------------------

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 2

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
118       wInGs               Pegasus                60
111       tInK                Pixie                  15
116       tAuRoS              Minotaur               77
110       sWiFt               Centaur                73
101       sTRolleR            Goblin                 45
112       sToNeR              Golem                  80
117       sPlItTeR            Hydra                  95
102       sMaUg               Dragon                 99
114       sKyClAw             Griffin                88
113       sHaDoW              Wraith                 67
120       sCrEeCh             Banshee                50
106       rOLLer              Stroller               12
103       rITA                Elf                    70
119       mIxUp               Chimera                82
104       gRoG                Orc                    32
105       fLaMeR              Phoenix                85
109       fAnG                Werewolf               64
108       dRaCuLa             Vampire                90
107       bOuNdEr             Troll                  55
115       aQuA                Mermaid                40
-----------------------------------------------------

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 3

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
113       sHaDoW              Wraith                 67
109       fAnG                Werewolf               64
108       dRaCuLa             Vampire                90
107       bOuNdEr             Troll                  55
106       rOLLer              Stroller               12
111       tInK                Pixie                  15
105       fLaMeR              Phoenix                85
118       wInGs               Pegasus                60
104       gRoG                Orc                    32
116       tAuRoS              Minotaur               77
115       aQuA                Mermaid                40
117       sPlItTeR            Hydra                  95
114       sKyClAw             Griffin                88
112       sToNeR              Golem                  80
101       sTRolleR            Goblin                 45
103       rITA                Elf                    70
102       sMaUg               Dragon                 99
119       mIxUp               Chimera                82
110       sWiFt               Centaur                73
120       sCrEeCh             Banshee                50
-----------------------------------------------------

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 4

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
102       sMaUg               Dragon                 99
117       sPlItTeR            Hydra                  95
108       dRaCuLa             Vampire                90
114       sKyClAw             Griffin                88
105       fLaMeR              Phoenix                85
119       mIxUp               Chimera                82
112       sToNeR              Golem                  80
116       tAuRoS              Minotaur               77
110       sWiFt               Centaur                73
103       rITA                Elf                    70
113       sHaDoW              Wraith                 67
109       fAnG                Werewolf               64
118       wInGs               Pegasus                60
107       bOuNdEr             Troll                  55
120       sCrEeCh             Banshee                50
101       sTRolleR            Goblin                 45
115       aQuA                Mermaid                40
104       gRoG                Orc                    32
111       tInK                Pixie                  15
106       rOLLer              Stroller               12
-----------------------------------------------------

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 5
Returning to main menu...

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 3
Enter search term (partial or full Name/Type): sToNeR

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
112       sToNeR              Golem                  80
-----------------------------------------------------

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 5
Invalid main menu selection.

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 1

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
101       sTRolleR            Goblin                 45
102       sMaUg               Dragon                 99
103       rITA                Elf                    70
104       gRoG                Orc                    32
105       fLaMeR              Phoenix                85
106       rOLLer              Stroller               12
107       bOuNdEr             Troll                  55
108       dRaCuLa             Vampire                90
109       fAnG                Werewolf               64
110       sWiFt               Centaur                73
111       tInK                Pixie                  15
112       sToNeR              Golem                  80
113       sHaDoW              Wraith                 67
114       sKyClAw             Griffin                88
115       aQuA                Mermaid                40
116       tAuRoS              Minotaur               77
117       sPlItTeR            Hydra                  95
118       wInGs               Pegasus                60
119       mIxUp               Chimera                82
120       sCrEeCh             Banshee                50
-----------------------------------------------------

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 2

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 7
Invalid choice. Try again.

--- Sort Submenu (Descending) ---
1. Sort by ID
2. Sort by Name
3. Sort by Type
4. Sort by Level
5. Back to Main Menu
Enter selection: 5
Returning to main menu...

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 3
Enter search term (partial or full Name/Type): 4321

-----------------------------------------------------
ID        Name                Type                Level
-----------------------------------------------------
-----------------------------------------------------
No matching records found.

=== Main Menu ===
1. Print Original List
2. Sort Menu (Descending)
3. Search (Name or Type)
4. Quit
Enter selection: 4
Exiting application. Goodbye!
aidentsang@Aidens-MacBook-Pro CS216_L4_AT % */
