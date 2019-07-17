#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

// Bad example of single responsability
// the journal should not be responsable of saving the content
struct Journal {
    string title;
    vector<string> entries;

    Journal(const struct &title) : title(title) {}

    void add_entry(string entry) {
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }

    void save(const string& filename){
        ofstream ofs(filename);

        for (auto& e: entries)
            ofs << e << endl;
    }
}

// Good Implementation for a journal
struct GoodJournal {
    string title;
    vector<string> entries;

    GoodJournal(const struct &title) : title(title) {}

    void add_entry(string entry) {
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }
}

// The Persistance Manager can be easily modified to incorporate new scenarios
struct PersistenceManager
{
    static void save_to_file(const GoodJournal& j, const string& filename)
    {
        ofstream ofs(filename);
        for(auto& e: j.entries)
            ofs << e << endl;
    }

    static void save_to_DB(const GoodJournal& j, const string& dbName)
    {
            // ToDo
    }

    static void print_to_screen(const GoodJournal& j)
    {
        for(auto& e: j.entries)
            cout << e << endl;
    }
}

int main() {
    return 0;

    Journal journal("My Journal");
    journal.add_entry("first entry");
    journal.add_entry("second entry");
    journal.add_entry("third entry");
    journal.save("file.txt");

    GoodJournal newJournal("My good journal");
    newJournal.add_entry("first entry");
    newJournal.add_entry("second entry");

    PersistenceManager::save_to_file(newJournal, "file2.txt");
    PersistenceManager::save_to_file(newJournal);
}

