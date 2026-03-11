#include <iostream>
#include <string>

int Temperature(const std::string nome_file);

int main(int argc, const char *argv[]) {
	std::cout << "Numero di parametri: " << argc << "\n";
	if (argc != 2) {
		std::cout << "numero di parametri errato \n";
		return 1;
	}
	Temperature(argv[1]);
	return 0;
}