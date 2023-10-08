//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_STUDENT_H
#define EXAMENPRACTIC_STUDENT_H
#include <string>

class Student{
private:
    int nrmatricol;
    std::string nume;
    int varsta;
    std::string facultate;
public:
    /*
     * Constructor Student
     */
    Student(int nrmatricol,std::string nume,int varsta,std::string facultate):nrmatricol{nrmatricol},nume{nume},varsta{varsta},facultate{facultate}{}

    /*
     * Destructor Student
     */
    ~Student()=default;

    /*
     * Getters si Setters
     */
    int getNrmatricol(){
        return this->nrmatricol;
    }

    void setNrmatricol(int nrmatricol){
        this->nrmatricol=nrmatricol;
    }

    std::string getNume(){
        return this->nume;
    };

    void setNume(std::string nume){
        this->nume=nume;
    }

    int getVarsta(){
        return this->varsta;
    }

    void setVarsta(int varsta){
        this->varsta=varsta;
    }

    std::string getFacultate(){
        return this->facultate;
    }

    void setFacultate(std::string facultate){
        this->facultate=facultate;
    }

    /*
     * Functie de to_string() pentru scrierea in fisier
     * Imi returneaza un string cu elementele componente si spatiu intre ele
     */
    std::string to_string(){
        return std::to_string(this->nrmatricol)+" "+this->nume+" "+std::to_string(this->varsta)+" "+this->facultate;
    }
};
#endif //EXAMENPRACTIC_STUDENT_H
