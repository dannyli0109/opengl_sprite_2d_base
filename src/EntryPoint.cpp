//These includes are specific to the way we’ve set up GLFW and GLAD.
#include "ProgramManager.h"

int main(void)
{
    ProgramManager programManager;
    if (programManager.Init())
    {
        programManager.Run();
    }
    programManager.Destroy();
    return 0;
}
