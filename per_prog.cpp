#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "entry.h"
#include "colors.h"
#include <fstream> 
#include <sstream>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
vector<Entry> entries(0);

void showInformation()
{
    cout    << "\n********************************************************************\n"<<
            "   This program is used to store information about Per.\n"<<
            "   Use the commands below to navigate the program.\n"<<
            "   All entries are saved in the file 'entries.txt'.\n"<<
            "   Don't edit it by hand.\n"<<
            "   Press 3 to see all current entries.\n"<<
            "   Everything should be entered in English,\n"<< 
            "   because Swedish letters are not supported :)\n" <<
            "   Entering -1 will abort most operations.\n"<<
            "   Additional functionality might be added if desired.\n"<<
            "   (Program created dec 2020 by Jonatan Eismark)"
            << "\n********************************************************************\n\n";
}

void showMenu()
{
    SetConsoleTextAttribute(hConsole, MAGENTA);
    cout <<     "=====================Per========================" << "\n" << "\n"; 
    SetConsoleTextAttribute(hConsole, WHITE);
    cout << "Enter one of the following commands:       " << "\n" << "\n" <<
    "   1: Add entry                                    " << "\n" <<
    "   2: Remove entry                                 " << "\n" <<
    "   3: Show entries                                 " << "\n" <<
    "   4: Update entry                                 " << "\n" <<
    "   5: Show menu                                    " << "\n" <<
    "   6: Clear screen                                 " << "\n" <<
    "   7: Show information                             " << "\n" <<
    "   8: Show entries (detailed)                      " << "\n" <<
    "  -1: Exit program                                 " << "\n"; 
    SetConsoleTextAttribute(hConsole, MAGENTA);
    cout << "\n" <<     "=====================================================================  " << "\n";
    SetConsoleTextAttribute(hConsole, WHITE);
}

void printElementsNIndex()
{
    cout << "\n";
    for (size_t i = 0; i < entries.size(); i++)
    {
        cout << "Entry " << entries[i].getDate() << " with ID " << i << "\n";
    }
    cout << "\n";
}

double getCorrectValue(string message)
{
    double result;
    cout << message;
    cin >> result;

    //cin.good() returns 0 if it has encountered a problem,
    //like assigning a char/string to an int.
    while(!cin.good())
    {
        // To clear standard input buffer. Clears error flag and skips to next line.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << message;
        cin >> result;
    }

    //Clear again just to be safe.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return result;
}

void writeAllEntries(string operation)
{
    //Delete everything
    std::fstream file;
    file.open(".\\entries.txt", ios::out);
    file.close();

    //Start filling again
    file.open(".\\entries.txt");
    if(!file.fail())
    {
        for (size_t i = 0; i < entries.size(); i++)
        {
            Entry e = entries[i];

            string line = e.getDate()+"$"+e.getAge()+"$"+e.getWeight()+"$"+e.getHeight()+"$"+e.getExtra()+"$";
            for (size_t j = 0; j < e.getWords().size(); j++)
            {
                if(j != e.getWords().size()-1) line += e.getWords()[j]+"~";
                else line += e.getWords()[j];
            }

            file << line << "<\n";

        }
        file.close();

        SetConsoleTextAttribute(hConsole, GREEN);
        cout << "\nWrite " + operation +" successful!\n";
        SetConsoleTextAttribute(hConsole, WHITE);

    }
    else
    {
        SetConsoleTextAttribute(hConsole, RED);
        cout << "\nWrite " + operation +" unsuccessful!\n";
        SetConsoleTextAttribute(hConsole, WHITE);
    }  
}

void addEntry()
{
    string date;
    cout << "Give date for new entry: " << "\n";
    getline(cin, date);
    Entry e(date);
    e.setExtra(" ");

    entries.push_back(e);

    system("cls");
    writeAllEntries("addition");
    showMenu();
}

void removeEntry()
{
    int index = -2;
    printElementsNIndex();
    while(index < -1 || index > entries.size()-1)
    {
        index = getCorrectValue("Type pos of entry to remove (or -1 to abort): ");

        //Ugly af
        if(index == -1)
        {
            system("cls");
            SetConsoleTextAttribute(hConsole, RED);
            cout << "\nRemoval aborted!\n";
            SetConsoleTextAttribute(hConsole, WHITE);
            showMenu();
            return;
        }
        //
        
        if(index < -1 || index > entries.size()-1) cout << "Wrong pos...\n";
    }

    if(index < entries.size() && index > -1)
    {
        vector<Entry> newArr(entries.size()-1);

        for (size_t i = 0; i <  newArr.size(); i++)
        {
            if(i < index) newArr[i] = entries[i];
            else if(i >= index) newArr[i] = entries[i+1];
        }

        entries = newArr;
    }
    else
    {
        cout << "Index out of bounds: " << "\n";
    }

    system("cls");
    writeAllEntries("deletion");
    showMenu();
    
}

void printEntries()
{
    cout << "\n";
    cout<<"All entries: \n";
    for (size_t i = 0; i < entries.size(); i++)
    {
        entries[i].printEntry();

    }
    SetConsoleTextAttribute(hConsole, CYAN);
        cout << "\n*******************************************\n";
    SetConsoleTextAttribute(hConsole, WHITE);
    cout << "\n";
}

