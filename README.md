## siberia

siberia 编程语言是一门动态类型脚本语言，千万不要用，否则让你的 siberia 程序变成性能瓶颈。

语法示例：

```plain
a = 0
b = 0

if (1 + 1 == 2) {
    a = 1
} elif (1 + 1 == 3) {
    a = 2
} else {
    a = 3
}

for (i = 1; i <= 10; i = i + 1) {
    a = b = null
}


a = 1
while (a < 10) {
    a = a + 1
}

a = 1
b = 0.1
c = "abc"
d = [1, 0.1, ["a", 'bc']]

func foo(a, b) {
    c = a + b; return a + b
}

c = foo(1, 2)
print(c) # this is a comment

#=
this
is
also
a
comment
=#
```

目前连上面那段代码都跑不了哈哈