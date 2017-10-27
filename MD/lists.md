#Lists

~~~
struct List 
{
	struct Node* head;
}
~~~
~~~
struct Node 
{
	int data;
	struct Node* next;
	struct Node* prev;
}
~~~
~~~
void ListPrint (const struct List* list)
{
	...
	struct Node* elem = list->head;
	while (elem)
	{	
		Print (elem);
		elem = elem->next;		
	}
}
~~~
Удаление элемента списка:
~~~
prev->next = elem->next;
~~~
Удаление элемента двусвязного списка:
~~~

~~~