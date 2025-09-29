function juros_composto(P, i, n) 
{ 
	let M;
	M = P *( 1 + i/100 ) ** n; 
	return M; 
} 
let res;

res = juros_composto(2000, 1.5, 10);


