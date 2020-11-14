#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::info *ui;
};

#endif // INFO_H
