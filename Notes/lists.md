##Списки

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
Удаление элемента односвязного списка:
~~~
prev->next = elem->next;
~~~

###Верификатор и дамп.

Какие ошибки могут быть в списке:

* Список может зациклиться.
* Обращение по нулевому указателю.

В дампе должны быть все параметры списка.

~~~
List "lst1" [0x1234EE]
{
	elems = 5;
	head = 0x1234CD;
	tail = 0x1234AB;
	
	elem[1] = [0x2131DE]
	{
		data = 10
		next = 0x7783FC
		prev = 0x6621EE
	}
}
~~~

Делаем красивые дампы, используя **dot**:
~~~
digraph 
{
	Вася->Катя
	Катя->Коля
	Коля->Лена
	Лена->Вася
}
~~~
Где посмотреть: *sizeof.lj.ru*.

Открываем картинку:
~~~
system ("dot list.dot"); 
system ("start list.jpg"); /* for Windows */
~~~

~~~
#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char* argv[])
{
	char buf[...] = "";
	sprintf (buf, "start %s", argv[0]);
	system (buf);
	system (buf);
}
~~~