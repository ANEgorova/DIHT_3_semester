#include <istream>
#include <iostream>
#include <string.h>
#include "mystring.h"

CString::CString(){//конструктор по умолчанию
		buffer = new char[InitialSize];
		buffersize = InitialSize;
		realsize = InitialSize;
	}

CString::CString(int initialsize) { //конструктор с начальным размером
		buffer = new char[initialsize];
		buffersize = initialsize;
		realsize = initialsize;
	}

CString::CString(char* string){// конструктор с char*
		int t = strlen(string);
		buffer = new char[sizeof(char) * t];
		buffersize = sizeof(char) * t;
		realsize = strlen(string);
		for (size_t i = 0; i < t; i++)
		{
			buffer[i] = string[i];
		}
	}

CString::CString(std::string string) {// конструктор из std::string
		int t = 0;
		char c = ' ';
		while (c != '\0'){
			c = string[t];
			t++;
		}
		t--;
		this->buffersize = sizeof(char) * t;
		this->realsize = t;
		buffer = new char[sizeof(char) * t];
		for (size_t i = 0; i < t; i++)
		{
			buffer[i] = string[i];
		}
	}

CString::~CString(){//деструктор
		delete[] this->buffer;
	}

	void CString::swap(CString &string) { // swap
		std::swap(buffer, string.buffer);
		std::swap(buffersize, string.buffersize);
		std::swap(realsize, string.realsize);
	}

	CString::CString(const CString& arr){ //конструктор копирования
		this->realsize = arr.realsize;
		this->buffersize = arr.buffersize;
		this->buffer = new char[this->buffersize];
		std::memcpy(this->buffer, arr.buffer, arr.buffersize*sizeof(char));
	}

	std::istream & operator >> (std::istream &stream, CString& arr){//ввод
		char currentChar = 0;
		stream >> currentChar;
		int i = 0;
		while (currentChar != '0') {
			arr.buffer[i] = currentChar;
			i++;
			stream >> currentChar;
		}
		arr.buffersize = i;
		arr.realsize = i;
		return stream;
	}

	std::ostream & operator << (std::ostream &stream, CString& arr) { // вывод
		for (int i = 0; i < arr.realsize; i++) {
			stream << arr.buffer[i];
		}
		return stream;
	}

	CString CString::operator +(const CString& string){//оператор +
		CString result((this->realsize + string.realsize) * sizeof(char));
		int i = 0;
		for (i; i < this->realsize; i++) {
			result.buffer[i] = this->buffer[i];
		}
		int k = i;
		for (i; i < string.realsize + k; i++) {
			result.buffer[i] = string.buffer[i - k];
		}
		return result;
	}

	bool & CString::operator <(CString& string){ //оператор <
		bool result = false;
		int i = 0;
		for (i = 0; (i < string.realsize) && (i < this->realsize); i++) { // посимвольное сравнение строк
			if (string.buffer[i] > this->buffer[i]) {
				result = true;
				break;
			}
			if (string.buffer[i] < this->buffer[i]) {
				result = false;
				break;
			}
		}
		if (i == this->realsize) { // если все одной строки совпадают с началом другой, то строка с меньшей длиной считается меньшей
			result = true;
		}
		if (i == string.realsize) {
			result = false;
		}
		// если строки равны, то результат будет false
		return result;
	}

	CString& CString::operator = (CString string){//оператор присваивания объекта
		swap(string);
		return *this;
	}

	CString CString::operator = (char* string){//оператор присваивания строки
		this->realsize = strlen(string);
		for (size_t i = 0; i < this->realsize; i++)
		{
			this->buffer[i] = string[i];
		}
		return *this;
	}

	void CString::PutMiddle(char whatins){// вставка в середину

		this->realsize = this->realsize + 1; //увеличение размера сроки на 1
		char* bufa = new char[this->buffersize * 2]; //создание буфера строки, с размером, исходный + на 1 символ
		std::memcpy(bufa, this->buffer, sizeof(char)*(this->buffersize)); //копирование всего в буфер

		char change;
		if (realsize % 2 == 0){
			change = bufa[(this->realsize - 1) / 2]; //сохраняем символ посередине
			bufa[(this->realsize - 1) / 2] = whatins; //вставляем в середину
			for (size_t i = this->realsize / 2; i < realsize; i++) //смещаем все элементы вправо
			{
				char k = bufa[i];
				bufa[i] = change;
				change = k;
			}
		}
		else {
			char change = bufa[(this->realsize) / 2]; //сохраняем серединный символ
			bufa[(this->realsize) / 2] = whatins; //вставляем в середину
			for (size_t i = (this->realsize) / 2 + 1; i < this->realsize; i++) //смещаем все элементы вправо
			{
				char k = bufa[i];
				bufa[i] = change;
				change = k;
			}
		}
		delete[] this->buffer;
		this->buffer = bufa;  //копирование строки на место	
		this->buffersize = this->buffersize * 2;
	}

	void CString::PutEnd(char whatins){ //вставка в конец
		this->realsize = this->realsize + 1; //увеличение размера сроки на 1
		char* bufa = new char[this->buffersize * 2]; //создание буфера строки, с размером, исходный + на 1 символ
		std::memcpy(bufa, this->buffer, sizeof(char)*(buffersize)); //копирование всего в буфер
		bufa[this->realsize - 1] = whatins;//вставка элемента в конец
		delete[] this->buffer;
		this->buffer = bufa;  //копирование строки на место	
		this->buffersize = this->buffersize * 2;
	}

	char CString::GetToIndex(int index){// получение буквы по индексу
		return this->buffer[index];
	}

	void CString::RemoveEnd(){//удаление последней буквы
		this->realsize = this->realsize - 1;//уменьшение размера сроки
	}