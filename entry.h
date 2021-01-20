#include <iostream>
#include <vector>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <string>
#include "colors.h"
using namespace std;

HANDLE hConsole2 = GetStdHandle(STD_OUTPUT_HANDLE);

class Entry
{
private:
    string date;
    string age;
    string weight;
    string height;
    string extra;
    vector<string> words;

    string remIllCh(string s)
    {
        string result = s;
        result.erase(std::remove(result.begin(), result.end(), '~'), result.end());
        result.erase(std::remove(result.begin(), result.end(), '$'), result.end());
        result.erase(std::remove(result.begin(), result.end(), '<'), result.end());
        return result;
    };
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
    };
    void printElementsNIndex()
    {
        cout << "\n";
        for (size_t i = 0; i < words.size(); i++)
        {
            cout << "Element " << words[i] << " at pos [" << i << "]\n";
        }
        cout << "\n";
    };
    void addWord()
    {
        string word;
        cout << "Enter a word: " << "\n";
        getline(cin, word);
        words.push_back(remIllCh(word));
    };
    void removeWord()
    {
        int index = -1;
        printElementsNIndex();
        while(index < 0 || index > words.size()-1)
        {
            index = getCorrectValue("Type pos of word to remove: ");
            if(index < 0 || index > words.size()-1) cout << "Wrong pos...\n";
        }

        if(index < words.size() && index > -1)
        {
            vector<string> newArr(words.size()-1);

            for (size_t i = 0; i <  newArr.size(); i++)
            {
                if(i < index) newArr[i] = words[i];
                else if(i >= index) newArr[i] = words[i+1];
                
            }

            words = newArr;
        }
        else
        {
        cout << "Index out of bounds: " << "\n";
        }
        
    };

public:
    Entry(){};
    Entry(string d)
    {
        date = remIllCh(d);
        age = " ";
        weight = " ";
        height = " ";
    };

    void setDate(string d){date = remIllCh(d);};
    void setAge(string a){age = remIllCh(a);};
    void setWeight(string w){weight = remIllCh(w);};
    void setHeight(string l){height = remIllCh(l);};
    void setWords(vector<string> wo)
    {
        words = wo;
        for (size_t i = 0; i < words.size(); i++)
        {
            words[i] = remIllCh(words[i]);
        }
        
    };
    void setExtra(string e){extra = remIllCh(e);};
    
    void updateDate()
    {   
        string date_;
        cout << "\nGive new date: " << "\n";
        getline(cin, date_);

        date = remIllCh(date_);
    };
    void updateAge()
    {
        string age_;
        cout << "\nGive new age: " << "\n";
        getline(cin, age_);

        age = remIllCh(age_);
    };
    void updateWeight()
    {
        string weight_;
        cout << "\nGive new weight: " << "\n";
        getline(cin, weight_);

        weight = remIllCh(weight_);
    };
    void updateHeight()
    {
        string height_;
        cout << "\nGive new height: " << "\n";
        getline(cin, height_);

        height = remIllCh(height_);
    };
       
    void updateWords()
    {
        int input;
        input = getCorrectValue(date+": Press 1 to add a word and 2 to remove a word: ");

        switch (input)
        {
        case 1:
            addWord();
            break;
        case 2:
            if(words.size() > 0) removeWord();
            else cout << "\nThere are no words to remove\n";
            break;
        case -1:
            cout << "Exiting operation" << "\n";
            break;
        default:
            cout << "Unrecoqnized command \n";
            break;
        }

    };

    void updateExtra()
    {   
        int mode;
        string extra_;
        std::string::size_type sz;
        mode = getCorrectValue("Press 1 to add text or 2 to rewrite:  ");
        
        switch (mode)
        {
        case 1:       
            cout << "\nAdd to extra info: \n";
            cout << extra << " ";
            getline(cin, extra_);
            if(extra_.size() == 2 && extra_[0] == '-' && isdigit(extra_[1]) && stoi(extra_, &sz) == -1) break;
            else extra += remIllCh(extra_); break;
        case 2:
            cout << "\nWrite new extra info: \n";
            getline(cin, extra_);
            if(extra_.size() == 2 && extra_[0] == '-' && isdigit(extra_[1]) && stoi(extra_, &sz) == -1) break;
            else extra = remIllCh(extra_); break;
        default:
            cout << "Unrecognized command, aborting\n";
            break;
        }
       
    };

    string getDate(){return date;};
    string getAge(){return age;};
    string getWeight(){return weight;};
    string getHeight(){return height;};
    vector<string> getWords(){return words;};
    string getExtra(){return extra;};

    void printEntry(){
        SetConsoleTextAttribute(hConsole2, CYAN);
        cout << "\n*******************************************\n";
        SetConsoleTextAttribute(hConsole2, WHITE);
        cout    << "Date:         " << date << "\n" 
                << "Age:          " << age << "\n" 
                << "Weight:       " << weight << "\n" 
                << "Height:       " << height << "\n"
                << "Extra info:   " << extra << "\n\n";
        cout << "Words spoken during (up until) " << date << ":\n";
        for (size_t j = 0; j < words.size(); j++)
        {
            cout << " - " << words[j]<<"\n";
        }
        SetConsoleTextAttribute(hConsole2, CYAN);
        cout << "\n*******************************************\n";
        //cout << "\n___________________________________________\n";
        SetConsoleTextAttribute(hConsole2, WHITE);
    };

};


