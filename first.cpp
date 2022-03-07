#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cmath>
using namespace std;

class Person
{
public:
	void ChangeFirstName(int year, const string& first_name)
	{
		f[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name)
	{
		l[year] = last_name;
	}
	string GetFullName(int year)
	{
		a = "";
		b = "";
		for (auto t : f)
		{
			if (t.first <= year && t.second.size() != 0) a = t.second;
		}
		for (auto t : l)
		{
			if (t.first <= year && t.second.size() != 0) b = t.second;
		}
		if (a.size() == 0 && b.size() == 0)
			return "Incognito";
		if (a.size() == 0)
			return b + " with unknown first name";
		if (b.size() == 0)
			return a + " with unknown last name";
		return a + " " + b;
	}
	string GetFullNameWithHistory(int year)
	{
		a = "";
		for (auto t : f)
		{
			if (t.first <= year && t.second.size() != 0 && t.second != a)
			{
				buff.push_back(t.second);
				a = t.second;
			}
		}
		a = "";
		for (auto t : l)
		{
			if (t.first <= year && t.second.size() != 0 && t.second != a)
			{
				bufl.push_back(t.second);
				a = t.second;
			}
		}
		a = "";
		int tmp = 0;
		for (int i = buff.size() - 1; i >= 0; i--)
		{
			tmp++;
			if (tmp == 2)
				a += " (";
			if (tmp > 2)
				a += ", ";
			a += buff[i];
		}
		if (tmp > 1)
			a += ")";
		tmp = 0;
		b = "";
		for (int i = bufl.size() - 1; i >= 0; i--)
		{
			tmp++;
			if (tmp == 2)
				b += " (";
			if (tmp > 2)
				b += ", ";
			b += bufl[i];
		}
		if (tmp > 1)
			b += ")";
		buff.clear();
		bufl.clear();
		if (a.size() == 0 && b.size() == 0)
			return "Incognito";
		if (a.size() == 0)
			return b + " with unknown first name";
		if (b.size() == 0)
			return a + " with unknown last name";
		return a + " " + b;
	}
private:
	map<int, string> f;
	map<int, string> l;
	vector<string> buff;
	vector<string> bufl;
	string a, b;
};

int main()
{
	vector<int> a = {5, 4, 3, 2, 1};
	for (auto s : a)
	{
		cout << s << endl;
	}
	int i, j, tmp;
	i = 0;
	for (i = 1; i < 5; i++)
	{
		for (j = 0; j > 5-i; j++)
		{
			if (a[j] < a[j+1])
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
		}
	}

	for (auto s : a)
	{
		cout << s << endl;
	}
	Person person;
	person.ChangeFirstName(1965, "Polina");
	  person.ChangeLastName(1967, "Sergeeva");
	  for (int year : {1900, 1965, 1990}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeFirstName(1970, "Appolinaria");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeLastName(1968, "Volkova");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeFirstName(1990, "Polina");
	  person.ChangeLastName(1990, "Volkova-Sergeeva");
	  cout << person.GetFullNameWithHistory(1990) << endl;

	  person.ChangeFirstName(1966, "Pauline");
	  cout << person.GetFullNameWithHistory(1966) << endl;

	  person.ChangeLastName(1960, "Sergeeva");
	  for (int year : {1960, 1967}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeLastName(1961, "Ivanova");
	  cout << person.GetFullNameWithHistory(1967) << endl;
	return 0;
}
