import os
from typing import Tuple

# 检查一个文件是否是 matrix 数据
def check_one_file(filepath:str) -> bool:
    matrix = []
    for line in open(filepath, "r"):
        if line.strip() != "":
            matrix.append(line.split())
    # 不允许空矩阵
    if len(matrix) == 0:
        return False
    # 所有行必须元素数量相同
    for i in range(1, len(matrix)):
        if len(matrix[i]) != len(matrix[0]):
            return False
    return True

# 递归获取一个文件夹中的所有文件
def get_all_file(dirnow:str) -> list[str]:
    assert os.path.isdir(dirnow)
    dirnow = os.path.abspath(dirnow)
    arr = []
    for filename in os.listdir(dirnow):
        filepath = os.path.join(dirnow, filename)
        if os.path.isfile(filepath):
            arr.append(filepath)
        elif os.path.isdir(filepath):
            arr += get_all_file(filepath)
    return arr

# 递归获取文件夹中的所有 txt 文件
def get_all_txt_file(dirnow:str) -> list[str]:
    return [
        filepath for filepath in get_all_file(dirnow)
        if filepath.lower().endswith(".txt")]

# 检查所有 txt 文件，是否是矩阵
def check_all_file(dirnow:str) -> Tuple[list[str], list[str]]:
    err = []
    suc = []
    for filepath in get_all_txt_file(dirnow):
        if not check_one_file(filepath):
            err.append(filepath)
        else:
            suc.append(filepath)
    return err, suc

if __name__ == "__main__":
    DIRNOW = os.path.dirname(os.path.abspath(__file__))
    err_files, suc_files = check_all_file(DIRNOW)

    if len(err_files) == 0:
        print(f"\033[1;32m{len(suc_files)}\033[0m file(s) checked, OK")

    else:
        print(f"\033[1;31m{len(err_files)}\033[0m file(s) is not matrix")
        for filepath in err_files:
            print(f" - {filepath}")
