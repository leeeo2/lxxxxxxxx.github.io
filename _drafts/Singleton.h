/**
* 题目：面试题二：C++实现singleton模式
* 时间：2018-08-05 16:13
* 作者：李祥
* 来源：剑指offer P31
* 难点：线程安全性
*/

#include <iostream>
#include <mutex>

///懒汉模式：在需要实例的时候创建，只创建一次
///首先判断实例是否存在，如果不存在，则加锁，防止其他线程同时在创建线程，
///然后再判断一次实例是否存在，防止在加锁过程中其他进程以及创建好了一个实例，
///如果不存在，就new一个实例
class Singleton1{
public:
	static Singleton1* GetInstance(){
		if (instance == nullptr){
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr){
				instance = new Singleton1;
			}
		}
		return instance;
	}
	
private:
	Singleton1(){}
	Singleton1(Singleton1 &s) = delete;

private:
	static Singleton1* instance;
	static std::mutex mtx;
};

Singleton1* Singleton1::instance = nullptr;
std::mutex Singleton1::mtx;


///饿汉模式：在编译的时候就创建好实例
///由于在编译时就创建好了实例，所以就不存在运行是不同线程重复创建实例的情况，所以是线程安全的
class Singleton2{
public:
	static Singleton2* GetInstance(){
		return instance;
	}

private:
	Singleton2(){}
	Singleton2(Singleton2 &s) = delete;

private:
	static Singleton2* instance;
};

Singleton2* Singleton2::instance = new Singleton2;



////////////////////////////////////////////////////////////////////
//  test

void testSingleton(){
	std::cout << "\n------------------------------------test Singleton------------------------------------" << std::endl;

	Singleton1* single1 = Singleton1::GetInstance();
	std::cout << "instance1 offset: " << single1 << std::endl;
	std::cout << "instance2 offset: " << Singleton1::GetInstance() << std::endl;

	Singleton2* single2 = Singleton2::GetInstance();
	std::cout << "instance1 offset: " << single2 << std::endl;
	std::cout << "instance2 offset: " << Singleton2::GetInstance() << std::endl;
}