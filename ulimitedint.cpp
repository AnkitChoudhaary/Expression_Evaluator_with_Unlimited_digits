/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// Some points to check detele []arr;      //*********** Don't delete pointers that you not created via new,add,sub,mul,div ***
// dev_helper string type
string Dev_helper(UnlimitedInt *i1, UnlimitedInt *i2, int t, int &z);

// 1st > 2nd :1 ; 1st< 2nd :0; 1st==2nd 2;
int Is_greater(UnlimitedInt *i1, UnlimitedInt *i2)
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
    return 2;
}
UnlimitedInt::UnlimitedInt()
{
    unlimited_int = new int[1];
    size = 0;
    sign = 0;
    unlimited_int[0] = 0;
    capacity = 1;
}
UnlimitedInt::UnlimitedInt(int i)
{
    int a = 0;
    if (i > 0)
    {
        sign = 1;
    }
    else if (i < 0)
    {
        sign = -1;
    }
    else
    {
        sign = 0;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        size = 1;
        capacity = 1;
        return;
    }
    i *= sign;
    int b = i;
    while (b > 0)
    {
        b /= 10;
        a += 1;
    }
    size = a;
    capacity = a;
    unlimited_int = new int[capacity];
    for (int j = capacity - 1; j >= 0; j--)
    {
        unlimited_int[j] = i % 10;
        i /= 10;
    }
}
UnlimitedInt::UnlimitedInt(string s)
{
    if (s == "0/0")
    {
        sign = -2;
        capacity = 0;
        size = 0;
        unlimited_int = new int[1];
        unlimited_int[0] = -1;
        return;
    }
    int z = 0;
    if (s[0] - '0' < 0)
    {
        z = 1;
        if (s[0] == '+')
        {
            sign = 1;
            size = s.size() - 1;
        }
        else
        {
            sign = -1;
            size = s.size() - 1;
        }
    }
    else if (s.size() == 1 && s[0] == '0')
    {
        sign = 0;
        size = 1;
    }
    else
    {
        sign = 1;
        size = s.size();
    }
    while (s[z] == '0' && size > 0)
    {
        z++;
        size--;
    }
    capacity = size;
    unlimited_int = new int[max(1, capacity)];
    if (size == 0)
    {
        sign = 0;
        size = 1;
        capacity = size;
        unlimited_int[0] = 0;
    }
    for (size_t i = z; i < s.size(); i++)
    {
        unlimited_int[i - z] = s[i] - '0';
    }
}

// New Constructor
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    sign = sgn;
    capacity = cap;
    unlimited_int = ulimited_int;
    size = sz;
}

// Initilized completed
UnlimitedInt::~UnlimitedInt()
{
    if (unlimited_int)
    {
        delete[] unlimited_int;
        unlimited_int = nullptr;
    }
}
int UnlimitedInt::get_size()
{
    return this->size;
}
int UnlimitedInt::get_sign()
{
    return this->sign;
}
int *UnlimitedInt::get_array()
{
    return this->unlimited_int;
}
string UnlimitedInt::to_string()
{
    if (this->sign == -2)
    {
        return "0/0";
    }
    string a = "";
    if (this->sign == -1)
    {
        a += '-';
    }
    for (int i = 0; i < this->capacity; i++)
        a += std::to_string(this->unlimited_int[i]);
    return a;
}
int UnlimitedInt::get_capacity()
{
    return capacity;
}

