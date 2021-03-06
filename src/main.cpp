#include <iostream>
#include "var.h"

using namespace std;

int main() {
	cout << "Welcome!\nI wrote this little library to see what I could learn about automatic differentiation and (hopefully) backpropagation.\nAs a check to my sanity, I wrote this little example program which should (hopefully) show that I was at least somewhat succesful.\n";
	cout << "Consider the equations,\n\nz = (x^2)y + exp(3xy) + 2y\nx = 2t^2\ny = -t\n\nwhere we would like to calculate the derivative of z with respect to t, evaluated at a certain value of t. Help me check if I've made an error!\n";
	Var *t, *x, *y, *z;
	t = new Var;
	x = t->multiply(t)->multiply(2);
	y = t->multiply(-1);
	z = x->multiply(x)->multiply(y)->add(Exp(x->multiply(3)->multiply(y)))->add(y->multiply(2));
	cout << "At what value of t would you like to evaluate this derivative?\n";
	double val;
	cin >> val;
	t->setValue(val);

	std::cout << "Val of z: " << z->evaluate() << '\n';
	std::cout << "Derivative of z wrt t" << ": " << z->derivative(t) << '\n';
}
