#include "MainIncludes.h"
#include "DEFINITIONS.h"

int main() {
	NumberConverter convert;
	int n;
	
	std::cin >> n;
	std::vector<int> out1;
	int out2, dec;
	
	out1 = convert.vd2b(n);
	std::cout << std::endl;
	
	for (int i = 0; i < out1.size(); i++) {
		std::cout << out1[i];
	}
	
	std::cout << std::endl;

	out2 = convert.d2b(n);
	dec = convert.b2d(out2);
	
	std::cout << out2 << std::endl << dec;
	
	return 0;
}