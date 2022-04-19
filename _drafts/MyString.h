/**
* 题目：面试题一：实现MyString,为MyString类添加赋值预算符重载
* 时间：2018-08-04 11:33
* 作者：李祥
* 来源：剑指offer P24
* 难点：赋值操作符参数为常量引用，返回值为*this，返回类型为引用类型（为了连续赋值）
*/


//test git

#include <iostream>
#include <string>

#define INCREASE_STEP 16

class MyString{
public:
	explicit MyString(const char *pData = nullptr);   //构造函数、默认构造函数
	MyString(const MyString& str) :MyString(str.data()){}  //拷贝构造函数
	bool operator==(const MyString& str);  //判等
	MyString& operator=(const MyString& str);   //赋值运算符重载
	const size_t size() const{ return length; }  //取长度
	const char* data() const { return m_pData; }  //取值
	~MyString(void);  //析构函数

private:
	char* m_pData;  //存数据
	size_t length;  //长度
	size_t capacity;  //容量
};


MyString::MyString(const char *pData){
	if (pData == nullptr){
		length = 0;
		capacity = INCREASE_STEP;
		m_pData = new char[capacity];
		memset(m_pData, 0, capacity);
	}
	else{
		length = strlen(pData);
		capacity = (length > INCREASE_STEP) ? (INCREASE_STEP*(length / INCREASE_STEP + 1)) : INCREASE_STEP;
		m_pData = new char[capacity];
		memset(m_pData, 0, capacity);
		strcpy_s(m_pData, length + 1, pData);
	}
}

bool MyString::operator==(const MyString& str){
	return ((length == str.size()) && ((m_pData == nullptr &&nullptr == str.data())
		|| (strcmp(m_pData, str.data()) == 0)) ? true : false);
}

MyString& MyString::operator=(const MyString& str){
	if (this != &str){
		length = str.size();
		capacity = str.capacity;
		if (m_pData != nullptr){
			delete[] m_pData;
			m_pData = nullptr;
		}
		m_pData = new char[capacity];
		memset(m_pData, 0, capacity);
		if (str.data() != nullptr){
			strcpy_s(m_pData, length + 1, str.data());
		}
	}
	return *this;

}

MyString::~MyString(){
	if (m_pData != nullptr){
		delete m_pData;
		m_pData = nullptr;
	}
}


/////////////////////////////////////////////////////////////////
// test

void testMyString(){

	std::cout << "\n------------------------------------test MyString------------------------------------" << std::endl;
	MyString myStr1("123456");
	MyString myStr2(myStr1);
	MyString myStr3 = myStr2;
	MyString myStr4;
	myStr4 = myStr1 = myStr2 = myStr3;

	std::cout << "myStr1\n  length:" << myStr1.size() << "\n  content:"
		<< myStr2.data() << std::endl;
	std::cout << "myStr2\n  length:" << myStr2.size() << "\n  content:"
		<< myStr2.data() << std::endl;
	std::cout << "myStr3\n  length:" << myStr3.size() << "\n  content:"
		<< myStr3.data() << std::endl;
	std::cout << "myStr4\n  length:" << myStr4.size() << "\n  content:"
		<< myStr4.data() << std::endl;

	MyString myStr5;
	myStr5 = myStr5;
	std::cout << "myStr5;\n  length:" << myStr5.size() << "\n  content:"
		<< myStr5.data() << std::endl;
}