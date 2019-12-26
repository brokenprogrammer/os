#ifndef PROCESS_H
#define PROCESS_H

// TODO(Oskar): Implement the structures/types that this is dependat upon.

typedef s32 pid_t; // TODO(Oskar): Naming?

struct process_t
{
    list Threads;
    list Child;
    list ProcessList;
    memory_map *Map;
    pid_t ProcessId;

    uid_t uid, euid;
    gid_t gid, egid;
    pid_t Session;

    process *Parent;
    process *Next;

    s64 StartTime;
    s64 UserTime;
    s64 SystemTime;
    list Timer;
    timer Alarm;

    s32 Flag;
    s32 Status;
    s32 ExitStatus;
    list SignalQueue;

    sigaction Action[MAX_SIGNALS];
    spintlock_t SignalLock;

    stack_t SignalStack;
    syncstruct_t Sync;

    /* fd FileDescriptor; */

    spintlock_t Lock;
};
typedef struct process_t *process;

#endif // PROCESS_H