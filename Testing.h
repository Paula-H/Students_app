//
// Created by Paula on 6/19/2023.
//

#ifndef EXAMENPRACTIC_TESTING_H
#define EXAMENPRACTIC_TESTING_H

class Testing{
private:
    /*
     * Teste Student
     */
    void testStudent();

    /*
     * Teste Repository
     */
    void testRepository();

    /*
     * Teste Service
     */
    void testService();
public:
    /*
     * Testare all
     */
    void testAll(){
        testStudent();
        testRepository();
        testService();
    }
};

#endif //EXAMENPRACTIC_TESTING_H
