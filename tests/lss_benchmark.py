import time
import numpy as np
import LinearSystemSolver as LSS

def run_benchmark():
    # Array of matrix sizes (N x N) to benchmark
    sizes = [10, 50, 100, 250, 500, 1000, 10000, 20000]

    print(f"{'Size (N)':<10} | {'LSS Time (ms)':<15} | {'NumPy Time (ms)':<15} | {'Max Diff':<15}")
    print("-" * 65)

    for n in sizes:
        # Generate a random N x N matrix
        # Adding N to the diagonal ensures it's diagonally dominant and non-singular
        A = np.random.rand(n, n) + np.eye(n) * n
        b = np.random.rand(n)

        # Benchmark LSS Gaussian Solver
        start_time = time.perf_counter()
        x_lss = LSS.gaussian_solve(A, b)
        lss_time = (time.perf_counter() - start_time) * 1000.0

        # Benchmark NumPy Solver (for baseline comparison)
        start_time = time.perf_counter()
        x_np = np.linalg.solve(A, b)
        np_time = (time.perf_counter() - start_time) * 1000.0

        # Calculate maximum absolute difference between LSS and NumPy answers
        max_diff = np.max(np.abs(x_lss - x_np))

        print(f"{n:<10} | {lss_time:<15.6f} | {np_time:<15.6f} | {max_diff:<15.2e}")

if __name__ == "__main__":
    run_benchmark()