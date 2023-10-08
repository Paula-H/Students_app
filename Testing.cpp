//
// Created by Paula on 6/19/2023.
//

#include "Testing.h"
#include "Student.h"
#include "Repository.h"
#include "Service.h"
#include <string.h>
#include <cassert>

void Testing::testStudent() {
    Student s= Student(1,"a",18,"mate");
    assert(s.getNrmatricol()==1);
    assert(s.getNume()=="a");
    assert(s.getVarsta()==18);
    assert(s.getFacultate()=="mate");

    s.setNrmatricol(2);
    s.setNume("b");
    s.setVarsta(19);
    s.setFacultate("ai");

    assert(s.getNrmatricol()==2);
    assert(s.getNume()=="b");
    assert(s.getVarsta()==19);
    assert(s.getFacultate()=="ai");

    assert(s.to_string()=="2 b 19 ai");
}

void Testing::testRepository() {
    Repository repository= Repository("dummyFile.txt");
    assert(repository.listaStudenti().size()==4);

    Student s= Student(5,"e",18,"mate");
    repository.adaugaStudent(s);
    assert(repository.numarStudenti()==5);

    try{
        repository.adaugaStudent(s);
    }
    catch(std::invalid_argument&msg){
        assert(!strcmp(msg.what(),"Studentul exista deja in Repository!"));
    }

    repository.stergeStudent(5);
    try{
        repository.stergeStudent(5);
    }
    catch(std::invalid_argument&msg){
        assert(!strcmp(msg.what(),"Studentul nu exista in Repository!"));
    }
    Student s2=Student(1,"a",18,"mate");
    assert(repository.cautaStudent(1).getNume()=="a");
    Student s1= Student(1,"e",18,"mate-info");
    repository.modificaStudent(s1);
    assert(repository.cautaStudent(1).getNume()=="e");
    assert(repository.cautaStudent(1).getNume()!="a");
    repository.modificaStudent(s2);
    assert(repository.cautaStudent(1).getNume()!="e");
    assert(repository.cautaStudent(1).getNume()=="a");
    try{
        repository.cautaStudent(5);
    }
    catch(std::invalid_argument&msg){
        assert(!strcmp(msg.what(),"Studentul nu exista in Repository!"));
    }

    try{
        repository.modificaStudent(s);
    }
    catch(std::invalid_argument&msg){
        assert(!strcmp(msg.what(),"Studentul nu exista in Repository!"));
    }

}

void Testing::testService() {
    Repository repository= Repository("dummyFile.txt");
    Service service=Service(repository);

    auto ls=service.listaStudentiSortati();
    assert(ls[0].getVarsta()==18);
    assert(ls[1].getVarsta()==19);
    assert(ls[2].getVarsta()==20);
    assert(ls[3].getVarsta()==21);

    service.imbatranireStudenti();
    auto ls2=service.listaStudentiSortati();
    assert(ls2[0].getVarsta()==19);
    assert(ls2[1].getVarsta()==20);
    assert(ls2[2].getVarsta()==21);
    assert(ls2[3].getVarsta()==22);

    service.undo();
    auto ls3=service.listaStudentiSortati();
    assert(ls3[0].getVarsta()==18);
    assert(ls3[1].getVarsta()==19);
    assert(ls3[2].getVarsta()==20);
    assert(ls3[3].getVarsta()==21);

    service.imbatranireStudenti();
    service.imbatranireStudenti();
    service.undo();
    service.redo();
    auto ls4=service.listaStudentiSortati();
    assert(ls4[0].getVarsta()==20);
    assert(ls4[1].getVarsta()==21);
    assert(ls4[2].getVarsta()==22);
    assert(ls4[3].getVarsta()==23);

    service.intinerireStudenti();
    service.intinerireStudenti();

    service.stergeStudent(1);
    service.undo();
    assert(service.listaStudentiSortati().size()==4);
}