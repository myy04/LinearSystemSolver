from random import randint

import numpy as np
import bindings
import random

def generate_random_matrix(rows, cols):
    """Generate a random matrix of given dimensions."""
    return np.random.rand(rows, cols)

def generate_random_vector(size):
    """Generate a random vector of given size."""
    return np.random.rand(size)

def get_numpy_solution(A, b):
    """Solve the linear system Ax = b."""
    return np.linalg.solve(A, b)

def get_my_solution(A, b):
    return bindings.gaussian_solve(A, b)


if __name__ == "__main__":
    # Test the bindings with random matrices and vectors
    for num_tests in range(100):
        rows = random.randint(100, 200)
        cols = rows # For a square matrix
        A = generate_random_matrix(rows, cols)
        b = generate_random_vector(rows)

        numpy_solution = get_numpy_solution(A, b)
        my_solution = get_my_solution(A, b)

        print("Matrix A:")
        print(A)
        print("\nVector b:")
        print(b)
        print("\nNumpy Solution:")
        print(numpy_solution)
        print("\nMy Solution:")
        print(my_solution)

        # Check if the solutions are close enough
        assert np.allclose(numpy_solution, my_solution), "The solutions do not match!"

    print("All tests passed successfully!")