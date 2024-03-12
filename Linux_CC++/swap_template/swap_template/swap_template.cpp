#include<iostream>
#include<vector>
#include<algorithm>>

std::vector<std::string> uga;
int main() {
	std::string uu;
	for (int i = 0; i < 5; i++) {
		std::cin >> uu;
		uga.push_back(uu);
	}

	std::sort(uga.begin(), uga.end());

	for (int i = 0; i < 5; i++) {
		std::cout << uga[i] << std::endl;
	}
}
