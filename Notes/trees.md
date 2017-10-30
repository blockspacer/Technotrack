##Деревья.
Дамп дерева:
~~~
void Print (Node* n)
{
	if (!n) return;
	Print (n->left);
	printf ("%d\n", n->data);
	Print (n->right);
} 
~~~