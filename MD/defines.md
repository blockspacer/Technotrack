#Templates & Defines

##Templates (C++)

~~~
Stack <double>  theStack = {};
Stack <int> retAddrStack = {};
~~~

~~~
template <typename ElemT>
struct Stack
{
	ElemT data [100];
	...
};
~~~
*Не компилируется при "первом проходе".*
~~~
template <typename ElemT>
StackPush (Stack<ElemT>* stk, ElemT wtp)
{
	...
	data [count++] = wtp;
	...
}
~~~
*Ошибка появится **только** при исполнении.*

##Defines (C)
~~~
/* Stack.c  (1) */

#define ElemT double
#include "Stack.h"
#undef ElemT
...
#define ElemT int
#include "Stack.h"
#undef
~~~
~~~
/* Stack.c (2) */

IMPLEMENT_STACK(double)
IMPLEMENT_STACK(int)
~~~
~~~
/* Stack.h  (2) */ 

#define IMPLEMENT_STACK(type)				 	\
												\	
struct Stack##ElemT								\
{												\
	ElemT data [...];							\
	...											\
}												\
												\
void StackPush##ElemT (Stack##type, type wtp)	\
{												\
	...											\
}												\
#undef IMPLEMENT_STAC							\
~~~
  	
##Asserts
Хитрый assert.
~~~
bool Push (Stack* stk, int value)
{
	ASSERT (count < 10, return false);
	...
	return true;
}
~~~