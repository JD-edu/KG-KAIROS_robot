#include<iostream>
#include<vector>

std::vector<int> vi; // siva 라는 배열이 있는데 이 배열의 항목이 integer 값이다. 
std::vector<float> vf;

int main() {
	vi.push_back(1000);
	vi.push_back(2313);
	vi.push_back(2351);
	for(int i = 0; i < vi.size(); i++){
		std::cout << vi[i] << std::endl;
	}
	std::cout << vi.at(1) << std::endl;
}