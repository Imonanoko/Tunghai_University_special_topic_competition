#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
//    void get(QLineEdit *l = nullptr);
    void clear(int);
    void k_cls();
    void ks_cls();
    void all_cls();
    void C1();
    void C2();
    void Cks();
    void Dcs();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
