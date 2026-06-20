import numpy as np
import pytest

import LinearSystemSolver as LSS

SIZES = [10, 50, 100, 250, 500, 1000]


def _make_system(n: int):
    """Diagonally-dominant N×N system (fixed seed → reproducible)."""
    rng = np.random.default_rng(42)
    A = rng.random((n, n)) + np.eye(n) * n
    b = rng.random(n)
    return A, b


@pytest.mark.parametrize("n", SIZES, ids=[f"n={n}" for n in SIZES])
def test_lss_solver(benchmark, n):
    A, b = _make_system(n)
    result = benchmark(LSS.gaussian_solve, A, b)
    np.testing.assert_allclose(result, np.linalg.solve(A, b), rtol=1e-8)


@pytest.mark.parametrize("n", SIZES, ids=[f"n={n}" for n in SIZES])
def test_numpy_solver(benchmark, n):
    A, b = _make_system(n)
    benchmark(np.linalg.solve, A, b)