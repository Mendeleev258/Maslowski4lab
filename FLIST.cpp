#pragma once
#include "FLIST.h"

FLIST::FLIST(std::ifstream& file)
{
    head = new NODE();
    tail = head;
    while (!file.eof())
    {
        ptrWorker worker = new Worker(file);
        add_to_tail(worker);
    }
}

void FLIST::copy(ptrNODE& beg, ptrNODE end)
{
    while (beg != end)
    {
        add_to_tail(beg->info);
        beg = beg->next;
    }
}

FLIST::~FLIST()
{
    while (head && !empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

void FLIST::add_to_head(ptrWorker elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail)
        tail = tail->next;
}

void FLIST::add_to_tail(ptrWorker elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

void FLIST::add_after(ptrNODE ptr, ptrWorker elem)
{
    if (ptr)
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

void FLIST::del_from_head()
{
    if (head->next)
    {
        deleting_by_pointer(head->next);
        if (!head->next)
            tail = head;
    }
}

void FLIST::del_after(ptrNODE ptr)
{
    if (ptr && ptr->next)
    {
        if (ptr->next == tail)
            tail = ptr;
        deleting_by_pointer(ptr->next);
    }
}

void FLIST::print(const char* message, std::ostream& stream) const
{
    ptrNODE p = head->next;
    while (p)
    {
        (p->info)->print(stream);
        p = p->next;
    }
}

void FLIST::clear(ptrNODE& begin, ptrNODE& end)
{
    while (begin != end)
        del_after(begin);
    begin = end;
}

void FLIST::clear()
{
    while (head->next)
        del_after(head);
}