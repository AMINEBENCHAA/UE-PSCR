#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <unordered_map>

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
    
    unordered_map <string, int> occurrences;
    // prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

    
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
         /////////////////////
         if(!word.empty()){
            occurrences[word]++;
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
    vector<pair<string, int>> mots_vector(occurrences.begin(), occurrences.end());
    
    for (size_t i = 0; i < min(size_t(10), mots_vector.size()); ++i) {
    cout << mots_vector[i].first << " : " << mots_vector[i].second << endl;
    std::sort(mots_vector.begin(), mots_vector.end(), [] (const Etu & a, const Etu & b) { return a.note > b.note ;});
    
}

    return 0;
}





