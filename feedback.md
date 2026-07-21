**NG 7/14/2026**
* **To provide you with thorough feedback, I read your code line by line, sometimes multiple times**. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main() and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise. Submit a fully completed lab by th due date using the correct GitHub invite link to get a second chance
* **feedback.md is for instructor use only**: please DO NOT change the feedback.md; make a copy if needed; do not add anything; if you do not understand  the feedback, let me know asap (mymail.laccd.edu, grigorn@laccd.edu)
* if any, items with (-X) - no deductions this time, serve as a warning; please ensure these errors are corrected, as repeating them in future assignments will result in X points being deducted
* in feedback, #N means line number, e.g., 
```text
* #25  global var(s); only constant may be global -10
meaning: see line #25 ; -10 deduction points for the mistake
```
* **class definition style & standards**:  first, member vars  one per line and do not forget to initialize them to state; although private is a default access specifier, still label private members  clearly for better readability; second- functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions, except for static function,  should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary;  to promote strong exception guarantee and to reduce redundancy, all setter functions, including c’tors, must call a setter function that sets all member variables
* **strong exception guarantee**: this guarantee acts as a transaction. If the operation successfully completes, all changes take effect; if it fails mid-execution, all partial changes are completely undone. If incoming values are invalid, do not change member variables; provided all member variables have been initialized to a valid state in the class definition and c’tors, the object will always be valid
* **there is no such thing as a partially valid record or set of related data** (let's say, a Creature record in an input file). If any required field (e.g., health, strength) in a record is invalid, then the entire record must be considered invalid. As a developer, your responsibility is to validate the input, not to "fix" it by replacing invalid values with defaults. Doing so changes the user's data and assumes you know what they intended to enter. In general, you should not guess what the user meant or silently modify invalid input. Instead, detect the invalid record and handle it according to the program's requirements (for example, by rejecting it or reporting an error). 
* in  CS 216, **classes must completely manage their own failures**; classes must catch and handle internal errors locally to maintain safe, fully encapsulated invariants. In other words, classes must maintain encapsulation by catching and handling internal exceptions locally. According to the C++ Core Guidelines, an object should achieve the no-fail or strong exception guarantee by rolling back state or swallowing expected failures internally so callers aren't burdened with cleanup.
* moving forward, if a lab submission does not comply with posted instructions, it will result in a loss of an attempt, further feedback will not be provided, and additional attempts will not be granted 
* 72 and like: initialize all member variables at the time of definition to default valid state (makes defaults obvious, reduces code duplication, prevents uninitialized variables) to avoid initialization lists and improve readabilty; members are initialized in the order they are declared in the class, not the order they appear in the initialization list; every time you add a new member that needs initialization, you may need to update in multiple locations;  pre C++11,  members could not be initialized in the class definition so it made sense to use initialization lists; nowadays, use initializations list only when it is absolutely necessary and there is no other way around it  ( const members, references, base classes) (-5) -2
*  #69 : poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”, e.g., MAX_TERMS, PRINT_RECORDS; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ( rhs- right-hand side, src – source); do not use IDs and default values that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious; vars should not be called value;  one char identifiers (e.g. j,k, i) are only suitable for loop counters;  (-2) -1
```text
 // NG - All variables hold values
setRecord
```
* 197 , 204 why are these members of the Army class?  (-2)
* #56  allows implicit conversion -2
* #44 missing default c’tor(s); all classes, including exception classes and child classes, must have their own default c’tors; c’tors are not inherited in C++; may not use =default, “using” in this class; easy fix for exception classes: explicit Exception(const string & ex =”Unknown error”); //parameterized default c’tor  -5
* 186 I would do it in c’tor(s)  so any time when an Army object is created, the creature array and pointer array would be parallel regardless of how creatures are loaded (-1)
* #353: cout should mimic output on the screen; in this context it should be on a single line; adds unnecessary amount of scrolling when reading the code  (-1)
***



**NG 7/13/2026**
* To provide you with thorough feedback, your instructor reads your code line by line, sometimes multiple times. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main() and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise. Submit a fully completed lab by th due date using correct GitHib invite link to get a second chance
* feedback.md is for instructor use only.  Please DO NOT change the feedback.md; make a copy if needed; do no add anything
* if any, items with (-X) - no deductions this time, serve as a warning; please ensure these errors are corrected, as repeating them in future assignments will result in X points being deducted
* in feedback, #N means line number, e.g., 
```text
* #25  global var(s); only constant may be global -10
meaning: see line #25 ; -10 deduction points for the mistake
```

  * 279  and like : I would have returned a very very long string with all records sorted ( in case of search) or  found records ( in case of search)  so it can be output to a screen or a file (  e.g.,result +=creatures[i].toString()) 
* 204 and like: do not put closing } on the same line as else; else/else-if should be on their lines;  hard to read -2
* #276 and like: use setfill() to output the same char multiple times (-1)
* class definition style & standards:  first, member vars  one per line and do not forget to initialize them; although private is a default access specifier, still label private members  clearly for better readability;  second- functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions, except for static function,  should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary;  to promote strong exception guarantee and to reduce redundancy, all setter functions, including c’tors, must call a setter function that sets all member variables
* 35 and like to ensure a strong exception guarantee, all setter functions, including c’tors,  must call the set function that sets all member variables, and all member variables must be initialized at the time of definition; this is to reduce the number of statements needed in setter function, reduce redundancy, simplify validation (if any),  and to avoid initialization list,e.g., setHealth() should be calling setCreature with 3 args -2 (-5)
* creature class does not comply with the assignment  -20
* #60 What does this function have to do with Army? It should belong to main() -2
* pointers are DANGEROUS if not handled properly;  ALWAYS initialize them at the time of definition; if you do not know yet where they should be pointing to, initialize them to nullptr -5
```
myClass *pMyObj=nullptr;
int *pList[MAX]={nullptr}; //initializes all pointers to nullptr; no loop needed
```
 * 64,63 the Army class should provide a strong exception guarantee: if the operation successfully completes, all changes take effect; if it fails mid-execution, all partial changes are completely undone.  The same applies to loading creatures from an input file ( loadCreatures()) .  If you make loadCretures()  public, it can be called at any time from outside the Army class (for example, by main() using an existing Army object).  Consider what happens if an Army object already contains creatures and a call to loadCreatures() fails while loading a new set. What state is the existing Army left in? Could some of the original data be lost or only partially replaced? For  Lab #4, the focus is on implementing sorting with a parallel array of pointers and searching, not on writing exception-safe reload logic. Therefore, make loadCreatures() a private member function so it cannot be called directly from outside the Army class. Instead, call it only from the Army constructor(s), where the object is being initialized. -10
