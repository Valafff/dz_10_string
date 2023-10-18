// �� � 473 ������
#include <iostream>
#include <time.h>
#include <Windows.h>//	Sleep;
#include <string>
#include<conio.h>
#include<vector>
#include <algorithm>
//#include "menu.h"
using namespace std;
enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���������� ��������� ����
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//�������������� ������������� ���������� ������ ���������
	SetConsoleCursorPosition(hStdOut, myCoords);
}
class MENU
{
	class SUBMENU
	{
		size_t count_y_slots{ 0 };
		size_t step_Y{ 0 };
		size_t sub_start_X{ 0 };
		size_t sub_start_Y{ 0 };
		size_t menupoint_Y{ 0 };
		size_t quit_Y{ 0 };

		Color text_Y{ Red };
		Color background_Y{ White };
		Color text_default_Y{ White };
		Color background_default_Y{ Black };

		string* y_list{ nullptr };

	public:

		SUBMENU() :SUBMENU(2, Red, White)
		{
			for (size_t i = 0; i < count_y_slots; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
			//y_list[0] = "SUB_1";
			//y_list[1] = "SUB_2";
		}
		SUBMENU(const size_t def_size) :SUBMENU(def_size, Red, White)
		{
			for (size_t i = 0; i < def_size; i++)
			{
				y_list[i] += "SUB_";
			}
		}
		SUBMENU(const size_t f_count_Y, const Color textcolor, const Color backgroung_color, const size_t X = 0, const size_t Y = 0, const size_t f_step_Y = 1)
		{
			count_y_slots = f_count_Y;
			y_list = new string[f_count_Y];
			step_Y = f_step_Y;
			text_Y = textcolor;
			background_Y = backgroung_color;
			quit_Y = f_count_Y;
			sub_start_X = X;
			sub_start_Y = Y;
			menupoint_Y = 1;

		}
		~SUBMENU()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
		}
		void setCount_Y_slots(const size_t& f_size)
		{
			count_y_slots = f_size;
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
			//!!!����������� ������� ��������� - ����� ���������� ����� �������� ���������� ������ ��� ����!!!
			y_list = nullptr;
			for (size_t i = 0; i < f_size; i++)
			{
				y_list = new string[f_size];
			}
			for (size_t i = 0; i < f_size; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
		}
		void setY_step(const size_t& f_size)
		{
			step_Y = f_size;
		}
		void set_BackGround_Y(const Color& f_color)
		{
			background_Y = f_color;
		}
		void set_Text_Y(const Color& f_color)
		{
			text_Y = f_color;
		}
		void setQuit_Y(const size_t f_size)
		{
			quit_Y = f_size;
		}
		void setSubStart_X(const size_t X)
		{
			sub_start_X = X;
		}
		void setSubStart_Y(const size_t Y)
		{
			sub_start_Y = Y;
		}
		void setMenupoint(const size_t f_menu)
		{
			menupoint_Y = f_menu;
		}
		void setY_list(const size_t index, const string f_name)
		{
			y_list[index] = f_name;
		}

		Color getBackground_Y() const
		{
			return background_default_Y;
		}
		size_t getCount_y_slots()
		{
			return count_y_slots;
		}

		// ������������ ����� ���������� ������ ��� y_list �.�. ���������� �������� ������� ������ �� ������, ������� ����������� �������������
		void delMem()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
				y_list = nullptr;
			}
		}

