#ifndef CLEAR_BUTTON_H
#define CLEAR_BUTTON_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
class clear_button : public QWidget
{
    Q_OBJECT
public:
    clear_button(QWidget *parent = nullptr);
signals:
    void clicked(QLineEdit *l = nullptr);
protected:
    void mousePressEvent(QMouseEvent *e) override;
//public slots:
//    void get(QLineEdit *l = nullptr);
};
clear_button::clear_button(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *button = new QPushButton("", this);
    QPushButton *button1 = new QPushButton("",this);
    connect(button, &QPushButton::clicked, this, &clear_button::clicked);
}
//void clear_button::get(QLineEdit *l)
//{
//    l->setText("");
//}

#endif // CLEAR_BUTTON_H
