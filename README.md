multipassCli
============

usage: multipass [-h] [-m MASTER] [-c] [-i IDENTIFIER] [-l LENGTH] [-p]

Generates a secure password

optional arguments:
  -h, --help            show this help message and exit
  -m MASTER, --master MASTER
                        argument to define the master password (Please omit
                        this variable and use the prompt instead, otherwise
                        your master password will be in your history!)
  -c, --confirm         prompt the user again for a password if not using
                        --master
  -i IDENTIFIER, --identifier IDENTIFIER
                        identifier to use (site name,program name, etc.)
  -l LENGTH, --length LENGTH
                        length of the resulting password (invalid if result is
                        a PIN)
  -p, --pin             output PIN instead
