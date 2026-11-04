import json
b=json.load(open('base-ro/results.json')); n=json.load(open('new-ro/results.json')); w=json.load(open('new-rw/results.json'))
print('ro regressions vs upstream:', [k for k in b if b[k][0]=='pass' and n[k][0]!='pass'])
print('ro fixed vs upstream:', [k for k in b if b[k][0]!='pass' and n[k][0]=='pass'])
print('ro still failing:', [(k,n[k][0]) for k in sorted(n) if n[k][0] not in ('pass','skip')])
print('rw failing where ro passes:', [(k,w[k][0]) for k in sorted(w) if w[k][0]!='pass' and n[k][0]=='pass'])
