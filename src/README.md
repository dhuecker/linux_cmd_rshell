# rShell

rShell is a command shell written in C++. The shell currently prints the users host name
and the name of the machine the user is logged into. It can take in multiple commands separated
by connectors, and handle the handle the && and || connectors. In any input everything after the # is ignored.

The test command has been implemented and can be called through either using "test *filepath*" or with \[ *filepath* ]

The flags  
  * -e
  * -f
  * -d

also correctly check for existence, regular file, or directory file.


### Prerequisites

The only additional libraries are the boost libraries which provide the **tokenizer** funtion.

The libraries can be downloaded from their here:
* [Boost](https://www.boost.org)

### In Progress

The Precedence operators do not currently work and are still under construction.

## Authors

* **Andres Rodriguez** 
* **David Huecker**
