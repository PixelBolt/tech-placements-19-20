There are two versions of my code, both coded in C++ as a console application, using Visual Basic and each labelled accordingly.
They are both included in the source files by default, so to run either one simply remove (do not delete) the one you wish to run first.
Then add the other one back and remove the first when you wish to run that one.
The 'Solution with map' runs independently.
The 'Solution with file' has a text file included which is positioned and ready to be used.
This text file may be edited to add new items that the code will function with if it's written in the correct format.
Iteam_ID,Price,Discount_Quantity,Save_Free,Discount     
Where Discount_Quantity is how many are required to be bought to apply the discount
And where Save_Free is one of those two words (lowercase) indicated the type of offer. Save means buy a certain amount for a separate price and Free means buy x get y free offer
Open it with the most recent version of Visual Basic (as outdated ones may not support it fully) and start it without debugging.

How I approached the problem:
I started off small, establishing what I needed to do. I laid out the groundwork for the classes and other things the speciation stated. Once I had that I sat back and had a think about how I wanted to approach the problem I decided that it would be good to map things, that way I could just associate all the different pieces of data  points of each item with the ID of that item, kind of like how a database does it, to save redundancy. That’s how I saw it anyways. I started by building up the functions individually to isolate them. It’s easier to tackle lots of small problems rather than one big one after all. As I went along I started thinking that with just a little bit of tweaking this could actually be a lot more, that’s when it occurred to me to have a file to read in. In hindsight, it would be cool if I then made it create a file with the basket, like a receipt. I wish I had thought of the file system originally, as I had to replace and modify the mapping system, as they weren’t easily compatible.
