//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_GUI_H
#define EXAMENPRACTIC_GUI_H

#include <QMouseEvent>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QSignalMapper>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <QString>
#include <QMessageBox>
#include <QTableWidget>
#include <vector>
#include <string>
#include "Service.h"
#include <QComboBox>
#include <QModelIndex>
#include <QBrush>
#include "MyTableWidget.h"
#include <QPainter>
#include <QTableView>
#include <QListView>
#include <iostream>
#include <qdebug.h>



class GUI:public QWidget{
    Q_OBJECT
private:
    //Service
    Service service;
    MyTableModel* m1=new MyTableModel(service);
    QTableView* t1= new QTableView;
    QHBoxLayout* main=new QHBoxLayout;

    QPushButton* intinerire=new QPushButton("Intinerire");
    QPushButton* imbatranire=new QPushButton("Imbatranire");

    QPushButton* sterge=new QPushButton("Sterge");


    QPushButton* undo=new QPushButton("Undo");
    QPushButton* redo=new QPushButton("Redo");

    //definesc 1 pentru intinerire,2 pentru imbatranire, 3 pentru stergere

public:
    GUI(Service& service): service{service}{
        init();
        connect();
    }
    ~GUI()=default;

    /*
     * Functie de initializare a ferestrei
     */
    void init();

    /*
     * Conectarea butoanelor si a selectiei tabelei
     */
    void connect();

    /*
     * Functia de reload a tabelei
     */
    void reloadTable();
};

#endif //EXAMENPRACTIC_GUI_H
