# nanobind - opencv typecaster

This repository provides a [nanobind](https://github.com/wjakob/nanobind) typecaster for opencv types.

The supported types are:

- `cv::Mat_<_Tp>`
- `cv::Matx<_Tp, m, n>`
- `cv::Vec<_Tp, n>`

## Build

```bash
pip3 install .
```

## Example

In C++:

```cpp
#include <iostream>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>
#include "cv_typecaster.h"

namespace nb = nanobind;
using namespace nb::literals;

template <typename _Tp>
void inspect(const cv::Mat_<_Tp> mat)
{
    std::cout << "[C++] Inspect cv::Mat_<_Tp>" << std::endl;
    std::cout << "        rows: " << mat.rows << std::endl;
    std::cout << "        cols: " << mat.cols << std::endl;
    std::cout << "        channels: " << mat.channels() << std::endl;
    std::cout << "        type: " << cv::typeToString(mat.type()) << std::endl;
}

NB_MODULE(_nanobind_opencv_example_impl, m)
{
    m.def("inspect", &inspect<float>, nb::arg("mat").noconvert());
}
```

In Python:

```python
import numpy as np
from nanobind_opencv_example import inspect

# Prepare numpy data
array = np.random.rand(128, 256).astype(np.float32)

# Inspect numpy data in Python
print("[Py]  Inspect np.ndarray")
print("        shape: ", array.shape)
print("        dtype: ", array.dtype)

# Pass numpy data to C++ and inspect it as cv::Mat_<_Tp>
inspect(array)
```

After running the above example, the output should be:

```
$ python3 test.py
[Py]  Inspect np.ndarray
        shape:  (128, 256)
        dtype:  float32
[C++] Inspect cv::Mat_<_Tp>
        rows: 128
        cols: 256
        channels: 1
        type: CV_32FC1
```
