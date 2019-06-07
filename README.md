[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a47d7b3d825e441894df5c0c91ed4f42)](https://www.codacy.com/app/paddy74/OleanderStemmingLibrary?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=paddy74/OleanderStemmingLibrary&amp;utm_campaign=Badge_Grade)

# Oleander Stemming Library

![logo](stemming.png)

Library for stemming words down to their root words.

## Getting started

### Adding to your project

The recommended way to add this library to you project is by including the following to your CMakeLists.txt:

```cmake
target_link_libraries(myProject oleanderstemminglibrary)
```

You may also add this library to your project using a relative path:

```cpp
#include "oleanderstemminglibrary/include/olestem/stemming/english_stem.h"
```

### Running an example

An example of this project's usage can be found in [samples/src/example.cpp](samples/src/example.cpp) and can be built with the following commands:

```bash
mkdir build && cd build
cmake ..
cmake --build .
./bin/olestem.example
```

## License

The license for this project can be found in [LICENSE.md](LICENSE.md).

Copyright (c) for portions of source code are held by 2016 Oleander Software, Ltd.
All other copyright for source code are held by 2019 Patrick Cox.

## Ac
