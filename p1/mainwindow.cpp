#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QObject>
#include <QPushButton>
#include <vector>
#include <string>
#include <algorithm>
#include <QSignalMapper>

using namespace std;
QStandardItemModel* model = new QStandardItemModel();

vector<int> StringToInt(string n1){
    vector<int> c(8);
    for(int i = 0;i < n1.length();i++)
        c[i] = n1[i];
    return c;
}
vector<int> S_Box = {52, 91, 130, 169, 208, 247, 30, 71, 112, 153, 194, 235, 20, 63, 106, 149, 192, 236, 23, 68, 114, 159, 204, 250, 39, 86, 134, 181, 228, 19, 70, 120, 170, 219, 12, 64, 117, 168, 221, 16, 73, 126, 180, 234, 34, 90, 146, 203, 4, 61, 123, 183, 242, 45, 105, 167, 230, 37, 100, 164, 229, 40, 104, 174, 241, 51, 122, 191, 5, 78, 148, 220, 38, 113, 189, 8, 85, 162, 244, 65, 144, 225, 53, 137, 217, 48, 136, 222, 55, 143, 237, 72, 161, 0, 95, 193, 29, 131, 231, 77, 178, 24, 129, 239, 88, 198, 49, 163, 18, 138, 254, 111, 233, 98, 216, 92, 213, 89, 215, 97, 232, 110, 253, 135, 21, 166, 56, 202, 101, 2, 156, 58, 214, 128, 36, 206, 125, 43, 223, 151, 76, 10, 197, 141, 80, 26, 238, 184, 142, 99, 62, 32, 9, 248, 218, 205, 196, 190, 195, 201, 212, 246, 11, 41, 75, 116, 160, 224, 31, 102, 175, 14, 107, 200, 66, 177, 59, 187, 93, 3, 165, 96, 42, 252, 207, 176, 171, 173, 199, 251, 44, 109, 186, 54, 158, 79, 1, 179, 140, 132, 147, 209, 25, 119, 17, 182, 133, 127, 172, 22, 139, 74, 60, 94, 227, 118, 108, 188, 81, 67, 154, 84, 152, 69, 150, 103, 6, 46, 50, 35, 28, 47, 145, 57, 157, 226, 7, 240, 87, 83, 82, 13, 210, 121, 15, 33, 27, 245, 211, 124, 115, 155, 185, 243, 249, 255};
int Inverse_S_Box(int Value)
{
    vector<int>::iterator it = find(S_Box.begin(), S_Box.end(), Value);
    int index = std::distance(S_Box.begin(), it);
    return index;
}
vector<int> BinaryAdd(vector<int> n1, vector<int> n2)
{
    vector<int> n3(8);
    int cy = 0;
    for (int i = 7; i >= 0; i--)
    {
        int sum = n1[i] + n2[i] + cy;
        cy = sum >> 8;
        int index = sum % 256;
        n3[i] = S_Box[index] ;
    }
    return n3;
}
vector<int> BinarySub(vector<int> n3,vector<int> n2)
{
    vector<int> n1(8);
    int br = 0;
    for (int i = 7; i >= 0; i--)
    {
        int sub = Inverse_S_Box(n3[i]) - n2[i] - br;
        if (sub < 0)
        {
            br = 1;
        }
        else
        {
            br = 0;
        }
        n1[i] = sub + (br << 8);
    }
    return n1;
}
vector<int> Rotate(vector<int> n1,vector<int> n2)
{
    vector<int> Rotaten3(8);
    int save0=n1.at(0);
    int save1=n1.at(1);
    for(int i=2;i<8;i++){
        n1.at(i-2)=n1.at(i);
    }
    n1.at(6)=save0;
    n1.at(7)=save1;
    for (int i = 0; i < 8; i++)
    {
        int a = (n1.at(i) ^ n2.at(i)) ^ 0b11111111;
        Rotaten3.at(i)= a;
    }
    return Rotaten3;
}
vector<int> InverseRotate(vector<int> n3,vector<int> n2)
{
    vector<int> InverseRotaten1(8);
    for (int i = 0; i < 8; i++)
    {
        int a = (n3[i] ^ n2[i]) ^ 0b11111111;
        InverseRotaten1[i] = a;
    }
    int save6=InverseRotaten1[6],save7=InverseRotaten1[7];
    for(int i = 5;i>=0;i--){
        InverseRotaten1[i+2]=InverseRotaten1[i];
    }
    InverseRotaten1[0]=save6;
    InverseRotaten1[1]=save7;
    return InverseRotaten1;
}
vector<int> XOR(vector<int> n1, vector<int> n2) {
    vector<int> n3(8);
    for (int i = 7; i >= 0; i--) {
        n3[i] = n1[i] ^ n2[i];
    }
    return n3;
}
QString display(vector<int> n1){
    string n2="";
    char hex[8];
    for(int i=0;i<8;i++){
        itoa(n1[i], hex, 16);
        n2 += hex;
        n2+=" ";
    }
    return QString::fromStdString(n2);
}
QString display2(vector<int> n1){
    string n2="";
    char hex[8];
    for(int i=0;i<8;i++){
        n2+=n1[i];
    }
    return QString::fromStdString(n2);
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i = 0;
//    QStandardItemModel* model = new QStandardItemModel();

    QLineEdit *array_line[8] = {ui->lineEdit,ui->lineEdit_9,ui->lineEdit_14,ui->lineEdit_5,ui->lineEdit_10,ui->lineEdit_12,ui->lineEdit_6,ui->lineEdit_11};
    QString array[18] = {
        "(((p ⊙ k1) ⊕ k3)+ k2)",
        "(((p ⊙ k3) + k2)⊕ k1)",
        "(((p + k2) ⊙ k1)⊕ k3)",
        "(((p + k3) ⊕ k1)⊙ k2)",
        "(((p ⊙ k2) + k3)⊕ k1)",
        "(((p ⊙ k3) + k1)⊕ k2)",
        "(((p ⊕ k1) + k3)⊙ k2)",
        "(((p ⊕ k2) + k3)⊙ k1)",
        "(((p ⊙ k3) ⊕ k2)+ k1)",
        "(((p ⊙ k3) ⊕ k1)+ k2)",
        "(((p ⊕ k3) ⊙ k2)+ k1)",
        "(((p ⊕ k1) ⊙ k3)+ k2)",
        "(((p ⊕ k2) ⊙ k3)+ k1)",
        "(((p ⊙ k1) + k2)⊕ k3)",
        "(((p + k1) ⊙ k2)⊕ k3)",
        "(((p ⊕ k1) + k2)⊙ k3)",
        "(((p ⊕ k2) + k1)⊙ k3)",
        "(((p + k1) ⊙ k3)⊕ k2)"};
    ui->setupUi(this);

    QStringList labels = QString("     ,加密 (key),加密 (key_s),解密 (key),解密 (key_s)").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);
    QStandardItem* item = 0;
    for(i = 0;i < 18;i++)
    {
        item = new QStandardItem(array[i]);
        model->setItem(i,0,item);
    }
    ui->tableView->setModel(model);
    for(i = 0;i < 5;i++)
    {
        ui->tableView->setColumnWidth(i,150);
    }
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->show();
    QPixmap pixmap("C:\\Users\\user\\Downloads\\3405244.png");
    QIcon ButtonIcon(pixmap);
    QSignalMapper * m = new QSignalMapper(this);
    for(i = 0;i < 3;i++)
    {
        QPushButton * k1_button = new QPushButton("",this);
        k1_button->setGeometry(170 + 219 * i,24,20,20);
        k1_button->setFlat(true);
        k1_button->setIcon(ButtonIcon);
        connect(k1_button,SIGNAL(clicked()),m,SLOT(map()));
        m->setMapping(k1_button,i);
    }
    connect(m, SIGNAL(mappedInt(int)),this, SLOT(clear(int)));
    for(i = 1;i < 3;i++)
    {
        int num1 = 24 + 40 * i;
        QPushButton * k1_button = new QPushButton("",this);
        k1_button->setGeometry(170,num1,20,20);
        k1_button->setFlat(true);
        k1_button->setIcon(ButtonIcon);
        connect(k1_button,SIGNAL(clicked()),m,SLOT(map()));
        m->setMapping(k1_button,0 + 3 * i);

        QPushButton * k2_button = new QPushButton("",this);
        k2_button->setGeometry(389,num1,20,20);
        k2_button->setFlat(true);
        k2_button->setIcon(ButtonIcon);
        connect(k2_button,SIGNAL(clicked()),m,SLOT(map()));
        m->setMapping(k2_button,1 + 3 * i);

        if(i != 2)
        {
            QPushButton * k3_button = new QPushButton("",this);
            k3_button->setGeometry(608,num1,20,20);
            k3_button->setFlat(true);
            k3_button->setIcon(ButtonIcon);
            connect(k3_button,SIGNAL(clicked()),m,SLOT(map()));
            m->setMapping(k3_button,2 + 3 * i);
        }
    }
    connect(m, SIGNAL(mappedInt(int)),this, SLOT(clear(int)));

    QPushButton * kcls = new QPushButton("",this);
    kcls->setText("key 清除");
    kcls->setGeometry(700,20,80,30);
    connect(kcls,SIGNAL(clicked()),this,SLOT(k_cls()));

    QPushButton * kscls = new QPushButton("",this);
    kscls->setText("key_s 清除");
    kscls->setGeometry(700,60,80,30);
    connect(kscls,SIGNAL(clicked()),this,SLOT(ks_cls()));

    QPushButton * allCls = new QPushButton("",this);
    allCls->setText("全部清除");
    allCls->setGeometry(700,100,80,30);
    connect(allCls,SIGNAL(clicked()),this,SLOT(all_cls()));

    QPushButton * C = new QPushButton("",this);
    C->setText("加密(key)");
    C->setGeometry(850,170,100,30);
    connect(C,SIGNAL(clicked()),this,SLOT(C()));

    QPushButton * Cs = new QPushButton("",this);
    Cs->setText("加密(key_s)");
    Cs->setGeometry(850,230,100,30);  
    connect(Cs,SIGNAL(clicked()),this,SLOT(Cs()));

    QPushButton * Dc = new QPushButton("",this);
    Dc->setText("解密(key)");
    Dc->setGeometry(850,290,100,30);
    connect(Dc,SIGNAL(clicked()),this,SLOT(Dc()));

    QPushButton * Dcs = new QPushButton("",this);
    Dcs->setText("解密(key_s)");
    Dcs->setGeometry(850,350,100,30);
    connect(Dcs,SIGNAL(clicked()),this,SLOT(Dcs()));
}

