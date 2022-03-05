#include "Dictionary.h"

using namespace std; //Trying it for std
int main() {
	printf("Letuth starteth da tests");
    Dictionary D;
    std::string s = "k";
    D.setValue(s, 12);
    s = "b";
    D.setValue(s, 1);
    s = "d";
    D.setValue(s, 11);
    s = "z";
    D.setValue(s, 2);
    std::cout << D << std::endl;
    Dictionary K;
	K = D;
    std::cout << K << std::endl;
	K.begin();
	s = K.currentKey();
	std::cout << s << std::endl;
	K.end();
	s = K.currentKey();
	std::cout << s << std::endl;
	D.end();
	s = D.currentKey();
	std::cout << s << std::endl;
	Dictionary B = K;
	if (!(B == K)) {
		printf("not right!");
	}
	D.clear();
	if (D == K) {
		printf("incorrreeeddck!!");
	}
	printf("Thus endeth the tests");
    return 0;
}
