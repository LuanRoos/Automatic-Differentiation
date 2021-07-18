#include "var.h"
#include <iostream>

Var::Var() {
	m_val_evaluated = false;
	m_der_evaluated = false;
	m_inputs[0] = 0;
	m_inputs[1] = 0;
}

Var::Var(double val) {
	m_val = val;
	m_val_evaluated = true;
	m_der_evaluated = false;
	m_inputs[0] = 0;
	m_inputs[1] = 0;
	m_type = 0;
}

void Var::setValue(double a) {
	m_val_evaluated = true;
	m_val = a;
}

void Var::resetValuesRecursive() {
	if (m_type == 0) return;
	m_val_evaluated = false;
	m_der_evaluated = false;
	for (int i = 0; i < 2; i++) {
		if (m_inputs[i] != 0) m_inputs[i]->resetValuesRecursive();
	}
}

Var* Var::apply(double (*f)(double), double(*f_)(double)) {
	Var* z = new Var;
	z->m_inputs[0] = this;
	z->m_f = f;
	z->m_f_ = f_;
	z->m_type = 1;
	return z;
}

double logis(double a) {
	return 1 / (1 + exp(-a));
}       

double logis_(double a) {
	return logis(a) * (1 - logis(a));
}   

double ReLu(double a) {
	if (a > 0) return a;
	return 0;
}

double ReLu_(double a) {
	if (a > 0) return 1;
	return 0;
}

Var* Exp(Var* x) {
	return x->apply(exp, exp);
}       
 
Var* Logis(Var* x) { 
	return x->apply(logis, logis_);
}

Var* ReLu(Var* x) {
	return x->apply(ReLu, ReLu_);
}

Var* Var::add(Var* x) {
	Var* z = new Var;
	z->m_inputs[0] = this;
	z->m_inputs[1] = x;
	z->m_type = 2;
	return z;
}

Var* Var::add(double a) {
	Var* x = new Var(a);
	return this->add(x);
}

Var* Var::multiply(Var* x) {
	Var* z = new Var;
	z->m_inputs[0] = this;
	z->m_inputs[1] = x;
	z->m_type = 3;
	return z;
}

Var* Var::multiply(double a) {
	Var* x = new Var(a);
	return this->multiply(x);
}

double Var::evaluate() {
	if (m_val_evaluated) {
		return m_val;
	}

	switch (m_type) {
		case 0:
			//todo we shouldn't ever be here.
			break;
		case 1:
			m_val = m_f(m_inputs[0]->evaluate());
			break;
		case 2:
			m_val = m_inputs[0]->evaluate() + m_inputs[1]->evaluate();
			break;
		case 3:
			m_val = m_inputs[0]->evaluate() * m_inputs[1]->evaluate();
			break;
	}
	m_val_evaluated = true;
	return m_val;
}

double Var::derivative(Var* x) {
	if (this == x) return 1;
	if (m_der_evaluated) return m_der;
	switch (m_type) {
		case 0:
			return 0;
		case 1:
			m_der = m_f_(m_inputs[0]->evaluate()) * m_inputs[0]->derivative(x);
			break;
		case 2:
			m_der =  m_inputs[0]->derivative(x) + m_inputs[1]->derivative(x);
			break;
		case 3:
			m_der = m_inputs[0]->derivative(x) * m_inputs[1]->evaluate() + m_inputs[1]->derivative(x) * m_inputs[0]->evaluate();
			break;
	}
	m_der_evaluated = true;
	return m_der;
}

void Var::printRecursive() {
	print();
	for (int i = 0; i < 2; i++) {
		if (m_inputs[i] != 0) {
			m_inputs[i]->print();
		}
	}
}

void Var::print() {
	std::cout << "My val: " << m_val;
	for (int i = 0; i < 2; i++) {
		if (m_inputs[i] != 0) {
			std::cout << " my child " << i << " val: " << m_inputs[i]->m_val << '\t';
		}
	}
	std::cout << '\n';
}
