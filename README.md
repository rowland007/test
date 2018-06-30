# Test

Master Branch: [![Build Status](https://travis-ci.org/rowland007/test.svg?branch=master)](https://travis-ci.org/rowland007/test)

Development Branch: [![Build Status](https://travis-ci.org/rowland007/test.svg?branch=development)](https://travis-ci.org/rowland007/test)

### Purpose
This repository is used to test out features of development tools such as Travis CI, autoconf, Git, and GitHub. 
**Source code within the repository should not be used as a full featured program.**

### Build Instructions

First, you need to generate an m4 environment for autotools to use:
```
aclocal
```
After you set the environment you will need to setup your `configure.ac` and `Makefile.am` templates. Let's start with the `configure.ac` template first.
```
AC_INIT([program_name], [verson_number], [maintainer@email.com])
AM_INIT_AUTOMAKE
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
```
For the `Makefile.am` template type the following:
```
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = program_name
program_name_SOURCES = cparse.cpp
```
Now you can run `autoconf` to turn your `configure.ac` into a `configure` script and `automake` to turn your `Makefile.am` into a `Makefile.in`:
```
autoconf
automake --add-missing
```
Now you are ready for the program to be distributed!! The end user will just need to run:
```
./configure && make && make install
```
**DO NOT** add `configure`, `Makefile.in`, or any of the other files from running `autoconf` and `automake` to the repository. That will break the Travis CI testing.

### Travis CI Instructions

Add a `.travis.yml` file to the root directory of the repository. Inside the `.travis.yml` file you will need:
```
language: cpp
before_install:
  - aclocal
  - autoconf
  - automake --add-missing
```
For more information on what can be placed in the `.travis.yml` file, see the **References** section. Currently Travis CI only works on Linux and OSX.

### References

* [Autotools Tutorial]
* [Travis CI Documentation]
* [Autoconf Manual]
* [Git Message Templates]

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

[Travis CI Documentation]: <https://docs.travis-ci.com/>
[Autotools Tutorial]: <https://robots.thoughtbot.com/the-magic-behind-configure-make-make-install>
[Autoconf Manual]: <https://www.gnu.org/software/autoconf/manual/autoconf.html>
[Git Message Templates]: <https://gist.github.com/adeekshith/cd4c95a064977cdc6c50>