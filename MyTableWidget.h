//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_MYTABLEWIDGET_H
#define EXAMENPRACTIC_MYTABLEWIDGET_H

#include <QAbstractTableModel>
#include <vector>
#include <QAbstractItemView>
#include <iostream>
#include "Student.h"
#include "Service.h"

class MyTableModel : public QAbstractTableModel {
    Service service;
    std::vector<Student> students;
public:
    MyTableModel(Service&service) : service{service} {
        students=service.listaStudentiSortati();
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return students.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Student st = students[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(std::to_string(st.getNrmatricol()));
            }
            if (index.column() == 1) {
                return QString::fromStdString(st.getNume());
            }
            if (index.column() == 2) {
                return QString::fromStdString(std::to_string(st.getVarsta()));
            }
            if (index.column() == 3) {
                return QString::fromStdString(st.getFacultate());}
        }
        else if (role == Qt::BackgroundRole) {
            Student t = students[index.row()];
            if (t.getFacultate() == "mate") {
                return QBrush(QColor(255, 0, 0)); // rosu pentru mate
            }
            if (t.getFacultate() == "mate-info") {
                return QBrush(QColor(255, 255, 0)); // galben pentru mate-info
            }
            if (t.getFacultate() == "info") {
                return QBrush(QColor(0, 255, 0)); // verde pentru info
            }
            if (t.getFacultate() == "ai") {
                return QBrush(QColor(0, 0, 255)); // albastru pentru ai
            }

        }
        return QVariant{};

    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (orientation == Qt::Horizontal) {
            if (role == Qt::DisplayRole)
                switch (section) {
                    case 0:
                        return "nrmatricol";
                        break;
                    case 1:
                        return "nume";
                        break;
                    case 2:
                        return "varsta";
                        break;
                    case 3:
                        return "facultate";
                        break;
                    default:
                        return QString("Column %1").arg(section + 1);
                        break;
                }
        } else if (orientation == Qt::Vertical) {
            if (role == Qt::DisplayRole)
                return section + 1;
        }

        return QVariant();
    }

    Student getStudent(const QModelIndex &index) {
        return students[index.row()];
    }

    void setStudents(std::vector<Student> studs) {
        this->students = studs;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);//notify ca la observer
        emit layoutChanged();
    }

};


#endif //EXAMENPRACTIC_MYTABLEWIDGET_H
