multipassCli-2.0
============

Generates a secure password

Original program located at:
https://github.com/The-Overlord/multipass


Algorithm
-----------
Generate a SHA-256 hash of the master + " " + identifier

For passwords:
Represent the hash as a lowercase hex string and concatinate its first 16 characters to the end of "Mp2!"

For PINs:
Represent the hash as a positive decimal integer, and use the last 4 digits, padding with zeros if neccesary.


Changes in 2.0
----------------
* Switched to using C vs. Python 2.
* Algorithm changed