		// ������ ������� �� ���������
		void menuPrint_Y(const size_t& menupoint, const size_t& f_step_X)
		{
			for (size_t i = 0; i < count_y_slots; i++)
			{
				setCursor(f_step_X, sub_start_Y + i * step_Y + 1);
				if (i == menupoint)
				{
					setColor(text_Y, background_Y);
				}
				else
				{
					setColor(text_default_Y, background_default_Y);
				}
				cout << y_list[i];
			}
			setColor(text_default_Y, background_default_Y);
		}
		//������� ����������� �������(�� ��������� ���������� � ��������� 0,1) ���������� ����� ��� ������� ���������� ��� ��������, ����� ������ ���������� ��� ��������
		void cleanSubMenuZone(const size_t count_row, const size_t string_length, size_t f_start_x = 0, size_t f_start_y = 1)
		{
			setCursor(f_start_x, f_start_y);
			setColor(getBackground_Y(), getBackground_Y());
			char** cleanarr = new char* [count_row];
			for (size_t i = 0; i < count_row; i++)
			{
				cleanarr[i] = new char[string_length];
			}
			for (size_t i = 0; i < count_row; i++)
			{
				for (size_t j = 0; j < string_length; j++)
				{
					cleanarr[i][j] = '@';
					cout << cleanarr[i][j];
				}
				cout << endl;
			}
			if (cleanarr != nullptr)
			{
				for (size_t i = 0; i < count_row; i++)
				{
					delete[] cleanarr[i];
				}
				delete[] cleanarr;
			}
		}
	};

	size_t count_x_slots{ 0 };
	size_t step_X{ 0 };
	size_t quit{ 0 };
	size_t start_X{ 0 };
	size_t start_Y{ 0 };
	size_t menupoint{ 0 };

	Color text{ Red };
	Color background{ White };
	Color text_default{ White };
	Color background_default{ Black };

	//SUBMENU aaa;
	//SUBMENU aaa(10);

	string* x_list;
	SUBMENU* sub_menu;

	// ������ ���� ��� �����������
	void menuPrint_X(const size_t menupoint)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			setCursor(start_X + i * step_X, start_Y);
			if (i == menupoint)
			{
				setColor(text, background);
			}
			else
			{
				setColor(text_default, background_default);
			}
			cout << x_list[i];
		}
		setColor(text_default, background_default);
	}

