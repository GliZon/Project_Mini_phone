#include "text_editor_screen.h"
#include <stdio.h>



static text_editor_model_t *g_model =
    NULL;



void text_editor_open(
    text_editor_model_t *model
)
{
    if(model == NULL)
    {
        return;
    }

    g_model = model;
}



text_editor_model_t *text_editor_get_model(
    void
)
{
    return g_model;
}