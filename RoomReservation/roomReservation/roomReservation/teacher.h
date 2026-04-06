#pragma once
#include "identity.h"

using namespace std;

class Teacher : public Identity {
public:
	//默认构造
	Teacher();
	//有参构造
	Teacher(int id, string name, string pwd);
	//操作菜单
	void operMenu();
	//查看所有预约
	void showAllOrder();
	//审核预约
	void validOrder();
	//职工号
	int m_EmpId;
};