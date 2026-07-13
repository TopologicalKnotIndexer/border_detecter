from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]


class BorderDetectorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++") or r"C:\ProgramData\mingw64\mingw64\bin\g++.exe"
        if not Path(compiler).is_file():
            raise unittest.SkipTest("g++ is unavailable")
        cls.temporary = tempfile.TemporaryDirectory()
        cls.executable = Path(cls.temporary.name) / "border_detector.exe"
        result = subprocess.run(
            [compiler, "-std=c++17", "-O2", str(ROOT / "src" / "main.cpp"), "-o", str(cls.executable)],
            text=True,
            capture_output=True,
            timeout=120,
            check=False,
        )
        if result.returncode != 0:
            raise AssertionError(result.stderr)

    @classmethod
    def tearDownClass(cls):
        cls.temporary.cleanup()

    def run_matrix(self, content: str):
        path = Path(self.temporary.name) / "matrix.txt"
        path.write_text(content, encoding="utf-8")
        return subprocess.run(
            [str(self.executable), str(path)],
            text=True,
            capture_output=True,
            timeout=10,
            check=False,
        )

    def test_exposed_crossing_is_accepted(self):
        result = self.run_matrix("0 1 0\n2 -1 2\n0 1 0\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.strip(), "AC")

    def test_ragged_and_non_integer_matrices_fail_cleanly(self):
        ragged = self.run_matrix("0 1 0\n2 -1\n0 1 0\n")
        self.assertNotEqual(ragged.returncode, 0)
        self.assertIn("different lengths", ragged.stderr)
        invalid = self.run_matrix("0 1 0\n2 nope 2\n0 1 0\n")
        self.assertNotEqual(invalid.returncode, 0)
        self.assertIn("non-integer", invalid.stderr)

    def test_missing_file_and_missing_argument_are_failures(self):
        no_argument = subprocess.run(
            [str(self.executable)], text=True, capture_output=True, check=False
        )
        self.assertEqual(no_argument.returncode, 2)
        missing = subprocess.run(
            [str(self.executable), str(Path(self.temporary.name) / "missing.txt")],
            text=True,
            capture_output=True,
            check=False,
        )
        self.assertNotEqual(missing.returncode, 0)


if __name__ == "__main__":
    unittest.main()
