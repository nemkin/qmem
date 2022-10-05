#include "QMem.h"
#include<map>
#include<bitset>
#include<vector>
#include<complex>


using namespace std;

class QRegister {
public:
	vector<complex<double>> numbers;

	QRegister(int size) {
		numbers.resize(size);
		for (int i = 0; i < size; ++i) {
			numbers[i] = 1;
		}
	}

	void Print() {
		for (auto i : numbers) {
			cout << i << " ";
		}
		cout << endl;
	}
};

class QOperation {

private:
	int size;
	vector<vector<complex<double>>> hadamard;

public:

	QOperation(int size) {
		hadamard.resize(size);
		for (int i = 0; i < size; ++i) {
			hadamard[i].resize(size);
			for (int j = 0; j < size; ++j) {
				hadamard[i][j] = 2;
			}
		}
	}

	QRegister Apply(QRegister target) {
		QRegister result(size);

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				result.numbers[j] += target.numbers[i] * hadamard[i][j];
			}
		}

		return result;
	}

	void Print() {
		for (auto i : hadamard) {
			for (auto j : i) {
				cout << j << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int size = 1 << 2;
	auto reg = QRegister(size);
	auto op = QOperation(size);

	auto result = op.Apply(reg);

	reg.Print();
	op.Print();
	result.Print();

	return 0;
}
