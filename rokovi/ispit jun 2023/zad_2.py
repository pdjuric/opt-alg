BUDGET = 3e3

projects = [
    [237, 9, 4.3],
    [251, 4, 7.1],
    [249, 6, 6.3],
    [252, 6, 4.1],
    [276, 8, 5.3],
    [268, 7, 4.5],
    [220, 10, 3.7],
    [270, 5, 6.2],
    [275, 7, 4.6],
    [469, 12, 8.9],
    [368, 10, 6.2],
    [479, 17, 5.7],
    [101, 4, 2.7],
    [280, 5, 7.1],
    [271, 10, 1.9],
    [338, 8, 4.8],
    [307, 3, 9.1],
    [348, 13, 3.0],
    [225, 6, 5.7],
    [280, 8, 4.9]
]

sols = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
]


def get_costs(x) -> (bool, float, float):
    cost1 = 0  # profit
    cost2 = 0  # new employees
    amount_invested = 0
    for project, included in zip(projects, x):
        if included:
            amount_invested += project[0]
            cost1 += project[0] * project[2] / 100
            cost2 += project[1]

    return amount_invested <= BUDGET, cost1 * 1e3, cost2


pareto_front = []  # [[solution_idx, (profit, employees)]]
all = []           # [[solution_idx, (profit, employees)]]

def check_pareto_optimality(sol_idx, costs):
    for_removal = []
    is_pareto_optimal = True
    for idx, sol in enumerate(pareto_front):
        if sol[1][0] > costs[0] and sol[1][1] > costs[1]:
            is_pareto_optimal = False
        elif sol[1][0] < costs[0] and sol[1][1] < costs[1]:
            for_removal.append(idx)

    if len(for_removal) > 0:
        for_removal.reverse()
        for idx in for_removal:
            pareto_front.pop(idx)

    if is_pareto_optimal:
        pareto_front.append([sol_idx, costs])


for idx, s in enumerate(sols):
    is_possible, profit, employees = get_costs(s)

    if is_possible:
        all.append([idx, (profit, employees)])
        check_pareto_optimality(idx, (profit, employees))

    print(f"Solution {idx + 1}: ", end='')
    if not is_possible:
        print("not possible")
    else:
        print(f"profit - {profit}, employees - {employees}")


import matplotlib.pyplot as plt

plt.figure()
plt.xlabel('profit')
plt.ylabel('employees')

x = [t[1][0] for t in all]
y = [t[1][1] for t in all]
plt.plot(x, y, color='blue', linestyle="", marker=".", markersize=.7)

x = [t[1][0] for t in pareto_front]
y = [t[1][1] for t in pareto_front]

plt.plot(x, y, color='red', linestyle="", mfc='none', marker="o")
plt.xlim(1e5, 3e5)
plt.ylim(50, 100)
plt.savefig('zad_2.png', dpi=300)
