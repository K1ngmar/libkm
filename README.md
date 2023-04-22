# 📚libkm
An amazing library containg useful high performance functions

### 📦 CONTENTS
- [IO]()
- [LibC]()
- [Additional]()
- [Containers]()

### 🧬 IO: 
**printf family**
- dprintf
- printf
- sprintf
- snprintf

**Get delim**
- getdelim
- getline

### 📖 LibC:
> todo

### ➕ Additional:
> todo

### 🫙 Containers:
**Vector**  
Like in c++ this vector is templated, only you have to register the types yourself using macros
> here is a quick example on how to create a vector of type int
```c++
#include "libkm/containers/vector.h"

// put this in the .h 
REGISTER_KM_VECTOR_PROTOTYPES(int, integer)

// put this in the .c
REGISTER_KM_VECTOR_SOURCE(int, integer)

//after registering the vector you can initialise it like this:
km_vector_integer_initialise(&vec, NULL, NULL);

// and destroy it like this
km_vector_integer_destroy(&vec);
```