#include<thread>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<mutex>
#include<shared_mutex>
#include<locale>
#include<exception>
#include<algorithm>
using namespace std;
//класс исключения
class error:public std::exception
{
	string str;
public:
	error(const string& s) :str(s) {}
	const char* what()const override
	{
		return str.c_str();
	}

};
bool search(const string&t1, const string& t2);
bool compare_jakkar(const string& s1, const string& s2);//сравнение слов с помощью коэффицента жаккара
size_t count_word(const string& t2);//количество слов в тексте
void sort_word(const string& txt, vector<string>& ms); // возвращает список слов текста с уникальными элементами
void data_read(fstream& f1, string& text1, string& text2);//чтение данных из айла и преобразование их в нижний регистр	
double analysis(const string& text1, const string& text2);

int main()
{setlocale(LC_ALL, "Russian");
vector<string>ms_w1;
vector<string>ms_w2;
	
	fstream f1;
	string t1;
	string t2;
	try
	{
		data_read(f1, t1, t2);
	}
	catch (const exception&ex)
	{
		cout << ex.what() << endl;
	}
	sort_word(t1,ms_w1);
	sort_word(t2, ms_w2);
	size_t c =0;
	size_t a = ms_w1.size();
	size_t b = ms_w2.size();
	sort(ms_w1.begin(), ms_w1.end());
	ms_w1.erase(unique(ms_w1.begin(), ms_w1.end()), ms_w1.end());
	sort(ms_w2.begin(), ms_w2.end());
	ms_w2.erase(unique(ms_w2.begin(), ms_w2.end()), ms_w2.end());
	if (ms_w1.size() >= ms_w2.size())
	{
		for (size_t i = 0; i < ms_w2.size();i++)
		{
			for (size_t j = 0; j < ms_w1.size(); j++)
			{
				if (compare_jakkar(ms_w2[i], ms_w1[j]))
					c++;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < ms_w1.size(); i++)
		{
			for (size_t j = 0; j < ms_w2.size(); j++)
			{
				if (compare_jakkar(ms_w1[i], ms_w2[j]))
					c++;
			}
		}
	}
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << a + b - c << endl;
	double Kj = static_cast<double>(c) / (a + b - c);

	cout << 2*Kj/(1+Kj) << endl;
	system("pause");
}
bool compare_jakkar(const string& s1, const string& s2)
{
	size_t c = 0;
	if (s1[0] == s2[0])
	{
		c++;
		for (size_t i = 1; i < (s1.size()>=s2.size()?s2.size():s1.size()); i++)
		{
			
			if (s1[i] == s2[i])
				c++;
		}
		double Kj=static_cast<double>(c) / (s1.size() + s2.size() - c);
		double rez = 2 * Kj / (1 + Kj);
		if (rez >= 0.5)
		{
			return true;
		}
		else
		{
			
			return false;
		}
	}
	else return false;
}
size_t count_word(const string& t2)
{
	bool flag = true;
	size_t c_t2 = 0;
	for (size_t i = 0; i < t2.size(); i++)
	{

		if ('а' <= t2[i] && t2[i] <= 'я')
		{
			if (flag)
			{
				c_t2++;
				flag = false;
			}
		}
		else
		{
			flag = true;
			continue;
		}
	}
	return c_t2;
}
void sort_word(const string& txt, vector<string>& ms)
{
	bool flag = true;
	bool flag_2 = true;
	int j = 0, k = 0;
	for (size_t i = 0; i < txt.size(); i++)
	{
		if (('а' <= txt[i] && txt[i] <= 'я') || txt[i] == '-')
		{
			if (flag)
			{
				
				flag = false;
				j = i;
			}
			k = i;
			flag_2 = true;
		}
		else
		{
			if (!flag_2)
				continue;
			if ('а' <= txt[j] && txt[j] <= 'я')
			{
				flag_2 = false;
				ms.push_back(string(txt.begin() + j, txt.begin() + k + 1));
				flag = true;
				continue;
			}
		}
	}
} 
void data_read(fstream& f1, string& text1, string& text2)
{
	f1.open("text.txt");
	if (!f1.is_open())
	{
		throw error(" Error read text1 in data_read()");
	}
	getline(f1, text1);
	f1.close();
	f1.open("text_ot.txt");
	if (!f1.is_open())
	{
		throw error(" Error read text1 in data_read()");
	}
	getline(f1, text2);
	f1.close();
	for (size_t i = 0; i < text1.size(); i++)
		text1[i] = tolower(text1[i]);
	for (size_t i = 0; i < text2.size(); i++)
		text2[i] = tolower(text2[i]);
}
double analysis(const string& text1, const string& text2)
{
	double G = 34;

	return G;
}