public:

	MENU() :MENU(4, 18, Red, White)
	{
		x_list[0] = "MENU_1";
		x_list[1] = "MENU_2";
		x_list[2] = "MENU_3";
		x_list[3] = "QUIT";
	}
	//// �����, ����� ����������� ����������� ���������������� ������
	//MENU(int size): MENU(4, 18, Red, White)
	//{
	//	SUBMENU aaa(size);
	//}
	MENU(const size_t f_count_X, const size_t f_step_X, const Color textcolor, const Color backgroung_color, const size_t X = 0, const size_t Y = 0, const size_t f_step_Y = 1)
	{
		x_list = new string[f_count_X];
		sub_menu = new SUBMENU[f_count_X];
		count_x_slots = f_count_X;
		step_X = f_step_X;
		text = textcolor;
		background = backgroung_color;
		quit = f_count_X;
		start_X = X;
		start_Y = Y;
		menupoint = 0;
	}
	~MENU()
	{
		//����� ������ ������������ �������������� ������ ��� y_list
		this->sub_menu->delMem();
		if (x_list != nullptr)
		{
			delete[] x_list;
		}
		if (sub_menu != nullptr)
		{
			delete[] sub_menu;
		}
	}
	// ��������� ����� ������ ��� �������������� ������
	void setColorText(const Color textcolor)
	{
		text = textcolor;
	}
	// ��������� ����� ������ ��� ������������ ������
	void setColorText_Y(const Color textcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_Text_Y(textcolor);
		}
	}
	// ��������� ����� ���� ��� ������������ ������
	void setColorBackGround_Y(const Color backcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_BackGround_Y(backcolor);
		}
	}
	// ��������� ����� ������� ���� �������������� ������
	void setColorBackground(const Color f_bakground)
	{
		background = f_bakground;
	}
	// ��������� ���������� ����� ������ �� ��������� �������������� ������
	void setColorTextDefault(const Color f_def_text)
	{
		text_default = f_def_text;
	}
	//��������� ������� ���� �� ��������� �������������� ������
	void setColorBackgroundDefault(const Color f_def_background)
	{
		background_default = f_def_background;
	}
	// ������� ���������� ������ ���� �� �����������
	void setCount_X_Slots(const size_t f_count)
	{
		count_x_slots = f_count;
	}
	// ������� ���������� ������ ���� �� ��������� ��� �������
	void setCount_Y_Slots(const size_t f_index, const size_t f_count)
	{
		sub_menu[f_index].setCount_Y_slots(f_count);

	}
	// ������� �������� ������� ���� �� �����������
	void setName_X_list(const size_t index, const string f_name)
	{
		x_list[index] = f_name;
	}
	// ������� �������� ������� ���� �� ���������
	void setName_Y_list(const size_t index_x, const size_t index_y, const string f_name)
	{
		sub_menu[index_x].setY_list(index_y, f_name);
	}
	// ��������� ���� �� �����������
	void set_X_step(const size_t f_step)
	{
		step_X = f_step;
	}
	// ��������� ����� ������ �� �����������
	size_t getSizeX()
	{
		return count_x_slots;
	}
	// ��������� ���������� ������� ������ �� �����������
	size_t getLast_IndexX()
	{
		return count_x_slots - 1;
	}
	// ��������� ������� ���������� ���� �� �����������
	size_t getMenuIndex()
	{
		return menupoint;
	}
	// ����������� ������������� ���������� �����
	size_t getMaxRow()
	{
		size_t temp(0);
		for (size_t i = 0; i < count_x_slots; i++)
		{
			if (sub_menu[i].getCount_y_slots() > temp)
			{
				temp = sub_menu[i].getCount_y_slots();
			}
		}
		return temp;
	}

	// ���������� ������, ������� ���������� ������ ���� ��� ����������� � ���������
	size_t SelectMenuItem(const size_t f_lastmenu, const size_t f_lastmenu_Y, const bool f_flag)
	{
		size_t menupoint;
		size_t menupoint_Y;
		if (f_lastmenu == 0)
		{
			menupoint = 1;
		}
		else
		{
			menupoint = f_lastmenu;
		}
		if (f_lastmenu_Y == 0)
		{
			menupoint_Y = 1;
		}
		else
		{
			menupoint_Y = f_lastmenu_Y;
		}

		size_t lastmenupoint = 1;
		size_t maxrow = getMaxRow();
		//����� - ��������� ���� ������
		size_t key(0);
		do
		{
			if (menupoint != lastmenupoint)
			{
				if (key == Left or key == Right)
				{
					menupoint_Y = 1;
				}
				lastmenupoint = menupoint;
				sub_menu[menupoint - 1].cleanSubMenuZone(maxrow, 100);
			}
			menuPrint_X(menupoint - 1);
			sub_menu[menupoint - 1].menuPrint_Y(menupoint_Y - 1, step_X * (menupoint - 1));

			key = _getch();
			if (key == Right)
			{
				if (menupoint <= count_x_slots)
				{
					menupoint++;
				}
				if (menupoint > count_x_slots)
				{
					menupoint = 1;
				}
			}
			if (key == Left)
			{
				if (menupoint >= 1)
				{
					menupoint--;
				}
				if (menupoint < 1)
				{
					menupoint = count_x_slots;
				}
			}
			if (key == Down)
			{
				if (menupoint_Y <= sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y++;
				}
				if (menupoint_Y > sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y = 1;
				}
			}
			if (key == Up)
			{
				if (menupoint_Y >= 1)
				{
					menupoint_Y--;
				}
				if (menupoint_Y < 1)
				{
					menupoint_Y = sub_menu[menupoint - 1].getCount_y_slots();
				}
			}
			if (key == Enter)
			{
				if (sub_menu[menupoint - 1].getCount_y_slots() != 0)
				{
					//�� 1 �� 100 - ���� ������ ��������������� ����, ��������� ��� �� 101 �� 200 - MENU_1, SUB_1 - SUB_N �� ���������, MENU_2, SUB_1 - SUB_N  201-300...
					return menupoint_Y + (menupoint * 100);
				}
				else
				{
					return menupoint;
				}
			}
		} while (key != Enter);
		return this->quit;
	}
};

