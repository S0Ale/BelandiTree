#include <string>
#include <random>

using namespace std;

// Funzioni generiche

namespace util{
	int random(int, int);							/* restituisce un numero casuale tra due estremi */
	void normalize(string&);					/* normalizza la stringa */
	string* splitTwo(string, string); /* divide una stringa in due parti */
}