// Addition
UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == -2 || i2->sign == -2)
    {
        return new UnlimitedInt("0/0");
    }
    if (i1->get_size() < i2->get_size())
    {
        UnlimitedInt *temp = i2;
        i2 = i1;
        i1 = temp;
    }
    // String for Without overflow addition
    string a(i1->get_size(), '0');

    if (i1->get_sign() == 0)
    {
        UnlimitedInt *ptr = new UnlimitedInt(i2->to_string());
        return ptr;
    }
    else if (i2->get_sign() == 0)
    {
        UnlimitedInt *ptr = new UnlimitedInt(i1->to_string());
        return ptr;
    }
    // Str for starting sign & carry
    string k = "";
    // i1 array
    int *p = i1->get_array();
    // i2 array
    int *q = i2->get_array();
    // i2.size-1
    int l = i2->get_size() - 1;
    // i1.size-1
    int m = i1->get_size() - 1;
    // carry
    int r = 0;
    int s1 = i1->get_sign();
    int s2 = i2->get_sign();
    if (s1 == s2)
    {
        if (s1 == -1)
        {
            k += '-';
        }

        for (int j = m; j >= 0; j--)
        {
            if (l >= 0)
            {
                a[j] += (p[j] + q[l] + r) % 10;
                r = (p[j] + q[l] + r) / 10;
            }
            else
            {
                a[j] += (p[j] + r) % 10;
                r = (p[j] + r) / 10;
            }
            l--;
        }

        if (r == 1)
        {
            k += '1';
        }
        k += a;
    }
    else
    {
        if ((s1 == 1 && Is_greater(i1, i2)) || (s2 == 1 && Is_greater(i2, i1)))
        // case when Final ans is +ve;
        {
            for (int j = m; j >= 0; j--)
            {
                if (l >= 0)
                {
                    int e = s1 * p[j] + s2 * q[l] + r;
                    // printf("%d   Ankit\n", e);

                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                else
                {
                    int e = p[j] + r;
                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                l--;
            }
            k += a;
        }
        else
        { // case when Final ans is -ve;
            s1 *= -1;
            s2 *= -1;
            for (int j = m; j >= 0; j--)
            {
                if (l >= 0)
                {
                    int e = s1 * p[j] + s2 * q[l] + r;
                    // printf("%d   Ankit\n", e);

                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                else
                {
                    int e = p[j] + r;
                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                l--;
            }
            k += '-';
            k += a;
        }
    }
    // printf("%s\n", k.c_str());
    UnlimitedInt *point = new UnlimitedInt(k);
    return point;
}

// Subtraction
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == -2 || i2->sign == -2)
    {
        return new UnlimitedInt("0/0");
    }
    int st = 1;
    if (i1->get_size() < i2->get_size())
    {
        UnlimitedInt *temp = i2;
        i2 = i1;
        i1 = temp;
        st = -1;
    }
    // String for Without overflow sub
    string a(i1->get_size(), '0');

    if (i1->get_sign() == 0)
    {
        UnlimitedInt *ptr = new UnlimitedInt(i2->to_string());
        ptr->sign *= -1;
        return ptr;
    }
    else if (i2->get_sign() == 0)
    {
        UnlimitedInt *ptr = new UnlimitedInt(i1->to_string());
        return ptr;
    }
    // Str for starting sign & carry
    string k = "";
    // i1 array
    int *p = i1->get_array();
    // i2 array
    int *q = i2->get_array();
    // i2.size-1
    int l = i2->get_size() - 1;
    // i1.size-1
    int m = i1->get_size() - 1;
    // carry
    int r = 0;
    int s1 = i1->get_sign() * st;
    int s2 = i2->get_sign() * -1 * st;
    if (s1 == s2)
    {
        if (s1 == -1)
        {
            k += '-';
        }

        for (int j = m; j >= 0; j--)
        {
            if (l >= 0)
            {
                a[j] += (p[j] + q[l] + r) % 10;
                r = (p[j] + q[l] + r) / 10;
            }
            else
            {
                a[j] += (p[j] + r) % 10;
                r = (p[j] + r) / 10;
            }
            // printf("%s\n", a.c_str());
            l--;
        }

        if (r == 1)
        {
            k += '1';
        }
        k += a;
    }
    else
    {
        if ((s1 == 1 && Is_greater(i1, i2)) || (s2 == 1 && Is_greater(i2, i1)))
        // case when Final ans is +ve;
        {
            for (int j = m; j >= 0; j--)
            {
                if (l >= 0)
                {
                    int e = s1 * p[j] + s2 * q[l] + r;
                    // printf("%d   Ankit\n", e);

                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                else
                {
                    int e = p[j] + r;
                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                l--;
            }
            k += a;
        }
        else
        { // case when Final ans is -ve;
            s1 *= -1;
            s2 *= -1;
            for (int j = m; j >= 0; j--)
            {
                if (l >= 0)
                {
                    int e = s1 * p[j] + s2 * q[l] + r;
                    // printf("%d   Ankit\n", e);

                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                else
                {
                    int e = p[j] + r;
                    if (e < 0)
                    {
                        e += 10;
                        a[j] += e;
                        r = -1;
                    }
                    else
                    {
                        a[j] += e;
                        r = 0;
                    }
                }
                l--;
            }
            k += '-';
            k += a;
        }
    }
    // printf("%s\n", k.c_str());
    UnlimitedInt *point = new UnlimitedInt(k);
    return point;
}

// Mul
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == -2 || i2->sign == -2)
    {
        return new UnlimitedInt("0/0");
    }
    UnlimitedInt *res = new UnlimitedInt("0");
    if (i1->get_sign() == 0 || i2->get_sign() == 0)
    {
        return res;
    }
    else
    {
        string k = "";
        int *p = i1->get_array();
        int *q = i2->get_array();
        int l = i2->get_size();
        int m = i1->get_size();
        int r = 0;
        for (int i = m - 1; i >= 0; i--)
        {
            string a(l + 1, '0');
            for (int j = l - 1; j >= 0; j--)
            {
                a[j + 1] += (p[i] * q[j] + r) % 10;
                r = (p[i] * q[j] + r) / 10;
            }
            if (r > 0)
            {
                a[0] += r;
                r = 0;
            }
            a += k;

            UnlimitedInt *o = new UnlimitedInt(a);
            UnlimitedInt *temp = res;
            res = res->add(res, o);
            k += '0';
            delete temp;
            delete o;
        }
    }

    if (i1->get_sign() * i2->get_sign() == -1)
    {
        string a = res->to_string();
        string k = "-";
        k += a;
        delete res;

        res = new UnlimitedInt(k);
    }
    return res;
}

// Divide
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == -2 || i2->sign == -2)
    {
        return new UnlimitedInt("0/0");
    }
    if (i2->get_sign() == 0)
    {
        return new UnlimitedInt("0/0");
    }
    if (i1->get_size() < i2->get_size())
    {
        UnlimitedInt *ptr = new UnlimitedInt(0);
        return ptr;
    }
    if (i2->to_string() == "1")
    {
        UnlimitedInt *ptr = new UnlimitedInt(i1->to_string());
        return ptr;
    }
    else if (i2->to_string() == "-1")
    {
        string k = "-";
        k += i1->to_string();
        UnlimitedInt *ptr = new UnlimitedInt(k);
        return ptr;
    }
    // Res
    string k = "";
    string a = i1->to_string();
    string b = i2->to_string();
    int st = 1;
    if (a[0] == '-')
    {
        a = a.substr(1, a.size());
        st *= -1;
    }
    if (b[0] == '-')
    {
        b = b.substr(1, a.size());
        st *= -1;
    }
    int h_ = 0;
    while (a.size() > b.size())
    {
        h_++;
        b += '0';
    }
    if (st < 0)
    {
        k += '-';
    }

    UnlimitedInt *aU = new UnlimitedInt(a);
    UnlimitedInt *bU = new UnlimitedInt(b);
    int e = 0;
    k += Dev_helper(aU, bU, h_, e);
    // printf("%s\n", k.c_str());
    UnlimitedInt *res = new UnlimitedInt(k);
    if (st < 0 && (e <= 0))
    {
        UnlimitedInt *temp = res;
        UnlimitedInt *temp2 = new UnlimitedInt("1");
        res = sub(res, temp2);
        delete temp2;
        delete temp;
    }
    return res;
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *a = div(i1, i2);
    UnlimitedInt *b = mul(a, i2);
    UnlimitedInt *c = sub(i1, b);
    string k = c->to_string();
    delete a;
    delete b;
    delete c;
    return new UnlimitedInt(k);
}

// Devision String
string Dev_helper(UnlimitedInt *i1, UnlimitedInt *i2, int t, int &z)
{
    if (t == -1)
    {
        delete i1;
        delete i2;
        return "";
    }
    else
    {
        int r = 0;
        UnlimitedInt *p = i1;
        i1 = i1->sub(i1, i2);
        while (i1->get_sign() > 0)
        {
            UnlimitedInt *temp = p;
            p = i1;
            i1 = i1->sub(i1, i2);
            delete temp;
            r++;
        }
        if (i1->get_sign() == 0)
        {
            delete p;
            delete i1;
            delete i2;
            string k = "";
            k += '0' + r + 1;
            for (int i = 0; i < t; i++)
            {
                k += '0';
            }
            z = 1;
            return k;
        }
        else
        {
            string k = "";
            k += '0' + r;
            delete i1;
            string op = i2->to_string().substr();
            op = op.substr(0, op.size() - 1);
            delete i2;
            i2 = new UnlimitedInt(op);
            return k + Dev_helper(p, i2, t - 1, z);
        }
    }
}