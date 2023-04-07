#include <iostream>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>
#include "cv_typecaster.h"

namespace nb = nanobind;
using namespace nb::literals;

class ViewData
{
public:
    cv::Mat3b mat;
    cv::Matx33f K; // intrinsic matrix
    cv::Matx33f R; // rotation matrix
    cv::Vec3f t;   // translation vector

    ViewData(const cv::Mat3b &mat, const cv::Matx33f &K, const cv::Matx33f &R, const cv::Vec3f &t) : mat(mat), K(K), R(R), t(t) {}
    ViewData(const cv::Mat3b &mat) : mat(mat), K(cv::Matx33f::eye()), R(cv::Matx33f::eye()), t(cv::Vec3f::all(0)) {}

    void set_focal_length(float focal_length)
    {
        K(0, 0) = focal_length;
        K(1, 1) = focal_length;
    }
};

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
    m.def("inspect", &inspect<cv::Vec3b>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<cv::Vec3f>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<uint8_t>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<float>, nb::arg("mat").noconvert());

    nb::class_<ViewData>(m, "ViewData")
        .def(nb::init<const cv::Mat3b &, const cv::Matx33f &, const cv::Matx33f &, const cv::Vec3f &>(), "mat"_a.noconvert(), "K"_a, "R"_a, "t"_a)
        .def(nb::init<const cv::Mat3b &>(), "mat"_a)
        .def("set_focal_length", &ViewData::set_focal_length, "focal_length"_a)
        .def_rw("mat", &ViewData::mat)
        .def_rw("K", &ViewData::K)
        .def_rw("R", &ViewData::R)
        .def_rw("t", &ViewData::t);
}
