//
// Created by Paula on 6/19/2023.
//

#include "GUI.h"

void GUI::init() {
    setLayout(main);

    QVBoxLayout* buto=new QVBoxLayout;
    main->addLayout(buto);
    buto->addWidget(intinerire);
    buto->addWidget(imbatranire);
    buto->addWidget(sterge);
    buto->addWidget(new QLabel("--------------"));
    buto->addWidget(undo);
    buto->addWidget(redo);

    t1->setModel(m1);
    main->addWidget(t1);
}

void GUI::reloadTable() {
    m1->setStudents(this->service.listaStudentiSortati());
}

void GUI::connect() {
    QObject::connect(this->intinerire,&QPushButton::clicked,[&](){
        this->service.intinerireStudenti();

        reloadTable();
    });
    QObject::connect(this->imbatranire,&QPushButton::clicked,[&](){
        this->service.imbatranireStudenti();


        reloadTable();
    });

    QObject::connect(t1->selectionModel(), &QItemSelectionModel::currentChanged, [&](const QModelIndex& current, const QModelIndex& previous) {
        if (current.isValid()) {
            Student selectedStudent = m1->getStudent(current);
            auto DeSters=selectedStudent.getNrmatricol();
            QObject::connect(this->sterge,&QPushButton::clicked,[=](){
                this->service.stergeStudent(DeSters);
                reloadTable();
                t1->clearSelection();
            });

        }
    });

    QObject::connect(this->undo,&QPushButton::clicked,[&](){
        try{
        this->service.undo();
        }
        catch(std::invalid_argument&msg){
            auto mesaj=QString::fromStdString(msg.what());
            QMessageBox::information(nullptr,"Eroare!",mesaj);
            close();
        }
        reloadTable();
    });
    QObject::connect(this->redo,&QPushButton::clicked,[&](){
        try{
            this->service.redo();
        }
        catch(std::invalid_argument&msg){
            auto mesaj=QString::fromStdString(msg.what());
            QMessageBox::information(nullptr,"Eroare!",mesaj);
            close();
        }
        reloadTable();
    });


}
