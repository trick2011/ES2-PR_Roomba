#include "roombacontroller.h"


Roombacontroller::EnableCleaning(Basicclean* input)
{

    if(CleaningProgram != NULL)
    {
        delete CleaningProgram;
    }
    CleaningProgram = input;
    input->clean();
//Moet gethread
    return 0;
}

Roombacontroller::Enablesetter()
{
    CleaningProgram->SetEnableCleaning();
    return 0;
}

Roombacontroller::Disablesetter()
{
    CleaningProgram->SetDisableCleaning();
    return 0;
}
