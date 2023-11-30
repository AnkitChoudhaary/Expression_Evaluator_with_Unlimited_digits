/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
void Destoryer(SymEntry *root)
{
    if (root)
    {
        Destoryer(root->left);
        Destoryer(root->right);
        delete root;
    }
}
SymEntry *rm_helper(SymEntry *k)
{

    if (k == nullptr)
    {
        return nullptr;
    }
    else if (k->left == nullptr)
    {
        SymEntry *temp = k->right;

        delete k;
        return temp;
    }
    else if (k->right == nullptr)
    {
        SymEntry *temp = k->left;
        delete k;
        return temp;
    }
    else
    {
        SymEntry *temp = k->right;
        SymEntry *temp2 = k;
        while (temp->left != nullptr)
        {
            temp2 = temp;
            temp = temp->left;
        }
        if (temp2->key == k->key)
        {
            k->key = temp->key;
            k->val = temp->val;
            k->right = temp->right;
            delete temp;
            return k;
        }
        k->key = temp->key;
        UnlimitedRational *tp = k->val;
        k->val = temp->val;
        temp->val = tp;
        temp2->left = temp->right;
        delete temp;
        return k;
    }
}
SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}
SymbolTable::~SymbolTable()
{
    if (root)
    {
        Destoryer(root);
    }
}
void SymbolTable::insert(string k, UnlimitedRational *v)
{
    bool z = false;
    if (this->size == 0)
    {
        root = new SymEntry(k, v);
        size++;
        return;
    }
    size++;
    SymEntry *q = root;
    SymEntry *p = this->root;
    while (p != nullptr)
    {
        if (k > p->key)
        {
            q = p;
            z = false;
            p = p->right;
        }
        else if (k == p->key)
        {
            delete p->val;
            p->val = v;
            size--;
            return;
        }
        else
        {
            q = p;
            z = true;
            p = p->left;
        }
    }
    if (z)
    {
        q->left = new SymEntry(k, v);
    }
    else
    {
        q->right = new SymEntry(k, v);
    }
    return;
}
void SymbolTable::remove(string k)
{
    SymEntry *p = this->root;
    SymEntry *q = nullptr;
    bool z = false;
    while (p != nullptr)
    {
        if (k > p->key)
        {
            q = p;
            z = true;
            p = p->right;
        }
        else if (k == p->key)
        {
            break;
        }
        else
        {
            q = p;
            z = false;
            p = p->left;
        }
    }
    if (p == nullptr)
    {
        // printf("Got..it!/\n");
        return;
    }
    if (q == nullptr)
    {
        this->root = rm_helper(p);
        this->size--;
    }
    else
    {
        this->size--;
        if (z)
        {
            q->right = rm_helper(p);
        }
        else
        {
            q->left = rm_helper(p);
        }
    }
    return;
}
UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *p = this->root;

    while (p != nullptr)
    {
        if (k > p->key)
        {
            p = p->right;
        }
        else if (k == p->key)
        {
            break;
        }
        else
        {
            p = p->left;
        }
    }
    return p->val;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}