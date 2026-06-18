//
// Created by Yerdaulet Mussabek on 18.06.2026.
//

#include "../include/Matrix.h"
#include "../include/Vector.h"
#include "../include/GaussianSolver.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

py::array_t<double> GaussianSolver_wrapper(const py::array_t<double>& A, const py::array_t<double>& b) {
    auto a = py::array_t<double, py::array::c_style | py::array::forcecast>(A);
    auto b_vec = py::array_t<double, py::array::c_style | py::array::forcecast>(b);

    py::buffer_info a_buf = a.request();
    py::buffer_info b_buf = b_vec.request();

    if (a_buf.ndim != 2 || b_buf.ndim != 1) {
        throw std::runtime_error("Input arrays must be 2D and 1D respectively");
    }

    const double *a_ptr = static_cast<double *>(a_buf.ptr);
    const double *b_ptr = static_cast<double *>(b_buf.ptr);

    size_t n = a_buf.shape[0];
    size_t m = a_buf.shape[1];

    Matrix<double> A_mat_cpp(n, m, 0);
    Vector<double> b_vec_cpp(n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            A_mat_cpp[i, j] = a_ptr[(i - 1) * m + (j - 1)];
        }

        b_vec_cpp[i] = b_ptr[i - 1];
    }

    Vector<double> x = GaussianSolver<double>().solve(A_mat_cpp, b_vec_cpp);

    // Allocate space for the numpy array to be sent back to Python
    py::array_t<double> result(x.size());
    py::buffer_info res_buf = result.request();
    double *res_ptr = static_cast<double *>(res_buf.ptr);

    // Copy from 1-based indexing C++ Vector to 0-based numpy buffer
    for (size_t i = 1; i <= x.size(); i++) {
        res_ptr[i - 1] = x[i];
    }

    return result;
}

PYBIND11_MODULE(bindings, m) {
    m.doc() = "Python bindings for the C++ library";

    // Bind the wrapper function that python tests are trying to use
    m.def("gaussian_solve", &GaussianSolver_wrapper, "Solve linear system Ax = b");

    py::class_<GaussianSolver<double>>(m, "GaussianSolver")
        .def(py::init<>())
        .def("solve", &GaussianSolver<double>::solve);
}
