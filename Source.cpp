#define AMOUNT_OF_PARAM 3
#define MAX_POLOK 0
#define CREATE_MISSING 1
#define IF_NEW_SEARCH 2
#define VERSION "0.43-new search+"
#define _CRT_SECURE_NO_WARNINGS
#define ACCURACY_OF_SEARCH 40

#include <iostream>
#include <fstream>
//#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <ctime>


using namespace std;

int DIF_AUTORS;

struct book
{
	string autor, name;
	unsigned int place;
};
vector<short int> param(AMOUNT_OF_PARAM);

//vector<int> init(map<string, string>&);
vector<string> read(const string & adress);
string I_S(int I);
void rvr(string & T);
int check_autor(const string & T);
bool compare_book(const book & A, const book & B);
void find_polk(vector<book> & out, int polka, const vector<book> & list);
void findby_autor(vector<book> & out, const vector<book> & list, string autor);
void findby_name(vector<book> & out, const vector<book> & list, string autor);
unsigned int diff_autors(const vector<book> & list);
bool exist_autor(const vector<book> & list, string autor);
void write(const vector<book> & out, const string & adress, const vector<short int> & extra);
void rebuild_katalog(vector<book> & list);
int get_param();
int find_param(string T);
void create_param();
int S_I(string S);
int compare_string(const string & A, const string & B);

bool operator==(const book & a, const book & b) { return a.autor == b.autor && a.name == b.name && a.place == b.place; }

bool operator!=(const book & a, const book & b) { return !(a == b); }

bool exist_autor(const vector<book> & list, string autor)
{
	for (int i = 0; i < list.size(); i++)
		if (list[i].autor == autor)
			return true;

	return false;
}

unsigned int diff_autors(const vector<book> & list)
{
	//map<string, int> famous;
	vector<book> was;
	for (int i = 0; i < list.size(); i++)
	{
		//famous[list[i].autor]++;
		if (exist_autor(was,list[i].autor))
		{
			
		}
		else
		{
			was.push_back(list[i]);
		}
	}
	return was.size();
}

void findby_autor(vector<book> & out, const vector<book> & list, string autor)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (autor.size() < list[i].autor.size())
		{
			for (int j = 0; j < list[i].autor.size() - autor.size(); j++)
			{
				if (autor == list[i].autor.substr(j, autor.size()))
					out.push_back(list[i]);
			}
		}
		else
		{
			for (int j = 0; j < autor.size()- list[i].autor.size(); j++)
			{
				if (autor.substr(j, list[i].autor.size()) == list[i].autor)
					out.push_back(list[i]);
			}
		}
	}
}

void findby_autor(vector<book> & out, const vector<book> & list, string autor, vector<int> & index)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (autor.size() < list[i].autor.size())
		{
			for (int j = 0; j < list[i].autor.size() - autor.size(); j++)
			{
				if (autor == list[i].autor.substr(j, autor.size())) 
				{
					out.push_back(list[i]);
					index.push_back(i);
				}
			}
		}
		else
		{
			for (int j = 0; j < autor.size() - list[i].autor.size(); j++)
			{
				if (autor.substr(j, list[i].autor.size()) == list[i].autor)
				{
					out.push_back(list[i]);
					index.push_back(i);
				}
			}
		}
	}
}

void findby_autor_new(vector<book> & out, const vector<book> & list, string autor, vector<int> & index)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (autor.size() < list[i].autor.size())
		{
			if (compare_string(autor, list[i].autor) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
				index.push_back(i);
			}
		}
		else
		{
			if (compare_string(list[i].autor, autor) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
				index.push_back(i);
			}
		}
	}
}

void findby_autor_new(vector<book> & out, const vector<book> & list, string autor)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (autor.size() < list[i].autor.size())
		{
			if (compare_string(autor, list[i].autor) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
			}
			else { cout << compare_string(autor, list[i].autor) << endl; }
		}
		else
		{
			if (compare_string(list[i].autor, autor) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
			}
			else{ cout << compare_string(autor, list[i].autor) << endl;}
		}
	}
}

void findby_name(vector<book> & out, const vector<book> & list, string name)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (name.size() < list[i].name.size())
		{
			for (int j = 0; j < list[i].name.size() - name.size(); j++)
			{
				if (name == list[i].name.substr(j, name.size()))
					out.push_back(list[i]);
			}
		}
		else
		{
			for (int j = 0; j < name.size() - list[i].name.size(); j++)
			{
				if (name.substr(j, list[i].name.size()) == list[i].name)
					out.push_back(list[i]);
			}
		}
	}
}

