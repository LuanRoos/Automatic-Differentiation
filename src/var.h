#ifndef VAR_H
#define VAR_H

class Var {
public:
	Var();
	Var(double var);
	void setValue(double a);
	void resetValuesRecursive();
	Var* apply(double (*f)(double), double (*f_)(double));
	Var* add(Var* x);
	Var* add(double a);
	Var* multiply(Var* x);
	Var* multiply(double a);
	double evaluate();
	double derivative(Var* x);
	void print();
	void printRecursive();
private:
	double m_val;
	bool m_val_evaluated;
	double m_der;
	bool m_der_evaluated;
	// 4 types:
	// 0: root; 1: unary; 2: addition; 3: multiplication
	int m_type;
	Var* m_inputs[2];
	// for case 1:
	double (*m_f)(double);
	double (*m_f_)(double);
};

double logis(double a);
double logis_(double a);
double ReLu(double a);
double ReLu_(double a);
Var* Exp(Var* x);
Var* Logis(Var* x);
Var* ReLu(Var* x);

#endif
