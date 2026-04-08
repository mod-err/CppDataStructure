#include "student.h"

//默认构造
Student::Student() {

}

//有参构造
Student::Student(int id, string name, string pwd) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//操作菜单
void Student::operMenu() {
    cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.申请预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.查看我的预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.查看所有预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.取消预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder() {

}

//查看我的预约
void Student::showMyOrder() {

}

//查看所有预约
void Student::showAllOrder() {

}

//取消预约
void Student::cancelOrder() {

}