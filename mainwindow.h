#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window2.h"
#include <QtWidgets>
#include <QtXml>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showXML(const QDomNode &);
    void addElem( QDomElement &, QDomDocument &);
    QString name;
    QString age;




    ~MainWindow();

private slots:
    void on_actionOpenXML_triggered();

    void on_actionadd_triggered();




private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
