#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;


int main (int argc, char const *argv[]) {
	Matrix a(2, 2);
	Matrix b(2, 2);

	ifstream filea("m1.txt");
	filea >> a;

	b(0, 0) = 1;
	b(0, 1) = 1;
	b(1, 0) = 1;
	b(1, 1) = 1;

	cout << "a: " << endl << a << endl;
	cout << "b: " << endl << b << endl;

	Matrix c(2, 2);
	Matrix d(a);
	Matrix e(b);
	c = a - b;
	a -= b;

	cout << "AFTER:" << endl;
	cout << "a: " << endl << a << endl;
	cout << "b: " << endl << b << endl;
	cout << "c: " << endl << c << endl;
	cout << "d: " << endl << d << endl;
	cout << "e: " << endl << e << endl;

	Matrix x(5, 6), y(3, 4), z(a), w(a);
	ifstream filex("m2.txt");
	ifstream filey("m3.txt");

	filex >> x;
	filey >> y;

	//z = x * y;
	//x *= y;
	cout << "x: "<< endl << x << endl;
	cout << "y: "<< endl << y << endl;
	cout << "z: "<< endl << z << endl;
	cout << "w: "<< endl << w << endl;

	cout << "x == y: " << (x == y) << endl;
	cout << "x != y: " << (x != y) << endl;

	filea.close();
	filex.close();
	filey.close();

	return 0;
}