/*1. ��������� �������� �� ������ �����������. (��������� - ��� ���������, ������� �������� ��������� ����� ������� � ������ ������).
�� ������ ����� ������ ��, ��� �� �������� ������, ������ ��� ������ ���������.
����� ����, ��������� ������ ����������� ��� ����� ��������.*/
//2. ���������� ����� ������� � ����� �������� ����� � ���� ������.
/*3. ����� ������� ����������� �������� ������� ( :) ) � ������:

� ����� �������� ���, ��� ����� � ������� ��� ������ �� ���� � ��� �� ��������� ����������� �� ����� �������!
��... ���� ������. �������, �������� � ������������, � ������� ������.� ������ ������ � ����� ��������� � ������������ ������ 400 �����.
��� �� ������ � ��������� � ���������� ������� ������ ������������ ����� �������, ���������� �������� ��, ����� ��������� � ������� �������� � ��������� � ����� �������������?
��� ���������� �������� ��������� ����������, ������� �������� ������ ����� ������ ����?��� ����� ���?
����? ������? ��� �� ����� � ��� �� �����������? ��������� ���� �����... � ���� ���� �� ��� �������.

��������� �������� �� �����
*/
/*4. ������� ��� ����� � ������ - �.�. ��� �����, ������������ � ���� � ����.
����� -  �������� �� �� �����.

���� � ����� ������ �������, ����� � ����� ������� �������. ������� ��� ������� ���������, ��� ��������� �����. ��������� ��������� � ���������.

5*. ������������ ������ ������. ����������� ������ �����, � ������� ���� ���� �� ��� ������� ����.
������� ��������� ������ �� �����.
*/
void cleanZone(const size_t X, const size_t Y, const size_t row, const size_t col, const Color color = Black)
{
	Color temptxtcol = White;
	Color tempbackcol = Black;

	setCursor(X, Y);
	setColor(color, color);
	vector <char> cln;
	cln.assign(row * col, '@');
	int count = 1;
	for (auto symbol : cln)
	{
		cout << symbol;
		count++;
		if (count % col == 0)
		{
			cout << endl;
		}
	}
	setColor(temptxtcol, tempbackcol);
	setCursor(X, Y);
}

void formatPrint(const size_t col_size, const string& originalstr)
{

	size_t tempindex = 1;
	for (auto s : originalstr)
	{
		tempindex++;
		cout << s;
		if (tempindex % col_size == 0)
		{
			cout << endl;
		}
	}
}
//������ ������
string stringRevers(const string& f_string)
{
	string temp;
	size_t count(0);
	do
	{
		temp.append(f_string, f_string.size() - count, 1);
		count++;
	} while (count - 1 != f_string.size());
	return temp;
}
//������ ���� � number(�����) � ����� ��������
string stringRevers(const string& f_string, const size_t number, const string& f_spec_symbol = "���������")
{

	string temp{ f_string }, word, result{};
	int pos(0), wpos(0);
	size_t count(0);
	do
	{
		pos = temp.find_first_not_of(" ., !&@#$ % ^&*[]() {}:'\"", 0);
		if (pos != temp.npos)
		{
			result.append(temp.begin(), temp.begin() + pos);
			temp.erase(temp.begin(), temp.begin() + pos);
		}
		else
		{
			result += temp;
			break;
		}
		pos = temp.find_first_of(" ., !&@#$ % ^&*[]() {}:'\"", 0);
		if (pos != temp.npos)
		{
			word.assign(temp.begin(), temp.begin() + pos);
			count = 0;
			wpos = 0;
			do
			{
				wpos = word.find_first_of(f_spec_symbol.c_str(), wpos);
				if (wpos != word.npos)
				{
					count++;
					wpos++;
				}

			} while (wpos != word.npos);
			if (count >= number)
			{
				word = stringRevers(word);
			}
			temp.erase(temp.begin(), temp.begin() + pos);
			result.append(word);
		}
		else
		{
			pos = temp.find_last_not_of(" ., !&@#$ % ^&*[]() {}:'\"");
			if (pos != temp.npos)
			{
				word.assign(temp.begin(), temp.begin() + pos + 1);
				count = 0;
				wpos = 0;
				do
				{
					wpos = word.find_first_of(f_spec_symbol.c_str(), wpos);
					if (wpos != word.npos)
					{
						count++;
						wpos++;
					}

				} while (wpos != word.npos);
				if (count >= number)
				{
					word = stringRevers(word);
				}
				temp.erase(temp.begin(), temp.begin() + pos + 1);
				result.append(word);
				break;
			}
		}
	} while (pos != temp.npos);

	return result;
}

