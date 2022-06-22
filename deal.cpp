#include"iostream"
#include"regex"
#include"cstring"
#include <unordered_map>
using namespace std;
static regex reg("<.*>.*</.*>");
const int rnum = 0;

class Operator {
	private: 
		Operator* left;
		Operator* right;
 	public:
 		Operator();
 		Operator(Operator left, Operator right);
 		int getResult();
 		Operator getLeft();
 		Operator getRight();
};

Operator::Operator(Operator left, Operator right) {
	this->left = &left;
	this->right = &right;
}

Operator::Operator() {
};

int Operator::getResult() {
	return 0;
} 

Operator Operator::getLeft() {
	return *(this->left); 
}

Operator Operator::getRight() {
	return *(this->right); 
}

class Num : public Operator {
	private:
		int value;
	public :
	 	Num(int value);
	 	int getResult();
};  

Num::Num(int value) : Operator () {
	//super(null, null);
	this->value = value;
}

int Num::getResult() {
	return this->value;
}

class Add : public Operator {
	public:
		Add(Operator left, Operator right) ;
		int getResult();
};

Add::Add(Operator left, Operator right) : Operator (left, right){
	//Operator(left, right);
}

int Add::getResult() {
	Operator o1 = (Operator::getLeft());
	Operator o2 = (Operator::getRight());
	Num* n1 = (Num*) &o1;
	Num* n2 = (Num*) &o2;
	return (*n1).getResult() + (*n2).getResult();
}

class Sub : public Operator {
	public:
		Sub(Operator left, Operator right);
		int getResult();
}; 

Sub::Sub(Operator left, Operator right) : Operator (left, right){
	//Operator(left, right);
}

int Sub::getResult() {
	Operator o1 = (Operator::getLeft());
	Operator o2 = (Operator::getRight());
	Num* n1 = (Num*) &o1;
	Num* n2 = (Num*) &o2;
	return (*n1).getResult() - (*n2).getResult();
}

class Mul : public Operator {
	public:
		Mul(Operator left, Operator right);
		int getResult();
};

Mul::Mul(Operator left, Operator right) : Operator (left, right){
	//Operator(left, right);
}

int Mul::getResult() {
	Operator o1 = (Operator::getLeft());
	Operator o2 = (Operator::getRight());
	Num* n1 = (Num*) &o1;
	Num* n2 = (Num*) &o2;
	return (*n1).getResult() * (*n2).getResult();	
}

class Parser{
	private:
		unordered_map<string, int> Hashmap;
		int findAddOrSub(string e);
		int findMul(string e);
	public:
		Parser(unordered_map<string, int> h);
		Operator parse(string s);
		bool findMin(string e);	
};

Operator Parser::parse(string expression) {
	int position = findAddOrSub(expression);
	if (position != -1) {
		if (expression.at(position) == '+') {
			cout << expression.substr(0, position) << endl;
			cout << expression.substr(position + 1) << endl;
			return Add(parse(expression.substr(0, position)), 
			parse(expression.substr(position + 1))); 
		} else {
			return Sub(parse(expression.substr(0, position)),
			parse(expression.substr(position + 1)));
		}
	} else {
		position = findMul(expression);
		if (position != -1) {
			return Mul(parse(expression.substr(0, position)), 
			parse(expression.substr(position + 1)));
		} else {
			if (expression.length() != 0) {
				smatch matcher;
				regex_search(expression, matcher, reg);
				if (matcher.size() != 0) {
					if (findMin(matcher.str(0))) {
						return Num(Hashmap[matcher.str(0)]);
					} else {
						char c[200];
						int k; 
						for (k = 0; k < matcher.str(0).size(); k++) {
							c[k] = matcher.str(0).at(k);
						} 
						c[k] = '\0';
						printf("%d\n", atoi((const char*)c));
						return Num(atoi((const char*)c)); 
					}
				} else {
					return Num(0);
				}
			} else {
				return Num(0); 
			}
		}
	}
		
}

Parser::Parser(unordered_map<string, int> h) {
	this->Hashmap = h;
}

int Parser::findAddOrSub(string s) {
	int position = -1;
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) == '+' || s.at(i) == '-') {
			position = i;
		} 
	}
	return position;
}

int Parser::findMul(string s) {
	int position = -1;
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) == '*') {
			position = i;
		}
	}
	return position;
}

bool Parser::findMin(string e) {
	for (int i = 0; i < e.length(); i++) {
		if (e.at(i) >= 'a' && e.at(i) <= 'z') {
			return true;
		} else if (e.at(i) >= 'A' && e.at(i) <= 'Z') {
			return true;
		}
	}
	return false;
}

int main() {
	string expression;
	cin >> expression ;
	unordered_map<string, int> map ;
	Parser parser = Parser(map);
	Operator o = parser.parse(expression);
	Num* num = (Num*)(&o); 
	cout << (*num).getResult() << endl;
} 