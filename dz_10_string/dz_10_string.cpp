// Добавлен на GitHub
// ДЗ с 473 строки
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
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получаем дискриптор активного окна
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
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
			//!!!ОБЯЗАТЕЛЬНО НУЛЕВОЙ УКАЗАТЕЛЬ - ИНАЧЕ ДЕСТРУКТОР БУДЕТ ПЫТАТЬСЯ ОСВОБОДИТЬ ПАМЯТЬ ДВА РАЗА!!!
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

		// Освобождение вновь выделенной памяти для y_list Т.К. ДЕСТРУКТОР ПЫТАЕТСЯ БАХНУТЬ ПАМЯТЬ ПО АДРЕСУ, КОТОРАЯ ВЫДЕЛЯЛАЛСЬ КОНСТРУКТОРОМ
		void delMem()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
				y_list = nullptr;
			}
		}

		// ПЕЧАТЬ ПОДМЕНЮ ПО ВЕРТИКАЛИ
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
		//ОЧИСТКА ПРЕДЫДУЩЕГО ПОДМЕНЮ(по умолчанию происходит с координат 0,1) количество строк для очистки передается как аргумент, длина строки передается как аргумент
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

	// ПЕЧАТЬ МЕНЮ ДЛЯ ГОРИЗОНТАЛИ
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
	//// Далее, через конструктор копирования инициализировать объект
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
		//ВЫЗОВ МЕТОДА ОСВОБОЖДЕНИЯ ПЕРЕВЫДЕЛЕННОЙ ПАМЯТИ ДЛЯ y_list
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
	// Установка цвета текста для ГОРИЗОНТАЛЬНОЙ строки
	void setColorText(const Color textcolor)
	{
		text = textcolor;
	}
	// Установка цвета текста для ВЕРТИКАЛЬНОЙ строки
	void setColorText_Y(const Color textcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_Text_Y(textcolor);
		}
	}
	// Установка цвета фона для ВЕРТИКАЛЬНОЙ строки
	void setColorBackGround_Y(const Color backcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_BackGround_Y(backcolor);
		}
	}
	// Установка цвета заднего фона ГОРИЗОНТАЛЬНОЙ строки
	void setColorBackground(const Color f_bakground)
	{
		background = f_bakground;
	}
	// Установка дефолтного цвета текста по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorTextDefault(const Color f_def_text)
	{
		text_default = f_def_text;
	}
	//Установка заднего фона по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorBackgroundDefault(const Color f_def_background)
	{
		background_default = f_def_background;
	}
	// Задание количества слотов меню по ГОРИЗОНТАЛИ
	void setCount_X_Slots(const size_t f_count)
	{
		count_x_slots = f_count;
	}
	// Задание количества слотов меню по ВЕРТИКАЛИ для подменю
	void setCount_Y_Slots(const size_t f_index, const size_t f_count)
	{
		sub_menu[f_index].setCount_Y_slots(f_count);

	}
	// Задание названий пунктов меню по ГОРИЗОНТАЛИ
	void setName_X_list(const size_t index, const string f_name)
	{
		x_list[index] = f_name;
	}
	// Задание названий пунктов меню по ВЕРТИКАЛИ
	void setName_Y_list(const size_t index_x, const size_t index_y, const string f_name)
	{
		sub_menu[index_x].setY_list(index_y, f_name);
	}
	// Установка шага по ГОРИЗОНТАЛИ
	void set_X_step(const size_t f_step)
	{
		step_X = f_step;
	}
	// получение длины списка по ГОРИЗОНТАЛИ
	size_t getSizeX()
	{
		return count_x_slots;
	}
	// получение последнего индекса списка по ГОРИЗОНТАЛИ
	size_t getLast_IndexX()
	{
		return count_x_slots - 1;
	}
	// Получение индекса выбранного меню по ГОРИЗОНТАЛИ
	size_t getMenuIndex()
	{
		return menupoint;
	}
	// Определение максимального количества строк
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

	// Назначение клавиш, возврат выбранного пункта меню для ГОРИЗОНТАЛИ И ВЕРТИКАЛИ
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
		//ВЫХОД - последний член списка
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
					//От 1 до 100 - коды только горизонтального меню, выводится код от 101 до 200 - MENU_1, SUB_1 - SUB_N по ВЕРТИКАЛИ, MENU_2, SUB_1 - SUB_N  201-300...
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