int updateEntry(double index)
{
    cout << "\nEntry to edit: \n\n";
    entries[index].printEntry();
    int input = 0;
    cout << "\nEditing date, age, weight and height will replace them.\n";
    cout << "More options are available when editing words and extra information.\n";
    input = getCorrectValue("\nEnter:\n1 to edit date\n2 to edit age\n3 to edit weight\n4 to edit height\n5 to edit words\n6 to edit extra\n\nEdit nr: ");
    switch (input)
    {
    case 1:
        entries[index].updateDate();
        break;
    case 2:
        entries[index].updateAge();
        break;
    case 3:
        entries[index].updateWeight();
        break;
    case 4:
        entries[index].updateHeight();
        break;
    case 5:
        entries[index].updateWords();
        break;
    case 6:
        entries[index].updateExtra();
        break;
    case -1:
        cout << "Exiting operation" << "\n";
        return 0;
    default:
        cout << "Unrecognized command\n";
        break;
    }
    system("cls");
    writeAllEntries("update");
    return 1;
    
}

void chooseEntry()
{
    system("cls");
    printEntries();

    //Remove?
    ifstream file("entries.txt");
    string entry_S = "";
    vector<string> string_entries;

    while (getline(file, entry_S,'<'))
    {
        entry_S.erase(std::remove(entry_S.begin(), entry_S.end(), '\n'), entry_S.end()); // remove newline
        string_entries.push_back(entry_S);
    }
    file.close();
    //

    printElementsNIndex();
    double input = -2;
    while (input > entries.size()-1 || input < -1)
    {
        input = getCorrectValue("\nChoose entry to update by entering the ID: ");
        if(input == -1) break;
    }
    if(input == -1)
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, RED);
        cout << "\nUpdate aborted!\n";
        SetConsoleTextAttribute(hConsole, WHITE);
        showMenu();
    }
    else
    {
        system("cls");
        int status = updateEntry(input);

        if(status == 0)
        {
            SetConsoleTextAttribute(hConsole, RED);
            cout << "\nUpdate aborted!\n";
            SetConsoleTextAttribute(hConsole, WHITE);
        } 

        showMenu();
    }
}

void initEntries()
{
    ifstream file(".\\entries.txt");
    string entry_S = "";
    vector<string> string_entries;

    while (getline(file, entry_S,'<'))
    {
        entry_S.erase(std::remove(entry_S.begin(), entry_S.end(), '\n'), entry_S.end()); // remove newline
        string_entries.push_back(entry_S);
    }
    file.close();

    for (size_t i = 0; i < string_entries.size(); i++)
    {
        std::stringstream temp(string_entries[i]);
        string data = "";
        vector<string> entry;

        while(getline(temp, data,'$'))
        {
            entry.push_back(data);
        }        
        
        if(entry.size() > 4)
        {
            string date = entry[0];
            size_t sz;
            string age = entry[1];
            string weight = entry[2];
            string height = entry[3];
            string extra = entry[4];;
            vector<string> words;            

            if(entry.size() > 5)
            {
                string wds =  entry[5];
                std::stringstream tmp(wds);
                string segment;

                while(std::getline(tmp, segment, '~'))
                {
                    words.push_back(segment);
                }

            }

            Entry e(date);
            e.setAge(age);
            e.setWeight(weight);
            e.setHeight(height);
            e.setWords(words);
            e.setExtra(extra);

            entries.push_back(e);
        }
    }  
}

void printAndChoose()
{
    system("cls");

    printElementsNIndex();
    bool done = false;
    int index, choice;
    
    while(!done)
    {
        index = getCorrectValue("\nEnter the ID of the entry to see more information or -1 to go back: ");
        
        if(index == -1) done = true;
        else if(index > entries.size()-1 || index < -1) cout << "Entry with ID " << index << " does not exist\n";
        else 
        {
            system("cls");
            entries[index].printEntry();
            choice = getCorrectValue("\nEnter 1 to edit current entry or -1 to return to main menu: ");
            //TODO add remove entry?
            switch (choice)
            {
            case 1:
                updateEntry(index);
                done = true;
                break;
            case -1:
                done = true;
                break;
            default:
                cout << "Unrecognized command.";
                break;
            }
        }
    }
    
    system("cls");
    showMenu();
}

int main ()
{
    SetConsoleTextAttribute(hConsole, WHITE);
    int input = 0;
    showInformation();
    showMenu();
    initEntries();
    while(input != -1)
    {    
        input = getCorrectValue("\nEnter a command: ");
        switch (input)
        {
        case 1:
            addEntry();
            break;
        case 2:
            removeEntry();
            break;
        case 3:
            printAndChoose();
            break;
        case 4:
            chooseEntry();
            break;
        case 5:
            showMenu();
            break; 
        case 6:
            system("cls");
            showMenu();
            break;
        case 7:
            showInformation();
            break;
        case 8:
            printEntries();
            break;                  
        case -1:
            cout << "Program exiting" << "\n";
            break;
        default:
            cout << "Unrecognized command" << "\n";
            break;
        }

    }
    return 0;
}
