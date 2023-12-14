# Expression_Evaluator_with_Unlimited_digits
This tool helps us to evaluate an expression with the unlimited number and represent variables in rational i.e. p/q form.


<p>
  <l>Using this tool, you can compute infinite numbers for certain types of expressions.</l><br>
 I have developed this during my Course in COL106 using multiple data structures like **Binary Search** Tree (For variable storage) and **stacks** for expression evaluation.
  Also all the used Data Structure **Developed from scratch**.
</p>

Requirements :=
<ol>
  <li> Linux-based environment.</li>
  <li> g++ or any c++ compiler </li>
</ol>

## Getting Started :
Clone this repo by using the bash command:=

```
git clone https://github.com/AnkitChoudhaary/Expression_Evaluator_with_Unlimited_digits/tree/main
```

Now, write all your expressions in a .txt file, and the syntax of expressions should follow the following
The syntax of E++ is straightforward. There are two types of statements:
<ol>
<li> Variable Assignment: v:= E where the LHS is a variable v and the RHS is a well-formed expression
E as defined above.</li>
Statements in E++ need to be separated with a new line. You need also to note the following semantics:
<li> Declaration Before Use: A variable x can appear on the RHS of an expression only if it exists
a statement before it of the form x:= E.</li>
  <li>A well-formed expression E  should have an opening and closing parenthesis for every operator i.e., if there are two operators then there should be two well-placed complete parenthesis, not less than that or not more than that.</li>
</ol>

Example :
```
a:=2
b:=(a*3)
c:=((a+b)*5)
d:=(((a-1)*7)+((b+c)/2))
e:=((a*c)+((b*d)*4))
f:=((e/2)+((c-d)*a))
```
Now run the `make` command on your terminal.
Then run execute `exp_evaluator` and then type your .txt file name.
Yay! You will receive all your values on the terminal and in a txt file called **eval_output.txt**

P.S.: This is my learning project for DSA you may not find this as more useful, but this is a perfect project for learning. Hopefully, you liked it :).
