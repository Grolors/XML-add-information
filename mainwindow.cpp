#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::showXML(const QDomNode & domE)
{
    QDomNode domNode = domE.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()){
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()){
                if ( domElement.tagName( ) == "man")
                    ui->textEdit->append("");
                else {
                    ui->textEdit->append(domElement.tagName()+": "+domElement.text());

                }
            }
        }
        showXML(domNode);
        domNode = domNode.nextSibling();
    }
}

void MainWindow::addElem( QDomElement & domElem , QDomDocument & docD)
{
    QDomElement domElementMan = docD.createElement("man");
    QDomElement domElementAge = docD.createElement("age");
    QDomElement domElementName = docD.createElement("name");
    QDomText txtAge =docD.createTextNode(age);
    QDomText txtName =docD.createTextNode(name);

    domElementMan.appendChild(domElementAge);
    domElementMan.appendChild(domElementName);
    domElementAge.appendChild(txtAge);
    domElementName.appendChild(txtName);

    domElem.appendChild(domElementMan);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenXML_triggered()
{
    QDomDocument dom;
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QFile::ReadOnly)) return;
    if(!dom.setContent(&file)) return;
    QDomElement elem = dom.documentElement();
    showXML(elem);
    file.close();
}



void MainWindow::on_actionadd_triggered()
{


    bool ok;
     name  = QInputDialog::getText(this,
                                 "Введите текст",
                                 "Имя",
                                 QLineEdit::Normal,
                                 "John", &ok);

    if (!ok || name.isEmpty()) return;


    bool ok2;
     age  = QInputDialog::getText(this,
                                 "Введите текст",
                                 "Возраст",
                                 QLineEdit::Normal,
                                 "11", &ok2);

    if (!ok2 || age.isEmpty()) return;


    QDomDocument doc;
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QFile::ReadWrite )) return;
    if(!doc.setContent(&file)) return;
    QDomElement domElement = doc.documentElement();

    addElem(domElement, doc);
    file.resize(0);
    QTextStream(&file) << doc.toString();
    file.close();


}


