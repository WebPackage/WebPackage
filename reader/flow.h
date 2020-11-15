#ifndef FLOW_H
#define FLOW_H

#include <QMainWindow>

namespace Ui {
class Flow;
}

class Flow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Flow(QWidget *parent = nullptr);
    ~Flow();

private slots:
    void on_actionImport_triggered();

    void on_InfoButton_clicked();

    void on_startButton_clicked();

    void on_actionExport_triggered();

    void on_actionDelete_triggered();

    void on_actionRefresh_triggered();

private:
    Ui::Flow *ui;
};

#endif // FLOW_H
