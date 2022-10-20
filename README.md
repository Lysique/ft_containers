# ft_containers

This project's purpose is to get a better understanding of c++'s containers by reproducing their behavior (vector, set, map and stack).  
  
Other std's functionnalities were also implemented as they were needed in the implementation of the containers (enable_if, iterator_traits, pair, equal, lexicographical_compare, reverse_iterator and is_integral).  
  
The containers are compiling with -std=c++98 but -std=c++11 was used in the makefile for the main tests.

## launch

Use 'make' to compile the main. It will create 2 executables:
- One using ft namespace, thus using the containers implemented in the files.
- One using std namespace, thus using the std containers.
