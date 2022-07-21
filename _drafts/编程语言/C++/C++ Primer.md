


## 关于输入运算符>>  
左侧运算对象是一个istream对象，右侧是一个其他对象，返回值是左侧运算对象，所以输入a之后，返回std::in这个istream对象，又可以接着输入b。
当std::in作为判断条件时,如果输入流有效则真，如遇到错误（如输入值与需要类型不一致）或遇到文件结束符（end-of-file  EOF)时，返回false，所以可以用std::in来作为循环条件，直到输入文件结束符（windows上是Ctrl+Z，Unix上是Ctrl+D)。
```
int a,b;
std::in>>a>>b;

while(std::in>>a){
    std::cout>>a>>std::endl;
}
```