void findby_name(vector<book> & out, const vector<book> & list, string name, vector<int> & index)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (name.size() < list[i].name.size())
		{
			for (int j = 0; j < list[i].name.size() - name.size(); j++)
			{
				if (name == list[i].name.substr(j, name.size())) 
				{
					out.push_back(list[i]);
					index.push_back(i);
				}
			}
		}
		else
		{
			for (int j = 0; j < name.size() - list[i].name.size(); j++)
			{
				if (name.substr(j, list[i].name.size()) == list[i].name) 
				{
					out.push_back(list[i]);
					index.push_back(i);
				}
			}
		}
	}
}

int compare_string(const string & sm, const string & big)
{
	int pos = 0;
	for (int i = 0; i < sm.size(); i++)
	{
		if (sm[i] == big[i] || sm[i] == big[i]+32 || sm[i] == big[i]-32) pos++;
	}
	return 100 * (pos / sm.size());
}

void findby_name_new(vector<book> & out, const vector<book> & list, string name, vector<int> & index)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (name.size() < list[i].name.size())
		{
			if (compare_string(name, list[i].name) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
				index.push_back(i);
			}
		}
		else
		{
			if (compare_string(list[i].name, name) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
				index.push_back(i);
			}
		}
	}
}

void findby_name_new(vector<book> & out, const vector<book> & list, string name)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (name.size() < list[i].name.size())
		{
			if (compare_string(name, list[i].name) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
			}
		}
		else
		{
			if (compare_string(list[i].name, name) >= ACCURACY_OF_SEARCH)
			{
				out.push_back(list[i]);
			}
		}
	}
}

void find_polk(vector<book> & out, int polka, const vector<book> & list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].place == polka)
			out.push_back(list[i]);
	}
}

void find_polk(vector<book> & out, int polka, const vector<book> & list, vector<int> & index)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].place == polka) 
		{
			out.push_back(list[i]);
			index.push_back(i);
		}
	}
}

int check_autor(const string & T)
{
	//cout << "checking " << T << endl;
	for (int i = 0; i < T.size() - 2; i++)
	{
		if (T[i] == ' ' && (T[i + 1] == '-' |T[i+1] == '�') && T[i + 2] == ' ')
			return i + 1;
	}
	return -1;
}

void rvr(string & T)
{
	for (int i = 0; i < T.size() / 2; i++)
		swap(T[i], T[T.size() - 1 - i]);
}

string I_S(int I)
{
	string res = "";
	while (I > 0)
	{
		res += char(I%10 + 48);
		I /= 10;
	}
	rvr(res);
	return res;
}

vector<string> read(const string & adress)
{
	vector<string> res;
	res.push_back("");
	string t;
	ifstream IF(adress);
	if (IF.fail())
	{
		res[0] = "ERROR: file do not exist";
		IF.close();
		return res;
	}
	while (!IF.eof()) {
		getline(IF, t);
		if (t.substr(0, 4) == "<LI>") {
			t = t.substr(4, t.size());
			res.push_back(t);
		}
	}
	IF.close();
	return res;
}

int end_LI(const string & T)
{
	//cout << "checking " << T << endl;
	for (int i = T.size(); i >= 5; i -= 1)
	{
		if (T.substr(i - 5, 5) == "</LI>")
		{
			//cout << "returned " << i - 5 << endl;
			return i - 5;
		}
	}
	return T.size() - 1;
}

bool compare_book(const book & A,const book & B)
{
	return A.autor<B.autor || (A.autor == B.autor && A.name<B.name);
}

bool create_polk(string I)
{
	ofstream OF(string("html\\Polka" + I + ".html"));
	OF << "<HTML>" << endl << "<HEAD>" << endl << "<Title> ����� " << I << "</Title>" << endl << "</HEAD>" << endl << "<Body>" << endl << "<div align = left> <a href = \"Biblio.html\">�� �������</a> <a href = \"Biblio_big.html\">������� �������</a></div>" << endl << "<H1 ALIGN=\"center\">������ ���</H1>" << endl << "<OL TYPE=\"1\" START=\"1\">" << endl << "<H1 ALIGN=\"center\">������ ���</H1>" << endl << "</Body>" << endl << "</HTML>";
	OF.close();
	return true;
}

