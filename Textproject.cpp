#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string RemovePunct(string word) {
    string newWord;

    if (!isalpha(word.at(word.length()-1))) {
        newWord = word.substr(0, word.length()-1);
    }

    return newWord;
}

string Option2(string theWords2[], int size) {
    int lengthWord = 0;
    char lastAlpha = 'a';
    string longestWord, newlongestWord;
    
    for (int i = 0; i < size; i++) {
        // finds longest word so far and updates
        if (theWords2[i].length() > lengthWord) {
            lastAlpha = theWords2[i].at(0);
            lengthWord = theWords2[i].length();
            longestWord = theWords2[i];
        }
        // if a word and the longest word have the same length - the last alphabet of first letter of the word takes priority. Ex.) (t > b)
        else if ((theWords2[i].length() == lengthWord) && (theWords2[i].at(0)) > lastAlpha) {
            lastAlpha = theWords2[i].at(0);
            lengthWord = theWords2[i].length();
            longestWord = theWords2[i];
        }
        // if a word has same length AND same first letter. Finds next occuring letter that is different.
        else if ((theWords2[i].length() == lengthWord) && (theWords2[i].at(0) == lastAlpha)) {
            for (int j = 0; j < lengthWord; j++) {
                if (theWords2[i].at(j) > longestWord.at(j)) {
                    longestWord = theWords2[i];
                } 
            }
        }
    }

    return longestWord;
}

string Option3(string sentence, int sizeLine) {
    string temp;
    string revisedText = "";

    for (int i = 0; i < sizeLine; i++) {
       if (!isalpha(sentence.at(i))) {
           revisedText += " ";
       }
       else {
           revisedText += sentence.at(i);
       }
    }
    return revisedText;
}

// (Option 4)sorts words in array by length and alphabetically
void sort(string sWords[], int n) { 
    bool compare, swap;  
    for (int i=1 ;i<n; i++) {
        string temp = sWords[i];
 
        int j = i - 1;
        while (j >= 0 && temp.length() <= sWords[j].length()) {
            if ((temp.length() == sWords[j].length()) && temp.at(0) > sWords[j].at(0)) {      
                sWords[j] = sWords[j];
                break;    
            }

            else if ((temp.length() == sWords[j].length()) && temp.at(0) == sWords[j].at(0)) {
                int count = 0;
                for (int i = 0; i < temp.length(); i++) {
                    if (temp.at(i) > sWords[j].at(i)) {
                        sWords[j] = sWords[j];
                        break;
                    }
                    else if (temp.at(i) < sWords[j].at(i)) {
                        sWords[j+1] = sWords[j];
                        count++;
                        j--;
                        break;    

                    }
                }
                if (count > 0) {
                    continue;
                }
                else {
                    break;
                }
            }
            else {
                sWords[j+1] = sWords[j];
                j--;
            }
            
        }
        sWords[j+1] = temp;
    }
}
  
// prints out the sorted array of string
void PrintSortedArray(string str[], int n) {
    ofstream fout("sorted.txt");
    
    for (int i=0; i<n; i++) {
        for (int j = 0; j < str[i].length();j++) {
            if(isalpha(str[i].at(j))) {
                fout << str[i].at(j);
            }
        }
        fout << endl;
    } 
}
 

int main() {
    string filename, readlines;
    int menuNum;

    
    cin >> filename;

    ifstream fin(filename);
    ifstream fin2(filename);

    if (!fin.is_open()) {
        cout << "File not found!" << endl;
        return -1;
    }

    string tempwords[100];
    int j = 0;

    while (!fin.eof()) {    
        fin >> tempwords[j];
        j++;
    }


   
    // (Option1) removing non-words and punctuation from temp array, and updating new array
   string words[100];
   for (int i = 0; i < j; i++) {
        if (isalpha(tempwords[i].at(0))) {
            if (!isalpha(tempwords[i].at(tempwords[i].length()-1))) {
                words[i] = RemovePunct(tempwords[i]);
            }
            else {
                words[i] = tempwords[i];
            }
            
        }
        else {  
            words[i] = RemovePunct(tempwords[i+1]);
            j--;
        }
    }

    do {
        cout << "--------------------------------------------------------------" << endl;
        cout << "Please make your choice:" << endl;
        cout << " 0 - Exit" << endl;
        cout << " 1 - Word count" << endl;
        cout << " 2 - Find the longest word that appears the last alphabetically" << endl;
        cout << " 3 - Replace all non alphabetical characters with whitespaces and output the new text on screen" << endl;
        cout << " 4 - Output all words in order of their lengths and alphabetically" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cin >> menuNum;
        while ((menuNum < 0) || (menuNum > 4)) {
            cout << "Please only enter 0, 1, 2, 3, or 4!" << endl;
             cout << "--------------------------------------------------------------" << endl;
            cout << "Please make your choice:" << endl;
            cout << " 0 - Exit" << endl;
            cout << " 1 - Word count" << endl;
            cout << " 2 - Find the longest word that appears the last alphabetically" << endl;
            cout << " 3 - Replace all non alphabetical characters with whitespaces and output the new text on screen" << endl;
            cout << " 4 - Output all words in order of their lengths and alphabetically" << endl;
            cout << "--------------------------------------------------------------" << endl;
            cin >> menuNum;
        }
        
        
        if (menuNum == 1){
            cout << "The number of words in the text is " << j << endl; 
        }   

        string sizeWord = Option2(words, j);
        if (menuNum == 2) {
            cout << "The longest word that appears the last alphabetically is " << sizeWord << endl;
        }

        if (menuNum == 3) {
            while (getline(fin2, readlines)) {
                int lineSize = readlines.length();
                cout << Option3(readlines, lineSize) << endl;
            }
            
        }

        if (menuNum == 4) {
            sort(words, j);
            PrintSortedArray(words, j);
        }
        
    } while (menuNum != 0);

    fin.close();
  
return 0;
}