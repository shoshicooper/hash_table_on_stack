<b>Stack Allocated Hash Table Class</b>

Every so often, you stumble upon a situation where you need a quick,  small hash table that'll only be useful in a local scope.  The data size is pre-determined and you want something really small, really fast, and really simple.

This is a Hash Table class that does not include the actual hash table itself.  It performs all the functions of a hash table without ever taking ownership of the table. 
 
Does it come up often?  No.  But does it come up?  Yes!

Enter the SmallHash class!

This is a hash table designed to be allocated entirely on the stack.

"But wait, that makes no sense!" You may say.  "How do you allocate the hash table itself?"

"Oh, but there is no hash table!" I would explain to you.

"But isn't this a hash table class?" you would ask, scratching your head.

"Yes!  But the class is only a hollow, empty shell that owns nothing," I would reply.  "You own the table.  It just provides you with the methods you need to process that table into something you can use and index like a hash table."

<b>How it works:</b>

This Hash Table class borrows the idea of split tables, which is the concept used by Python in their dictionary class.  Split tables make the hash table smaller and faster.

Therefore, instead of a series of bucket objects, this hash table consists of three different small, fixed-size arrays.  The user (YOU) create those arrays and allocate them on the heap before the constructor is ever run.  All that gets passed to the constructor are some pointers and the array  length.

The idea is that you, the user, can allocate everything to the stack rather than the heap. That allows the hash table to work extremely fast.

However, there is no safety in this object, as it exists to be used only inside a local scope.  Is this wise?  Possibly not.  But it'd be easy enough to add in safety features if you wanted -- and it's a cute idea, overall!