* #80-85 and like: excessive use of cout/cin/ file stream/and/or endl and/or << >> results in unnecessary computational expense (time and space); applies to all output, not just menu; << and >> are not just symbols, they are  operators with functions “behind” them; calling an object ( cin, cout, infile, etc., is a computation expense  as well, menu options should be on separate lines in the source code and console; same applies when working with files -5
* << not needed between strings
* put ‘\n’ is at the end of the previous whenever possible
* Should print a couple of blank lines before the menu to separate from the lines of text above it * no need for the “.” at the end of menu options; it is just clutter, but no useful info to a user
*  e.g., input>>name>>id>gpa; 
```text
//e.g.
cout<<fixed<<showpoint<<setprecision(2);
//needed once only unless they need to be changed
cout << "\n\nMenu:\n" //note \n\n before Menu – automatically creates separation
"1. Encrypt\n" //not ‘\n’ at the end of the previous line for better readability
"2. Decrypt\n"
```
*#90 and like cin.ignore(…); what will happen if a user enters +1 more chars than you specified; should discard max char possible  -2 

* 87 redundant; invalid menu choice should be handled by default case of the menu switch; create a highly reusable function that takes an error message string as a parameter, clears the failed input, and outputs the error message to be called in the default case of the menu switch -5
```text
do {
switch (sortChoice) {
            case SORT_NAME:
            case SORT_HEALTH:
                sortMenu(names, types, health, strength, numCreatures, sortChoice);
                break;
            case BACK:
		//message about going back to the previous menu
                break;
            default:
                clearCin("Invalid menu choice");
        }
}while (sortChoice!=QUIT) 
```
* #100 and like: modularization; each menu option should have its own function with the possible exception of the QUIT case with one cout statement; as a rule of thumb, if a case in a switch has more than 2 statements, make it a function;  all menus should be implemented using switch and enum; see assignment -5
* Do not use NULL  to initialize pointers;  NULL is actually an integer 0 (or a macro for 0) rather than a true pointer type; this causes serious issues with function overloading and type safety -5
***