void MainWindow::clear(int i)
{
QLineEdit *array_line[8] = {ui->lineEdit,ui->lineEdit_9,ui->lineEdit_14,ui->lineEdit_5,ui->lineEdit_10,ui->lineEdit_12,ui->lineEdit_6,ui->lineEdit_11};
    array_line[i]->setText("");
}
void MainWindow::all_cls()
{
    QLineEdit *array_line[8] = {ui->lineEdit,ui->lineEdit_9,ui->lineEdit_14,ui->lineEdit_5,ui->lineEdit_10,ui->lineEdit_12,ui->lineEdit_6,ui->lineEdit_11};
    for(int i = 0;i < 8;i++)
    {
        array_line[i]->setText("");
    }
}
void MainWindow::k_cls()
{
    QLineEdit *array_line[3] = {ui->lineEdit,ui->lineEdit_5,ui->lineEdit_6};
    for(int i =0;i < 3;i++)
    {
        array_line[i]->setText("");
    }
}
void MainWindow::ks_cls()
{
    QLineEdit *array_line[3] = {ui->lineEdit_9,ui->lineEdit_10,ui->lineEdit_11};
    for(int i =0;i < 3;i++)
    {
        array_line[i]->setText("");
    }
}
void MainWindow::C()
{
    vector<int> k1=StringToInt(ui->lineEdit->text().toStdString());
    vector<int> k2=StringToInt(ui->lineEdit_5->text().toStdString());
    vector<int> k3=StringToInt(ui->lineEdit_6->text().toStdString());
    vector<int> p=StringToInt(ui->lineEdit_14->text().toStdString());
    vector<vector<int>> n = {BinaryAdd(XOR(Rotate(p,k1), k3),k2),
                             XOR(BinaryAdd(Rotate(p,k3), k2),k1),
                             XOR(Rotate(BinaryAdd(p,k2), k1),k3),
                             Rotate(XOR(BinaryAdd(p,k3), k1),k2),
                             XOR(BinaryAdd(Rotate(p,k2), k3),k1),
                             XOR(BinaryAdd(Rotate(p,k3), k1),k2),
                             Rotate(BinaryAdd(XOR(p,k1), k3),k2),
                             Rotate(BinaryAdd(XOR(p,k2), k3),k1),
                             BinaryAdd(XOR(Rotate(p,k3), k2),k1),
                             BinaryAdd(XOR(Rotate(p,k3), k1),k2),
                             BinaryAdd(Rotate(XOR(p,k3), k2),k1),
                             BinaryAdd(Rotate(XOR(p,k1), k3),k2),
                             BinaryAdd(Rotate(XOR(p,k2), k3),k1),
                             XOR(BinaryAdd(Rotate(p,k1), k2),k3),
                             XOR(Rotate(BinaryAdd(p,k1), k2),k3),
                             Rotate(BinaryAdd(XOR(p,k1), k2),k3),
                             Rotate(BinaryAdd(XOR(p,k2), k1),k3),
                             XOR(Rotate(BinaryAdd(p,k1), k3),k2)
                   };
    for(int i=0;i<18;i++){
        model->setData(model->index(i,1),display(n[i]));
    }
}