vector<int> init(vector<book> & list)
{
	list.clear();
	vector<int> errors;
	string T, ch_i;
	vector<string> page;
	book temp_book;
	for (int i = 1; i <= param[MAX_POLOK]; i++)
	{
		ch_i = I_S(i);
		page = read("html\\Polka" + ch_i + ".html");
		if (page[0] == "ERROR: file do not exist")
		{
			if(param[CREATE_MISSING] == 0)	cout << string("���� \"Polka" + ch_i + ".html\" �� ������") << endl;
			else
			{
				if(create_polk(ch_i)) cout << string("���� \"Polka" + ch_i + ".html\" ������") << endl;
				else cout << string("�� ������� ������� ���� \"Polka" + ch_i + ".html\"") << endl;
			}
		}
		else
		{
			if (page.size() == 1) errors.push_back(i);
			for (int j = 1; j < page.size(); j++)
			{
				T = page[j];
				int autor_place = check_autor(T);

				if (autor_place != -1)
				{
					temp_book.autor = T.substr(0, autor_place);
					temp_book.name = T.substr(autor_place + 1, -1 - autor_place + end_LI(T));
					temp_book.place = i;
				}
				else
				{
					temp_book.autor = "����� ����������";
					temp_book.name = T.substr(0, end_LI(T));
					temp_book.place = i;
				}
				list.push_back(temp_book);
			}
		}
	}
	cout << '.';
	sort(list.begin(), list.end(), compare_book);
	cout << '.';
	DIF_AUTORS = diff_autors(list);
	cout << '.' << endl;
	return errors;
}

string I_from_polkadress(const string & adress)
{
	string res;
	for (int i = 10; adress[i] != '.'; i++)
	{
		res.push_back(adress[i]);
	}
	return res;
}

void write(const vector<book> & out, const string & adress, const vector<short int> & extra)
{
	vector<string> page;
	ifstream IFF(adress);
	if (IFF.fail()) 
	{
		IFF.close();
		cout << "����� � ������� " << I_from_polkadress(adress) << " ���" << endl;
		create_polk(I_from_polkadress(adress));
		cout << "����� �������!" << endl;
	}
	else IFF.close();
	ifstream IF(adress);
	string str, ALRM_str;
	ALRM_str = "<OL TYPE=\"1\" START=\"1\">";
	while (!IF.eof() && str != ALRM_str)
	{
		getline(IF, str);
		page.push_back(str);
	}
	for (int i = 0; i < out.size(); i++)
	{
		if (extra[i] == 1)
		{
			if (out[i].autor != "-")	page.push_back("<LI>"  + out[i].autor + " - " + out[i].name + "</LI>");
			else page.push_back("<LI>" + out[i].name + "</LI>");
		}
	}
	ALRM_str = "<H1 ALIGN=\"center\">������ ���</H1>";
	while (!IF.eof() && str != ALRM_str)
	{
		getline(IF, str);
		page.push_back(str);
	}
	for (int i = 0; i < out.size(); i++)
	{
		if (extra[i] == 2)
		{
			if (out[i].autor != "-") page.push_back("<LI>" + out[i].autor + " - " + out[i].name + "</LI>");
			else page.push_back("<LI>" + out[i].name + "</LI>");
		}
	}
	while (!IF.eof())
	{
		getline(IF, str);
		page.push_back(str);
	}
	IF.close();
	ofstream OF(adress, ios_base::trunc | ios_base::out);
	for (int i = 0; i < page.size(); i++) OF << page[i] << endl;
}

void rebuild_katalog(vector<book> & list)
{
	ofstream OF("html\\Katalog.html", ios_base::trunc | ios_base::out);
	OF << "<HTML>" << endl << "<HEAD>" << endl << "<TITLE></TITLE>" << endl << "</HEAD>" << endl << "<BODY>" << endl << "<div align = left><a href = \"Biblio.html\">�� �������</a> <a href = \"Biblio_big.html\">������� �������</a></div>" << endl << "<OL TYPE=\"1\" START=\"1\">" << endl;
	for (int i = 0; i < list.size(); i++)
	{
		OF << "<LI>" << list[i].autor << " - " << list[i].name << "</LI>" << endl;
	}
	OF << "</BODY>" << endl << "</HTML>";
	OF.close();
}

int get_param()
{
	ifstream IF("options.txt");
	if (IF.fail()) return 1;
	string str, I_str;
	int i;
	for (i = 0; i < AMOUNT_OF_PARAM && !IF.eof(); i++)
	{
		getline(IF, str);
		I_str = str.substr(find_param(str) + 2, str.size() - find_param(str)-2);
		param[i] = S_I(I_str);
	}
	if (i < AMOUNT_OF_PARAM) return 2;
	return 0;
}

int find_param(string T)
{
	for (int i = T.size() - 1; i >= 0; i--)
	{
		if (T[i] == ':') return i;
	}
	return -1;
}

string create_adress(int I)
{
	string ch_i = I_S(I);
	return "html\\Polka" + ch_i + ".html";
}

string create_adress(string I)
{
	return "html\\Polka" + I + ".html";
}

int get_max_polok() //�������
{
	string adress;
	for (int i = 1; i < 10000000; i++)
	{
		ifstream IF(create_adress(i));
		if (IF.fail())
		{
			IF.close();
			return i-1;
		}
		IF.close();
	}
	return 9999999;
}

