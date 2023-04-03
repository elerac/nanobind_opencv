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

    cv::Matx34f get_camera_matrix() const
    {
        // Copy rotation matrix and translation vector to extrinsic matrix
        cv::Matx44f extrinsic = cv::Matx44f::eye();
        extrinsic(0, 0) = R(0, 0);
        extrinsic(0, 1) = R(0, 1);
        extrinsic(0, 2) = R(0, 2);
        extrinsic(1, 0) = R(1, 0);
        extrinsic(1, 1) = R(1, 1);
        extrinsic(1, 2) = R(1, 2);
        extrinsic(2, 0) = R(2, 0);
        extrinsic(2, 1) = R(2, 1);
        extrinsic(2, 2) = R(2, 2);
        extrinsic(0, 3) = t(0);
        extrinsic(1, 3) = t(1);
        extrinsic(2, 3) = t(2);

        // Copy intrinsic matrix
        cv::Matx33f intrinsic = K;

        // Dot product of intrinsic and extrinsic
        cv::Matx34f camera_matrix = cv::Matx34f::zeros();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    camera_matrix(i, j) += intrinsic(i, k) * extrinsic(k, j);
                }
            }
        }

        return camera_matrix;
    }
};

template <typename _Tp>
cv::Mat_<_Tp> inspect(const cv::Mat_<_Tp> mat)
{
    std::cout << "[C++] Inspect cv::Mat_<_Tp>" << std::endl;
    std::cout << "        rows: " << mat.rows << std::endl;
    std::cout << "        cols: " << mat.cols << std::endl;
    std::cout << "        channels: " << mat.channels() << std::endl;
    std::cout << "        type: " << cv::typeToString(mat.type()) << std::endl;
    return mat;
}

NB_MODULE(example_ext, m)
{
    m.def("inspect", &inspect<cv::Vec3b>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<cv::Vec3f>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<uint8_t>, nb::arg("mat").noconvert());
    m.def("inspect", &inspect<float>, nb::arg("mat").noconvert());

    nb::class_<ViewData>(m, "ViewData")
        .def(nb::init<const cv::Mat3b &, const cv::Matx33f &, const cv::Matx33f &, const cv::Vec3f &>(), "mat"_a.noconvert(), "K"_a, "R"_a, "t"_a)
        .def(nb::init<const cv::Mat3b &>(), "mat"_a)
        .def_rw("mat", &ViewData::mat)
        .def_rw("K", &ViewData::K)
        .def_rw("R", &ViewData::R)
        .def_rw("t", &ViewData::t)
        .def("get_camera_matrix", &ViewData::get_camera_matrix);
}