void MainWindow::Cs()
{
    vector<int> k1=StringToInt(ui->lineEdit_9->text().toStdString());
    vector<int> k2=StringToInt(ui->lineEdit_10->text().toStdString());
    vector<int> k3=StringToInt(ui->lineEdit_11->text().toStdString());
    vector<int> p=StringToInt(ui->lineEdit_14->text().toStdString());
    vector<vector<int>> n = {BinaryAdd(XOR(Rotate(p,k1), k3),k2),
                             XOR(BinaryAdd(Rotate(p,k3), k2),k1),
                             XOR(Rotate(BinaryAdd(p,k2), k1),k3),
                             Rotate(XOR(BinaryAdd(p,k3), k1),k2),
                             XOR(BinaryAdd(Rotate(p,k2), k3),k1),
                             XOR(BinaryAdd(Rotate(p,k3), k1),k2),
                             Rotate(BinaryAdd(XOR(p,k1), k3),k2),
                             Rotate(BinaryAdd(XOR(p,k2), k3),k1),
                             BinaryAdd(XOR(Rotate(p,k3), k2),k1),
                             BinaryAdd(XOR(Rotate(p,k3), k1),k2),
                             BinaryAdd(Rotate(XOR(p,k3), k2),k1),
                             BinaryAdd(Rotate(XOR(p,k1), k3),k2),
                             BinaryAdd(Rotate(XOR(p,k2), k3),k1),
                             XOR(BinaryAdd(Rotate(p,k1), k2),k3),
                             XOR(Rotate(BinaryAdd(p,k1), k2),k3),
                             Rotate(BinaryAdd(XOR(p,k1), k2),k3),
                             Rotate(BinaryAdd(XOR(p,k2), k1),k3),
                             XOR(Rotate(BinaryAdd(p,k1), k3),k2),
                   };
    for(int i=0;i<18;i++){
        model->setData(model->index(i,2),display(n[i]));
    }
}
void MainWindow::Dc()
{
    vector<int> k1=StringToInt(ui->lineEdit->text().toStdString());
    vector<int> k2=StringToInt(ui->lineEdit_5->text().toStdString());
    vector<int> k3=StringToInt(ui->lineEdit_6->text().toStdString());
    string str1 = ui->lineEdit_12->text().toStdString();
    string str = "";
    int num1 = 0;
    vector<int> c(8);
    int j=0;
    for(int i = 0;i < str1.length();i++)
    {
        if(str1[i] != ' ')
        {
            str += str1[i];
        }
        else
        {
            num1=stoi(str, 0, 16);
            c[j++]=num1;
            num1=0;
            str="";
        }
    }
    vector<vector<int>> n = {InverseRotate(XOR(BinarySub(c,k2), k3),k1),
                             InverseRotate(BinarySub(XOR(c,k1), k2),k3),
                             BinarySub(InverseRotate(XOR(c,k3), k1),k2),
                             BinarySub(XOR(InverseRotate(c,k2), k1),k3),
                             InverseRotate(BinarySub(XOR(c,k1), k3),k2),
                             InverseRotate(BinarySub(XOR(c,k2), k1),k3),
                             XOR(BinarySub(InverseRotate(c,k2), k3),k1),
                             XOR(BinarySub(InverseRotate(c,k1), k3),k2),
                             InverseRotate(XOR(BinarySub(c,k1), k2),k3),
                             InverseRotate(XOR(BinarySub(c,k2), k1),k3),
                             XOR(InverseRotate(BinarySub(c,k1), k2),k3),
                             XOR(InverseRotate(BinarySub(c,k2), k3),k1),
                             XOR(InverseRotate(BinarySub(c,k1), k3),k2),
                             InverseRotate(BinarySub(XOR(c,k3), k2),k1),
                             BinarySub(InverseRotate(XOR(c,k3), k2),k1),
                             XOR(BinarySub(InverseRotate(c,k3), k2),k1),
                             XOR(BinarySub(InverseRotate(c,k3), k1),k2),
                             BinarySub(InverseRotate(XOR(c,k2), k3),k1),
                   };
    for(int i=0;i<18;i++){
        model->setData(model->index(i,3),display2(n[i]));
    }
}
void MainWindow::Dcs()
{
    vector<int> k1=StringToInt(ui->lineEdit_9->text().toStdString());
    vector<int> k2=StringToInt(ui->lineEdit_10->text().toStdString());
    vector<int> k3=StringToInt(ui->lineEdit_11->text().toStdString());
    string str1 = ui->lineEdit_12->text().toStdString();
    string str = "";
    int num1 = 0;
    vector<int> c(8);
    int j=0;
    for(int i = 0;i < str1.length();i++)
    {
        if(str1[i] != ' ')
        {
            str += str1[i];
        }
        else
        {
            num1=stoi(str, 0, 16);
            c[j++]=num1;
            num1=0;
            str="";
        }
    }
    vector<vector<int>> n = {InverseRotate(XOR(BinarySub(c,k2), k3),k1),
                             InverseRotate(BinarySub(XOR(c,k1), k2),k3),
                             BinarySub(InverseRotate(XOR(c,k3), k1),k2),
                             BinarySub(XOR(InverseRotate(c,k2), k1),k3),
                             InverseRotate(BinarySub(XOR(c,k1), k3),k2),
                             InverseRotate(BinarySub(XOR(c,k2), k1),k3),
                             XOR(BinarySub(InverseRotate(c,k2), k3),k1),
                             XOR(BinarySub(InverseRotate(c,k1), k3),k2),
                             InverseRotate(XOR(BinarySub(c,k1), k2),k3),
                             InverseRotate(XOR(BinarySub(c,k2), k1),k3),
                             XOR(InverseRotate(BinarySub(c,k1), k2),k3),
                             XOR(InverseRotate(BinarySub(c,k2), k3),k1),
                             XOR(InverseRotate(BinarySub(c,k1), k3),k2),
                             InverseRotate(BinarySub(XOR(c,k3), k2),k1),
                             BinarySub(InverseRotate(XOR(c,k3), k2),k1),
                             XOR(BinarySub(InverseRotate(c,k3), k2),k1),
                             XOR(BinarySub(InverseRotate(c,k3), k1),k2),
                             BinarySub(InverseRotate(XOR(c,k2), k3),k1),
                   };
    for(int i=0;i<18;i++){
        model->setData(model->index(i,4),display2(n[i]));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