bool if_int(string S)
{
	for (int i = 0; i < S.size(); i++) if (S[i] < 48 || S[i] > 57) return 0;
	return 1;
}

void create_param()
{
	cout << "���� �� ������, ����� �������� ��� ���������� �������������, �� ������� \" - \" (��� �������)" << endl << "������� ����� � ����������?" << endl;
	string t;
	cin >> t;
	while ((S_I(t) > 9999999 || S_I(t) < 0 || !if_int(t)) && t != "-") 
	{
		cout << "������� ����� ������ 10000000" << endl;
		cin >> t;
	}
	if (t == "-")
	{
		param[MAX_POLOK] = get_max_polok();
		cout << "����������� �������� " << param[MAX_POLOK] << endl;
	}
	else param[MAX_POLOK] = S_I(t);
	
	cout << "��������� ������ �����, ���� ����� ����� ���? (������� �� ��� ���)" << endl;
	string yes;
	cin >> yes;
	while (yes != "��" && yes != "��" && yes != "���" && yes != "���" && yes != "-")
	{
		cin >> yes;
	}
	if (yes == "��" || yes == "��" || yes == "-")	param[CREATE_MISSING] = 1;
	else param[CREATE_MISSING] = 0;

	cout << "������������ ����� �������� �����? (������� �� ��� ���)" << endl;
	cin >> yes;
	while (yes != "��" && yes != "��" && yes != "���" && yes != "���" && yes != "-")
	{
		cin >> yes;
	}
	if (yes == "��" || yes == "��" || yes == "-")	param[IF_NEW_SEARCH] = 1;
	else param[IF_NEW_SEARCH] = 0;

	cout << "��������� ���������" << endl;
	ofstream OF("options.txt", ios_base::trunc | ios_base::out);
	OF << "Amount: " << param[0] << endl << "Create missing: " << param[1] << endl << "Use new search: " << param[IF_NEW_SEARCH];
	OF.close();
}

int S_I(string S)
{
	rvr(S);
	int res = 0;
	for (int i = 0; i < S.size(); i++)	res += (S[i]-48) * pow(10, i);
	return res;
}

int cin_index()
{
	string IND;
	cin >> IND;
	while (!if_int(IND) || S_I(IND) >= 10000000 || S_I(IND) < 1)
	{
		cout << "������� ����� � ��������� �� 1 �� 9999999 " << endl;
		cin >> IND;
	}
	return S_I(IND);
}

bool RASRABOTKA()
{
	cout << "��� ������� ��� � ���������� � ����� �� �������� / �������� �� ��������� / �������� ������." << endl << "������� 'Y', ���� �������, ��� ������ ����������" << endl;
	char a;
	cin >> a;
	if (a == 'Y') return true;
	else return false;
}

short int check_ending(int I)
{
	short int l = I % 10;
	I /= 10;
	short int pl = I % 10;
	if (pl == 1) return 5;
	else
	{
		if (l == 1) return 1;
		if (l >= 2 && l <= 4) return 2;
		if (l == 0 || (l >= 5 && l <= 9)) return 5;
	}

}

short int check_ending(string I)
{
	char l = I[I.size() - 1], pl = '0';
	if (I.size() > 1) pl = I[I.size() - 2];
	if (pl == 49) return 5;
	else
	{
		if (l == 49) return 1;
		if (l >= 50 && l <= 52) return 2;
		if (l == 48 || (l >= 53 && l <= 57)) return 5;
	}
}

vector<book> search(const vector<book> & list)
{
	cout << "����� �� ������, �������� ��� �� �����? (������� '�����' ��� '��������' ��� '��')" << endl;
	string I;
	cin >> I;
	while (I != "�����" && I != "��������" && I != "��" && I != "�����" && I != "��������" && I != "��" && I != "���" && I != "���")
	{
		if (I == "�����" || I == "�����") 
		{
			vector<book> ERR;
			return ERR;
		}
		cin >> I;
	}
	if (I == "�����" || I == "�����")
	{
		cout << "������� ������" << endl;
		string aut;
		getline(cin, aut);
		getline(cin, aut);
		vector<book> theautor;
		if(param[IF_NEW_SEARCH] == 1) findby_autor_new(theautor, list, aut);
		else findby_autor(theautor, list, aut);
		return theautor;
	}
	if (I == "��������" || I == "��������")
	{
		cout << "������� ��������" << endl;
		string aut;
		getline(cin, aut);
		getline(cin, aut);
		vector<book> thename;
		if (param[IF_NEW_SEARCH] == 1) findby_name_new(thename, list, aut);
		else findby_name(thename, list, aut);
		return thename;
	}
	if (I == "��" || I == "��" || I == "���" || I == "���")
	{
		cout << "������� �������� ������" << endl;
		string key;
		getline(cin, key);
		getline(cin, key);
		vector<book> all;
		if (param[IF_NEW_SEARCH] == 1)
		{
			findby_autor_new(all, list, key);
			findby_name_new(all, list, key);
		}
		else 
		{ 
			findby_autor(all, list, key);
			findby_name(all, list, key);
		}
		return all;
	}
}

