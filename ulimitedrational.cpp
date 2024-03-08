/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// 1  i1>i2   2 :>i1==i2    0:  i1<i2   Didn't care abt sign
int is_Greater(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return 1;
    }
    else if (i1->get_size() < i2->get_size())
    {
        return 0;
    }
    else
    {
        string s1 = i1->to_string();
        string s2 = i2->to_string();
        if (s1 > s2)
        {
            return 1;
        }
        else if (s1 < s2)
        {
            return 0;
        }
        else
        {
            return 2;
        }
    }
}
UnlimitedInt *GCD(string s1, string s2)
{
    if (s1[0] == '-')
    {
        s1 = s1.substr(1, s1.size());
    }
    if (s2[0] == '-')
    {
        s2 = s2.substr(1, s2.size());
    }
    if (s1 == "1" || s2 == "1")
    {
        return new UnlimitedInt("1");
    }
    if (s2 == "0")
    {
        return new UnlimitedInt(s1);
    }
    else
    {
        UnlimitedInt *i1 = new UnlimitedInt(s1);
        UnlimitedInt *i2 = new UnlimitedInt(s2);
        UnlimitedInt *temp = i1->mod(i1, i2);
        string modd = temp->to_string();
        delete temp;
        delete i1;
        delete i2;
        return GCD(s2, modd);
    }
    // UnlimitedInt *i1 = new UnlimitedInt(s1);
    // UnlimitedInt *i2 = new UnlimitedInt(s2);
    // int i = is_Greater(i1, i2);
    // if (i == 2)
    // {
    //     string k = i1->to_string();
    //     delete i1;
    //     delete i2;
    //     return new UnlimitedInt(k);
    // }
    // else if (i == 1)
    // {
    //     UnlimitedInt *ir = i1->sub(i1, i2);
    //     delete i1;
    //     string s1 = ir->to_string();
    //     string s2 = i2->to_string();
    //     delete ir;
    //     delete i2;
    //     return GCD(s1, s2);
    // }
    // else
    // {
    //     UnlimitedInt *ir = i2->sub(i2, i1);
    //     delete i2;
    //     string s1 = ir->to_string();
    //     string s2 = i1->to_string();
    //     delete ir;
    //     delete i1;
    //     return GCD(s1, s2);
    // }
}
UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(0);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (den->to_string() == "0")
    {
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("0");
        return;
    }
    else if (num->to_string() == "0")
    {
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("1");
        return;
    }
    UnlimitedInt *temp = GCD(num->to_string(), den->to_string());
    p = num->div(num, temp);
    q = num->div(den, temp);
    delete temp;
}
UnlimitedRational::~UnlimitedRational()
{
    delete this->p;
    this->p = nullptr;
    delete this->q;
    this->q = nullptr;
}
UnlimitedInt *UnlimitedRational::get_p()
{
    return this->p;
}
UnlimitedInt *UnlimitedRational::get_q()
{
    return this->q;
}
string UnlimitedRational::get_p_str()
{
    return this->p->to_string();
}
string UnlimitedRational::get_q_str()
{
    return this->q->to_string();
}
string UnlimitedRational::get_frac_str()
{
    string k = "";
    k += this->p->to_string();
    k += '/';
    k += this->q->to_string();
    return k;
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0")
    {
        return new UnlimitedRational();
    }
    UnlimitedInt *i1p = i1->p;
    UnlimitedInt *i1q = i1->q;
    UnlimitedInt *i2p = i2->p;
    UnlimitedInt *i2q = i2->q;
    UnlimitedInt *a1 = i1p->mul(i1p, i2q);
    UnlimitedInt *a2 = i1p->mul(i2p, i1q);
    UnlimitedInt *num = a1->add(a1, a2);
    delete a1;
    delete a2;
    UnlimitedInt *den = den->mul(i1q, i2q);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return res;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0")
    {
        return new UnlimitedRational();
    }
    UnlimitedInt *i1p = i1->p;
    UnlimitedInt *i1q = i1->q;
    UnlimitedInt *i2p = i2->p;
    UnlimitedInt *i2q = i2->q;
    UnlimitedInt *a1 = i1p->mul(i1p, i2q);
    UnlimitedInt *a2 = i1p->mul(i2p, i1q);
    UnlimitedInt *num = a1->sub(a1, a2);
    delete a1;
    delete a2;
    UnlimitedInt *den = den->mul(i1q, i2q);
    // printf("%s   Num\n ", num->to_string().c_str());
    // printf("%s   den\n ", den->to_string().c_str());
    UnlimitedRational *res = new UnlimitedRational(num, den);
    delete num;
    delete den;
    return res;
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0")
    {
        return new UnlimitedRational();
    }
    UnlimitedInt *p1 = p1->mul(i1->p, i2->p);
    // printf("%s    p1\n", p1->to_string().c_str());

    UnlimitedInt *q1 = q1->mul(i1->q, i2->q);
    // printf("%s    q1\n", q1->to_string().c_str());

    // UnlimitedInt *temp = GCD(p->to_string(), q->to_string());
    // p = p->div(num, temp);
    // q = q->div(den, temp);
    // delete temp;
    UnlimitedRational *res = new UnlimitedRational(p1, q1);
    delete p1;
    delete q1;
    return res;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if (i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0" || i2->get_p_str() == "0")
    {
        return new UnlimitedRational();
    }
    UnlimitedInt *q1 = q1->mul(i2->p, i1->q);
    // printf("%s    q1\n", q1->to_string().c_str());

    UnlimitedInt *p1 = p1->mul(i1->p, i2->q);
    // printf("%s    p1\n", p1->to_string().c_str());
    UnlimitedRational *res = new UnlimitedRational(p1, q1);
    delete p1;
    delete q1;
    return res;
}