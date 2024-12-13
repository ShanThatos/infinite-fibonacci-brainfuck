import subprocess

from pathlib import Path

from c2bf.bf.bfc import main as bfc_main
from c2bf.bf.code.common import bf_b, bf_f, bf_glide_b, bf_glide_f
from c2bf.bf.code.main import BFCode
from c2bf.compile.mem.units import USIZE, memrange, unit
from c2bf.compile.mem.workspaces.unit import UNIT, nextunit, prevunit


def infinite_fib():
    code = bf_f(USIZE * 3)
    code += UNIT.set(unit.n0, [0])
    code += UNIT.set(unit.n1, [1])

    code += UNIT.set(prevunit.marker, [255])
    code += UNIT.set(memrange([USIZE * 2], unit=unit), [254])

    code += UNIT.loop(prevunit.marker, fib_pass())

    return code


def fib_pass():
    code = output_n1()

    code += (glide_add := BFCode())

    glide_add += "++[--" + (add_unit := BFCode()) + bf_f(USIZE) + "++]--"

    # add n0+n1 and possible leftover carry
    add_unit += UNIT.copy(unit.n0, unit.empty[1], unit.empty[0])
    add_unit += UNIT.copy(unit.n1, unit.empty[2], unit.empty[0])
    add_unit += UNIT.foreach(unit.empty[2], inc_result := BFCode())
    inc_result += UNIT.inc_num(unit.empty[:2], nextunit.empty[0], nextunit.empty[1])
    add_unit += UNIT.if_(prevunit.empty[0], inc_result) # carry

    # update n0 and n1
    add_unit += UNIT.move(unit.n1, unit.n0)
    add_unit += UNIT.move(unit.empty[1], unit.n1)
    
    # move 254 marker forward if it's too close
    glide_add += UNIT.copy(prevunit.n1, unit.empty[0], unit.empty[1])
    glide_add += UNIT.if_(unit.empty[0], move_marker := BFCode())
    move_marker += UNIT.clear(unit.marker) + UNIT.set(nextunit.marker, [254])

    code += bf_glide_b(255, USIZE) + bf_f(USIZE)

    return code


