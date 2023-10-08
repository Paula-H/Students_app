//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_SERVICE_H
#define EXAMENPRACTIC_SERVICE_H

#include "Repository.h"
typedef std::pair<int,Student> pereche;

class Service{
private:
    /*
     * Repository-ul de baza
     */
    Repository repository;
    //pentru undo voi tine un vector de perechi
    std::vector<pereche> undoList;
    //primul index pe care voi realiza undo va fi 0, deci pornim de la -1
    int curentIndex=-1;

public:
    /*
     * Constructor pentru Service
     */
    Service(Repository& repo): repository{repo}{}

    /*
     * Destructor pentru Service
     */
    ~Service()=default;

    /*
     * Returneaza un vector de Studenti sortat dupa varsta
     */
    std::vector<Student> listaStudentiSortati(){
        auto ls=this->repository.listaStudenti();
        for(int i=0;i<ls.size();i++){
            for(int j=0;j<ls.size();j++){
                if(ls[i].getVarsta()<ls[j].getVarsta())
                    std::swap(ls[i],ls[j]);
            }
        }
        return ls;
    }

    /*
     * Intinereste cu un an(-1) toti Studentii existenti in Repository
     */
    void intinerireStudenti(){
        for(auto&el:repository.listaStudenti()){
            if(el.getVarsta()>0){
                Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()-1,el.getFacultate());
                this->repository.modificaStudent(s);
            }
        }
        Student nulls=Student(-1,"",-1,"");
        undoList.push_back(std::make_pair(1,nulls));
        curentIndex++;
    }

    /*
     * Imbatraneste cu un an (+1) toti Studentii existenti in Repository
     */
    void imbatranireStudenti(){
        for(auto&el:repository.listaStudenti()){
            if(el.getVarsta()<100){
                Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()+1,el.getFacultate());
                this->repository.modificaStudent(s);
            }
        }
        Student nulls=Student(-1,"",-1,"");
        undoList.push_back(std::make_pair(2,nulls));
        curentIndex++;
    }

    /*
     * Sterge un student din Service
     */
    void stergeStudent(int nrmatricol){
        undoList.push_back(std::make_pair(3,this->repository.cautaStudent(nrmatricol)));
        this->repository.stergeStudent(nrmatricol);
        curentIndex++;
    }

    /*
     * Functie de undo
     */
    void undo(){
        if(curentIndex<0)
            throw std::invalid_argument("Nu se mai poate face undo!");
        if(undoList[curentIndex].first==1){
            //imbatranesc studentii
            for(auto&el:repository.listaStudenti()){
                if(el.getVarsta()<100){
                    Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()+1,el.getFacultate());
                    this->repository.modificaStudent(s);
                }
            }


        }
        if(undoList[curentIndex].first==2){
            //intineresc studentii
            for(auto&el:repository.listaStudenti()){
                if(el.getVarsta()>0){
                    Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()-1,el.getFacultate());
                    this->repository.modificaStudent(s);
                }
            }


        }
        if(undoList[curentIndex].first==3){
            Student deAdaugat=undoList[curentIndex].second;
            this->repository.adaugaStudent(deAdaugat);
        }
        curentIndex--;

    }

    /*
     * Functie de redo
     */
    void redo(){
        if(curentIndex>undoList.size()-1)
            throw std::invalid_argument("Nu se mai poate face redo!");
        if(undoList[curentIndex+1].first==1){
            //intineresc studentii
            for(auto&el:repository.listaStudenti()){
                if(el.getVarsta()<100){
                    Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()-1,el.getFacultate());
                    this->repository.modificaStudent(s);
                }
            }
            curentIndex++;


        }
        if(undoList[curentIndex+1].first==2){
            //imbatranesc studentii
            for(auto&el:repository.listaStudenti()){
                if(el.getVarsta()>0){
                    Student s=Student(el.getNrmatricol(),el.getNume(),el.getVarsta()+1,el.getFacultate());
                    this->repository.modificaStudent(s);
                }
            }
            curentIndex++;


        }
        if(undoList[curentIndex+1].first==3){
            auto deSters=undoList[curentIndex+1].second.getNrmatricol();
            this->repository.stergeStudent(deSters);
        }
        curentIndex++;
    }



};

#endif //EXAMENPRACTIC_SERVICE_H
