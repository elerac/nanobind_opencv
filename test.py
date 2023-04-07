import numpy as np
from nanobind_opencv_example import inspect
from nanobind_opencv_example import ViewData


def main():
    print("-------- Test1 --------")
    # Prepare numpy data
    height, width = np.random.randint(10, 100, 2)
    array = np.random.rand(height, width).astype(np.float32)

    # Inspect numpy data from Python
    print("[Py]  Inspect np.ndarray")
    print("        shape: ", array.shape)
    print("        dtype: ", array.dtype)

    # Pass numpy data to C++ and inspect it as cv::Mat_<_Tp>
    inspect(array)

    print("-------- Test2 --------")
    # Class containg cv::Mat_<_Tp>
    multiview_data = []
    for i in range(5):
        value = i * 10
        img_src = np.full((height, width, 3), value, dtype=np.uint8)
        view_data = ViewData(img_src)
        multiview_data.append(view_data)

    print("[Py]  multiview_data")
    for i, view_data in enumerate(multiview_data):
        img = view_data.mat
        print(f"        view {i}: {img[0, 0, 0]}")

    print("-------- Test3 --------")
    view_data = multiview_data[0]
    print("[Py] Before setting focal length")
    print("K: \n", view_data.K)

    view_data.set_focal_length(1000)
    print("[Py] After setting focal length")
    print("K: \n", view_data.K)


if __name__ == "__main__":
    main()
