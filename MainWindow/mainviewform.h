#ifndef MAINVIEWFORM_H
#define MAINVIEWFORM_H

#include <QWidget>

namespace Ui {
class MainViewForm;
}

class MainViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainViewForm(QWidget *parent = 0);
    ~MainViewForm();

private:
    Ui::MainViewForm *ui;
};

#endif // MAINVIEWFORM_H
