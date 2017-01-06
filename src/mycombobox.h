#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>

class myComboBox : public QComboBox
{
    Q_OBJECT
public:
    myComboBox(QWidget* w);
    ~myComboBox();
public slots:
    void slot_setList(QStringList);
};

#endif // MYCOMBOBOX_H