// ��������  .,!&@#$%^&*[](){}:'"
void symbolsErase(string& f_str)
{
	int pos(0);
	do
	{
		pos = f_str.find_first_of(" .,!&@#$%^&*[](){}:'\"", 0);
		if (pos != f_str.npos)
		{
			f_str.erase(f_str.begin() + pos);
		}
	} while (pos != f_str.npos);
}

// ��������� ���� �� ������ �������� ������ ����
vector<string>  getWords(const string& f_string)
{
	vector <string> words;
	string word;
	string temp{ f_string };
	int pos(0);
	do
	{
		pos = temp.find_first_not_of(" ., !&@#$ % ^&*[]() {}:'\"", 0);
		if (pos != temp.npos)
		{
			temp.erase(temp.begin(), temp.begin() + pos);
		}
		else
		{
			break;
		}
		pos = temp.find_first_of(" ., !&@#$ % ^&*[]() {}:'\"", 0);
		if (pos != temp.npos)
		{
			words.push_back(word.assign(temp.begin(), temp.begin() + pos));
			temp.erase(temp.begin(), temp.begin() + pos);
		}
		if (pos == temp.npos and temp.find_last_not_of(" ., !&@#$ % ^&*[]() {}:'\"", 0) != temp.npos)
		{
			words.push_back(word.assign(temp));
		}
		//pos = temp.find_first_of(" ., !&@#$ % ^&*[]() {}:'\"", 0);
	} while (pos != temp.npos);
	return words;
}
// ��������� ������ �������� ����� � ������
string getMaxWord(const string& f_string)
{
	vector <string> words{ getWords(f_string) };
	string maxword{};
	for (auto str : words)
	{
		if (str.size() > maxword.size())
		{
			maxword = str;
		}
	}
	return maxword;
}
// ��������� ������ ��������� ����� � ������
string getMinWord(const string& f_string)
{
	vector <string> words{ getWords(f_string) };
	string minword;
	if (words.size() > 0)
	{
		minword = words[0] ;
	}
	else
	{
		minword="";
	}

	for (auto str : words)
	{
		if (str.size() < minword.size())
		{
			minword = str;
		}
	}
	return minword;
}
// ������� ���������� � ����� ����������� ������
string setSmile(const string& str, const string& spec_str)
{
	string temp{ str }, result{};
	int pos(0);
	bool first = true;
	do
	{
		pos = temp.find_first_not_of(".!?");
		if (pos != temp.npos)
		{
			result.append(temp.begin(), temp.begin() + pos);
			temp.erase(temp.begin(), temp.begin() + pos);
		}
		pos = temp.find_first_of(".!?");
		if (pos != temp.npos)
		{
			first = false;
			if (temp[pos + 1] != '.' and temp[pos + 1] != '!' and temp[pos + 1] != '?')
			{
				result.append(temp.begin(), temp.begin() + pos + 1);
				temp.erase(temp.begin(), temp.begin() + pos + 1);
				result.append(spec_str);
			}
			else
			{
				pos = temp.find_first_not_of(".!?", pos);
				if (pos != temp.npos)
				{
					result.append(temp.begin(), temp.begin() + pos);
					temp.erase(temp.begin(), temp.begin() + pos);
					result.append(spec_str);
				}
				else
				{
					result += temp + spec_str;
					break;
				}
			}
		}
		else
		{
			if (first)
			{
				result = temp + spec_str;
			}
		}
	} while (pos != temp.npos);
	return result;
}
vector<string> getWordsWithRoot(const string& f_str, const string& root)
{
	vector <string> words;
	string  tempword{}, temp{ f_str };
	int pos(0);

	do
	{
		pos = temp.find_first_not_of(" ., !&@#$ % ^&*[]() {}:'\"");
		if (pos != temp.npos)
		{
			temp.erase(temp.begin(), temp.begin() + pos);
		}
		else
		{
			break;
		}
		pos = temp.find_first_of(" ., !&@#$ % ^&*[]() {}:'\"");
		if (pos != temp.npos)
		{
			tempword.assign(temp.begin(), temp.begin() + pos);
			if (!tempword.compare(0, root.size(), root))
			{
				words.push_back(tempword);
			}
			temp.erase(temp.begin(), temp.begin() + pos);
		}


	} while (pos != temp.npos);
	return words;
}

