[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a47d7b3d825e441894df5c0c91ed4f42)](https://www.codacy.com/app/paddy74/PStem?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=paddy74/PStem&amp;utm_campaign=Badge_Grade)

# Oleander Stemming Library

Library for stemming words down to their root words using Porter Stemming.

## Getting started

### Adding to your project

The recommended way to add this library to you project is by including the following to your CMakeLists.txt:

```cmake
target_link_libraries(myProject pstem)
```

You may also add this library to your project using a relative path:

```cpp
#include "pstem/include/pstem/stemming/english_stem.h"
```

### Running an example

An example of this project's usage can be found in [samples/src/example.cpp](samples/src/example.cpp). You can build and run it with the following commands:

```bash
mkdir build && cd build
cmake ..
cmake --build .
./bin/pstem.example
```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](tags).

## Authors

- **Patrick Cox** - [paddy74](https://github.com/paddy74)
- **OleanderSoftware** - [OleanderSoftware](https://github.com/OleanderSoftware)


## License

The license for this project can be found in [LICENSE.md](LICENSE.md).

Copyright (c) for portions of source code are held by 2016 Oleander Software, Ltd.
All other copyright for source code are held by 2019 Patrick Cox.

## Acknowledgements

- **[OleanderSoftware](https://github.com/OleanderSoftware) - The creator of the project's [parent repository](https://github.com/OleanderSoftware/PStem).
