/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode()
{
    this->type = "UNDef";
    this->id = "";
    this->left = nullptr;
    this->right = nullptr;
    this->val = nullptr;
    this->evaluated_value = nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{
    this->type = t;
    if (t == "VAL")
    {
        UnlimitedInt *a = new UnlimitedInt(1);
        this->val = new UnlimitedRational(v, a);
        delete a;
        delete v;
        this->evaluated_value = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->id = "";
    }
    else
    {
        this->val = nullptr;
        this->evaluated_value = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->id = "";
    }
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v)
{
    this->type = t;
    if (t == "VAR" || t == "ADD" || t == "SUB" || t == "MUL" || t == "DIV")
    {
        this->evaluated_value = v;
    }
    this->val = v;
    this->evaluated_value = v;
    this->left = nullptr;
    this->right = nullptr;
    this->id = "";
}
ExprTreeNode::~ExprTreeNode()
{
    if (val)
    {
        delete val;
    }
    if (type == "ADD" || type == "SUB" || type == "MUL" || type == "DIV")
    {
        delete evaluated_value;
    }
    this->type = "UNDef";
    this->id = "";
    val = nullptr;
    evaluated_value = nullptr;
}