/*1. Проверить является ли строка палиндромом. (Палиндром - это выражение, которое читается одинаково слева направо и справа налево).
Из строки нужно убрать всё, что не является буквой, цифрой или знаком пунтуации.
Кроме того, сравнение должно происходить без учёта регистра.*/
//2. Напечатать самое длинное и самое короткое слово в этой строке.
/*3. После каждого предложения добавьте смайлик ( :) ) в строке:

Я очень гордился тем, что попал в команду для полета на Марс – кто бы отказался прогуляться по чужой планете!
Но... меня забыли. Бросили, раненого и растерянного, и корабль улетел.В лучшем случае я смогу протянуть в спасательном модуле 400 суток.
Что же делать – разыскать в безбрежных красных песках поврежденную бурей антенну, попытаться починить ее, чтобы связаться с базовым кораблем и напомнить о своем существовании?
Или дожидаться прибытия следующей экспедиции, которая прилетит только через ЧЕТЫРЕ ГОДА?Где брать еду?
Воду? Воздух? Как не сойти с ума от одиночества? Робинзону было легче... у него хотя бы был Пятница.

Результат выведите на экран
*/
/*4. Найдите все имена в строке - т.е. все слова, начинающиеся с Карл и Клар.
После -  выведите их на экран.

Карл у Клары забрал кораллы, Клара у Карла забрала кларнет. Карлуша был хорошим мальчиком, его связывали тёплые. дружеские отношения с Кларочкой.

5*. Пользователь вводит строку. Перевернуть каждое слово, в котором есть хотя бы три гласных букв.
Вывести изменённую строку на экран.
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
//Реверс строки
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
//Реверс слов с number(тремя) и более гласными
string stringRevers(const string& f_string, const size_t number, const string& f_spec_symbol = "аиеёоуыэюя")
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

// Удаление  .,!&@#$%^&*[](){}:'"
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

// Получение слов из строки передает вектор слов
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
// Получение самого длинного слова в строке
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
// Получение самого короткого слова в строке
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
// Вставка спецтекста в конце предложения строки
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
		cout << "Совпадений не найдено";
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
	dz10_menu.setName_X_list(0, "ВВОД ДАННЫХ");
	dz10_menu.setName_X_list(1, "ЧТЕНИЕ ДАННЫХ");
	dz10_menu.setName_X_list(2, "ВЫХОД");
	dz10_menu.setCount_Y_Slots(0, 5);
	dz10_menu.setCount_Y_Slots(1, 6);
	dz10_menu.setCount_Y_Slots(2, 0);

	dz10_menu.setName_Y_list(0, 0, "Ввод пользовательской строки");
	dz10_menu.setName_Y_list(0, 1, "Указать палиндром по умолчанию");
	dz10_menu.setName_Y_list(0, 2, "Указать не палиндром по умолчанию");
	dz10_menu.setName_Y_list(0, 3, "Ввод текста из \"Марсианина\"");
	dz10_menu.setName_Y_list(0, 4, "Ввод текста из скороговорки");

	dz10_menu.setName_Y_list(1, 0, "Проверка на палиндромность");
	dz10_menu.setName_Y_list(1, 1, "Вывод самого длинного слова в строке");
	dz10_menu.setName_Y_list(1, 2, "Вывод самого короткого слова в строке");
	dz10_menu.setName_Y_list(1, 3, "Добавление :) в конец предложения");
	dz10_menu.setName_Y_list(1, 4, "Вывод всех имен в строке (Карл, Клар)");
	dz10_menu.setName_Y_list(1, 5, "Реверс слов с тремя и более гласными");

	size_t select(0);
	size_t count(0);
	int pos(0);
	size_t lastmenu(0);
	size_t lastmenu_Y(0);

	bool flag(false);

	string userstr{}, str{}, temp{};
	vector <string> default_palindroms{ "Вижу жив","Дару рад", "112252211", "123321" };
	vector <string> default_non_palindroms{ "Муть зеленая","зеленая плесень", "123450", "Тараканы в голове" };
	vector <string> words;


	do
	{
		select = dz10_menu.SelectMenuItem(lastmenu, lastmenu_Y, flag);
		cleanZone(0, 10, 20, 110);
		//count = 0;
		temp.clear();
		str = userstr;
		//Ввод пользовательской строки
		if (select == 101)
		{
			//Переключение кодовой страницы > NUL обращение в  пустой файл 
			system("chcp 1251 > NUL");
			setCursor(0, 10);
			cout << "Введите строку: ";
			getline(cin, userstr);
			cleanZone(0, 10, 10, 100);
			system("chcp 866 > NUL");
			cout << "Введена пользовательская строка: " << userstr;
		}
		//Указать палиндром по умолчанию метод .at
		if (select == 102)
		{
			userstr = default_palindroms.at(rand() % 4);
			cout << "Данные введены, указано слово: " << userstr;
		}
		//Указать не палиндром по умолчанию
		if (select == 103)
		{
			userstr = default_non_palindroms[rand() % 4];
			cout << "Данные введены, указано слово: " << userstr;
		}
		//Ввод текста из \"Марсианина\"
		if (select == 104)
		{
			userstr = "Я очень гордился тем, что попал в команду для полета на Марс – кто бы отказался прогуляться по чужой планете! Но... меня забыли.Бросили, раненого и растерянного, и корабль улетел.В лучшем случае я смогу протянуть в спасательном модуле 400 суток. Что же делать – разыскать в безбрежных красных песках поврежденную бурей антенну, попытаться починить ее, чтобы связаться с базовым кораблем и напомнить о своем существовании ? Или дожидаться прибытия следующей экспедиции, которая прилетит только через ЧЕТЫРЕ ГОДА ? Где брать еду ? Воду ? Воздух ? Как не сойти с ума от одиночества ? Робинзону было легче... у него хотя бы был Пятница.";
			cout << "Данные введены, исходный текст: " << endl;
			formatPrint(105, userstr);
		}
		//Ввод текста из скороговорки
		if (select == 105)
		{
			userstr = "Карл у Клары забрал кораллы, Клара у Карла забрала кларнет. Карлуша был хорошим мальчиком, его связывали тёплые. дружеские отношения с Кларочкой...";
			cout << "Данные введены, исходный текст: " << endl;
			formatPrint(105, userstr);
		}

		// Проверка на палиндромность
		if (select == 201)
		{
			//!!!transform корректно не работает с SetConsoleCP(1251); SetConsoleOutputCP(1251)!!!;
			transform(str.begin(), str.end(), str.begin(), tolower);
			symbolsErase(str);
			temp = stringRevers(str);
			setCursor(0, 10);
			if (temp == str)
			{
				cout << "Строка \""; formatPrint(90, userstr); cout << "\" - палиндром";
			}
			else
			{
				cout << "Строка \""; formatPrint(90, userstr); cout << "\" - не палиндром";
			}
		}
		//Вывод самого длинного слова в строке
		if (select == 202)
		{
			cout << "Исходная строка: " << endl;
			formatPrint(105, str);
			setColor(Red, Black);
			cout << "\nСамое длинное слово в строке: \"" << getMaxWord(str) << "\"\t длина слова: " << getMaxWord(str).size() << " символов";
			setColor(White, Black);
		}
		//Вывод самого короткого слова в строке
		if (select == 203)
		{
			cout << "Исходная строка: " << endl;
			formatPrint(105, str);
			setColor(Red, Black);
			cout << "\nСамое короткое слово в строке: \"" << getMinWord(str) << "\"\t длина слова: " << getMinWord(str).size() << " символа(ов)";
			setColor(White, Black);
		}
		//Добавление :) в конец предложения"
		if (select == 204)
		{
			cout << "Исходная строка: " << endl;
			formatPrint(105, str);
			cout << "\nСтрока со смайликами: " << endl;
			formatPrint(105, setSmile(str, ":)"));
		}
		//Вывод всех имен в строке(Карл, Клар)
		if (select == 205)
		{
			cout << "Исходная строка: " << endl;
			formatPrint(105, str);
			cout << "\nВывод имен c \"Карл\", присутствующих в строке: " << endl;
			printVector(getWordsWithRoot(str, "Карл"));
			cout << "\nВывод имен c \"Клар\", присутствующих в строке: " << endl;
			printVector(getWordsWithRoot(str, "Клар"));
		}
		//Реверс слов с тремя и более гласными
		if (select == 206)
		{
			cout << "Исходная строка: " << endl;
			formatPrint(105, str);
			cout << "\nСтрока с реверсом: " << endl;
			formatPrint(105, stringRevers(str, 3));

		}
		// Вспомогательные переменные для фиксирования выбранной позиции меню
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