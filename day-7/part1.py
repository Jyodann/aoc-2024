def evaluate(combi_num, eqn, res, char_to_append):
    base_case = 2 ** combi_num
    
    if (combi_num == 0):
        return []
    if (base_case == len(res)):
        return res
    
    res = evaluate(combi_num - 1, eqn, res, '*') + evaluate(combi_num - 1, eqn, res, '+')
    
    for i  in range(len(res)):
        tmp = res[i] + char_to_append;
        res[i] = tmp
        
    return res
        
    
        
eqns = ['*', '+']  
f = open("input.txt", "r")
total = 0
for line in f:
    data = line.strip()
    
    hello = data.split(':')
    
    target = int(hello[0])
    targets = hello[1].strip().split(' ')
    evaluations = set(evaluate(len(targets), eqns, ['*', '+'], ''))

    for e in evaluations:
        number = int(targets[0])
        next_idx = 1
        for eqn in e:
            if (eqn == '+'):
                number = number + int(targets[next_idx])
            else:
                number = number * int(targets[next_idx])
            next_idx = next_idx + 1
        if (number == target):
            print("Found " + str(target))
            total = total + target
            break

print(total)