#include<iostream>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<fstream>
#define SIZE 100
using namespace std;

bool _Open(fstream& _filen, string name) {
	_filen.open(name, ios::in);
	if (!_filen.is_open())
		return false;
	else
		return true;
}

void _ticktherow(int A[][SIZE], int* _Row, int _sizeofRow, int B[][SIZE], int* _Column, int sizeofColumn) {
	int temp1, temp2, k = 1, j = 0;
	for (int i = 0; i < (_sizeofRow / 2); i++, k = k + 2, j = j + 2) {
		temp1 = _Row[j], temp2 = _Row[k];
		A[temp1 - 1][temp2 - 1] = 1;
	}
	for (int i = 0, k = 1, j = 0; i < (sizeofColumn / 2); i++, k = k + 2, j = j + 2) {
		temp1 = _Column[j], temp2 = _Column[k];
		B[temp2 - 1][temp1 - 1] = 1;
	}
}

void _search(int row[][SIZE], int column[][SIZE], int Size, ofstream& _file) {
	int _i = 0, flag = 0, x = 1, y = 0, counter = 0, counter1 = 0;
   	while (x < Size) {
		while (_i < Size - x) {
			for (int i = 0; i < Size - x; i++) {
				for (int j = 0; j < 1; j++) {
 					for (int k = 0; k < x; k++) {
						if (row[j + y][k + i] == 1 && column[y + k][i + j] == 1) {
							flag = 1;
						}
						else {
							flag = 0;
							break;
						}
					}
					if (flag == 1) {
						for (int k = 0; k < x; k++) {
							if (row[x + y][k + i] == 1 && column[y + k][x + i] == 1) {
								flag = 1;
							}
							else {
								flag = 0;
								break;
							}
						}
					}
				}
				if (flag == 1) {
					counter++, counter1++;
				}
				flag = 0;
			}
			_i++, y++;
		}
		if (counter != 0) {
			cout << counter << " Square (S) Of Size " << x << endl;
			_file << counter << " Square (S) Of Size " << x << endl;
		}
		counter = 0, _i = 0, y = 0, x++;
	}
	if (counter1 == 0) {
		cout << "No Square Can be Found ...!" << endl;
		_file << "No Square Can be Found ...!" << endl;
	}
}

void main(void) {
	fstream _new_f;
	ofstream _out("Output.txt", ios::out, ios::trunc);
	int counter = 0, _i = 0, _j = 0, _size, i = 0, _Size, _c = 0, a = 0;
	int _H1[SIZE], _v1[SIZE], A[SIZE][SIZE], B[SIZE][SIZE], _S[SIZE];
	char _array[250]{ 0 }, add{ '0' };
	int _st = _Open(_new_f, "Input.txt");
	if (_st == true) {
		cout << "The File Opened Succesfully .." << endl;
	}
	else {
		cout << "Error..!" << endl; exit(0);
	}
	
	for (i = 0; !_new_f.eof(); i++) {//taking Size and number of lines...
		if (i == 2) break;
		_new_f >> _S[i];
	}
	_size = _S[0], _Size = _S[1], _new_f >> add;
	while (!_new_f.eof()) { //Getting all values inside the file....
		_array[_i] = add, _new_f >> add;
		_i++, counter++;
	}
	_new_f.close();
	_i = 0, _j = 0, i = 0;
	while (i < counter) {//Getting the Value which is Started With 
		if (toupper(_array[i]) == 'V') {
			for (int k = i + 1; k < i + 3; k++) {
				_v1[a] = _array[k] - '0', a++;
			}
			i = i + 2;
		}
		else if (toupper(_array[i]) == 'H') {
			for (int k = i + 1; k < i + 3; k++) {
				_H1[_j] = _array[k] - '0', _j++;
			}
			i = i + 2;
		}
		else { break; }
		i++;
	}

	memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
	cout << endl, _out << endl;
	cout << "Problem #1" << endl << endl, _out << "Problem #1" << endl << endl;
	_ticktherow(A, _H1, (_j), B, _v1, (a)), _search(A, B, _size, _out);
	_c = i;
	if (_c < counter) {
		for (i = 0; i < counter && _c < counter; i++, _c++) {
			if (i == 2) break;
			_S[i] = _array[_c] - '0';
		}
		_Size = _S[1], _size = _S[0], _j = 0, a = 0;
		memset(_H1, 0, sizeof(_H1)), memset(_v1, 0, sizeof(_v1));
		for (int i = _c; i < counter; i++, _c++) {//Getting the Value which is Started With 'H'
			if (toupper(_array[i]) == 'V')
				break;
			else if (toupper(_array[i]) != 'H') {
				_H1[_j] = _array[i] - '0';
				_j++;
			}
		}
		for (a = 0; _c < counter; ++_c) {//Getting the Value which is Started With 'V'...
			if (toupper(_array[_c]) != 'V') {
				_v1[a] = _array[_c] - '0';
				a++;
			}
		}
		cout << endl, _out << endl;
		cout << "*****************************" << endl << endl;
		_out << "*****************************" << endl << endl;
		cout << "Problem #2" << endl << endl;
		_out << "Problem #2" << endl << endl;
		memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
		_ticktherow(A, _H1, (_j), B, _v1, (a)), _search(A, B, _size, _out);
	}
	_out.close();
	cout << endl << endl;
	system("pause");
}
