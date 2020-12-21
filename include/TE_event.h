#ifndef TEEVENT_H_
#define TEEVENT_H_

typedef void (*event_function)(void* object, void *args, int argc);

#define EventFunction(name) void name(void* object, void *args, int argc)

typedef struct 
{
    event_function* event_functions;
    int count;
}TE_Event;

TE_Event* TE_event_create();
void TE_event_free(TE_Event* event);
void TE_event_add(TE_Event* event, event_function function);
void TE_event_invoke(TE_Event* event, void* object, void *args, int argc);


#endif