#include <istream>
#include <iostream>
#include <string.h>

const int InitialSize = 10;

class CString
{
public:
	CString();

	CString(int initialsize); 		

	CString(char* string);	

	CString(std::string string);
	
	~CString();
		
	void CString::swap(CString &string);
	
	CString(const CString& arr); 

	friend std::istream & operator >> (std::istream &stream, CString& arr);
	
	friend std::ostream &operator << (std::ostream &stream, CString& arr); 

	CString operator +(const CString& string);

	bool &operator <(CString& string); 

	CString& operator = (CString string);

	CString operator = (char* string);

	void PutMiddle(char whatins);

	void PutEnd(char whatins); 

	char GetToIndex(int index);

	void RemoveEnd();

private:
	char* buffer;
	int buffersize; 
	int realsize;
};
