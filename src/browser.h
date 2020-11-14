#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>

namespace Ui {
class Browser;
}

class Browser : public QMainWindow
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = nullptr);
    ~Browser();

private slots:
    void on_actionClose_triggered();

private:
    Ui::Browser *ui;
};

#endif // BROWSER_H
