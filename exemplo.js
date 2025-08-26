var x = 10;
var y = 20;

if (x > y) {
    console.log("x é maior");
} else {
    console.log("y é maior");
}

x = x * 2;
y = y + x;

while (x < 100) {
    x = x + 5;
    y = y - 3;
}


z = x ** 2 + y / 2 - 5 % 3;


if (x >= y && z != 0 || y < 50) {
    console.log("Condições complexas funcionando!");
}