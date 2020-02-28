Example 02.

This example shows how **rep** will find any file that ends with **.rep** in the same folder and work on them out of order. It also shows how you can leverage template files to build structured, generated output.

In this example, we build a generated SQL query. We can build many queries this way since we are working on files and templates that are machine-readable.

You should get a file **GeneratedSQL.sql** with the contents 

*insert into testTable1 values(2020,10,March,PersonName) where testIndexCol > 1500* 
as a result.


That's it!