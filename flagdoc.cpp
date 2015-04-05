#include "flagdoc.h"
#include <algorithm>		//std::max
#include <iostream>       // std::cout

using namespace std;

const size_t FFlagDoc::GetMaxLength()
{
	size_t&& Length = 0;
	for (auto It : ObjectFlags)
	{
		Length = std::max(Length, It.second[0].length());
	}
	return Length + 1;
}

const string FFlagDoc::Indent(string& Name, string& Desc)
{
	string Rslt;
	size_t RsltSize = IndentLength + Desc.length() + (Desc.length() / DescWidth) * (IndentLength + 1) + 1;
	Rslt.reserve(RsltSize);
	Rslt += Name;
	Rslt += string(IndentLength - Name.length(), ' ');

	for (size_t i = 0; i <= (Desc.length() / DescWidth); ++i)
	{
		if (i != 0)
		{
			Rslt += string(IndentLength, ' ');
		}
		Rslt += Desc.substr(i * DescWidth, DescWidth);
		Rslt += '\n';
	}
	if (Desc.length() >= DescWidth)
	{
		Rslt += '\n';
	}
	return Rslt;
}

void FFlagDoc::operator()(size_t Flag) const
{
	for (auto Doc : ObjectFlags)
	{
		auto Match = Doc.first;
		if (Match & Flag)
		{
			auto Name = Doc.second[0];
			auto Desc = Doc.second[1];
			cout << Indent(Name, Desc);
		}
	}
}

int main()
{
	while (1)
	{
		cin.clear();
		cout << "Enter UObject flag:";
		size_t Flag;
		cin >> Flag;
		FFlagDoc()(Flag);

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n";
	}
	return 0;
}