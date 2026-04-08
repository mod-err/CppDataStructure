#include "manager.h"

//默认构造
Manager::Manager() {

}

//有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
    this->initVector();

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "机房文件不存在！" << endl;
        return;
    }
    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum) {
        vCom.push_back(c);
    }
    //cout << "当前机房数量为： " << vCom.size() << endl;
    ifs.close();
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
    bool ret = false;

    int id;
    string name;
    string pwd;

    string fileName;

    while (true) {
        cin >> select;

        switch (select) {
        case 1:
            fileName = STUDENT_FILE;
        LABLE_ID:
            cout << "请输入学生学号：" << endl;
            cin >> id;
            ret = checkRepeat(id, select);
            if (ret) {
                cout << "学号重复，请重新输入！" << endl;
                goto LABLE_ID;
            }
            goto LABLE_OTHER;
            break;
        case 2:
            fileName = TEACHER_FILE;
        LABLE_EMPID:
            cout << "请输入老师职工编号：" << endl;
            cin >> id;
            ret = checkRepeat(id, select);
            if (ret) {
                cout << "职工编号重复，请重新输入！" << endl;
                goto LABLE_EMPID;
            }
            goto LABLE_OTHER;
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

 LABLE_OTHER:
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

    this->initVector();
}

//遍历输出学生信息
void printStudent(Student& s) {
    cout << "学号： " << s.m_Id << "\t姓名： " << s.m_Name << "\t密码： " << s.m_Pwd << endl;
}

//遍历输出老师信息
void printTeacher(Teacher& t) {
    cout << "职工编号： " << t.m_EmpId << "\t姓名： " << t.m_Name << "\t密码： " << t.m_Pwd << endl;
}

//查看账号
void Manager::showPerson() {
    int select = 0;

    while (true) {
        cout << "请选择查看内容：" << endl;
        cout << "1、查看所有学生" << endl;
        cout << "2、查看所有老师" << endl;

        cin >> select;

        if (select == 1) {
            cout << "所有学生信息如下： " << endl;
            for_each(vStu.begin(), vStu.end(), printStudent);
            break;
        }
        else if (select == 2) {
            cout << "所有老师信息如下： " << endl;
            for_each(vTea.begin(), vTea.end(), printTeacher);
            break;
        }
        else {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
        }
    }
    system("pause");
    system("cls");
}

//查看机房信息
void Manager::showComputer() {
    cout << "机房信息如下： " << endl;
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "机房编号： " << it->m_ComId << "\t机房最大容量： " << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}

//清空预约记录
void Manager::cleanFile() {
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::trunc);//先删除再创建
    cout << "清空成功！" << endl;

    system("pause");
    system("cls");
}

//初始化容器
void Manager::initVector() {
    //先清空容器
    this->vStu.clear();
    this->vTea.clear();

    //读取学生信息
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "学生文件不存在！" << endl;
        return;
    }
    Student s; 
    //vector存的是拷贝后的新对象，和临时对象s无关，Student s;放在循环内增加构造和析构次数
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
        vStu.push_back(s);
    }
    //cout << "当前学生数量为： " << vStu.size() << endl;
    ifs.close();

    //读取老师信息
    ifs.open(TEACHER_FILE, ios::out);
    if (!ifs.is_open()) {
        cout << "老师文件不存在！" << endl;
        return;
    }
    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
        vTea.push_back(t);
    }
    //cout << "当前老师数量为： " << vTea.size() << endl;
    ifs.close();
}

//检测重复
bool Manager::checkRepeat(int id, int type) {
    if (type == 1) {
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
            if (it->m_Id == id) {
                return true;
            }
        }
    }
    else {
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
            if (it->m_EmpId == id) {
                return true;
            }
        }
    }
    return false;
}