def output_n1():

    # 53316291173
    code = BFCode()

    qc = unit.empty[4] # quotient cell
    rc = unit.empty[5] # remainder cell

    # clear digit stack
    code += bf_glide_f(254, USIZE) + ">[-]<" + bf_glide_b(255, USIZE) + bf_f(USIZE)

    # copy n1 to rc for every unit
    code += glide_each_unit(UNIT.copy(unit.n1, rc, unit.empty[0]))

    keep_digitizing = prevunit.empty[0]
    keep_dividing = prevunit.empty[1]
    code += UNIT.set(keep_digitizing, [1])
    code += UNIT.loop(keep_digitizing, digitize_code := BFCode())


    digitize_code += UNIT.set(keep_dividing, [1])
    digitize_code += UNIT.loop(keep_dividing, div_code := BFCode())

    # DIVISION CODE

    # divide each remainder by 10
    div_code += glide_each_unit(div10_unit := BFCode())

    # split rc to qc & rc
    inc_qc_clear_rc = UNIT.bt(unit.empty[1], inc_inf_num(qc, prevunit.empty[2], prevunit.empty[3], 253) + UNIT.clear(rc) + UNIT.set(unit.empty[3], [1]))
    inc_rc = UNIT.bt(unit.empty[1], UNIT.inc(rc))

    div10 = inc_rc + inc_qc_clear_rc + "<"
    for _ in range(9):
        div10 = "[-" + inc_rc + div10 + "]"
    div10 = UNIT.tb(unit.empty[1], "[-" + inc_rc + div10 + ">]>[-<]<")
    div10 = UNIT.set(unit.marker, [253]) + UNIT.set(unit.empty[:4], [0, 0, 0, 1]) + UNIT.move(rc, unit.empty[1]) + div10
    div10 += UNIT.clear(unit.marker) + UNIT.clear(unit.empty[:4])
    
    div10_unit += UNIT.copy(rc, unit.empty[0], unit.empty[1])
    div10_unit += UNIT.if_(unit.empty[0], div10)

    # split each rc to previous unit
    # rc -> 25 * qc[-1], 6 * rc[-1]
    pqc = memrange([qc.index - USIZE], unit=unit)
    prc = memrange([rc.index - USIZE], unit=unit)
    div_code += bf_f(USIZE) + glide_each_unit(split_rc := BFCode())
    split_rc += UNIT.set(unit.marker, [253])
    split_rc += UNIT.foreach(rc, (inc_pqc_prc := BFCode()))
    inc_pqc_prc += UNIT.set(unit.empty[2], [25])
    inc_pqc_prc += UNIT.foreach(unit.empty[2], inc_inf_num(pqc, prevunit.empty[0], prevunit.empty[1], 253))
    inc_pqc_prc += UNIT.set(unit.empty[2], [6])
    inc_pqc_prc += UNIT.foreach(unit.empty[2], inc_inf_num(prc, prevunit.empty[0], prevunit.empty[1], 253))
    split_rc += UNIT.clear(unit.marker)


    # check all remainder values to see if it's < 10 yet
    div_code += UNIT.clear(prevunit.empty[3])
    div_code += UNIT.set(unit.empty[0], [10])
    div_code += UNIT.copy(rc, unit.empty[1], unit.empty[2])
    div_code += UNIT.foreach(unit.empty[0], (check_zero := BFCode()) + UNIT.dec(unit.empty[1]))
    check_zero += UNIT.copy(unit.empty[1], unit.empty[2], unit.empty[3])
    check_zero += UNIT.not_(unit.empty[2], unit.empty[3])
    check_zero += UNIT.if_(unit.empty[2], UNIT.inc(prevunit.empty[3]))
    div_code += UNIT.clear(unit.empty[1])

    # if prevunit.empty[3] then the first rc < 10
    # and now need to check other rcs
    div_code += UNIT.if_(prevunit.empty[3], check_all_rcs := BFCode())
    check_all_rcs += UNIT.set(prevunit.empty[3], [1])
    check_all_rcs += bf_f(USIZE) + glide_each_unit(check_rc := BFCode())
    check_rc += UNIT.copy(rc, unit.empty[0], unit.empty[1])
    check_rc += UNIT.if_(unit.empty[0], clear_flag := BFCode())
    clear_flag += bf_glide_b(255, USIZE) + bf_f(USIZE)
    clear_flag += UNIT.clear(prevunit.empty[3])
    # glide to unit right before 254 to end it quick
    clear_flag += bf_glide_f(254, USIZE) + bf_b(USIZE)

    # if prevunit.empty[3] then stop dividing
    check_all_rcs += UNIT.if_(prevunit.empty[3], UNIT.clear(keep_dividing))


    # DIGITIZING CODE

    # move remainder to digit stack
    digitize_code += bf_glide_f(254, USIZE) + "[>]>[-]<" + "+" * 48 + bf_glide_b(254, 1) + bf_glide_b(255, USIZE) + bf_f(USIZE)
    digitize_code += UNIT.foreach(rc, move_code := BFCode())
    move_code += bf_glide_f(254, USIZE) + "[>]<+" + bf_glide_b(254, 1) + bf_glide_b(255, USIZE) + bf_f(USIZE)

    # check if all qcs are zero
    digitize_code += UNIT.set(prevunit.empty[3], [1])
    digitize_code += glide_each_unit(check_qc := BFCode())
    check_qc += UNIT.copy(qc, unit.empty[0], unit.empty[1])
    check_qc += UNIT.if_(unit.empty[0], clear_flag := BFCode())
    clear_flag += bf_glide_b(255, USIZE) + bf_f(USIZE)
    clear_flag += UNIT.clear(prevunit.empty[3])
    # glide to unit right before 254 to end it quick
    clear_flag += bf_glide_f(254, USIZE) + bf_b(USIZE)

    # if prevunit.empty[3] then stop digitizing
    digitize_code += UNIT.set(prevunit.empty[2], [1])
    digitize_code += UNIT.if_(prevunit.empty[3], stop_digitizing_code := BFCode())
    digitize_code += UNIT.if_(prevunit.empty[2], keep_digitizing_code := BFCode())

    # clear flag and print out all digits
    stop_digitizing_code += UNIT.clear(keep_digitizing) + UNIT.clear(prevunit.empty[2])
    stop_digitizing_code += bf_glide_f(254, USIZE) + "[>]<++[--.[-]<++]--" + bf_glide_b(255, USIZE) + bf_f(USIZE)

    # move qcs to rcs
    keep_digitizing_code += glide_each_unit(UNIT.move(qc, rc))

    code += UNIT.tb(unit.empty[0], "+" * 10 + ".[-]")
    return code


def inc_inf_num(mr: memrange, t1: memrange, t2: memrange, glide_back_target: int):
    code = UNIT.set(t1, [1])
    code += UNIT.loop(t1, inc_move := BFCode())
    inc_move += UNIT.inc(mr) + UNIT.copy(mr, t2, t1)
    inc_move += UNIT.not_(t2, t1)
    inc_move += UNIT.if_(t2, UNIT.set(memrange([t1.index + USIZE], unit=t1.unit), [1]))
    inc_move += bf_f(USIZE)
    return code + bf_glide_b(glide_back_target, USIZE)


def glide_each_unit(code: BFCode):
    return "++[--" + code + bf_f(USIZE) + "++]--" + bf_glide_b(255, USIZE) + bf_f(USIZE)


def main():
    build_path = Path("./build/")
    build_path.mkdir(parents=True, exist_ok=True)

    code = infinite_fib()
    bf_code_path = build_path.joinpath("code.bf")
    bf_code_path.write_text(code.to_bf())

    bfc_main([str(bf_code_path), str(build_path.joinpath("code.c"))])
    subprocess.run(["gcc", str(build_path.joinpath("code.c")), "-o", str(build_path.joinpath("code"))])
    subprocess.run([str(build_path.joinpath("code"))])


if __name__ == "__main__":
    main()
