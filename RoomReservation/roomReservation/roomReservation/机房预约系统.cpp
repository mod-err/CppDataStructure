#include<iostream>
#include<fstream>
#include"globalFile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;

//登录函数
void LoginIn(string filename, int type);
//管理员菜单
void ManagerMenu(Identity* person);
//学生菜单
void StudentMenu(Identity* person);

int main() {

    int select = 0;

    while (true) {

        cout << "=================  欢迎来到传智播客机房预约系统  ================" << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学生代表           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.老    师           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管 理 员           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退    出           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "输入您的选择: ";

        cin >> select;

        switch (select) {
            case 1:
                //学生代表
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:
                //老师
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:
                //管理员
                LoginIn(ADMIN_FILE, 3);
                break;
            case 0:
                cout << "欢迎下次使用！" << endl;
                system("pause");
                exit(0);
                break;
            default:
                cout << "输入有误，请重新输入！" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    system("pause");
    return 0;
}

//登录函数
void LoginIn(string filename, int type) {

    //父类指针指向子类对象
    Identity* person = NULL;

    //读文件
    ifstream ifs;
    ifs.open(filename, ios::in);

    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    int id = 0;
    string name = "";
    string pwd = "";

    if (type == 1) {
        cout << "请输入您的学号" << endl;
        cin >> id;
    }
    else if (type == 2) {
        cout << "请输入您的职工号" << endl;
        cin >> id;
    }

    cout << "请输入用户名" << endl;
    cin >> name;
    cout << "请输入密码" << endl;
    cin >> pwd;

    if (type == 1) {
        //学生登录验证
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            //cout << fId << " " << fName << " " << fPwd << endl;
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "学生验证登录成功！" << endl;
                system("pause");
                system("cls");
                //创建学生对象，进入学生操作界面
                person = new Student(id, name, pwd);

                StudentMenu(person);

                //终止登录函数的执行
                return;
            }
        }
    }
    else if (type == 2) {
        //老师登录验证
        int fId = 0;
        string fName = "";
        string fPwd = "";
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            //cout << fId << " " << fName << " " << fPwd << endl;
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "老师验证登录成功！" << endl;
                system("pause");
                system("cls");
                //创建老师对象，进入老师操作界面
                person = new Teacher(id, name, pwd);


                //终止登录函数的执行
                return;
            }
        }
    }
    else if (type == 3) {
        //管理员登录验证
        string fName = "";
        string fPwd = "";
        while (ifs >> fName && ifs >> fPwd) {
            //cout << fName << " " << fPwd << endl;
            if (fName == name && fPwd == pwd) {
                cout << "管理员验证登录成功！" << endl;
                system("pause");
                system("cls");
                //创建管理员对象，进入管理员操作界面
                person = new Manager(name, pwd);

                ManagerMenu(person);//传入指针

                //终止登录函数的执行
                return;
            }
        }
    }
    ifs.close();

    cout << "登录失败！" << endl;
    system("pause");
    system("cls");
}

//管理员菜单
void ManagerMenu(Identity* person) { //拷贝指针变量本身
    
    int select = 0;

    while (true) {
        //显示管理员菜单
        person->operMenu();
        //父类指针强制转为子类指针
        Manager* manager = (Manager*)person;

        cin >> select;

        switch (select) {
        case 1:
            //添加账号
            manager->addPerson();
            break;
        case 2:
            //查看账号
            manager->showPerson();
            break;
        case 3:
            //查看机房信息
            manager->showComputer();
            break;
        case 4:
            //清空预约记录
            manager->cleanFile();
            break;
        case 0:
            //注销登录
            cout << "注销登录成功！" << endl;
            system("pause");
            system("cls");
            return;
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

//学生菜单
void StudentMenu(Identity* person) {
    
    int select = 0;

    while (true) {
        person->operMenu();

        Student* student = (Student*)person;

        cin >> select;

        switch (select) {
        case 1:
            //申请预约
            student->applyOrder();
            break;
        case 2:
            //查看自身预约
            student->showMyOrder();
            break;
        case 3:
            //查看所有预约
            student->showAllOrder();
            break;
        case 4:
            //取消预约
            student->cancelOrder();
            break;
        case 0:
            //注销登录
            cout << "注销登录成功！" << endl;
            system("pause");
            system("cls");
            return;
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}