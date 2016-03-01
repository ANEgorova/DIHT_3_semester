#include <istream>
#include <iostream>
#include <string.h>
#include "mystring.h"

CString::CString(){//����������� �� ���������
		buffer = new char[InitialSize];
		buffersize = InitialSize;
		realsize = InitialSize;
	}

CString::CString(int initialsize) { //����������� � ��������� ��������
		buffer = new char[initialsize];
		buffersize = initialsize;
		realsize = initialsize;
	}

CString::CString(char* string){// ����������� � char*
		int t = strlen(string);
		buffer = new char[sizeof(char) * t];
		buffersize = sizeof(char) * t;
		realsize = strlen(string);
		for (size_t i = 0; i < t; i++)
		{
			buffer[i] = string[i];
		}
	}

CString::CString(std::string string) {// ����������� �� std::string
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

CString::~CString(){//����������
		delete[] this->buffer;
	}

	void CString::swap(CString &string) { // swap
		std::swap(buffer, string.buffer);
		std::swap(buffersize, string.buffersize);
		std::swap(realsize, string.realsize);
	}

	CString::CString(const CString& arr){ //����������� �����������
		this->realsize = arr.realsize;
		this->buffersize = arr.buffersize;
		this->buffer = new char[this->buffersize];
		std::memcpy(this->buffer, arr.buffer, arr.buffersize*sizeof(char));
	}

	std::istream & operator >> (std::istream &stream, CString& arr){//����
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

	std::ostream & operator << (std::ostream &stream, CString& arr) { // �����
		for (int i = 0; i < arr.realsize; i++) {
			stream << arr.buffer[i];
		}
		return stream;
	}

	CString CString::operator +(const CString& string){//�������� +
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

	bool & CString::operator <(CString& string){ //�������� <
		bool result = false;
		int i = 0;
		for (i = 0; (i < string.realsize) && (i < this->realsize); i++) { // ������������ ��������� �����
			if (string.buffer[i] > this->buffer[i]) {
				result = true;
				break;
			}
			if (string.buffer[i] < this->buffer[i]) {
				result = false;
				break;
			}
		}
		if (i == this->realsize) { // ���� ��� ����� ������ ��������� � ������� ������, �� ������ � ������� ������ ��������� �������
			result = true;
		}
		if (i == string.realsize) {
			result = false;
		}
		// ���� ������ �����, �� ��������� ����� false
		return result;
	}

	CString& CString::operator = (CString string){//�������� ������������ �������
		swap(string);
		return *this;
	}

	CString CString::operator = (char* string){//�������� ������������ ������
		this->realsize = strlen(string);
		for (size_t i = 0; i < this->realsize; i++)
		{
			this->buffer[i] = string[i];
		}
		return *this;
	}

	void CString::PutMiddle(char whatins){// ������� � ��������

		this->realsize = this->realsize + 1; //���������� ������� ����� �� 1
		char* bufa = new char[this->buffersize * 2]; //�������� ������ ������, � ��������, �������� + �� 1 ������
		std::memcpy(bufa, this->buffer, sizeof(char)*(this->buffersize)); //����������� ����� � �����

		char change;
		if (realsize % 2 == 0){
			change = bufa[(this->realsize - 1) / 2]; //��������� ������ ����������
			bufa[(this->realsize - 1) / 2] = whatins; //��������� � ��������
			for (size_t i = this->realsize / 2; i < realsize; i++) //������� ��� �������� ������
			{
				char k = bufa[i];
				bufa[i] = change;
				change = k;
			}
		}
		else {
			char change = bufa[(this->realsize) / 2]; //��������� ���������� ������
			bufa[(this->realsize) / 2] = whatins; //��������� � ��������
			for (size_t i = (this->realsize) / 2 + 1; i < this->realsize; i++) //������� ��� �������� ������
			{
				char k = bufa[i];
				bufa[i] = change;
				change = k;
			}
		}
		delete[] this->buffer;
		this->buffer = bufa;  //����������� ������ �� �����	
		this->buffersize = this->buffersize * 2;
	}

	void CString::PutEnd(char whatins){ //������� � �����
		this->realsize = this->realsize + 1; //���������� ������� ����� �� 1
		char* bufa = new char[this->buffersize * 2]; //�������� ������ ������, � ��������, �������� + �� 1 ������
		std::memcpy(bufa, this->buffer, sizeof(char)*(buffersize)); //����������� ����� � �����
		bufa[this->realsize - 1] = whatins;//������� �������� � �����
		delete[] this->buffer;
		this->buffer = bufa;  //����������� ������ �� �����	
		this->buffersize = this->buffersize * 2;
	}

	char CString::GetToIndex(int index){// ��������� ����� �� �������
		return this->buffer[index];
	}

	void CString::RemoveEnd(){//�������� ��������� �����
		this->realsize = this->realsize - 1;//���������� ������� �����
	}