vector<book> search(const vector<book> & list, vector<int> & index)
{
	cout << "����� �� ������, �������� ��� �� �����? (������� '�����' ��� '��������' ��� '��')" << endl;
	string I;
	cin >> I;
	while (I != "�����" && I != "��������" && I != "��" && I != "�����" && I != "��������" && I != "��" && I != "���" && I != "���")
	{
		if (I == "�����" || I == "�����")
		{
			vector<book> ERR;
			return ERR;
		}
		cin >> I;
	}
	if (I == "�����" || I == "�����")
	{
		cout << "������� ������" << endl;
		string aut;
		getline(cin, aut);
		getline(cin, aut);
		vector<book> theautor;
		if (param[IF_NEW_SEARCH] == 1) findby_autor_new(theautor, list, aut, index);
		else findby_autor(theautor, list, aut);
		return theautor;
	}
	if (I == "��������" || I == "��������")
	{
		cout << "������� ��������" << endl;
		string aut;
		getline(cin, aut);
		getline(cin, aut);
		vector<book> thename;
		if (param[IF_NEW_SEARCH] == 1) findby_name_new(thename, list, aut, index);
		else findby_name(thename, list, aut, index);
		return thename;
	}
	if (I == "��" || I == "��" || I == "���" || I == "���")
	{
		cout << "������� �������� ������" << endl;
		string key;
		getline(cin, key);
		getline(cin, key);
		vector<book> all;
		if (param[IF_NEW_SEARCH] == 1)
		{
			findby_autor_new(all, list, key, index);
			findby_name_new(all, list, key, index);
		}
		else
		{
			findby_autor(all, list, key, index);
			findby_name(all, list, key, index);
		}
		return all;
	}
}

bool delete_from_vec(vector<book> & A, book elem)
{
	int j = 0; bool flag = false;
	for (int i = 0; j < A.size(); i++)
	{
		if (A[i] == elem) { j++; flag == true; }
		A[i] = A[j];
		j++;
	}
	A.pop_back();
	return flag;
}

string form_string_from_book(book A)
{
	return A.autor + "-" + A.name;
}

void remove_from_polk(int polka, book item)
{
	string adress = create_adress(polka);
	ifstream IF(adress);
	string key = "<LI>" + form_string_from_book(item) + "</LI>";
	vector<string> page;
	string str;
	while (!IF.eof())
	{
		getline(IF, str);
		if(str != key && str != key + ' ') page.push_back(str);
	}
	IF.close();
	ofstream OF(adress, ios_base::trunc | ios_base::out);
	for (int i = 0; i < page.size(); i++)
	{
		OF << page[i] << endl;
	}
	OF.close();
}

void remove_from_polk(book item)
{
	string adress = create_adress(item.place);
	ifstream IF(adress);
	string key = "<LI>" + form_string_from_book(item) + "</LI>";
	vector<string> page;
	string str;
	while (!IF.eof())
	{
		getline(IF, str);
		if (str != key && str != key + ' ') page.push_back(str);
	}
	IF.close();
	ofstream OF(adress, ios_base::trunc | ios_base::out);
	for (int i = 0; i < page.size(); i++)
	{
		OF << page[i] << endl;
	}
	OF.close();
}

