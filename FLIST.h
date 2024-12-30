#pragma once
#include "Worker.h"
#include <functional>

using ptrWorker = Worker*;

struct NODE
{
    ptrWorker info;
    NODE* next;
    NODE(ptrWorker info = nullptr, NODE* ptr = nullptr) : info(info), next(ptr) {}
    ~NODE() { next = nullptr; } // 0
};

using ptrNODE = NODE*;

struct FLIST
{
private:
    ptrNODE head, tail;
    size_t size;
    void adding_by_pointer(ptrNODE& ptr, ptrWorker elem)
    {
        ptr = new NODE(elem, ptr);
        ++size;
    }
    void deleting_by_pointer(ptrNODE& ptr)
    {
        ptrNODE p = ptr;
        ptr = p->next;
        delete p;
        --size;
    }
public:
    FLIST()
    {
        tail = head = new NODE(0);
        size = 0;
    }
    FLIST(std::ifstream& file);
    void copy(ptrNODE& beg, ptrNODE end);
    ~FLIST();
    ptrNODE get_head() const { return head; }
    ptrNODE get_tail() const { return tail; }
    void set_tail(ptrNODE ptr) { tail = ptr; }
    ptrWorker get_elem(ptrNODE ptr) const { return ptr->info; }
    size_t get_size() const { return size; }
    bool empty() const { return !head->next; }
    void add_to_head(ptrWorker elem);
    void add_to_tail(ptrWorker elem);
    void add_after(ptrNODE ptr, ptrWorker elem);
    void del_from_head();
    void del_after(ptrNODE ptr);
    void print(const char* message = "", std::ostream& stream = std::cout) const;
    void clear(ptrNODE& begin, ptrNODE& end);
    void clear();
};