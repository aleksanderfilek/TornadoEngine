#ifndef TEEVENT_H_
#define TEEVENT_H_

typedef void (*TE_EventFunction)(void* object, void *args, int argc);

#define EventFunction(name) void name(void* object, void *args, int argc)

typedef struct 
{
    TE_EventFunction* event_functions;
    int count;
}TE_Event;

TE_Event* TE_event_create();
void TE_event_free(TE_Event* event);
void TE_event_add(TE_Event* event, TE_EventFunction function);
void TE_event_invoke(TE_Event* event, void* object, void *args, int argc);
void TE_event_clear(TE_Event* event);


#endif