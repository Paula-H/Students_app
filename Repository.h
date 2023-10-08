//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_REPOSITORY_H
#define EXAMENPRACTIC_REPOSITORY_H
#include <vector>
#include <map>
#include "Student.h"
#include <fstream>
#include <stdexcept>

class Repository{
private:
    /*
     * Stochez Studentii intr-un dictionar
     */
    std::map<int,Student> studenti;

    /*
     * String pentru citirea din fisier
     */
    std::string fisier;
public:
    /*
     * Constructor Repository
     */
    Repository(std::string fisier):fisier{fisier}{
        citireDinFisier();
    }

    /*
     * Destructor Repository
     */
    ~Repository()=default;

    /*
     * Citirea datelor din fisier
     */
    void citireDinFisier(){
        std::ifstream f(fisier);
        int nrmat;
        std::string num;
        int varst;
        std::string fac;
        while(f>>nrmat>>num>>varst>>fac){
            Student s=Student(nrmat,num,varst,fac);
            studenti.insert(std::make_pair(nrmat,s));
        }
        f.close();
    }

    /*
     * Scrierea datelor din fisier
     */
    void scriereInFisier(){
        std::ofstream f(fisier);
        f.clear();
        for(auto&stud:studenti){
            f<<stud.second.to_string()<<std::endl;
        }
        f.close();
    }

    /*
     * Adauga un student in dictionar
     */
    void adaugaStudent(Student s){
        auto it=studenti.find(s.getNrmatricol());
        if(it!=studenti.end()){
            throw std::invalid_argument("Studentul exista deja in Repository!");
        }
        studenti.insert(std::make_pair(s.getNrmatricol(),s));
        scriereInFisier();
    };

    /*
     * Sterge un student din dictionar
     */
    void stergeStudent(int nrmatricol){
        auto it=studenti.find(nrmatricol);
        if(it==studenti.end()){
            throw std::invalid_argument("Studentul nu exista in Repository!");
        }
        studenti.erase(nrmatricol);
        scriereInFisier();
    }

    /*
     * Returneaza numarul de studenti
     */
    int numarStudenti(){
        return this->studenti.size();
    }

    /*
     * Returneaza un vector de Studenti cu toate elementele dictionarului
     */
    std::vector<Student> listaStudenti(){
        std::vector<Student> lista;
        for(auto&stud:studenti){
            lista.push_back(stud.second);
        }
        return lista;
    }

    /*
     * Modifica un Student deja existent din dictionar
     */
    void modificaStudent(Student s){
        auto it=studenti.find(s.getNrmatricol());
        if(it==studenti.end()){
            throw std::invalid_argument("Studentul nu exista in Repository!");
        }
        studenti.erase(s.getNrmatricol());
        studenti.insert(std::make_pair(s.getNrmatricol(),s));
        scriereInFisier();
    }

    /*
     * Cauta un student existent in dictionar
     */
    Student cautaStudent(int nrmatricol){
        auto it=studenti.find(nrmatricol);
        if(it==studenti.end()){
            throw std::invalid_argument("Studentul nu exista in Repository!");
        }
        auto stud=*it;
        return stud.second;

    }

};

#endif //EXAMENPRACTIC_REPOSITORY_H
