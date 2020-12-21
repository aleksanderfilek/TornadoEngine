#include"TE_event.h"

#include<stdlib.h>

TE_Event* TE_event_create()
{
    TE_Event* event = (TE_Event*)malloc(sizeof(TE_Event));
    event->event_functions = NULL;
    event->count = 0;
    return event;
}

void TE_event_free(TE_Event* event)
{
    free(event->event_functions);
    event->event_functions = NULL;
    event->count = 0;
    free(event);
}

void TE_event_add(TE_Event* event, event_function function)
{
    event->count++;
    event->event_functions = (event_function*)realloc(event->event_functions, event->count * sizeof(event_function));
    event->event_functions[event->count-1] = function;
}

void TE_event_invoke(TE_Event* event, void* object, void *args, int argc)
{
    for(int i = 0; i < event->count; i++)
        event->event_functions[i](object, args, argc);
}