string raw_to_date(int raw)
{	
	raw += 345600;
	int year = 1970, month = 1, day = 1, hour = 0, min = 0;
	int add = raw / 126230400;
	year += add*4;
	raw -= add * 126230400;
	int vis = 2;
	while ((raw >= 31536000 && vis >0) || (raw >= 31622400 && vis==0))
	{
		if (vis > 0)
		{
			raw -= 31536000;
			vis--;
		}
		else
		{
			raw -= 31622400;
			vis = 3;
		}
		year++;
	}

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if(vis>0)//28-29
		if (raw > 2419200)
		{
			raw -= 2419200;
			month++;
		}
		else;
	else
		if (raw > 2505600)
		{
			raw -= 2505600;
			month++;
		}
		else;

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if (raw > 2592000)
	{
		raw -= 2592000;
		month++;
	}//30

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if (raw > 2592000)
	{
		raw -= 2592000;
		month++;
	}//30

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if (raw > 2592000)
	{
		raw -= 2592000;
		month++;
	}//30

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31

	if (raw > 2592000)
	{
		raw -= 2592000;
		month++;
	}//30

	if (raw > 2678400)
	{
		raw -= 2678400;
		month++;
	}//31
	add = raw / 86400;
	day += add;
	raw -= add * 86400;

	add = raw / 3600;
	hour += add;
	raw -= add * 3600;

	add = raw / 60;
	min += add;
	raw -= add * 60;

	return I_S(year) + '/' + I_S(month) + '/' + I_S(day) + ' ' + I_S(hour) + ':' + I_S(min) + ':' + I_S(raw);
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������ " << VERSION << endl;
	if (get_param() == 1)
	{
		cout << "������, �� ��������� ��������� � ������ ���." << endl << "��������� �������� ��������� ���������" << endl;
		create_param();
	}
	if (get_param() == 2)
	{
		cout << "������, ���� � ����������� ��������." << endl << "��������� �������� ��������� ���������" << endl;
		create_param();
	}
	cout << "�������������";
	vector<book> list;
	//vector<book> away;
	vector<int> init_err = init(list);
	for (int i = 0; i < init_err.size(); i++) cout << "�� ������� ����� ����� �� ����� " <<  init_err[i] << endl;
	//init_err.clear();
	if (list.size() == 0) cout << "������: �� ����� ����� �� �������!" << endl;
	ofstream HIS("history.txt", ios_base::app);
	time_t rawtime;
	time(&rawtime);
	string nor_time = raw_to_date(rawtime);
	HIS << '[' << nor_time << ']' << " ������ ������ " << VERSION << endl;
	HIS.close();
	cout << endl << "�������� '������' ��� ��������� ������ ������" << endl;
	string command;
	cin >> command;
	while (command != "�����" && command != "�����")
	{
		if (command == "������" || command == "������")
			for (int i = 0; i < list.size(); i++)
				cout << "�����: " << list[i].autor << " ��������: " << list[i].name << " ����� � " << list[i].place << endl;

		if (command == "�����" || command == "�����")
		{
			
			vector<book> results = search(list);
			cout << "��������� ��������:" << endl;
			for (int j = 0; j < results.size(); j++) cout << "�����: " << results[j].autor << " ��������: " << results[j].name << " ����� � " << results[j].place << endl;
			switch (check_ending(results.size()))
			{
			case 1: 
			{
				cout << "����� ������ " << results.size() << " �������" << endl;
				break;
			}
			case 2:
			{
				cout << "����� ������� " << results.size() << " ��������" << endl;
				break;
			}
			case 5:
			{
				cout << "����� ������� " << results.size() << " ���������" << endl;
				break;
			}
			default:
				break;
			}
			results.clear();
		}
		if (command == "�����" || command == "�����")
		{
			int index = cin_index();
			vector<book> polka;
			find_polk(polka, index, list);
			cout << "����� � " << index << ':' << endl;
			for (int i = 0; i < polka.size(); i++)
				cout << "�����: " << polka[i].autor << " ��������: " << polka[i].name << endl;
			cout << "�� ����� " << polka.size();
			switch (check_ending(polka.size()))
			{
			case 1:
			{
				cout << " �����" << endl;
				break;
			}
			case 2:
			{
				cout << " �����" << endl;
				break;
			}
			case 5:
			{
				cout << " ����" << endl;
				break;
			}
			default:
				break;
			}
		}
		if (command == "����������" || command == "����������")
		{
			cout << "����� " << list.size();
			switch (check_ending(list.size()))
			{
			case 1:
			{
				cout << " �����" << endl;
				break;
			}
			case 2:
			{
				cout << " �����" << endl;
				break;
			}
			case 5:
			{
				cout << " ����" << endl;
				break;
			}
			default:
				break;
			}
			cout << DIF_AUTORS;
			switch (check_ending(DIF_AUTORS))
			{
			case 1:
			{
				cout << " ������ �����" << endl;
				break;
			}
			case 2:
			{
				cout << " ������ ������" << endl;
				break;
			}
			case 5:
			{
				cout << " ������ �������" << endl;
				break;
			}
			default:
				break;
			}
			cout << "� ���������� " << param[MAX_POLOK];
			switch (check_ending(param[MAX_POLOK]))
			{
			case 1:
			{
				cout << " ����� (�� ��� ";
				break;
			}
			case 2:
			{
				cout << " ����� (�� ��� ";
				break;
			}
			case 5:
			{
				cout << " ����� (�� ��� ";
				break;
			}
			default:
				break;
			}
			cout << init_err.size();
			switch (check_ending(init_err.size()))
			{
			case 1:
			{
				cout << " ������)" << endl;
				break;
			}
			case 2:
			{
				cout << " ������)" << endl;
				break;
			}
			case 5:
			{
				cout << " ������)" << endl;
				break;
			}
			default:
				break;
			}

		}
		if (command == "������" || command == "������")
		{
			cout << "������ - ����� ������ ���������" << endl << "����� - ���������� ���������" << endl << "�������� - �������� ����� �� �����" << endl << "����� - � ����������� ����" << endl << "��������� - �������� ���������" << endl << "�������� ������� - �������� ������� ���� ���� ��� ���������� ������ ����������" << endl << "�������� ������ - �������� ������ ���� � ��������� (����������� ������������)" << endl << "�������� - �������� ���� �� ����������� ������" << endl << "����� - ����� �� ������/��������" << endl << "����� N - ����� ���� ���� �� ����� N" << endl << "�������� - ������� ���������� � ��������" << endl << "������ - ����� ���� ����" << endl << "���������� - ��������� �����" << endl << "������ - ������ ����� � ����� � �� ������ ������" << endl;
		}
		if (command == "��������" || command == "��������")
		{
			cout << "�� ����� ����� �� ������ �������� �����?" << endl;
			int index = cin_index();
			cout << "��� ���������� ����� ������ ������ ����� ������� \"����\" (� ���������)" << endl;
			cout << "������� ������ (���� ����� ����������, ������� -)" << endl;
			book newbook;
			getline(cin, newbook.autor);
			getline(cin, newbook.autor);
			vector<book> out;
			newbook.place = index;
			vector<short int> place;
			short int PL;
			while (newbook.autor != "\"����\"" && newbook.autor != "\"����\"")
			{
				cout << "������� ��������" << endl;
				getline(cin, newbook.name);
				cout << "������ ��� ������ ���? (������� 1 ��� 2)" << endl;
				cin >> PL;
				place.push_back(PL);
				out.push_back(newbook);
				if (newbook.autor == "-")newbook.autor = "����� ����������";
				list.push_back(newbook);
				cout << "������� ������" << endl;
				cin.clear();
				getline(cin, newbook.autor);
				getline(cin, newbook.autor);
			}
			cout << "�� �������, ��� ������ �������� ��� �����? (������� �� ��� ���)" << endl;
			for (int i = 0; i < out.size(); i++) cout << "�����: " << out[i].autor << " ��������: " << out[i].name << endl;
			string yes;
			cin >> yes;
			while (yes != "��" && yes != "��" && yes != "���" && yes != "���")
			{
				cin >> yes;
			}
			if (yes == "��" || yes == "��")
			{
				string ch_i = I_S(index);
				string adress = "html\\Polka" + ch_i + ".html";
				write(out, adress, place);
				sort(list.begin(), list.end(), compare_book);
				switch (check_ending(out.size()))
				{
				case 1:
				{
					cout << "��������� " << out.size() << " �����" << endl;
					break;
				}
				case 2:
				{
					cout << "��������� " << out.size() << " �����" << endl;
					break;
				}
				case 5:
				{
					cout << "��������� " << out.size() << " ����" << endl;
					break;
				}
				default:
					break;
				}

				ofstream HIS("history.txt", ios_base::app);
				time_t rawtime;
				time(&rawtime);
				string nor_time = raw_to_date(rawtime);
				HIS << '[' << nor_time << ']' << " ��������� �����: " << endl;
				for (int i = 0; i < out.size(); i++) HIS << '\t' + form_string_from_book(out[i]) << endl;
				cout << "�������� �����������? ('��' ��� '���')" << endl;
				string I; cin >> I;
				while (I != "��" && I != "��" && I != "���" && I != "���")
				{
					if (I == "�����" || I == "�����") goto again;
					cin >> I;
				}
				if (I == "��" || I == "��")
				{
					cout << "������� �����������" << endl;
					string comment;
					getline(cin, comment);
					getline(cin, comment);
					HIS << "���������� - " << out.size() << " | �����������: " + comment << endl;
				}
				else HIS << "���������� - " << out.size() << endl;
				HIS.close();
				cout << "������" << endl << "������� � ������� ����" << endl;
			}
			else cout << "����� �� ���������" << endl;
		}
		if (command == "��������" || command == "��������")
		{
			string I;
			cin >> I;
			if (I == "�������") 
			{
				rebuild_katalog(list);
				ofstream HIS("history.txt", ios_base::app);
				time_t rawtime;
				time(&rawtime);
				string nor_time = raw_to_date(rawtime);
				HIS << '[' << nor_time << ']' << "������� �������" << endl;
				HIS.close();
				cout << "������� �������" << endl;
			}
			if (I == "������")
			{
				init(list);
				ofstream HIS("history.txt", ios_base::app);
				time_t rawtime;
				time(&rawtime);
				string nor_time = raw_to_date(rawtime);
				HIS << '[' << nor_time << ']' << "������ �������" << endl;
				HIS.close();
				cout << "������ ��������" << endl;
			}
		}
		if (command == "��������" || command == "��������")
		{
			ShellExecuteW(NULL, L"open", L"html\\Biblio.html", NULL, NULL, SW_SHOWNORMAL);
		}
		if (command == "��������" || command == "��������")
		{
			system("CLS");
			cout  << "�������� '������' ��� ��������� ������ ������" << endl;
		}
		if (command == "���������" || command == "���������") 
		{
			create_param();
		}
		if (command == "������" || command == "������")
		{
			cout << "������ " << VERSION << endl;
		}
		if (command == "������" || command == "������")
		{
			cout << "��������, ��� ����� �����: ����� �� ������ ���� ����, ����� �� ����� ��� ���� ������ �����? (������� '�����' ��� '�����' ��� '�����')" << endl;
			string I; cin >> I;
			while (I != "�����" && I != "�����" && I != "�����" && I != "�����" && I != "�����" && I != "�����")
			{
				if (I == "�����" || I == "�����") goto again;
				cin >> I;
			}
			vector<book> results;
			vector<int> index;
			if (I == "�����" || I == "�����") 
			{
				results = search(list, index);
			}
			if (I == "�����" || I == "�����")
			{
				cout << "������� ����� �����" << endl;
				string N; cin >> N;
				while (!if_int(N) || S_I(N) > param[MAX_POLOK] || S_I(N) < 1)
				{
					if (N == "�����" || N == "�����") 
					{
						cout << "������� � ������� ����" << endl;
						goto again;
					}
					cout << "������� ����� �� 1 �� " << param[MAX_POLOK] << endl;
					cin >> N;
				}
				find_polk(results, S_I(N), list, index);
			}
			if (I == "�����" || I == "�����") 
			{
				cout << "������� �����" << endl;
				string ind; cin >> ind;
				while (!if_int(ind) || S_I(ind) >= list.size() || S_I(ind) < 0)
				{
					if (ind == "�����" || ind == "�����")
					{
						cout << "������� � ������� ����" << endl;
						goto again;
					}
					cout << "������� ����� �� 0 �� " << list.size()-1 << endl;
					cin >> ind;
				}
				cout << "�� �������, ��� ������ ������� ��� �����? (������� '��' ��� '���')" << endl;
				cout << "����� " << list[S_I(ind)].autor << " ��������: " << list[S_I(ind)].name << " ����� � " << list[S_I(ind)].place << endl;
				string yes; cin >> yes;
				while (yes != "��" && yes != "��" && yes != "���" && yes != "���")
				{
					if (yes == "�����" || yes == "�����") goto again;
					cin >> yes;
				}
				if (yes == "��" || yes == "��")
				{
					results.push_back(list[S_I(ind)]);
					index.push_back(S_I(ind));
				}
			}
			if (results.size() == 0)
			{
				cout << "������ �� �������!" << endl << "������� � ������� ����" << endl;
				goto again;
			}
			cout << "������� ����� �����, ������� �� ������ ������ �� ����������:" << endl;
			for (int i = 0; i < results.size(); i++)
			{
				cout << index[i] << ". �����: " << results[i].autor << " ��������: " << results[i].name << " ����� " << results[i].place << endl;
			}
			int id; cin >> id;
			string itm = form_string_from_book(list[id]);
			remove_from_polk(list[id]);
			delete_from_vec(list, list[id]);
			rebuild_katalog(list);
			cout << "����� ������" << endl << "�������� �����������? ('��' ��� '���')" << endl;
			cin >> I;
			while (I != "��" && I != "��" && I != "���" && I != "���")
			{
				if (I == "�����" || I == "�����") goto again;
				cin >> I;
			}
			if (I == "��" || I == "��")
			{
				cout << "������� �����������" << endl;
				string comment;
				getline(cin, comment);
				getline(cin, comment);
				ofstream OF("history.txt", ios_base::app);
				time_t rawtime;
				time(&rawtime);
				string nor_time = raw_to_date(rawtime);
				OF << '[' << nor_time << ']' << " Deleted " << id << ". " + itm + " | �����������: " << comment << endl;
				OF.close();
			}
			else
			{
				ofstream OF("history.txt", ios_base::app);
				time_t rawtime;
				time(&rawtime);
				string nor_time = raw_to_date(rawtime);
				OF << '[' << nor_time << ']' << " Deleted " << id << ". " + itm << endl;
				OF.close();
			}
			cout << "������" << endl << "������� � ������� ����" << endl;
		}
		if (command == "�������" || command == "�������")
		{
			ShellExecuteW(NULL, L"open", L"history.txt", NULL, NULL, SW_SHOWNORMAL);
		}
		if (command == "�����" || command == "�����") { cout << "�� ��� � ������� ����" << endl; }

	again:
		cin >> command;
	}
	end:
	system("pause");
}