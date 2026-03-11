#include <iostream>
#include <fstream>

int Temperature(const std::string nome_file) {
	std::ifstream ifs(nome_file);
	if (ifs.is_open() ) {
		for (int i = 1; i <= 3; i++ ) {
			std::string city;
			double temp0;
			double temp6;
			double temp12;
			double temp18;
			ifs >> city >> temp0 >> temp6 >> temp12 >> temp18;
			double temp = (temp0+temp6+temp12+temp18)/4.0;
			std::cout << "Temperature at " << city << " is " << temp << " \n";
		}
		return 0;
	}
	std::cout << "file non aperto correttamente \n";
	return 1;
}
	