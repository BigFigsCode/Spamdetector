
//Lab 5 is a program that determines wether an email is a spam or not a spam. This is done by creating a vector of unique words 
//if the frequency of these words appear often then it is a spam. If not then it is not a spam. 
//Created by Brandon, Ricky, Nick and Connor.
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <map>
#include <set>
#include <sstream>

using namespace std;

const int MAX_ITERATIONS = 19;
const vector<string> SPAM_TRIGGER_WORDS{ "act", "africa", "Africa", "nigeria", "apply", "buy",
                                      "direct", "call", "click",
                                      "clearance",
                                      "delete", "drastically",
                                      "exclusive", "deal", "deals", "expire",
                                      "important", "instant", "limited",
                                      "costumers", "costumer", "offer",
                                      "expires", "lifetime", "order", "orders",
                                      "special", "specials", "promotion",
                                      "promotions", "action", "urgent", "stock",
                                      "stocks", "100", "allnew", "bargain",
                                      "price", "bonus", "bonuses", "marketing",
                                      "free", "access", "gift", "trial",
                                      "turned", "down", "offer",
                                      "join", "millions", "million",
                                      "billions", "billion", "incredible", "prize",
                                      "prizes", "satisfaction", "satisfactions",
                                      "guaranteed", "believe", "direct", "unlimited", "visit",
                                      "website", "websites", "acceptance",
                                      "access", "avoid", "bankruptcy", "boss",
                                      "cancel", "cheap", "compare", "rates",
                                      "congrats", "congratulation", "congratulations",
                                      "credit", "card", "offers", "cures", "dear",
                                      "friend", "reduced", "terms",
                                      "grant", "money", "membership", "guarantee",
                                      "request", "requested", "join",
                                      "obligation", "purchase", "offer",
                                      "opportunity", "save", "win", "won", "winner",
                                      "winners", "youve", "additional",
                                      "income", "allnatural", "amazing",
                                      "bucks", "dollars", "cash", "debt", "debit",
                                      "consolidate", "double", "earn", "extra",
                                      "eliminate", "bad", "freedom", "financial",
                                      "independent", "investment", "paid", "home",
                                      "home-based", "sales", "traffic",
                                      "catch", "lose", "cost", "costs",
                                      "strings", "potential", "earnings", "pure",
                                      "profit", "removes", "remove", "wrinkles",
                                      "aging", "reverse", "reversing",
                                      "riskfree", "serious", "vacation", "weekend",
                                      "offers", "getaway", "loss", "sleep",
                                      "address", "addresses", "beneficiary", "billing",
                                      "casino", "celebrity", "celebrities",
                                      "collect", "child", "children", "copy",
                                      "copies", "dvd", "dvds", "hidden", "delivery",
                                      "human", "law", "laws", "investments", "junk",
                                      "legal", "life", "insurance", "loan", "lottery",
                                      "luxury", "medicine", "offshore", "degree", "password", "passwords",
                                      "refinance", "rolex", "score", "social",
                                      "security", "number", "spam", "undisclosed",
                                      "recipient", "recipients", "university", "diploma",
                                      "diplomas", "unsecured", "weather", "environment" };

class SpamResources {
public:
    SpamResources() = default;
    static vector<pair<string, int>> readFile(const string& namePath);
    string fileName = "Emails/em0000.txt"; // this text file is empty and is there as a starter

private:
    vector<pair<string, int>> fileContainer;
};

vector<pair<string, int>> SpamResources::readFile(const string& namePath) {
    ifstream in(namePath);
    vector<pair<string, int>> wordsInFile; // vector of pairs
    map<string, int> frequencies; // map
    pair<string, int> wordInVector; // pair
    string word; // element checked

    //cout << "WORD\t\tFREQUENCY" << endl;
    while (in.good())
    {
        in >> word; // get the word from the file

        for (int i = 0; i < word.size(); i++) {
            if (word[i] < 48 || (word[i] > 57 && word[i] < 65) || (word[i] > 90 && word[i] < 97) || word[i] > 122) {
                word.erase(remove(word.begin(), word.end(), word[i]), word.end());
            }
        }

        if (word.empty()) {
            continue;
        }

        for (auto& i : wordsInFile) {
            if (word == i.first) {
                i.second++;
                break;
            }
        }

        wordInVector.first = word;
        wordInVector.second = 1; // first time that the word appears
        wordsInFile.push_back(wordInVector); // increase the count of the word instead of re-adding it
    }
    for (auto& i : wordsInFile) {
        frequencies.insert(i);
    }

    // make the strings unique
    map<string, int>::iterator itr;

    wordsInFile.clear(); // re-use the vector

    for (itr = frequencies.begin(); itr != frequencies.end(); ++itr) {
        wordsInFile.emplace_back(itr->first, itr->second);
    }

    /*
    for (auto & i : wordsInFile) {
        cout << "Word: " << i.first << "           Frequency: " << i.second << endl;
    }
     */

    set<string> temp;

    int countTrigger = 0;
    for (auto& w : wordsInFile) {
        for (const auto& s : SPAM_TRIGGER_WORDS) {
            if (w.first == s) {
                countTrigger++;
                temp.insert(w.first);
            }
        }
    }

    int tempSize = temp.size();


    cout << endl;
    if (countTrigger >= 3 && tempSize >= 2) {
        cout << "The file containing an e-mail at path '" << namePath << "' is a spam" << endl;
    }
    else {
        cout << "The file containing an e-mail at path '" << namePath << "' is safe" << endl;
    }
    cout << "CountTrigger = " << countTrigger << endl;
    cout << "Different triggers = " << tempSize << endl;
    return wordsInFile;
}

void fileIterator(const string& s) {
    SpamResources spamResources;
    int counter = 1;
    string oldPath = s;
    string newPath = s.substr(9, 4);
    istringstream in(newPath);
    int int_key;
    in >> int_key;
    while (int_key < MAX_ITERATIONS) {
        if (int_key == pow(int_key, 10) && int_key != 1 && int_key != 0) {
            int_key /= 10;
            int_key++;
            int_key *= 10;
        }
        else {
            int_key++;
        }
        ostringstream out;
        out << int_key;
        newPath = out.str();
        if (int_key < 10) {
            oldPath = oldPath.replace(12, 1, newPath);
        }
        if (int_key >= 10 && int_key <= 99) {
            oldPath = oldPath.replace(11, 2, newPath);
        }
        if (int_key >= 100 && int_key <= 999) {
            oldPath = oldPath.replace(10, 3, newPath);
        }
        if (int_key >= 1000 && int_key <= 9999) {
            oldPath = oldPath.replace(9, 4, newPath);
        }
        newPath = oldPath;
        cout << "File #" << counter << ": " << newPath << "\n\n";
        spamResources.readFile(newPath);
        cout << "\n\n";
        counter++;
    }
}


int main() {
    SpamResources spamResources;

    fileIterator(spamResources.fileName);

    return 0;
}
