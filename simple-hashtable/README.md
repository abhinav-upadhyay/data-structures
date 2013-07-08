simple-hashtable
================

A very simple hashtable implementation in C


It has following limitations:
* Only strings can be used as the keys in the table.
* Cannot use NULL as a key.
* You have to initialize the table with a predefined size and you should not overflow the table (will fix this soon).
* No support for collision resolution currently (On my TODO list to add)
