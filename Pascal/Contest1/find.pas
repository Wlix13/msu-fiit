program find;
var
    a,n,x,i:Integer;

begin
    read(n);
    read(a);
    for i:=1 to n do
    begin
        read(x);
        if x=a then
            begin
                writeln(i);
                exit()
            end;
    end;
    writeln(0)
end.