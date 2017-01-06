#include "mycombobox.h"

myComboBox::myComboBox(QWidget* w) : QComboBox(w)
{}

void myComboBox::slot_setList(QStringList list)
{
    clear();
    addItems(list);
}

myComboBox::~myComboBox()
{}
