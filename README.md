# YottaDB-Database-Connector for C++
![logo](cpp-yottadb.png)
<!-- REVIEW: I really like this design! This makes the wrapper look a lot like M :) -->
This class allows access to YottaDB-trees (persistent and in-memory) like accessing a C++-tree (multidimensional array).
```cpp
_global[1][2]["foo"] = "bar";
cout << _global[1][2]["foo"]
```

# Prerequisites

YottaDB hierarchical NoSQL-database <https://yottadb.com/>

# Best Practise

If using named objects name the object like the global (but with a preceding underscore instead of caret).
Mapping an object to the global name is done via the constructor.
```cpp	
c_ydb_global _g("^g"), _counter("^counter");
```
# Error Processing

<!-- REVIEW: I am not very familiar with C++ error handling. Is it normal to allow either exceptions or error codes? -->
<!-- REVIEW: This is configured per global variable, not process-wide. It seems confusing to have some variables throw exceptions and other return errors. -->
If a second parameter in the constructor is passed as 1 the object throws errors (see test2.cpp).

<!--
REVIEW: `rc()` stands for 'return code'? I think it would be more familiar to users to name it
`ZSTATUS` or `last_error()` instead.
-->
<!--
REVIEW: this will mean the API is not thread-safe, the same way `ZSTATUS` is not thread-safe. I
saw all the functions call `_s` variants, not `_st`, but I would expect that to be easier to fix
than changing the error reporting.
-->

If the second parameter is passed as 0 (or omitted) error-processing is done by the method int rc(); which
can be called after each access.
# License

This project is licensed under the terms of the MIT license.
