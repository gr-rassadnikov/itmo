s1=input()
s2=input()
s3=input()
abc=["<<<", "<<=", "=<<","==="]
acb=["<<>", "<<=","<=<","==="]
bac=["><<",">=<","=<<","==="]
bca=[">>=",">><", ">=<","==="]
cab=["<>>","<=>","=>>","==="]
cba=[">>>",">>=","=>>","==="]
f=s1+s2+s3
if f in abc:
    print("abc")
if f in acb:
    print("acb")
if f in bac:
    print("bac")
if f in bca:
    print("bca")
if f in cab:
    print("cab")
if f in cba:
    print("cba")
