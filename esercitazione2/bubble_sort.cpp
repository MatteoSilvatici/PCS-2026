#include <iostream>
#include <algorithm>

int main() {
	static const int N = 10;
	double arr[N] = {3,5,6,7,1,2,4,9,8,10};
	int i = 0;
	while (i < 10) {
		if (arr[i] > arr[i+1]) {
			double temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
			i = 0;
		}
		else {
			i += 1;
		}
	}
	for (int k=0; k<10; k+=1){
		std::cout << arr[k] << " ";;
	}
	std::cout << "\n";
	return 0;
}
