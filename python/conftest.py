import os
import subprocess
import sys

# Make the compiled .so importable when pytest is invoked from the project root
sys.path.insert(0, os.path.dirname(__file__))

def _git_commit() -> str:
    try:
        return subprocess.check_output(
            ["git", "rev-parse", "--short", "HEAD"],
            stderr=subprocess.DEVNULL,
        ).decode().strip()
    except Exception:
        return "unknown"


def pytest_configure(config):
    """Tag benchmark saves with the current git commit hash."""
    try:
        if not config.option.benchmark_save:
            config.option.benchmark_save = _git_commit()
    except AttributeError:
        pass