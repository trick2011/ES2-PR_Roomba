#include "roombacontroller.h"


void Roombacontroller::EnableCleaning(Basicclean* input)
{

    if(CleaningProgram != NULL)
    {
        delete CleaningProgram;
    }
    CleaningProgram = input;
    input->clean();
//Moet gethread
}

void Roombacontroller::Enablesetter()
{
    CleaningProgram->SetEnableCleaning();
}

void Roombacontroller::Disablesetter()
{
    CleaningProgram->SetDisableCleaning();
}
