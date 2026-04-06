#include "manager.h"

//默认构造
Manager::Manager() {

}

//有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//操作菜单
void Manager::operMenu() {
    cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

//添加账号
void Manager::addPerson() {
    cout << "请输入添加账号的类型" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;

    int select = 0;

    int id;
    string name;
    string pwd;

    string fileName;

    while (true) {
        cin >> select;

        switch (select) {
        case 1:
            fileName = STUDENT_FILE;
            cout << "请输入学生学号：" << endl;
            cin >> id;
            goto LABLE;
            break;
        case 2:
            fileName = TEACHER_FILE;
            cout << "请输入老师职工编号：" << endl;
            cin >> id;
            goto LABLE;
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

 LABLE:
    cout << "请输入姓名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;
    cout << "添加成功" << endl;

    ofstream ofs;
    ofs.open(fileName, ios::out | ios::app);//追加方式写文件

    ofs << id << " " << name << " " << pwd << endl;

    ofs.close();

    system("pause");
    system("cls");
}

//查看账号
void Manager::showPerson() {

}

//查看机房信息
void Manager::showComputer() {

}

//清空预约记录
void Manager::cleanFile() {

}