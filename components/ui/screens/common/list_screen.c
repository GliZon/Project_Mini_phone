#include "list_screen.h"
#include <stdio.h>

static list_screen_model_t *g_model =
    NULL;



void list_screen_open(
    list_screen_model_t *model
)
{
    if(model == NULL)
    {
        return;
    }

    g_model = model;
}



list_screen_model_t *list_screen_get_model(
    void
)
{
    return g_model;
}