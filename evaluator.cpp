/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
// EVAL Helper      //Ther are two types of string first x:=(3+(5+6)+(9+8));     x:=
UnlimitedRational *EVAL(ExprTreeNode *a, SymbolTable *p)
{
    if (a->evaluated_value)
    {
        return a->evaluated_value;
    }
    else if (a->type == "VAL")
    {
        a->evaluated_value = a->val;
        return a->evaluated_value;
    }
    else if (a->type == "VAR")
    {
        UnlimitedRational *r = p->search(a->id);
        a->evaluated_value = new UnlimitedRational(r->get_p(), r->get_q());
        a->val = a->evaluated_value;
        return a->evaluated_value;
    }
    else if (a->type == "ADD")
    {
        a->evaluated_value = a->val->add(EVAL(a->left, p), EVAL(a->right, p));
        return a->evaluated_value;
    }
    else if (a->type == "SUB")
    {
        a->evaluated_value = a->val->sub(EVAL(a->left, p), EVAL(a->right, p));
        return a->evaluated_value;
    }
    else if (a->type == "MUL")
    {
        a->evaluated_value = a->val->mul(EVAL(a->left, p), EVAL(a->right, p));
        return a->evaluated_value;
    }
    else if (a->type == "DIV")
    {
        a->evaluated_value = a->val->div(EVAL(a->left, p), EVAL(a->right, p));
        return a->evaluated_value;
    }
    else
    {
        printf("%s\n", a->type.c_str());
        printf("UNDEFINED BEHAVIOR OF E++ ERR: LN_51_Eval\n");
        return NULL;
    }
}
ExprTreeNode *parse_Helper(vector<string> cd)
{

    for (size_t j = 0; j < cd.size(); j++)
    {
        string k = cd[j];
    }

    ExprTreeNode *res = new ExprTreeNode();
    vector<ExprTreeNode *> n;
    ExprTreeNode *temp = res;
    for (size_t i = 0; i < cd.size() - 1; i++)
    {
        if (cd[i] == "(")
        {
            n.push_back(temp);
            temp->left = new ExprTreeNode();
            temp = temp->left; // v := (13 + (2 / 51))
        }
        else if (cd[i] == ")")
        {
            if (n.size() > 0)
            {
                temp = n[n.size() - 1];
                n.pop_back();
            }
            else
            {
                printf("ERROR IN CODE\n");
            }
        }
        else if ((cd[i][0] <= 57 && cd[i][0] >= 48) || (cd[i].size() > 1 && cd[i][0] == '-'))
        {
            temp->type = "VAL";
            UnlimitedInt *v = new UnlimitedInt(cd[i]);
            UnlimitedInt *a = new UnlimitedInt(1);
            temp->evaluated_value = new UnlimitedRational(v, a);
            temp->val = temp->evaluated_value;
            delete v;
            delete a;
            temp = n[n.size() - 1];
            n.pop_back();
        }
        else if (cd[i] == "+")
        {
            temp->type = "ADD";
            temp->evaluated_value = nullptr;
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "-")
        {
            temp->type = "SUB";
            temp->evaluated_value = nullptr;
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "*")
        {
            temp->type = "MUL";
            temp->evaluated_value = nullptr;
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else if (cd[i] == "/")
        {
            temp->type = "DIV";
            temp->evaluated_value = nullptr;
            temp->right = new ExprTreeNode();
            n.push_back(temp);
            temp = temp->right;
        }
        else
        {
            temp->type = "VAR";
            temp->id = cd[i];
            temp->evaluated_value = nullptr;
            temp = n[n.size() - 1];
            n.pop_back();
        }
    }
    return res;
}

void Destructor(ExprTreeNode *rt)
{
    if (rt)
    {
        Destructor(rt->left);
        Destructor(rt->right);
        delete rt;
    }
    return;
}

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}
Evaluator::~Evaluator()
{
    for (int i = 0; i < 1; i++)
    {
        Destructor(expr_trees[i]);
    }
    this->expr_trees.clear();
    // printf("Came to Delete symtable\n");
    delete symtable;
}
void Evaluator::parse(vector<string> code)
{
    ExprTreeNode *root = new ExprTreeNode();
    root->left = new ExprTreeNode();
    root->left->type = "VAR";
    root->left->id = code[0];
    root->type = "ASSIGN";
    vector<string> a;
    a.assign(code.begin() + 2, code.end());
    if (a.size() == 1)
    {
        if (a[0][0] <= 57 && a[0][0] >= 48)
        {
            root->right = new ExprTreeNode("VAL", new UnlimitedInt(a[0]));
        }
        else
        {
            root->right = new ExprTreeNode();
            root->right->type = "VAR";
            root->right->id = a[0];
            root->right->evaluated_value = nullptr;
            root->right->val = nullptr;
        }
    }
    else
    {
        root->right = parse_Helper(a);
    }
    this->expr_trees.push_back(root);
}
void Evaluator::eval()
{
    for (size_t i = 0; i < expr_trees.size(); i++)
    {
        UnlimitedRational *a = EVAL(expr_trees[i]->right, symtable);
        UnlimitedRational *res = new UnlimitedRational(a->get_p(), a->get_q());
        if (expr_trees[i]->left->id != "")
        {
            symtable->insert(expr_trees[i]->left->id, res);
        }
        else
        {
            printf("EXP_Tree doesn't start with ASSIGN OP ERR: LN_193_Eval\n");
        }
    }
}
void Helper_PreOrder(SymEntry *root, vector<string> &ans)
{
    if (root)
    {
        if (root->val)
        {
            string p = root->key + " = " + root->val->get_frac_str() + "\n";
            ans.push_back(p);
            Helper_PreOrder(root->left, ans);
            Helper_PreOrder(root->right, ans);
        }
    }
}
vector<string> Evaluator::print_result()
{
    vector<string> ans;
    ans.clear();
    Helper_PreOrder(symtable->get_root(), ans);
    return ans;
};
