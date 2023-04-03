import numpy as np
from build import example_ext


def main():
    # Test for function
    # Prepare numpy data
    height, width = np.random.randint(10, 100, 2)
    array = np.random.rand(height, width).astype(np.float32)

    # Inspect numpy data
    print("[Py]  Inspect np.ndarray")
    print("        shape: ", array.shape)
    print("        dtype: ", array.dtype)

    # Pass numpy data to C++ and inspect it as cv::Mat_<_Tp>
    array_from_cpp = example_ext.inspect(array)
    print("[Py] np.allclose: ", np.allclose(array, array_from_cpp))

    print()

    # Test for class
    multiview_data = []
    for i in range(5):
        value = i * 10
        img_src = np.full((height, width, 3), value, dtype=np.uint8)
        view_data = example_ext.ViewData(img_src)
        multiview_data.append(view_data)

    print("[Py]  multiview_data")
    for i, view_data in enumerate(multiview_data):
        img = view_data.mat
        print(f"        view {i}: {img[0, 0, 0]}")


if __name__ == "__main__":
    main()
