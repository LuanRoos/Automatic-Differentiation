#include <iostream>
#include "var.h"

using namespace std;

int main() {
	cout << "Welcome!\nI wrote this little library to see what I could learn about automatic differentiation and (hopefully) backpropagation.\nAs a check to my sanity, I wrote this little example program which should (hopefully) show that I was at least somewhat succesful.\n";
	cout << "Consider the equations,\n\nz = (x^2)y + exp(3xy) + 2t\nx = 2t^2\ny = -t\n\nwhere we would like to calculate the partial derivative of z with respect to the variables x, y or t, evaluated at a certain value of t. Help me check if I've made an error!\n";
	Var *t, *x, *y, *z;
	t = new Var;
	x = t->multiply(t)->multiply(2);
	y = t->multiply(-1);
	z = x->multiply(x)->multiply(y)->add(Exp(x->multiply(3)->multiply(y)))->add(t->multiply(2));
	Var* choice;
	char c;
	bool exit = false;
	while (!exit) {
		cout << "With respect to which variable would you like to differentiate to? (t, x, y, z)\n";
		cin >> c;
		exit = true;
		switch (c) {
			case 't':
				choice = t;
				break;
			case 'x':
				choice = x;
				break;
			case 'y':
				choice = y;
				break;
			case 'z':
				choice = z;
				break;
			default:
				cout << "Incorrect option. Type only t, x, y or z.\n";
				exit = false;
		}
	}
	cout << "What value would you like to assign t?\n";
	double val;
	cin >> val;
	t->setValue(val);

	std::cout << "Val of z: " << z->evaluate() << '\n';
	std::cout << "Derivative of z wrt " << c << ": " << z->derivative(choice) << '\n';
}
