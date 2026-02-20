import os
from tqdm import tqdm
import subprocess

DIRNOW = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(DIRNOW, "..", "src")
DIAGRAM_0 = os.path.join(DIRNOW, "diagram_0")
RESULT = os.path.join(DIRNOW, "result")

# 生成一个文件的覆盖性报告
def create_one_result(filepath, aimpath) -> int:
    with open(aimpath, 'w', encoding="utf-8") as fpout:
        ret = subprocess.run(args=[os.path.join(SRC, "..", "bin", "a.exe"), filepath], stdout=fpout)

    with open(aimpath, "r", encoding="utf-8") as fpin:
        content = fpin.read()

    # 如果能够成功覆盖，不需要调整，返回 1
    # 否则返回 0
    return int(content.upper().startswith("AC"))

# 计算扭结交叉点个数
def knot_crossing(knotname:str):
    return int(knotname.lower().split("l")[-1].split("a")[0].split("n")[0])

def knot_type(knotname:str):
    return "a" if knotname.lower().find("a") != -1 else "n"

def knot_id(knotname:str):
    return int(knotname.split("a")[-1].split("n")[-1])

def create_all_result() -> None:
    total = 0
    ac = 0
    total_10 = 0
    ac_10 = 0
    files = list(os.listdir(DIAGRAM_0))
    
    # 记录所有存在内陆联通分支的扭结
    bad_knots = []

    for idx in tqdm(range(len(files))):
        filename = files[idx]
        knotname = os.path.basename(filename)[:-4]
        filepath = os.path.join(DIAGRAM_0, filename)
        aimpath = os.path.join(RESULT, filename)

        total += 1
        ac += (ac_now := create_one_result(filepath, aimpath))

        if knot_crossing(knotname) <= 10:
            total_10 += 1
            ac_10 += ac_now

        if not ac_now:
            bad_knots.append(knotname)

    # 按照交叉点个数对这些数据排序
    bad_knots.sort(key=lambda kname: (knot_crossing(kname), knot_type(kname), knot_id(kname)))

    print(f"ac/total: {ac}/{total}")
    print(f"ac_10/total_10: {ac_10}/{total_10}")

    with open(os.path.join(DIRNOW, "bad_knots.txt"), "w", encoding="utf-8") as fp:
        fp.write("\n".join(bad_knots))

if __name__ == "__main__":
    # 保证文件夹存在
    os.makedirs(RESULT, exist_ok=True)

    create_all_result()
