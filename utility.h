#include <string>

using namespace std;

// Funzioni generiche

namespace util{
	int random(int, int);							/* restituisce un numero casuale tra due estremi */
	void normalize(string&);					/* normalizza la stringa */
	void removeBlanks(string&); 			/* rimuove gli psazi */
	string* splitTwo(string, string); /* divide una stringa in due parti */
}
