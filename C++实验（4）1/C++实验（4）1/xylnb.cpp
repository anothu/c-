#include <iostream>
#include <string>
using namespace std;
class PhoneNumber {
	string AreaCode;
	string number;
public:
	friend ostream& operator<<(ostream&, PhoneNumber&);
	friend istream& operator>>(istream&, PhoneNumber&);
};

ostream& operator<<(ostream& out, PhoneNumber& a)
{
	out <<  "("<<a.AreaCode<<")"  << a.number;
	return out;
	// TODO: �ڴ˴����� return ���
}

istream& operator>>(istream& in, PhoneNumber& a)
{
	in >> a.AreaCode >> a.number;
	return in;
	// TODO: �ڴ˴����� return ���
}

int main() {
	PhoneNumber a;
	cin >> a;
	cout << a << endl;
	system("pause");
	return 0;
	system("pause");
}