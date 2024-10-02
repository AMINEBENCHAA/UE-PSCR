#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>


int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
    vector<pair<string, int>> occurrences;
    // prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

    auto find_inocc = [&](const string& word) -> vector<pair<string, int>>::iterator {
        return find_if(occurrences.begin(), occurrences.end(),
                       [&word](const pair<string, int>& element) { return element.first == word; });
    };

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
         /////////////////////
        
          if (!word.empty()) {
            auto w = find_inocc(word);
            if (w != occurrences.end()){
                w->second++;
            }
            else{
                occurrences.emplace_back(word, 1);
            }
          }
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
  
    auto print_occ = [&](const string& word) {
        auto w = find_inocc(word);
        if (w != occurrences.end()) {
            cout << "The word \"" << word << "\" appears " << w->second << " times." << endl;
        } else {
            cout << "The word \"" << word << "\" does not appear in the text." << endl;
        }
    };
    print_occ("war");
    print_occ("peace");
    print_occ("toto");
    return 0;
}


