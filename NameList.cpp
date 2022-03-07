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
	Person(const string &name, const string &surname, int year)
	{
		ChangeFirstName(year, name);
		ChangeLastName(year, surname);
		por = year;
	}
	void ChangeFirstName(int year, const string& first_name)
	{
		if (year >= por)
			f[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name)
	{
		if (year >= por)
			l[year] = last_name;
	}
	string GetFullName(int year) const
	{
		string a, b;
		a = "";
		b = "";
		if (year < por)
			return "No person";
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
	string GetFullNameWithHistory(int year) const
	{
		string a, b;
		vector<string> buff;
		vector<string> bufl;
		a = "";
		if (year < por)
				return "No person";
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
	int por;
};

int main()
{
	Person person("Polina", "Sergeeva", 1960);
	  for (int year : {1959, 1960}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }

	  person.ChangeFirstName(1965, "Appolinaria");
	  person.ChangeLastName(1967, "Ivanova");
	  for (int year : {1965, 1967}) {
	    cout << person.GetFullNameWithHistory(year) << endl;
	  }
}