void printVector(const vector<string>& vct)
{
	size_t count(1);
	if (vct.size() == 0)
	{
		cout << "���������� �� �������";
	}
	else
	{
		for (string str : vct)
		{
			cout << str << "\t";
			count++;
			if (count % 5 == 0)
			{
				cout << endl;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	srand(time(NULL));
	MENU dz10_menu(3, 18, Black, LightCyan);
	dz10_menu.setColorText_Y(Black);
	dz10_menu.setColorBackGround_Y(LightGray);
	dz10_menu.setName_X_list(0, "���� ������");
	dz10_menu.setName_X_list(1, "������ ������");
	dz10_menu.setName_X_list(2, "�����");
	dz10_menu.setCount_Y_Slots(0, 5);
	dz10_menu.setCount_Y_Slots(1, 6);
	dz10_menu.setCount_Y_Slots(2, 0);

	dz10_menu.setName_Y_list(0, 0, "���� ���������������� ������");
	dz10_menu.setName_Y_list(0, 1, "������� ��������� �� ���������");
	dz10_menu.setName_Y_list(0, 2, "������� �� ��������� �� ���������");
	dz10_menu.setName_Y_list(0, 3, "���� ������ �� \"����������\"");
	dz10_menu.setName_Y_list(0, 4, "���� ������ �� ������������");

	dz10_menu.setName_Y_list(1, 0, "�������� �� ��������������");
	dz10_menu.setName_Y_list(1, 1, "����� ������ �������� ����� � ������");
	dz10_menu.setName_Y_list(1, 2, "����� ������ ��������� ����� � ������");
	dz10_menu.setName_Y_list(1, 3, "���������� :) � ����� �����������");
	dz10_menu.setName_Y_list(1, 4, "����� ���� ���� � ������ (����, ����)");
	dz10_menu.setName_Y_list(1, 5, "������ ���� � ����� � ����� ��������");

	size_t select(0);
	size_t count(0);
	int pos(0);
	size_t lastmenu(0);
	size_t lastmenu_Y(0);

	bool flag(false);

	string userstr{}, str{}, temp{};
	vector <string> default_palindroms{ "���� ���","���� ���", "112252211", "123321" };
	vector <string> default_non_palindroms{ "���� �������","������� �������", "123450", "�������� � ������" };
	vector <string> words;


	do
	{
		select = dz10_menu.SelectMenuItem(lastmenu, lastmenu_Y, flag);
		cleanZone(0, 10, 20, 110);
		//count = 0;
		temp.clear();
		str = userstr;
		//���� ���������������� ������
		if (select == 101)
		{
			//������������ ������� �������� > NUL ��������� �  ������ ���� 
			system("chcp 1251 > NUL");
			setCursor(0, 10);
			cout << "������� ������: ";
			getline(cin, userstr);
			cleanZone(0, 10, 10, 100);
			system("chcp 866 > NUL");
			cout << "������� ���������������� ������: " << userstr;
		}
		//������� ��������� �� ��������� ����� .at
		if (select == 102)
		{
			userstr = default_palindroms.at(rand() % 4);
			cout << "������ �������, ������� �����: " << userstr;
		}
		//������� �� ��������� �� ���������
		if (select == 103)
		{
			userstr = default_non_palindroms[rand() % 4];
			cout << "������ �������, ������� �����: " << userstr;
		}
		//���� ������ �� \"����������\"
		if (select == 104)
		{
			userstr = "� ����� �������� ���, ��� ����� � ������� ��� ������ �� ���� � ��� �� ��������� ����������� �� ����� �������! ��... ���� ������.�������, �������� � ������������, � ������� ������.� ������ ������ � ����� ��������� � ������������ ������ 400 �����. ��� �� ������ � ��������� � ���������� ������� ������ ������������ ����� �������, ���������� �������� ��, ����� ��������� � ������� �������� � ��������� � ����� ������������� ? ��� ���������� �������� ��������� ����������, ������� �������� ������ ����� ������ ���� ? ��� ����� ��� ? ���� ? ������ ? ��� �� ����� � ��� �� ����������� ? ��������� ���� �����... � ���� ���� �� ��� �������.";
			cout << "������ �������, �������� �����: " << endl;
			formatPrint(105, userstr);
		}
		//���� ������ �� ������������
		if (select == 105)
		{
			userstr = "���� � ����� ������ �������, ����� � ����� ������� �������. ������� ��� ������� ���������, ��� ��������� �����. ��������� ��������� � ���������...";
			cout << "������ �������, �������� �����: " << endl;
			formatPrint(105, userstr);
		}

		// �������� �� ��������������
		if (select == 201)
		{
			//!!!transform ��������� �� �������� � SetConsoleCP(1251); SetConsoleOutputCP(1251)!!!;
			transform(str.begin(), str.end(), str.begin(), tolower);
			symbolsErase(str);
			temp = stringRevers(str);
			setCursor(0, 10);
			if (temp == str)
			{
				cout << "������ \""; formatPrint(90, userstr); cout << "\" - ���������";
			}
			else
			{
				cout << "������ \""; formatPrint(90, userstr); cout << "\" - �� ���������";
			}
		}
		//����� ������ �������� ����� � ������
		if (select == 202)
		{
			cout << "�������� ������: " << endl;
			formatPrint(105, str);
			setColor(Red, Black);
			cout << "\n����� ������� ����� � ������: \"" << getMaxWord(str) << "\"\t ����� �����: " << getMaxWord(str).size() << " ��������";
			setColor(White, Black);
		}
		//����� ������ ��������� ����� � ������
		if (select == 203)
		{
			cout << "�������� ������: " << endl;
			formatPrint(105, str);
			setColor(Red, Black);
			cout << "\n����� �������� ����� � ������: \"" << getMinWord(str) << "\"\t ����� �����: " << getMinWord(str).size() << " �������(��)";
			setColor(White, Black);
		}
		//���������� :) � ����� �����������"
		if (select == 204)
		{
			cout << "�������� ������: " << endl;
			formatPrint(105, str);
			cout << "\n������ �� ����������: " << endl;
			formatPrint(105, setSmile(str, ":)"));
		}
		//����� ���� ���� � ������(����, ����)
		if (select == 205)
		{
			cout << "�������� ������: " << endl;
			formatPrint(105, str);
			cout << "\n����� ���� c \"����\", �������������� � ������: " << endl;
			printVector(getWordsWithRoot(str, "����"));
			cout << "\n����� ���� c \"����\", �������������� � ������: " << endl;
			printVector(getWordsWithRoot(str, "����"));
		}
		//������ ���� � ����� � ����� ��������
		if (select == 206)
		{
			cout << "�������� ������: " << endl;
			formatPrint(105, str);
			cout << "\n������ � ��������: " << endl;
			formatPrint(105, stringRevers(str, 3));

		}
		// ��������������� ���������� ��� ������������ ��������� ������� ����
		if (select < 101)
		{
			lastmenu = select;
		}
		else
		{
			lastmenu = select / 100;
			lastmenu_Y = select % (100 * lastmenu);
			flag = true;
		}
	} while (select != dz10_menu.getSizeX());
	return 0;
}